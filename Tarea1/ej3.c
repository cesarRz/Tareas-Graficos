#include <stdio.h>
#include <stdlib.h>

struct fraccion
{
    int numerador;
    int denominador;
    struct fraccion *sig;
};

typedef struct fraccion fraccion;
typedef struct lista lista;

struct fraccion *ultimaFraccion(fraccion *lista){
    fraccion *p;
    p = lista;
    while (p->sig != NULL)
    {
        p = p->sig;
    }
    return p;
}

void agregaFraccion(fraccion *anterior, fraccion *nuevo){
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

fraccion *creafraccion(int num, int den){
    fraccion *p;
    p = (fraccion *)malloc(sizeof(fraccion));
    p->numerador = num;
    p->denominador = den;
    p->sig = NULL;
    return p;
}

//https://isseu.wordpress.com/2009/08/27/funcion-reducir-fraccion-c/
int reducir(int nominador,int denominador){
	if(denominador==1){
		
        printf("%d/%d", nominador, denominador);
	}else{
	int b=2;
	while(b<=nominador){
		if(denominador%b==0 && nominador%b==0){
			denominador=denominador/b;
			nominador=nominador/b;
		}else{
		b++;
		}
	}
	printf("%d/%d", nominador, denominador);

	}
	return 0;

}

void printLista(fraccion *lista)
{
    struct fraccion *p;
    p = lista;
    printf("Direccion - V - Direccion Siguiente\n");

    while (p != NULL)
    {
        printf("%d / %d = ", p->numerador, p->denominador);
        reducir(p->numerador, p->denominador);
        printf("\n");
        p = p->sig;
    }
}

int main()
{
    fraccion *lista = NULL;
    fraccion *nuevo;
    int num, den = -1;
    int i = 1;

    while (den != 0)
    {
        printf("\nCaso %d", i);
        printf("\n Numerador -> ");
        scanf("%d", &num);
        printf(" Denominador -> ");
        scanf("%d", &den);

        if (den != 0){
            nuevo = creafraccion(num, den);
            if (lista == NULL)
            {
                lista = nuevo;
            }
            // printf("%d/%d", nuevo->numerador, nuevo->denominador);
            agregaFraccion(ultimaFraccion(lista), nuevo);
            i++;
        }
    }

    printLista(lista);

    return 0;
}
