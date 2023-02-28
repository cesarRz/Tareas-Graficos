#include <stdio.h>

char tablero[8][8] =
        {
            {'-','-','-','-','-', '-', '-', '-'},
            {'-','-','-','-','-', '-', '-', '-'},
            {'-','-','-','-','-', '-', '-', '-'},
            {'-','-','-','-','-', '-', '-', '-'},
            {'-','-','-','-','-', '-', '-', '-'},
            {'-','-','-','-','-', '-', '-', '-'},
            {'-','-','-','-','-', '-', '-', '-'},
            {'-','-','-','-','-', '-', '-', '-'}
        };

void primeraDiagonal(int x, int y) {
    int j = 0;
    if ((x + 1) <= 7)
    {
        j = x + 1;
        for (int i = (y + 1); i < 8; i++)
        {
            tablero[i][j] = 'X';
            if (i == 7 || j == 7)
            {
                break;
            }else
            {
                j++;
            }
        }
    }
    if ((y - 1) >= 0 && x - 1 > 0)
    {
        j = x - 1;
        for (int i = (y - 1); i >= 0; i--)
        {
            tablero[i][j] = 'X';
            if (i == 0 || j == 0)
            {
                break;
            }
            else
            {
                j--;
            }
        }
    }
}

void segundaDiagonal(int x, int y) {
    int j = x + 1;
    if ((x + 1) <= 7)
    {
        for (int i = (y - 1); i >= 0; i--)
        {
            tablero[i][j] = 'X';
            if (i == 0 || j == 7)
            {
                break;
            }
            else
            {
                j++;
            }
        }
    }
    j = x;
    for (int i = (y + 1); i >= 0; i++)
    {
        if (i == 8 || j == 0)
        {
            break;
        }
        else
        {
            j--;
        }
        tablero[i][j] = 'X';
    }
}

int main(int argc, char const *argv[])
{
    int x;
    int y;
    printf("\nDonde quieres que este el alfil? (Dame coordenadas x, y)\n");
    scanf("%d", &x);
    scanf("%d", &y);
    printf("\n\n");

    // Para obtener las diagonales de X, abajo hacia la derecha
    primeraDiagonal(x, y);
    segundaDiagonal(x, y);

    // Hacemos el tablero
    for (int i = 7; i >= 0; i--)
    {
        printf("%d  ", i);
        for (int j = 0; j < 8; j++)
        {
            if (i == y && j == x)
            {
                tablero[i][j] = 'A';
                printf("%c", tablero[i][j]);
                printf("  ");
            } else
            {
                //printf("-  ");
                printf("%c", tablero[i][j]);
                printf("  ");
            }
        }
        printf("\n");
    }
    printf("   ");
    for (int i = 0; i < 8; i++)
    {
        printf("%d  ", i);
    }
    return 0;
}