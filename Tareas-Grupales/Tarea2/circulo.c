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


void circulo(int r, int centro_x, int centro_y){
    int  x = 0;
    int y = r;
    int d = 3 - (2*r);
    
    glColor3ub(0,0,0);

    for (int i = 0; i < 15; i++){
        glVertex2d(centro_x + x,centro_y + y);
        glVertex2d(centro_x - x,centro_y - y);
        glVertex2d(centro_x - x,centro_y + y);
        glVertex2d(centro_x + x,centro_y - y);
        glVertex2d(centro_x + y,centro_y + x);
        glVertex2d(centro_x - y,centro_y - x);
        glVertex2d(centro_x - y,centro_y + x);
        glVertex2d(centro_x + y,centro_y - x);

        if (d > 0)
        {
            d = d + (4 * (x -y)) + 10;
            y -= 20;
        }else
        {
            d = d+ 4*x + 6;
        }
        
        x += 20;
    }
    if (x == y)
    {
        glVertex2d(centro_x + x,centro_y + y);
        glVertex2d(centro_x - x,centro_y - y);
        glVertex2d(centro_x - x,centro_y + y);
        glVertex2d(centro_x + x,centro_y - y);
        glVertex2d(centro_x + y,centro_y + x);
        glVertex2d(centro_x - y,centro_y - x);
        glVertex2d(centro_x - y,centro_y + x);
        glVertex2d(centro_x + y,centro_y - x);
    }
    
}

void dibuja(){
    glClear(GL_COLOR_BUFFER_BIT);
    glPointSize(5);
    glBegin(GL_POINTS);
        circulo(100, 320, 240);
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