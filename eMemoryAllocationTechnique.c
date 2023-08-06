#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MEMORY_SIZE 1024

// Structure for a memory block
struct memory_block {
    int start;
    int end;
    int size;
    bool isFree;
};

// Array of memory blocks
struct memory_block memory[MEMORY_SIZE];

// Number of memory blocks
int numBlocks = 1;

// Function to initialize the memory
void initializeMemory() {
    memory[0].start = 0;
    memory[0].end = MEMORY_SIZE - 1;
    memory[0].size = MEMORY_SIZE;
    memory[0].isFree = true;
}

// Function to allocate memory using worst fit
bool allocateWorstFit(int size, int* start, int* end) {
    int i, j, largestBlockSize = -1, largestBlockIndex = -1;
    for (i = 0; i < numBlocks; i++) {
        if (memory[i].isFree && memory[i].size >= size && memory[i].size > largestBlockSize) {
            largestBlockSize = memory[i].size;
            largestBlockIndex = i;
        }
    }
    if (largestBlockIndex == -1) {
        printf("Memory allocation failed\n");
        return false;
    }
    *start = memory[largestBlockIndex].start;
    *end = memory[largestBlockIndex].start + size - 1;
    memory[largestBlockIndex].start = *end + 1;
    memory[largestBlockIndex].size -= size;
    if (memory[largestBlockIndex].size == 0) {
        for (j = largestBlockIndex; j < numBlocks - 1; j++) {
            memory[j] = memory[j+1];
        }
        numBlocks--;
    }
    printf("Memory allocated successfully from %d to %d\n", *start, *end);
    return true;
}

// Function to allocate memory using best fit
bool allocateBestFit(int size, int* start, int* end) {
    int i, j, smallestBlockSize = MEMORY_SIZE + 1, smallestBlockIndex = -1;
    for (i = 0; i < numBlocks; i++) {
        if (memory[i].isFree && memory[i].size >= size && memory[i].size < smallestBlockSize) {
            smallestBlockSize = memory[i].size;
            smallestBlockIndex = i;
        }
    }
    if (smallestBlockIndex == -1) {
        printf("Memory allocation failed\n");
        return false;
    }
    *start = memory[smallestBlockIndex].start;
    *end = memory[smallestBlockIndex].start + size - 1;
    memory[smallestBlockIndex].start = *end + 1;
    memory[smallestBlockIndex].size -= size;
    if (memory[smallestBlockIndex].size == 0) {
        for (j = smallestBlockIndex; j < numBlocks - 1; j++) {
            memory[j] = memory[j+1];
        }
        numBlocks--;
    }
    printf("Memory allocated successfully from %d to %d\n", *start, *end);
    return true;
}

// Function to allocate memory using first fit
bool allocateFirstFit(int size, int* start, int* end) {
    int i, j, firstBlockIndex = -1;
    for (i = 0; i < numBlocks; i++) {
        if (memory[i].isFree && memory[i].size >= size) {
            firstBlockIndex = i;
            break;
        }
    }
    if (firstBlockIndex == -1) {
        printf("Memory allocation failed\n");
        return false;
    }
    *start = memory[firstBlockIndex].start;
    *end = memory[firstBlockIndex].start + size - 1;
    memory[firstBlockIndex].start = *end + 1;
    memory[firstBlockIndex].size -= size;
    if (memory[firstBlockIndex].size == 0) {
        for (j = firstBlockIndex; j < numBlocks - 1; j++) {
            memory[j] = memory[j+1];
        }
        numBlocks--;
    }
    printf("Memory allocated successfully from %d to %d\n", *start, *end);
    return true;
}

// Function to deallocate memory
void deallocate(int start, int end) {
    int i, j;
    for (i = 0; i < numBlocks; i++) {
        if (memory[i].start == end + 1) {
            memory[i].start = start;
            memory[i].size += end - start + 1;
            if (i > 0 && memory[i-1].end && memory[i-1].end == start - 1) {
                memory[i-1].end = memory[i].end;
                memory[i-1].size += memory[i].size;
                for (j = i; j < numBlocks - 1; j++) {
                    memory[j] = memory[j+1];
                }
                numBlocks--;
                i--;
            }
            return;
        } else if (memory[i].end == start - 1) {
            memory[i].end = end;
            memory[i].size += end - start + 1;
            if (i < numBlocks - 1 && memory[i+1].isFree && memory[i+1].start == end + 1) {
                memory[i].end = memory[i+1].end;
                memory[i].size += memory[i+1].size;
                for (j = i+1; j < numBlocks - 1; j++) {
                    memory[j] = memory[j+1];
                }
                numBlocks--;
            }
            return;
        }
    }
    // If the memory block to be deallocated is not adjacent to any existing memory block,
    // create a new memory block for it
    if (numBlocks == MEMORY_SIZE) {
        printf("Memory deallocation failed\n");
        return;
    }
    for (i = 0; i < numBlocks; i++) {
        if (memory[i].start > start) {
            for (j = numBlocks - 1; j >= i; j--) {
                memory[j+1] = memory[j];
            }
            memory[i].start = start;
            memory[i].end = end;
            memory[i].size = end - start + 1;
            memory[i].isFree = true;
            numBlocks++;
            printf("Memory deallocated successfully from %d to %d\n", start, end);
            return;
        }
    }
    memory[numBlocks].start = start;
    memory[numBlocks].end = end;
    memory[numBlocks].size = end - start + 1;
    memory[numBlocks].isFree = true;
    numBlocks++;
    printf("Memory deallocated successfully from %d to %d\n", start, end);
}

// Function to print the list of memory blocks
void printMemory() {
    int i;
    printf("Start\tEnd\tSize\tStatus\n");
    for (i = 0; i < numBlocks; i++) {
        printf("%d\t%d\t%d\t", memory[i].start, memory[i].end, memory[i].size);
        if (memory[i].isFree) {
            printf("Free\n");
        } else {
            printf("Occupied\n");
        }
    }
}

int main() {
    initializeMemory();
    allocateWorstFit(100, &memory[0].start, &memory[0].end);
    allocateWorstFit(200, &memory[0].start, &memory[0].end);
    allocateWorstFit(300, &memory[0].start, &memory[0].end);
    printMemory();
    deallocate(100, 199);
    printMemory();
    allocateBestFit(150, &memory[0].start, &memory[0].end);
    printMemory();
    allocateFirstFit(50, &memory[0].start, &memory[0].end);
    printMemory();
    return 0;
}