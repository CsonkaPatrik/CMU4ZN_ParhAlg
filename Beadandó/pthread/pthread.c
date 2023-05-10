#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define SIZE 10000

void *sortArray(void *arg);
int *generateRandomArray(int size);
int compareIntegers(const void *a, const void *b);

int main()
{
    int *numbers = generateRandomArray(SIZE); // Tömb generálása random számokkal

    int threadCounts[] = {1, 2, 4, 8}; // Különböző szállal való tesztelés
    int numThreadCounts = sizeof(threadCounts) / sizeof(threadCounts[0]);

    for (int i = 0; i < numThreadCounts; i++)
    {
        printf("Teszt %d szállal:\n", threadCounts[i]);

        pthread_t threads[threadCounts[i]];
        double startTime, endTime;

        startTime = clock(); // Mérőóra indítása

        // Szálak létrehozása és indítása
        for (int j = 0; j < threadCounts[i]; j++)
        {
            pthread_create(&threads[j], NULL, sortArray, numbers);
        }

        // Várakozás a szálak befejezésére
        for (int j = 0; j < threadCounts[i]; j++)
        {
            pthread_join(threads[j], NULL);
        }

        endTime = clock(); // Mérőóra leállítása

        double elapsedTime = (endTime - startTime) / (double)CLOCKS_PER_SEC * 1000.0;
        printf("Futási idő: %.2lf ms\n\n", elapsedTime);
    }

    printf("Kész!\n");
    return 0;
}

void *sortArray(void *arg)
{
    int *array = (int *)arg;
    qsort(array, SIZE, sizeof(int), compareIntegers);
    pthread_exit(NULL);
}

int *generateRandomArray(int size)
{
    int *array = (int *)malloc(size * sizeof(int));

    srand(time(NULL));
    for (int i = 0; i < size; i++)
    {
        array[i] = rand() % 100 + 1;
    }

    return array;
}

int compareIntegers(const void *a, const void *b)
{
    int num1 = *(const int *)a;
    int num2 = *(const int *)b;

    if (num1 < num2)
        return -1;
    if (num1 > num2)
        return 1;
    return 0;
}