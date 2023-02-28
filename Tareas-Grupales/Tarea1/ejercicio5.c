#include <stdio.h>
#include <stdlib.h>

FILE *fp;

void leer (const char name[20]) {
    unsigned short numLineas, vertices;
    float x, y;
    fp = fopen(name, "r");
    if (fp == NULL)
    {
        printf("\nError al intentar abrir el archivo %s\n", name);
        exit(1); 
    }

    fscanf(fp, "%hu", &numLineas);
    printf("\nNúmero de líneas - %hu\n", numLineas);
    for (int i = 0; i < numLineas; i++)
    {
        fscanf(fp, "%hu", &vertices);
        printf("\nLinea %d - %hu vertices ", i + 1, vertices);
        for (int j = 0; j < vertices; j++)
        {
            fscanf(fp, "%f %f", &x, &y);
            printf("(%.3f, %.3f) ", x, y);
        }
        
        
    }
    
    fclose(fp);
}

int main(int argc, char const *argv[])
{
    leer("polilineas.dat");
    return 0;
}