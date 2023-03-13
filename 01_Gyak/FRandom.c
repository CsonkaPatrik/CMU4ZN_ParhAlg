#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

float float_rand( float min, float max )
{
    float scale = rand() / (float) RAND_MAX;
    return min + scale * ( max - min );
}

int main()
{
    float lower = 500, upper = 1000;
 
    srand(time(0));
 
    printf("%lf",float_rand(lower, upper));
 
    return 0;
}
