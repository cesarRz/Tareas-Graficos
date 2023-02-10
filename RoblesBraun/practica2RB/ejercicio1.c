#ifdef __APPLE__
#define GL_SILENCE_DEPRECATION
#include <GLUT/glut.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
#else
#include <GL/glut.h>
#endif

int puntos = 0;
int tam = 4;  // tama�o inicial del punto
GLboolean mostrar = GL_TRUE; //mostrar o no los puntos
GLboolean rojo = GL_TRUE;    // elecci�n de color

float colorUser [3] = {1.0, 0.0, 0.0};

struct Punto {
    int cx;
    int cy;
    float color[3];
    int tamanio;
    struct Punto *sig;
};

typedef struct Punto Punto;

Punto *puntoInicial = NULL;

struct Punto *creaPunto(int x, int y){
    struct Punto *p;
    p = (struct Punto *) malloc(sizeof(struct Punto));
    p->cx = x;
    p->cy = y;
    p->color[0] = colorUser[0];
    p->color[1] = colorUser[1];
    p->color[2] = colorUser[2];
    p->tamanio = tam;
    p->sig = NULL;
    return p;
}

void insertaPunto (int x, int y) {
    Punto *p = puntoInicial;
    if(puntoInicial == NULL)
        puntoInicial = creaPunto(x, y);
    else{
        while(p->sig != NULL){
            p = p->sig;
        }
        p->sig = creaPunto(x, y);
    }
}

void ajusta(int ancho, int alto) {
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, 640, 0, 480);
}
void raton(int boton, int estado, int x, int y){
    int alto_ventana = 480;
    if(boton == GLUT_LEFT_BUTTON && estado == GLUT_DOWN)    {
        insertaPunto(x, alto_ventana - y);
        puntos++;
    }
    glutPostRedisplay();
}
void pageUp_Down(int tecla, int x, int y) {
    switch(tecla) {
      case GLUT_KEY_UP:   tam++;
                               break;
      case GLUT_KEY_DOWN: tam--;
                               break;
      case GLUT_KEY_HOME: puntos=0;
    }
}
void teclado(unsigned char tecla, int x, int y){
    switch(tecla) {
        case 27:
            exit(0);// Esc =>Salir del programa
        case 'r':	
            colorUser[0] = 1.0;
            colorUser[1] = 0.0;
            colorUser[2] = 0.0;  //rojo
            break;
        case 'a':
            colorUser[0] = 0.0;
            colorUser[1] = 0.0;
            colorUser[2] = 1.0;  //azul
            break;
        case 'v':
            colorUser[0] = 0.0;
            colorUser[1] = 1.0;
            colorUser[2] = 0.0;  //verde
            break;
        case 'n':
            colorUser[0] = 1.0;
            colorUser[1] = 0.647;
            colorUser[2] = 0.0;  //naranja
            break;
        case 'm':
            mostrar=!mostrar;
    }
}
void dibuja(void){
	Punto *p;
    p = puntoInicial;
	glClear(GL_COLOR_BUFFER_BIT);
    if (mostrar){
        // Regresamos al inicio de la lista ligada de puntos
        glBegin(GL_LINE_STRIP);
        for (int i = 0 ; i < puntos; i++)	{
            glPointSize(p->tamanio);
            glColor3fv(p->color);
            glVertex2i(p->cx, p->cy);
            p = p->sig;
        }
        glEnd();
        p = puntoInicial;
        for (int i = 0 ; i < puntos; i++)	{
            glPointSize(p->tamanio);
            glColor3fv(p->color);
            glBegin(GL_POINTS);
                glVertex2i(p->cx, p->cy);
            glEnd();
            p = p->sig;
        }
    }

    
    glFlush();
}
int main(int argc, char** argv){
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
	glutInitWindowSize(640,480);
	glutInitWindowPosition(100, 150);
	glutCreateWindow("Dibujando puntos estructuras");
	glutMouseFunc(raton);
    glutDisplayFunc(dibuja);
	glutKeyboardFunc(teclado);
	glutSpecialFunc(pageUp_Down);
	glutReshapeFunc(ajusta);
	glutMainLoop();
	return 0;
}
