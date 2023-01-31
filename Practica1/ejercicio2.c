#ifdef __APPLE__
#define GL_SILENCE_DEPRECATION
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <math.h>

void ajusta () {
    glClearColor(0.9, 0.9, 0.9, 0.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, 640, 0, 480);
}

void dibuja(void)
{
    GLboolean colorBlanco = GL_TRUE;  
    float azul[]={0.0, 0.0, 0.9};
    float negro[]={0.0, 0.0, 0.0};
    glClear(GL_COLOR_BUFFER_BIT);
    // Habilitamos la linea punteada
    glEnable(GL_LINE_STIPPLE);
    glLineStipple(2, 0xCCCC);
    for (int i = 1; i < (640); i += 20){
        for (int j = 1; j < (480); j += 20){
            glColor3fv(azul);
            glBegin(GL_LINE_LOOP);
                glVertex2i(i, j);
                glVertex2i(i, j + 20);
                glVertex2i(i + 20, j + 20);
                glVertex2i(i + 20, j);
            glEnd();
            // glRecti(i, j, i + 20, j + 20);
        }
    }
    glDisable(GL_LINE_STIPPLE);
    //Cambiamos a color negro
    glColor3fv(negro);
    // Creamos el eje
    glLineWidth(2);
    glBegin(GL_LINES);
        glVertex2i(0, 240);
        glVertex2i(640, 240);
        glVertex2i(320, 480);
        glVertex2i(320, 0);
    glEnd();
    // Graficamos coseno
    glPointSize(3);
    glBegin(GL_LINE_STRIP);
        for (float i = -1.5; i <= 1.5; i+= 0.1)
        {
            float x = (float)i*640 + 320 ; 
            float y = 480 * cos(i);
            glVertex2f(x, y);
        }
    glEnd();
    glFlush();
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(640,480);
    glutInitWindowPosition(100, 150);
    glutCreateWindow("Titulo");
    glutReshapeFunc(ajusta);
    glutDisplayFunc(dibuja);
    glutMainLoop();
    return 0;
}