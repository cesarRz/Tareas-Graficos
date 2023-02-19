#ifdef __APPLE__
#define GL_SILENCE_DEPRECATION
#include <GLUT/glut.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <ctype.h>
#else
#include <GL/glut.h>
#endif

#include "pixelart.h"

#define ALTO 30
#define ANCHO 30

GLubyte paleta_soccer[6][4] = {{255, 255, 255, 0}, {0, 255, 255, 255}, {0, 0, 0, 255}};
GLubyte paleta_soccer1[6][4] = {{255, 255, 255, 0}, {255, 255, 255, 255}, {0, 0, 180, 255}};
GLubyte soccer[ALTO][ANCHO] = {{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,1,1,2,2,2,2,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,1,1,1,1,2,2,2,2,1,1,1,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,1,1,1,1,1,1,2,2,2,2,1,1,1,1,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,1,1,1,1,1,1,1,2,2,2,2,1,1,1,1,1,0,0,0,0,0,0,0},
{0,0,0,0,0,0,1,1,1,1,1,1,1,2,1,1,1,1,2,1,1,1,1,0,0,0,0,0,0,0},
{0,0,0,0,0,0,2,1,1,1,1,1,2,1,1,1,1,1,2,1,1,1,1,1,0,0,0,0,0,0},
{0,0,0,0,0,0,1,2,1,1,1,1,2,1,1,1,1,1,2,1,1,1,1,1,0,0,0,0,0,0},
{0,0,0,0,0,1,1,1,2,2,2,2,1,1,1,1,1,1,1,2,2,2,2,2,1,0,0,0,0,0},
{0,0,0,0,0,1,1,1,2,2,2,2,1,1,1,1,1,1,1,2,2,2,2,2,1,0,0,0,0,0},
{0,0,0,0,0,1,1,1,2,2,2,2,1,1,1,1,1,1,1,2,2,2,2,2,1,0,0,0,0,0},
{0,0,0,0,0,1,1,1,2,2,2,2,1,1,1,1,1,1,1,2,2,2,2,2,1,0,0,0,0,0},
{0,0,0,0,0,0,1,2,1,1,1,1,2,1,1,1,1,1,2,1,1,1,1,1,0,0,0,0,0,0},
{0,0,0,0,0,0,2,1,1,1,1,1,2,1,1,1,1,1,2,1,1,1,1,1,0,0,0,0,0,0},
{0,0,0,0,0,0,1,1,1,1,1,1,1,2,2,2,2,2,1,1,1,1,1,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,1,1,1,1,1,1,2,2,2,2,2,1,1,1,1,1,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,1,1,1,1,1,2,2,2,2,2,1,1,1,1,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,1,1,1,1,2,2,2,2,2,1,1,1,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,1,1,2,1,1,1,1,1,2,1,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}};

GLboolean colores = GL_TRUE;
int x = 250;
int y = 300;

int lados = 3;

void ajusta(int ancho, int alto){
    glClearColor(0.5, 0.5, 0.5, 0.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, 640, 0, 480);
}

void animaT(int v){
   colores = !colores;
   glutTimerFunc(600, animaT, 0);
   glutPostRedisplay();
}

void dibuja(void){
    glClear(GL_COLOR_BUFFER_BIT);
    if (colores)
    {
        pixelArt(soccer, paleta_soccer, x, y, 7);
    } else
    {
        pixelArt(soccer, paleta_soccer1, x, y, 7);
    }
    glutSwapBuffers();
}


int main(int argc, char** argv){
   glutInit(&argc, argv);
   glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
   glutInitWindowSize(640,480);
   glutInitWindowPosition(100, 150);
   glutCreateWindow("Ejercicio 2 - Pixel Art");
   glutReshapeFunc(ajusta);
   glutTimerFunc(2, animaT, 0);
   glutDisplayFunc(dibuja);
   glutMainLoop();
   return 0;
}