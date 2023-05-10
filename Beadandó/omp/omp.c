#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>

#define SIZE 10000

void sortArray(int *array);
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

        double start = omp_get_wtime(); // Mérőóra indítása

        // Szálak létrehozása és indítása
        omp_set_num_threads(threadCounts[i]);
#pragma omp parallel
        {
            sortArray(numbers);
        }

        double end = omp_get_wtime(); // Mérőóra leállítása

        double elapsedTime = (end - start) * 1000;
        printf("Futási idő: %.2lf ms\n\n", elapsedTime);
    }

    printf("Kész!\n");
    return 0;
}

void sortArray(int *array)
{
    qsort(array, SIZE, sizeof(int), compareIntegers);
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