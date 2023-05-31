using System;
using System.Diagnostics;
using System.Threading;
using System.Threading.Tasks;

class Program
{
    static void Main()
    {
        int[] array = GenerateArray(N);
        int[] threadCounts = { 1, 2, 4, 8 }; 

        foreach (int threadCount in threadCounts)
        {
            Stopwatch stopwatch = new Stopwatch();
            stopwatch.Start(); 

            int totalSum = 0;

            object lockObject = new object(); // Zár objektum

            Parallel.For(0, threadCount, () => 0, (i, loop, localSum) =>
            {
                int startIndex = (N / threadCount) * i;
                int endIndex = (N / threadCount) * (i + 1);

                for (int j = startIndex; j < endIndex; j++)
                {
                    localSum += array[j];
                }

                return localSum;
            }, localSum =>
            {
                lock (lockObject)
                {
                    totalSum += localSum; // Részeredmények összeadása
                }
            });

            stopwatch.Stop();

            Console.WriteLine($"Szálak száma: {threadCount}");
            Console.WriteLine($"Összeg: {totalSum}");
            Console.WriteLine($"Futási idő: {stopwatch.Elapsed.TotalSeconds} sec");
            Console.WriteLine();
        }

        Console.ReadLine();
    }

    static int N = 100000000;

    static int[] GenerateArray(int size)
    {
        int[] array = new int[size];
        Random random = new Random();

        for (int i = 0; i < size; i++)
        {
            array[i] = random.Next(100000) + 1;
        }

        return array;
    }
}