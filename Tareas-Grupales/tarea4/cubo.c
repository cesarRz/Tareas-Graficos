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


void dibuja(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //Limpiamos frame buffer y z-buffer
    glColor3ub(0, 0, 255);
    glLineWidth(2);

    //Cara azul
    glPushMatrix();
        glRotatef(-90, 1, 0, 0);
        glBegin(GL_QUADS);
            glVertex2f(0, 1);
            glVertex2f(1, 1);
            glVertex2f(1, 0);
            glVertex2f(0, 0);
        glEnd();
    glPopMatrix();

    //Cara verde
    glPushMatrix();
        glColor3ub(0, 255, 0);
        //glRotatef(45, 0, 1, 0);
        glBegin(GL_QUADS);
            glVertex2f(-1, 0);
            glVertex2f(0, 0);
            glVertex2f(0, -1);
            glVertex2f(-1, -1);
        glEnd();
    glPopMatrix();

    //Cara amarillo
    glPushMatrix();
        glColor3ub(245, 196, 74);
        //glRotatef(45, 0, 1, 0);
        glBegin(GL_QUADS);
            glVertex2f(0, 0);
            glVertex2f(1, 0);
            glVertex2f(1, -1);
            glVertex2f(0, -1);
        glEnd();
    glPopMatrix();

    glPushMatrix();
        glColor3ub(255, 0, 0);
        glPointSize(4);
        glBegin(GL_POINTS);
            glVertex2f(0, 0);
        glEnd();
    glPopMatrix();
    glutSwapBuffers();
}

void teclado (unsigned char key, int x, int y)
{
    switch (key) {
        case 27: 
            exit(0);
    }
    glutPostRedisplay();
}


void ajusta(int ancho, int alto) {
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glEnable(GL_DEPTH_TEST); // Habilitamos el z-buffer
    glOrtho(-5, 5, -5, 5, -5, 5);
}


int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH); // GLU DEPTH es el z-buffer
    glutInitWindowSize(700, 700);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Armado de un cubo");
    glutDisplayFunc(dibuja);
    glutReshapeFunc(ajusta);
    glutKeyboardFunc(teclado);
    glutMainLoop();
    return 0;
}