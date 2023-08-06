#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_DEVICES 10

// Structure for a device
struct device {
    int id;
    char* name;
    bool isAvailable;
};

// Array of devices
struct device devices[MAX_DEVICES];

// Number of devices
int numDevices = 0;

// Function to add a new device
void addDevice(int id, char* name) {
    if (numDevices == MAX_DEVICES) {
        printf("Maximum number of devices reached\n");
        return;
    }
    struct device newDevice;
    newDevice.id = id;
    newDevice.name = name;
    newDevice.isAvailable = true;
    devices[numDevices] = newDevice;
    numDevices++;
    printf("Device added successfully\n");
}

// Function to remove a device
void removeDevice(int id) {
    int i;
    for (i = 0; i < numDevices; i++) {
        if (devices[i].id == id) {
            devices[i].isAvailable = false;
            printf("Device removed successfully\n");
            return;
        }
    }
    printf("Device not found\n");
}

// Function to check if a device is available
bool isDeviceAvailable(int id) {
    int i;
    for (i = 0; i < numDevices; i++) {
        if (devices[i].id == id) {
            return devices[i].isAvailable;
        }
    }
    printf("Device not found\n");
    return false;
}

// Function to print the list of devices
void printDevices() {
    int i;
    printf("ID\tName\t\tStatus\n");
    for (i = 0; i < numDevices; i++) {
        printf("%d\t%s\t\t", devices[i].id, devices[i].name);
        if (devices[i].isAvailable) {
            printf("Available\n");
        } else {
            printf("Not available\n");
        }
    }
}

int main() {
    addDevice(1, "Printer");
    addDevice(2, "Scanner");
    addDevice(3, "Projector");
    printDevices();
    removeDevice(2);
    printDevices();
    printf("Is Printer available? %d\n", isDeviceAvailable(1));
    printf("Is Scanner available? %d\n", isDeviceAvailable(2));
    printf("Is Projector available? %d\n", isDeviceAvailable(3));
    return 0;
}