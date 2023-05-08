using System;
using System.Diagnostics;
using System.Threading;

namespace ThreadTesting
{
    class Program
    {
        static void Main(string[] args)
        {
            int[] numbers = GenerateRandomArray(10000); // Tömb generálása random számokkal

            int[] threadCounts = { 1, 2, 4, 8 }; // Különböző szállal való tesztelés

            foreach (int threadCount in threadCounts)
            {
                Stopwatch stopwatch = new Stopwatch();

                Console.WriteLine($"Teszt {threadCount} szállal:");

                // Szálak létrehozása és indítása
                Thread[] threads = new Thread[threadCount];
                for (int i = 0; i < threadCount; i++)
                {
                    threads[i] = new Thread(() => SortArray(numbers));
                    threads[i].Start();
                }

                stopwatch.Start(); // Mérőóra indítása

                // Várakozás a szálak befejezésére
                foreach (Thread thread in threads)
                {
                    thread.Join();
                }

                stopwatch.Stop(); // Mérőóra leállítása

                long elapsedMilliseconds = stopwatch.ElapsedMilliseconds;
                Console.WriteLine($"Futási idő: {elapsedMilliseconds} ms");
                Console.WriteLine();
            }

            Console.WriteLine("Kész!");
            Console.ReadKey();
        }

        static int[] GenerateRandomArray(int size)
        {
            Random random = new Random();
            int[] array = new int[size];

            for (int i = 0; i < size; i++)
            {
                array[i] = random.Next(1, 100);
            }

            return array;
        }

        static void SortArray(int[] array)
        {
            Array.Sort(array);
        }
    }
}