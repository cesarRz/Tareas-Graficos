#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <time.h>
#include <math.h>

double funcionImp(double x, double y){
    return (x*x + y*y);
}

int main()
{
    double puntos = 10000000, puntosDentro = 0;
    double max = 1, min = 0, randNum = 0, x, y, pi;
    srand(time(NULL));
    randNum = (double)rand()/RAND_MAX * (max - min) + min;
    for (int i = 0; i < puntos; i++)
    {
        x = (double)rand()/RAND_MAX * (max - min) + min;
        y = (double)rand()/RAND_MAX * (max - min) + min;
        // printf("\nx: %f y: %f", x, y);
        if (funcionImp(x, y) <= 1.0)
        {
            puntosDentro++;
        }
    }
    pi = 4*(puntosDentro/puntos);
    printf("El valor de Pi es: %f", pi);
    return 0;
}