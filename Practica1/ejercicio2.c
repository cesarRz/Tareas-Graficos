#ifdef __APPLE__
#define GL_SILENCE_DEPRECATION
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <stdio.h>
#include <math.h>

void ajusta()
{
    glClearColor(0.9, 0.9, 0.9, 0.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, 640, 0, 480);
}

void dibuja()
{
    glClear(GL_COLOR_BUFFER_BIT);
    
    // Cuadrados de tabla
    glLineWidth(2);
    glEnable(GL_LINE_STIPPLE);
    glLineStipple(2,0x0F0F);
    glBegin(GL_LINES);
        glColor3ub(0,0,255);
        for (int i = 0; i <= 640; i+=20)
        {
            glVertex2i(i,480);
            glVertex2i(i,0);

        }
    glEnd();
    glBegin(GL_LINES);
        glColor3ub(0,0,100);
        for (int i = 0; i <= 480; i+=20)
        {
            glVertex2i(640,i);
            glVertex2i(0,i);

        }
    glEnd();
    glDisable(GL_LINE_STIPPLE);

    // Eje de Tabla
    glLineWidth(5);
    glBegin(GL_LINES);
        glColor3ub(0,0,0);
            glVertex2i(320,0);
            glVertex2i(320,640);

            glVertex2i(0,240);
            glVertex2i(640,240);
    glEnd();


    // Coseno
    glBegin(GL_LINE_STRIP);
    glLineWidth(3);
    glColor3ub(255,0,0);
    float a = 3.14;
    for (float x = (a*-1); x <= a; x+= .1)
        {
            
            float x_escalado = (float)x* (640 / (2*a)) + 320;
            float y = cos(x);
            float y_escalado = y * 240 + 240;
            
            glVertex2f(x_escalado, y_escalado);

        }   
    glEnd();
    glFlush();
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(640, 480);
    glutInitWindowPosition(100, 150);
    glutCreateWindow("Coseno");
    glutReshapeFunc(ajusta);
    glutDisplayFunc(dibuja);
    glutMainLoop();
    return 0;
}