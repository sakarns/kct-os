#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define NUM_THREADS 2

void *compute(void *arg)
{
    int i, sum = 0;

    for (i = 0; i < 1000000; i++)
    {
        sum += i;
    }

    printf("Thread %d: Sum is %d\n", *(int *)arg, sum);

    pthread_exit(NULL);
}

int main()
{
    pthread_t threads[NUM_THREADS];
    int thread_ids[NUM_THREADS];
    int i;

    /* create threads */
    for (i = 0; i < NUM_THREADS; i++)
    {
        thread_ids[i] = i;
        if (pthread_create(&threads[i], NULL, compute, &thread_ids[i]) != 0)
        {
            fprintf(stderr, "Error creating thread %d.\n", i);
            exit(-1);
        }
    }

    /* wait for threads to complete */
    for (i = 0; i < NUM_THREADS; i++)
    {
        pthread_join(threads[i], NULL);
    }

    printf("All threads completed.\n");

    return 0;
}