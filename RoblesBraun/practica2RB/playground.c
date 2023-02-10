#include <stdio.h>
#include <stdlib.h>

int main(int argc, char const *argv[])
{
    int semillas = 2;
    int semillax1 = 10;
    int semillay1 = 10;
    int semillax2 = 20;
    int semillay2 = 20;
    int x = semillax1;
    int y = semillay1;
    int xi = 0;
    int yi = 0;
    int L = 5;
    for (int i = 0; i < semillas; i++)
    {
        printf("Valor de la %d semilla: %d  %d\n", i+1, x, y);
        for (int j = 0 ; j < L; j++){
            xi = 40*(1 + 2*L) - y + abs(x - 120);
            yi = x;
            printf("%d, %d", xi, yi);
            printf("\n");
            x = xi;
            y = yi;
        }
        printf("\n\n\n");
        x = semillax2;
        y = semillay2;
    }
    return 0;
}