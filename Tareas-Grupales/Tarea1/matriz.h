#include <stdio.h>


void imprime(int r, int c, float m[][c]) {
    for (int i = 0; i < r; i++)
    {
        for (int j = 0; j < c; j++)
        {
            printf("%.2f\t", m[i][j]);
        }
        printf("\n");
    }
}

void suma (int r, int c, float m1[][c], float m2[][c]) {
    printf("\nLa suma de las 2 matrices es:\n");
    for (int i = 0; i < r; i++)
    {
        for (int j = 0; j < c; j++)
        {
            printf("%.2f\t", m1[i][j] + m2[i][j]);
        }
        printf("\n");
    }
}

void multiplica (int r, int c, float m1[][c], float m2[][c]) {
    float mr[r][c];
    //Inicializamos en cero toda la matriz
    for (int i = 0; i < r; ++i)
    {
        for (int j = 0; j < c; ++j)
        {
                mr[i][j] = 0;
        }
    }
    printf("\nLa multiplicacion de las 2 matrices es:");
    for (int i = 0; i < r; i++)
    {
        for (int j = 0; j < c; j++)
        {
            for (int k = 0; k < r; k++)
            {
                mr[i][j] += m1[i][k] * m2[k][j];
            }
        }
        printf("\n");
    }
    imprime(r, c, mr);
}

void creaS(int d, float v[d], float m[][d]) {
    int j = 0;
    for (int i = 0; i < d; i++)
    {
        m[i][j] = v[i];
        j++;
    }
    imprime(d, d, m);
}