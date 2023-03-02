#ifdef __APPLE__
#define GL_SILENCE_DEPRECATION
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

int x = 75;
int y = 100;
int i = 0;

struct dot
{
    int x;
    int y;
};

typedef struct dot dot;

dot *uniqueDot = NULL;


void ajusta () {
    glClearColor(0.9, 0.9, 0.9, 0.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, 640, 0, 480);
}

int letra[][2] =    {{200, 200}, {200, 50}, {220, 50}, {220, 200}, //rectangulo izquierdo
                    {220, 200}, {220, 220}, {280, 220}, {280, 200}, // rectangulo superior
                    {280, 200}, {280, 50}, {300, 50}, {300, 200}, // rectangulo izquierdo
                    {220, 50}, {220, 30}, {280, 30}, {280, 50} // rectangulo inferior
                };


struct dot *createDot(int x, int y){
    struct dot *p;
    p = (struct dot *) malloc(sizeof(struct dot));
    p->x = x;
    p->y = y;
    return p;
}

void insertDot (int x, int y) {
    dot *p = uniqueDot;
    uniqueDot = createDot(x, y);
}

void raton(int boton, int estado, int x, int y)
{
    int height = 480;
    if(boton == GLUT_LEFT_BUTTON && estado == GLUT_DOWN)    {
        insertDot(x, height - y);
    }
    glutPostRedisplay();
}

void dibujaLetra (int style, int x, int y) {
    int allIterator = 0;
    int j = 0;
    glColor3f(0.0, 0.0, 0.0);
    if (style == 1)
    {
        glBegin(GL_QUADS);
            for(int i = 0; i < 16; i++)
                glVertex2i(letra[i][0] + x, letra[i][1] + y);
        glEnd();
    }
}

void giraLetra(void){
    if (i <= 1080)
    {
        i = i + 2;
    }
    else
    {
        glutIdleFunc(NULL);
        i = 0;
    }
    glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y){
    switch(key) {
        case 27:
            exit(0);// Esc =>Salir del programa
            break;
        case 'r':
            glutIdleFunc(giraLetra);
            break;
    }
}


void dibuja(void)
{
    dot *p;
    p = uniqueDot;
    glClear(GL_COLOR_BUFFER_BIT);
    glPushMatrix();
        if (p != NULL)
        {
            // Dibujamos el punto
            glColor3d(1, 0, 0);
            glPointSize(4);
            glBegin(GL_POINTS);
                glVertex2i(p->x, p->y);
            glEnd();
            glPushMatrix();
                // Mover a punto pivote
                glTranslatef(p->x, p->y, 0.0);
                // Rotar respecto al punto
                glRotatef(i, 0.0, 0.0, 1.0);
                // Mover a posicion original
                glTranslatef(-p->x, -p->y, 0.0);
                dibujaLetra(1, x, y);
            glPopMatrix();
        }
        else {
            // Letra solida
            dibujaLetra(1, x, y);
            // Dibujamos el punto
        }
    glPopMatrix();
    glutSwapBuffers();
}


int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(640,480);
    glutInitWindowPosition(100, 150);
    glutCreateWindow("Practica 4 - Ejercicio 2");
    glutMouseFunc(raton);
    glutKeyboardFunc(keyboard);
    glutReshapeFunc(ajusta);
    glutDisplayFunc(dibuja);
    glutMainLoop();
    return 0;
}