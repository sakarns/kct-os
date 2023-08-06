#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#define SHM_SIZE 1024 // size of shared memory segment

int main()
{
    int shmid;
    char *shmaddr;
    key_t key;

    /* generate a unique key for the shared memory segment */
    key = ftok("/tmp", 'a');
    if (key == -1)
    {
        perror("ftok");
        exit(-1);
    }

    /* create the shared memory segment */
    shmid = shmget(key, SHM_SIZE, IPC_CREAT | 0666);
    if (shmid == -1)
    {
        perror("shmget");
        exit(-1);
    }

    /* attach to the shared memory segment */
    shmaddr = shmat(shmid, NULL, 0);
    if (shmaddr == (char *)-1)
    {
        perror("shmat");
        exit(-1);
    }

    /* write a message to the shared memory segment */
    sprintf(shmaddr, "Hello, world!");

    /* detach from the shared memory segment */
    shmdt(shmaddr);

    return 0;
}