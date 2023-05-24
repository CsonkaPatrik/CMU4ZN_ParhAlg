#include <stdio.h>
#include <omp.h>
#include <time.h>
#include <stdlib.h>

#define N 100000000

int main(int argc, char **argv)
{
    int sizes[] = {N}; // Csak egy méretű tömb
    int numSizes = sizeof(sizes) / sizeof(sizes[0]);

    int threadCounts[] = {1, 2, 4, 8}; // Különböző szállal való tesztelés
    int numThreadCounts = sizeof(threadCounts) / sizeof(threadCounts[0]);

    for (int i = 0; i < numSizes; i++)
    {
        int size = sizes[i];
        printf("Tömb mérete: %d\n", size);

        for (int j = 0; j < numThreadCounts; j++)
        {
            int threadCount = threadCounts[j];
            printf("Szálak száma: %d\n", threadCount);

            double start = omp_get_wtime(); // Mérőóra indítása

            float total_sum = 0;

#pragma omp parallel num_threads(threadCount)
            {
                float sum_part = 0;

#pragma omp for
                for (int l = 0; l <= size; l++)
                {
                    sum_part += (rand() % 100000) + 1;
                }

#pragma omp critical
                {
                    total_sum += sum_part;
                }
            }

            double end = omp_get_wtime(); // Mérőóra leállítása

            double elapsedTime = (end - start);

            printf("Futási idő: %.6lf sec\n", elapsedTime);
            printf("Összeg: %.2f\n\n", total_sum);
        }

        printf("----------------------------------------\n");
    }

    return 0;
}

