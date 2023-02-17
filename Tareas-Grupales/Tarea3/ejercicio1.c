#ifdef __APPLE__
#define GL_SILENCE_DEPRECATION
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

struct Punto{
   int cx;
   int cy;
   int color[3];
   int radio;
   struct Punto *sig;
};

typedef struct Punto Punto;

// Funciones para manejo de estructuras
struct Punto *ultimaPunto(Punto *lista){
    Punto *p;
    p = lista;
    while (p->sig != NULL)
    {
        p = p->sig;
    }
    return p;
}
void agregaPunto(Punto *anterior, Punto *nuevo){
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
Punto *creaPunto(int cx, int cy,int clr[3]){
    Punto *p;
    p = (Punto *)malloc(sizeof(Punto));
    p->cx = cx;
    p->cy = cy;
    p->color[0] = clr[0];
    p->color[1] = clr[1];
    p->color[2] = clr[2];
    p->sig = NULL;
    return p;
}

int color[3] = {255,0,0};
Punto *p = NULL;
int clicks = 1;

void ajusta () {
    glClearColor(0.9, 0.9, 0.9, 0.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, 640, 0, 480);
}

void Bresenham(int centro_x, int centro_y, int radio){
    int x = 0;
    int y = radio;
    int e = 3 - 2 * radio;

    glBegin(GL_POINTS);
    while (x < y)
    {
        glVertex2i(centro_x + x, centro_y + y );
        glVertex2i(centro_x + y, centro_y + x );
        glVertex2i(centro_x - x, centro_y + y );
        glVertex2i(centro_x - y, centro_y + x );
        glVertex2i(centro_x + x, centro_y - y );
        glVertex2i(centro_x + y, centro_y - x );
        glVertex2i(centro_x - x, centro_y - y );
        glVertex2i(centro_x - y, centro_y - x );

        if (e > 0)
        {
            e = e + 4*(x-y) + 10;
            y = y-1;
        }else
        {
            e = e +4*x+6;
        }
            x = x+1;
    }
    if (x == y)
    {
        glVertex2i(centro_x + x, centro_y + y );
        glVertex2i(centro_x + y, centro_y + x );
        glVertex2i(centro_x - x, centro_y + y );
        glVertex2i(centro_x - y, centro_y + x );
        glVertex2i(centro_x + x, centro_y - y );
        glVertex2i(centro_x + y, centro_y - x );
        glVertex2i(centro_x - x, centro_y - y );
        glVertex2i(centro_x - y, centro_y - x );
    }


    glEnd();

}

void dibuja(){
    
    Punto *a;
    a = p;
    glClear(GL_COLOR_BUFFER_BIT);

    if (a != NULL)
    {
        while (a != NULL)
        {
            glColor3ub(a->color[0], a->color[1], a->color[2]);
            Bresenham(a->cx,a->cy, a->radio);
            a = a->sig;
        }
        
    }
    glFlush();
}

void motion(int x, int y){
    int alto_ventana = 480;
    Punto *nuevo;
    nuevo = ultimaPunto(p);
    nuevo->radio = sqrt( pow(x - nuevo->cx, 2) + pow(alto_ventana-y - nuevo->cy, 2));
    glutPostRedisplay();

}
void raton(int boton, int estado, int x, int y){
    int alto_ventana = 480;
    Punto *nuevo;

    if(boton == GLUT_LEFT_BUTTON && estado == GLUT_DOWN)    {

            nuevo = creaPunto(x, alto_ventana-y, color); 
            if (p == NULL){
                    p = nuevo;
            }
            agregaPunto(ultimaPunto(p), nuevo);   
    }
}
void teclado(unsigned char tecla, int x, int y){
    switch(tecla) {
        case 27:	
            exit(0);		// Esc =>Salir del programa
            break;
        case 'r':
            color[0] = 255;
            color[1] = 0;
            color[2] = 0; 
            
		    break;
        case 'b':
            color[0] = 0;
            color[1] = 0;
            color[2] = 255;  //azul
            
			break;
        case 'g':
            color[0] = 0;
            color[1] = 255;
            color[2] = 0;  //verde
            
            break;
        case 'o':
            color[0] = 255;
            color[1] = 144;
            color[2] = 0;  //naranja
            
            break;
    }

}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(640,480);
    glutInitWindowPosition(100, 150);
    glutCreateWindow("Ejercicio 1: Bresenham");
    glutReshapeFunc(ajusta);
    glutMouseFunc(raton);
    glutMotionFunc(motion);
    glutKeyboardFunc(teclado);
    glutDisplayFunc(dibuja);
    glutMainLoop();
    return 0;
}