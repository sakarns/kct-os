#include <stdio.h>

#define N 10
#define M 4

int referenceString[N] = {1, 2, 3, 4, 1, 2, 5, 1, 2, 3};
int frames[M] = {-1, -1, -1, -1};
int queue1[M] = {-1, -1, -1, -1};
int queue2[M] = {-1, -1, -1, -1};
int queue1Front = 0, queue1Rear = -1;
int queue2Front = 0, queue2Rear = -1;

int pageFaults = 0;

bool isInFrames(int page)
{
    int i;
    for (i = 0; i < M; i++)
    {
        if (frames[i] == page)
        {
            return true;
        }
    }
    return false;
}

bool isInQueue(int page, int *queue)
{
    int i;
    for (i = 0; i < M; i++)
    {
        if (queue[i] == page)
        {
            return true;
        }
    }
    return false;
}

int getQueue(int page)
{
    if (isInQueue(page, queue1))
    {
        return 1;
    }
    else if (isInQueue(page, queue2))
    {
        return 2;
    }
    else
    {
        return -1;
    }
}

int getEmptyFrame()
{
    int i;
    for (i = 0; i < M; i++)
    {
        if (frames[i] == -1)
        {
            return i;
        }
    }
    return -1;
}

void addToQueue(int page, int *queue, int *front, int *rear)
{
    if (*rear == M - 1)
    {
        printf("Queue is full\n");
        return;
    }
    (*rear)++;
    queue[*rear] = page;
}

void removeFromQueue(int page, int *queue, int *front, int *rear)
{
    if (*front > *rear)
    {
        printf("Queue is empty\n");
        return;
    }
    int i, index = -1;
    for (i = *front; i <= *rear; i++)
    {
        if (queue[i] == page)
        {
            index = i;
            break;
        }
    }
    if (index == -1)
    {
        printf("Page not found in queue\n");
        return;
    }
    for (i = index; i < *rear; i++)
    {
        queue[i] = queue[i + 1];
    }
    (*rear)--;
}

void replacePage(int page)
{
    int queueNum = getQueue(page);
    int emptyFrame = getEmptyFrame();
    if (emptyFrame != -1)
    {
        frames[emptyFrame] = page;
        if (queueNum == 1)
        {
            removeFromQueue(page, queue1, &queue1Front, &queue1Rear);
        }
        else if (queueNum == 2)
        {
            removeFromQueue(page, queue2, &queue2Front, &queue2Rear);
        }
    }
    else
    {
        int victimPage;
        if (queueNum == 1)
        {
            if (queue1Front <= queue1Rear)
            {
                victimPage = queue1[queue1Front];
                removeFromQueue(victimPage, queue1, &queue1Front, &queue1Rear);
            }
            else
            {
                victimPage = queue2[queue2Front];
                removeFromQueue(victimPage, queue2, &queue2Front, &queue2Rear);
            }
        }
        else if (queueNum == 2)
        {
            victimPage = queue2[queue2Front];
            removeFromQueue(victimPage, queue2, &queue2Front, &queue2Rear);
        }
        else
        {
            int i;
            for (i = 0; i < M; i++)
            {
                if (!isInQueue(frames[i], queue1) && !isInQueue(frames[i], queue2))
                {
                    victimPage = frames[i];
                    break;
                }
            }
        }
        int victimFrame;
        for (victimFrame = 0; victimFrame < M; victimFrame++)
        {
            if (frames[victimFrame] == victimPage)
            {
                break;
            }
        }
        frames[victimFrame] = page;
        if (queueNum == 1)
        {
            removeFromQueue(page, queue1, &queue1Front, &queue1Rear);
        }
        else if (queueNum == 2)
        {
            removeFromQueue(page, queue2, &queue2Front, &queue2Rear);
        }
    }
}

void printFrames()
{
    int i;
    for (i = 0; i < M; i++)
    {
        if (frames[i] == -1)
        {
            printf("- ");
        }
        else
        {
            printf("%d ", frames[i]);
        }
    }
    printf("\n");
}

void simulateMQ()
{
    int i;
    for (i = 0; i < N; i++)
    {
        printf("%d: ", referenceString[i]);
        if (isInFrames(referenceString[i]))
        {
            printf("Hit ");
        }
        else
        {
            printf("Miss ");
            pageFaults++;
            if (i % 2 == 0)
            {
                addToQueue(referenceString[i], queue1, &queue1Front, &queue1Rear);
            }
            else
            {
                addToQueue(referenceString[i], queue2, &queue2Front, &queue2Rear);
            }
            replacePage(referenceString[i]);
        }
        printFrames();
    }
}

int main()
{
    simulateMQ();
    printf("Total page faults: %d\n", pageFaults);
    return 0;
}