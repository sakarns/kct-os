#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define BUFFER_SIZE 1024

int main()
{
    int fd[2];
    pid_t pid;
    char buffer[BUFFER_SIZE];

    /* create the pipe */
    if (pipe(fd) == -1)
    {
        perror("pipe");
        exit(-1);
    }

    /* fork a child process */
    pid = fork();
    if (pid == -1)
    {
        perror("fork");
        exit(-1);
    }

    if (pid == 0)  // child process
    {
        /* close the read end of the pipe */
        close(fd[0]);

        /* write a message to the pipe */
        write(fd[1], "Hello, world!", 13);

        /* close the write end of the pipe */
        close(fd[1]);

        exit(0);
    }
    else  // parent process
    {
        /* close the write end of the pipe */
        close(fd[1]);

        /* read a message from the pipe */
        read(fd[0], buffer, BUFFER_SIZE);

        printf("Message received: %s\n", buffer);

        /* close the read end of the pipe */
        close(fd[0]);
    }

    return 0;
}