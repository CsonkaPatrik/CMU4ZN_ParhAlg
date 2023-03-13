#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void printRandom(int lower, int upper)
{
        int num = (rand() %
        (upper - lower + 1)) + lower;
        printf("%d ", num);
}

int main()
{
    int lower = 500, upper = 1000;
 
    srand(time(0));
 
    printRandom(lower, upper);
 
    return 0;
}
