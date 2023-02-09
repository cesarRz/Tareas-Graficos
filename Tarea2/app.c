#ifdef __APPLE__
#define GL_SILENCE_DEPRECATION
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <stdio.h>


void ajusta() {
    glClearColor(0.9, 0.9, 0.9, 0.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, 640, 0, 480);
}

void circuloBressenham(int base_x, int base_y, int diametro){
    float radio = (diametro/2);
    float centro_x = base_x + radio; // 110
    float centro_y = base_y + radio; // 110
    glColor3ub(0,0,0);
    glPointSize(10);

    int x,y,e;
    x = radio; //100
    y = 0;
    e = 0;
    int i = 0;
    int a = 1;
    while (y <= x){
        glBegin(GL_POINTS);
            // Primer cuadrante
            glVertex2i(centro_x + x, centro_y + y); // 210, 210
            glVertex2i(centro_x + y, centro_y + x); // 210, 210
            // Segundo Cuadrante
            glVertex2i(centro_x - x, centro_y + y);
            glVertex2i(centro_x - y, centro_y + x);
            // Tercer cuadrante
            glVertex2i(centro_x - x, centro_y - y);
            glVertex2i(centro_x - y, centro_y - x);
            // Cuarto cuadrante
            glVertex2i(centro_x + x, centro_y - y);
            glVertex2i(centro_x + y, centro_y - x);
        glEnd();

        e = e + 2*y + a;
        y = y + a;

        int p1 = 2*e;
        int p2 = 2*x-1;

        if (p1 > p2)
        {
            x = x-a;
            e = e - 2*x + a;
        }

        i +=1;

    }

    printf("%d\n", i);

}


void dibuja(){
    glClear(GL_COLOR_BUFFER_BIT);
    // Code
    circuloBressenham(10,10, 200);
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