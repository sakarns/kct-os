#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <math.h>
int main()
{
    int choice, n, i, j, p[20], min, max, loc, seek = 0, cp, temp, a[20], min1, max1;
    float avg = 0;
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    printf("\nEnter the current position: ");
    scanf("%d", &cp);
    printf("\nEnter the requests of the processes:\n");
    for (i = 0; i < n; i++)
    {
        scanf("%d", &p[i]);
        a[i] = 0;
    }

    printf("\nChoose a disk scheduling algorithm:\n");
    printf("1. SSTF\n");
    printf("2. SCAN\n");
    printf("3. LOOK\n");
    printf("4. C-SCAN\n");
    printf("5. C-LOOK\n");
    printf("6. Exit\n\n");
j:
    printf("\n\nEnter your choice: ");
    scanf("%d", &choice);
    switch (choice)
    {
    case 1:
        for (i = 0; i < n; i++)
        {
            min = 9999;
            for (j = 0; j < n; j++)
            {
                if (a[j] == 0)
                {
                    if (abs(cp - p[j]) < min)
                    {
                        min = abs(cp - p[j]);
                        loc = j;
                    }
                }
            }
            a[loc] = 1;
            temp = cp - p[loc];
            seek += abs(temp);
            cp = p[loc];
        }
        avg = (float)seek / n;
        printf("\nTotal number of seek operations = %d", seek);
        printf("\nAverage seek time = %f", avg);
        break;

    case 2:
        for (i = 1; i < n; i++)
        {
            if (p[i] > max)
            {
                max = p[i];
            }
        }
        for (i = cp; i <= max; i++)
        {
            for (j = 0; j < n; j++)
            {
                if (p[j] == i && a[j] == 0)
                {
                    a[j] = 1;
                    printf("%d ", p[j]);
                    temp = cp - p[j];
                    seek += temp;
                    cp = p[j];
                }
            }
        }
        for (i = max; i >= 0; i--)
        {
            for (j = 0; j < n; j++)
            {
                if (p[j] == i && a[j] == 0)
                {
                    a[j] = 1;
                    printf("%d ", p[j]);
                    temp = cp - p[j];
                    seek += abs(temp);
                    cp = p[j];
                }
            }
        }
        avg = (float)seek / n;
        printf("\nTotal number of seek operations = %d", seek);
        printf("\nAverage seek time = %f", avg);
        break;
    case 3:
        min1 = p[0];
        max1 = p[0];
        for (i = 1; i < n; i++)
        {
            if (p[i] < min1)
            {
                min1 = p[i];
            }
            if (p[i] > max1)
            {
                max1 = p[i];
            }
        }
        for (i = cp; i <= max1; i++)
        {
            for (j = 0; j < n; j++)
            {
                if (p[j] == i && a[j] == 0)
                {
                    a[j] = 1;
                    printf("%d ", p[j]);
                    temp = cp - p[j];
                    seek += temp;
                    cp = p[j];
                }
            }
        }
        for (i = max1; i >= min1; i--)
        {
            for (j = 0; j < n; j++)
            {
                if (p[j] == i && a[j] == 0)
                {
                    a[j] = 1;
                    printf("%d ", p[j]);
                    temp = cp - p[j];
                    seek += abs(temp);
                    cp = p[j];
                }
            }
        }
        avg = (float)seek / n;
        printf("\nTotal number of seek operations = %d", seek);
        printf("\nAverage seek time= %f", avg);
        break;
    case 4:
        max1 = p[0];
        for (i = 1; i < n; i++)
        {
            if (p[i] > max1)
            {
                max1 = p[i];
            }
        }
        for (i = cp; i <= max1; i++)
        {
            for (j = 0; j < n; j++)
            {
                if (p[j] == i && a[j] == 0)
                {
                    a[j] = 1;
                    printf("%d ", p[j]);
                    temp = cp - p[j];
                    seek += temp;
                    cp = p[j];
                }
            }
        }
        cp = 0;
        for (i = 0; i <= cp; i++)
        {
            for (j = 0; j < n; j++)
            {
                if (p[j] == i && a[j] == 0)
                {
                    a[j] = 1;
                    printf("%d ", p[j]);
                    temp = cp - p[j];
                    seek += abs(temp);
                    cp = p[j];
                }
            }
        }
        avg = (float)seek / n;
        printf("\nTotal number of seek operations = %d", seek);
        printf("\nAverage seek time = %f", avg);
        break;

    case 5:
        min1 = p[0];
        max1 = p[0];
        for (i = 1; i < n; i++)
        {
            if (p[i] < min1)
            {
                min1 = p[i];
            }
            if (p[i] > max1)
            {
                max1 = p[i];
            }
        }
        for (i = cp; i <= max1; i++)
        {
            for (j = 0; j < n; j++)
            {
                if (p[j] == i && a[j] == 0)
                {
                    a[j] = 1;
                    printf("%d ", p[j]);
                    temp = cp - p[j];
                    seek += temp;
                    cp = p[j];
                }
            }
        }
        for (i = min1; i < cp; i++)
        {
            for (j = 0; j < n; j++)
            {
                if (p[j] == i && a[j] == 0)
                {
                    a[j] = 1;
                    printf("%d ", p[j]);
                    temp = cp - p[j];
                    seek += abs(temp);
                    cp = p[j];
                }
            }
        }
        avg = (float)seek / n;
        printf("\nTotal number of seek operations = %d", seek);
        printf("\nAverage seek time = %f", avg);
        break;

    case 6:
        printf("\nExiting disk scheduling program...");
        exit(0);
        break;
    default:
        printf("\nInvalid choice. Please try again.");
    }
    goto j;
    return 0;
}