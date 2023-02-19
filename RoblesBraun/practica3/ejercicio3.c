#ifdef __APPLE__
#define GL_SILENCE_DEPRECATION
#include <stdio.h>
#include <math.h>
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

int x = 0;
int y = 0;

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

void moveLetter(int tecla, int x1, int y1) {
    switch(tecla) {
        case GLUT_KEY_UP:
            if ((letra[5][1] + y + 10) <= 480) {
                y = y + 10;
            }
            break;
        case GLUT_KEY_DOWN:
            if ((letra[14][1] + y - 10) >= 0) {
                y = y - 10;
            }
            break;
        case GLUT_KEY_LEFT:
            if ((letra[0][0] + x - 10) >= -40) {
                x = x - 10;
            }
            else
            {
                x = 380;
            }
            break;
        case GLUT_KEY_RIGHT:
            if ((letra[11][0] + x + 10) <= 680) {
                x = x + 10;
            }
            else
            {
                x = -240;
            }
            
            break;
    }
    glutPostRedisplay();
}

void dibuja(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    // Letra solida
    dibujaLetra(1, x, y);
    glutSwapBuffers();
}
int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(640,480);
    glutInitWindowPosition(100, 150);
    glutCreateWindow("Practica 3 - Ejercicio 3");
    glutReshapeFunc(ajusta);
    glutDisplayFunc(dibuja);
    glutSpecialFunc(moveLetter);
    glutMainLoop();
    return 0;
}