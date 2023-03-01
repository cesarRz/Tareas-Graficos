#include <stdio.h>

void imprime(int r, int c, int m[][c]) {
    for (int i = 0; i < r; i++)
    {
        for (int j = 0; j < c; j++)
        {
            printf("%.2d\t", m[i][j]);
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

void multiplica(int m, int n, int q, int m1[][q], int m2[][m], int mr[][m])
{
    for (int a = 0; a < m; a++)
    {
        // Dentro recorremos las filas de la primera (A)
        for (int i = 0; i < n; i++)
        {
            float suma = 0;
            // Y cada columna de la primera (A)
            for (int j = 0; j < q; j++)
            {
                // Multiplicamos y sumamos resultado
                suma += m1[i][j] * m2[j][a];
            }
            // Lo acomodamos dentro del producto
            mr[i][a] = suma;
        }
    }
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