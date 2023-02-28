#include "matriz.h"

float m1[3][3] =    {{2, 3, 1},
                    {7, 4, 1},
                    {9, -2, 1}};

float m2[3][3] =    {{9, 3, 1},
                    {5, 4, 1},
                    {8, -2, 1}};
// const int rows = sizeof(m1) / sizeof(m1[0]);
// const int columns = sizeof(m1[0]) / sizeof(m1[0][0]);

int main(int argc, char const *argv[])
{
    //Calculamos rengoles de las matrices
    int rows = sizeof(m1) / sizeof(m1[0]);
    int columns = sizeof(m1[0]) / sizeof(m1[0][0]);
    
    printf("\nPrimera matriz:\n");
    imprime(rows, columns, m1);
    printf("\nSegunda matriz:\n");
    imprime(rows, columns, m2);
    
    //Suma de las 2 matrices
    suma(rows, columns, m1, m2);

    // Multiplicamos ambas matrices
    multiplica(rows, columns, m1, m2);

    // Agregamos un vector a la diagonal de m1
    printf("\nCambiando la diagonal de la matriz m1:\n");
    float v[3] = {1, 2, 3};
    creaS(rows, v, m1);


    return 0;
}
