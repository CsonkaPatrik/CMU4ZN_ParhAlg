#include <stdio.h>
#include <time.h>

void primeNum(int low, int high) {
   int i, flag;
   while (low < high) {
      flag = 0;

      if (low <= 1) {
         ++low;
         continue;
      }

      for (i = 2; i <= low / 2; ++i) {

         if (low % i == 0) {
            flag = 1;
            break;
         }
      }

      if (flag == 0)
         printf("%d ", low);

      ++low;
   }
}

int main() {
   int low=1, high;
   printf("Enter the upper limit: ");
   scanf("%d", &high);
   
   clock_t begin = clock();
   primeNum(low,high);

   clock_t end = clock();
   double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;

   printf("%f", time_spent);

   return 0;
}
