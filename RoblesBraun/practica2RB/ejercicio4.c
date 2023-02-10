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

int semillas = 0;
int tam = 4;  // tama�o inicial del punto
GLboolean trazo = GL_TRUE; //mostrar o no los puntos
GLboolean rojo = GL_TRUE;    // elecci�n de color

float colorUser [3] = {1.0, 0.0, 0.0};

struct Semilla {
    int cx;
    int cy;
    float color[3];
    struct Semilla *sig;
};

typedef struct Semilla Semilla;

Semilla *semillaInicial = NULL;

struct Semilla *creaSemilla(int x, int y){
    struct Semilla *p;
    p = (struct Semilla *) malloc(sizeof(struct Semilla));
    p->cx = x;
    p->cy = y;
    p->color[0] = colorUser[0];
    p->color[1] = colorUser[1];
    p->color[2] = colorUser[2];
    p->sig = NULL;
    return p;
}

void insertaSemilla (int x, int y) {
    Semilla *p = semillaInicial;
    if(semillaInicial == NULL)
        semillaInicial = creaSemilla(x, y);
    else{
        while(p->sig != NULL){
            p = p->sig;
        }
        p->sig = creaSemilla(x, y);
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
        insertaSemilla(x, alto_ventana - y);
        semillas++;
    }
    glutPostRedisplay();

}

void pageUp_Down(int tecla, int x, int y) {
    switch(tecla) {
      case GLUT_KEY_UP:   tam++;
                               break;
      case GLUT_KEY_DOWN: tam--;
                               break;
      case GLUT_KEY_HOME: semillas = 0;
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
    }
}
void dibuja(void){
    Semilla *p;
    p = semillaInicial;
    int x0 = 0;
    int y0 = 0;
    int x1 = 0;
    int y1 = 0;
    int L = 10;
    glClear(GL_COLOR_BUFFER_BIT);
    for (int j = 0; j < semillas; j++)
    {
        x0 = p->cx;
        y0 = p->cy;
        printf("Valor de la %d semilla: %d  %d\n", j + 1, x0, y0);
        for (int i = 0 ; i < L; i++){
            x1 = (40*(1 + 2*L)) - y0 + abs(x0 - 120);
            y1 = x0;
            glPointSize(tam);
            glColor3fv(p->color);
            glBegin(GL_POINTS);
                glVertex2i(x1, y1);
            glEnd();
            x0 = x1;
            y0 = y1;
            // printf("%d, %d", xi, yi);
        }
        p = p->sig;
    }
    glFlush();
}
int main(int argc, char** argv){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
    glutInitWindowSize(640,480);
    glutInitWindowPosition(100, 150);
    glutCreateWindow("Práctica 2 - Jengibre");
    glutMouseFunc(raton);
    glutDisplayFunc(dibuja);
    glutKeyboardFunc(teclado);
    glutSpecialFunc(pageUp_Down);
    glutReshapeFunc(ajusta);
    glutMainLoop();
    return 0;
}
