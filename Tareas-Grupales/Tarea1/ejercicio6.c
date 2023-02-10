#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <stdbool.h>

struct coordenada{
    int x;
    int y;
    struct coordenada *sig;
};

typedef struct coordenada coordenada;



// Manejo de Estructuras
void printLista(coordenada *lista)
{
    struct coordenada *p;
    p = lista;

    while (p != NULL)
    {
        printf("%d, %d", p->x, p->y);
        printf("\n");
        p = p->sig;
    }
}
struct coordenada *ultimacoordenada(coordenada *lista){
    coordenada *p;
    p = lista;
    while (p->sig != NULL)
    {
        p = p->sig;
    }
    return p;
}
void agregacoordenada(coordenada *anterior, coordenada *nuevo){
    if (anterior->sig == NULL)
    {
        anterior->sig = nuevo;
        nuevo->sig = NULL;
    }
    else
    {
        nuevo->sig = anterior->sig;
        anterior->sig = nuevo;
    }
}
struct coordenada *creacoordenada(int x, int y){
    coordenada *p;
    p = (coordenada *)malloc(sizeof(coordenada));
    p->x = x;
    p->y = y;
    p->sig = NULL;
    return p;
}


// Formaulas de seno y coseno
double seno(double x){
    return sin(x);
}
double coseno(double x){
    return cos(x);
}

// Tabla de coordenadas
coordenada *evalua(double (*funcion)(double), int a, int b){
    double i;
    int x, y;
    coordenada *lista = NULL;
    coordenada *nuevo;
    for (i = a; i < b; i += 1){
        x = i;
        y = (*funcion)(i) * 10;
        nuevo = creacoordenada(x, y);
            if (lista == NULL)
            {
                lista = nuevo;
            }
        agregacoordenada(ultimacoordenada(lista),nuevo);
    }
    return lista;
}

// Funcion para encontrar coordenadas en lista
bool buscaCoordenada(coordenada *lista, int x, int y) {
    coordenada *p = lista;
    while (p != NULL) {
        if (p->x == x && p->y == y) {
            return true;
        }
        p = p->sig;
    }
    return false;
}

int real_coordinate(int n, int n_len){
    return n-n_len;
}

void dibujatabla(double (*funcion)(double),int x_len){

    coordenada *lista = evalua(*funcion,-10,10);

    int y_len = 10;
    int x_real, y_real;

    for (int y = 0; y < y_len*2+1; y++)
    {
        for (int x = 0; x < x_len*2+1; x++)
        {
            x_real = real_coordinate(x,x_len);
            y_real = real_coordinate(y,y_len) *-1;
            
            if (buscaCoordenada(lista,x_real,y_real))
            {
                // printf("%d,%d\t",x_real,y_real);
                printf("*\t");
            }
            else if (x == x_len && y == y_len)
            {
                printf("+\t");
            }
            else if (x == x_len)
            {
                printf("|\t");
            }
            else if (y == y_len)
            {
                printf("-\t");
            }

            else
            {
                printf(" \t");
            }
        }

        printf("\n");
    }

    printf("\n");

    printLista(lista);
}

int main(int argc, char const *argv[])
{
    printf("Grafica de Seno\n");
    dibujatabla(seno,10);
    printf("\n\n");
    printf("Grafica de Coseno\n");
    dibujatabla(coseno,10);
    return 0;
}
