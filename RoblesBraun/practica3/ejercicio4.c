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

GLubyte paleta[3][3]={ {0, 255, 0}, {255, 255, 0}, {255, 0, 0} };
enum colores{verde, amarillo, rojo};
enum colores col = verde;

GLboolean colores = GL_TRUE;
int current_light = 0;

void ajusta(int ancho, int alto){
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, 640, 0, 480);
}

void animaT(int v){
    current_light++;
    if (current_light > 6) {
        current_light = 1;
    }
    switch (current_light)
    {
        case 1:
            glutPostRedisplay();
            glutTimerFunc(2000, animaT, 0);
            break;
        case 2:
            glutPostRedisplay();
            glutTimerFunc(1000, animaT, 0);
            break;
        case 3:
            glutPostRedisplay();
            glutTimerFunc(2000, animaT, 0);
            break;
        case 4:
            glutPostRedisplay();
            glutTimerFunc(500, animaT, 0);
            break;
        case 5:
            glutPostRedisplay();
            glutTimerFunc(500, animaT, 0);
            break;
        case 6:
            glutPostRedisplay();
            glutTimerFunc(500, animaT, 0);
            break;
        default:
            break;
    }
    // glutPostRedisplay();
    // glutTimerFunc(2000, animaT, 0);
}

void semaforo() {
    glBegin(GL_TRIANGLES);
        if (current_light == 1) {
            col = rojo;
            glColor3ubv(paleta[col]); // Rojo
        } else {
            glColor3ub(150, 150, 150);  // Gris
        }
        glVertex2i(280, 320);
        glVertex2i(360, 320);
        glVertex2i(320, 380);
        if (current_light == 2) {
            col = amarillo;
            glColor3ubv(paleta[col]); // Rojo
        } else {
            glColor3ub(150, 150, 150);  // Gris
        }
        glVertex2i(280, 220);
        glVertex2i(360, 220);
        glVertex2i(320, 280);
        if (current_light == 3) {
            col = verde;
            glColor3ubv(paleta[col]);  // Verde
        } else if (current_light == 4)
        {
            glColor3ub(150, 150, 150);  // Gris
        }
        else if (current_light == 5)
        {
            col = verde;
            glColor3ubv(paleta[col]);  // Verde
        }
        else if (current_light == 6)
        {
            glColor3ub(150, 150, 150);  // Gris
        }
        else {
            glColor3ub(150, 150, 150);  // Gris
        }
        glVertex2i(280, 120);
        glVertex2i(360, 120);
        glVertex2i(320, 180);
    glEnd();
}

void dibuja(void){
    glClear(GL_COLOR_BUFFER_BIT);
    semaforo();
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
