#include <stdio.h>
#include <pthread.h>
#include <time.h>
#include <stdlib.h>

#define THREADS_COUNT 4
#define N 100000000

typedef struct
{
    int start;
    int end;
    int *part_sum;
} ThreadData;

void *sum(void *arg);

int main()
{
    int threadCounts[] = {1, 2, 4, 8}; // Különböző szállal való tesztelés
    int numThreadCounts = sizeof(threadCounts) / sizeof(threadCounts[0]);

    for (int i = 0; i < numThreadCounts; i++)
    {
        int threadCount = threadCounts[i];
        pthread_t thread_id[threadCount];
        ThreadData thread_data[threadCount];

        int border = N / threadCount;
        int total_sum = 0;

        clock_t start = clock(); // Mérések kezdete

        for (int j = 0; j < threadCount; j++)
        {
            thread_data[j].start = j * border;
            thread_data[j].end = (j + 1) * border;
            thread_data[j].part_sum = malloc(sizeof(int)); // Allocate memory for each thread's part_sum

            pthread_create(&thread_id[j], NULL, sum, &thread_data[j]);
        }

        for (int j = 0; j < threadCount; j++)
        {
            pthread_join(thread_id[j], NULL);
            total_sum += *(thread_data[j].part_sum); // Access the value pointed by part_sum
            free(thread_data[j].part_sum); // Free the allocated memory
        }

        clock_t end = clock(); // Mérések vége
        double total = (double)(end - start) / CLOCKS_PER_SEC; // Számítás a helyes eltelt időért

        printf("szal: %d\n", threadCount);
        printf("osszeg (10 000 elem): %d\n", total_sum);
        printf("futasi ido: %lf (sec)\n", total);
        printf("\n");
    }

    return 0;
}

void *sum(void *arg)
{
    ThreadData *data = (ThreadData *)arg;
    int *part_sum = data->part_sum;
    *part_sum = 0;

    srand(time(NULL));
    for (int i = data->start; i < data->end; i++)
    {
        *part_sum += (rand() % N) + 1;
    }

    return NULL;
}