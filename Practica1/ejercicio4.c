#ifdef __APPLE__
#define GL_SILENCE_DEPRECATION
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

void ajusta () {
    glClearColor(0.9, 0.9, 0.9, 0.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, 640, 0, 480);
}

void dibuja(){
    glClear(GL_COLOR_BUFFER_BIT);
    // Code

    glFlush();
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(640,480);
    glutInitWindowPosition(100, 150);
    glutCreateWindow("Ejercicio 4");
    glutReshapeFunc(ajusta);
    glutDisplayFunc(dibuja);
    glutMainLoop();
    return 0;
}