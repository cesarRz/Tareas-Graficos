#ifdef __APPLE__
#define GL_SILENCE_DEPRECATION
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
#include <math.h>

#define ALTO 30
#define ANCHO 30


void pixelartPar(GLubyte girasol[ALTO][ANCHO], GLubyte paleta1[][4],int base_x, int base_y, int tam ){
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glPointSize(tam);
    glBegin(GL_POINTS);
    for (int i = 0; i < ALTO; i++)
        for (int j = 0; j < ANCHO; j++)
        {
            glColor4ubv(paleta1[girasol[i][j]]);
            glVertex2i(base_x + j * tam, base_y - i * tam);
        }
    glEnd();
}