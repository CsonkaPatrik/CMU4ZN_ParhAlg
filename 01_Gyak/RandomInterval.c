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
    int a,b;
 
    printf("Adja meg az 1. szamot:");
    while(scanf("%d", &a)!=1){
        printf("Hibas adat! Adja meg ujra:");
    }

    printf("Adja meg a 2. szamot:");
    while(scanf("%d", &b) != 1){
        printf("Hibas adat! Adja meg ujra:");
    }
    srand(time(0));
 
    printRandom(a, b);
 
    return 0;
}
