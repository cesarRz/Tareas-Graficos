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

void Bresenham(int centro_x, int centro_y, int radio){
    int e, x,y = 0;
    y = radio;

    e = 3 -2*radio;

    glBegin(GL_POINTS);
    while (x < y)
    {
        glVertex2i(centro_x + x, centro_y + y );
        glVertex2i(centro_x + y, centro_y + x );
        glVertex2i(centro_x - x, centro_y + y );
        glVertex2i(centro_x - y, centro_y + x );
        glVertex2i(centro_x + x, centro_y - y );
        glVertex2i(centro_x + y, centro_y - x );
        glVertex2i(centro_x - x, centro_y - y );
        glVertex2i(centro_x - y, centro_y - x );

        if (e > 0)
        {
            e = e + 4*(x-y) + 10;
            y = y-1;
        }else
        {
            e = e +4*x+6;
        }
            x = x+1;
    }
    if (x == y)
    {
        glVertex2i(centro_x + x, centro_y + y );
        glVertex2i(centro_x + y, centro_y + x );
        glVertex2i(centro_x - x, centro_y + y );
        glVertex2i(centro_x - y, centro_y + x );
        glVertex2i(centro_x + x, centro_y - y );
        glVertex2i(centro_x + y, centro_y - x );
        glVertex2i(centro_x - x, centro_y - y );
        glVertex2i(centro_x - y, centro_y - x );
    }
    


    glEnd();

}

void dibuja(){
    glClear(GL_COLOR_BUFFER_BIT);
    Bresenham(320,240, 50);
    glFlush();
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(640,480);
    glutInitWindowPosition(100, 150);
    glutCreateWindow("Ejercicio 1");
    glutReshapeFunc(ajusta);
    glutDisplayFunc(dibuja);
    glutMainLoop();
    return 0;
}