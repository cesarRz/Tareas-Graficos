#ifdef __APPLE__
#define GL_SILENCE_DEPRECATION
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

void ajusta () {
    glClearColor(0.8, 0.9, 0.005, 0.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, 640, 0, 480);
}

void dibuja(){
    glClear(GL_COLOR_BUFFER_BIT);

    // Cuadilatero
    glBegin(GL_QUADS);
        glColor3ub(235, 52, 232);
        glVertex2i(100,100);
        glVertex2i(100,200);
        glVertex2i(200,200);
        glVertex2i(200,100); 
    glEnd();

    // Pentagono Wireframe
    glLineWidth(3);
    glBegin(GL_LINE_LOOP);
        glColor3ub(0,0,255);
        glVertex2i(100,250);
        glVertex2i(200,250);
        glVertex2i(200,350);
        glVertex2i(150,400);
        glVertex2i(100,350);
    glEnd();

    // Pentagono Solido
    glLineWidth(3);
    glBegin(GL_POLYGON);
        glColor3ub(0,255,0);
        glVertex2i(300,250);
        glVertex2i(400,250);
        glVertex2i(400,350);
        glVertex2i(350,400);
        glVertex2i(300,350);
    glEnd();


    // Pentagono Lineas punteadas
    glLineWidth(3);
    glEnable(GL_LINE_STIPPLE);
    glLineStipple(2,0xFFFA);
    glBegin(GL_LINE_LOOP);
        glColor3ub(86, 52, 235);
        glVertex2i(300 + 200,250);
        glVertex2i(400 + 200,250);
        glVertex2i(400 + 200,350);
        glVertex2i(350 + 200,400);
        glVertex2i(300 + 200,350);
    glEnd();
    glDisable(GL_LINE_STIPPLE);


    // Pentagono Gouraud
    glLineWidth(3);
    glBegin(GL_TRIANGLE_FAN);
        glColor3ub(100, 50, 200);
        glVertex2i(300 + 200,250 - 200);
        glVertex2i(400 + 200,250 - 200);
        glVertex2i(400 + 200,350 - 200);
        glColor3ub(86, 204, 240);
        glVertex2i(350 + 200,400 - 200);
        glColor3ub(86, 240, 155);
        glVertex2i(300 + 200,350 - 200);
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