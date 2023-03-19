#ifdef __APPLE__
#define GL_SILENCE_DEPRECATION
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <math.h>
#include <stdlib.h>

g_ancho = 800;
g_alto = 600;

void dibuja(void)
{
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT);

        // glColor3f(0.7, 0.0, 1.0);
        glLineWidth(1);

        // Arriba Izquierda
        glViewport(0, g_alto / 2, g_ancho / 2, g_alto / 2);
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glOrtho(-15,15,-15,15,-30,30);
        gluLookAt(0,8,0,   0,0,0,   0,0,-1);

        glColor3f(0,1,0);
        glPushMatrix();
            glutWireTeapot(5);
        glPopMatrix();

        // Arriba Derecha
        glViewport(g_ancho/2, g_alto/2, g_ancho/2, g_alto/2);
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        gluPerspective(45,1,1,50);
        gluLookAt(10,10,25,   0,0,0,   0,1,0);

        glColor3f(0,0,0);
        glPushMatrix();
            glutWireTeapot(5);
        glPopMatrix();

        // Abajo Izquierda
        glViewport(0, 0, g_ancho/2, g_alto/2);
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glOrtho(-15,15,-15,15,-30,30);

        glColor3f(1,0,0);
        glPushMatrix();
            glutWireTeapot(5);
        glPopMatrix();
        
        // Abajo derecha
        glViewport(g_ancho/2, 0, g_ancho/2, g_alto/2);
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glOrtho(-15,15,-15,15,-30,30);
        gluLookAt(8,0,0,   0,0,0,   0,1,0);

        glColor3f(0,0,1);
        glPushMatrix();
            glutWireTeapot(5);
        glPopMatrix();

   
    glFlush();
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(800, 600);
    glutInitWindowPosition(100, 150);
    glutCreateWindow("ejercicio 5");
    glutDisplayFunc(dibuja);
    glutMainLoop();
    return 0;
}