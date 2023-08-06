#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#define MESSAGE_SIZE 1024int main()
{
    int msgid;
    key_t key;
    struct msgbuf
    {
        long mtype;
        char mtext[MESSAGE_SIZE];
    } message;

    /* generate a unique key for the message queue */
    key = ftok("/tmp", 'a');
    if (key == -1)
    {
        perror("ftok");
        exit(-1);
    }

    /* create the message queue */
    msgid = msgget(key, IPC_CREAT | 0666);
    if (msgid == -1)
    {
        perror("msgget");
        exit(-1);
    }

    /* send a message to the message queue */
    message.mtype = 1;
    sprintf(message.mtext, "Hello, world!");
    if (msgsnd(msgid, &message, sizeof(message.mtext), 0) == -1)
    {
        perror("msgsnd");
        exit(-1);
    }

    /* receive a message from the message queue */
    if (msgrcv(msgid, &message, sizeof(message.mtext), 0, 0) == -1)
    {
        perror("msgrcv");
        exit(-1);
    }

    printf("Message received: %s\n", message.mtext);

    /* delete the message queue */
    if (msgctl(msgid, IPC_RMID, NULL) == -1)
    {
        perror("msgctl");
        exit(-1);
    }

    return 0;
}