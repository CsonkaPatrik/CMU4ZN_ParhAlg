#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void printRandom(int also, int felso)
{
        int num = (rand() %
        (felso - also + 1)) + also;
        printf("%d ", num);
}

int main()
{
    int also = 500, felso = 1000;
 
    srand(time(0));
 
    printRandom(also, felso);
 
    return 0;
}
