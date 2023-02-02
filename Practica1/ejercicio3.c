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


void dibuja_letra(int tipo, int base_x, int base_y){
    
    int letra_wire[16][2] = {{0,50},{0,200},{50,250},{100,250},{150,200},{150,150},{100,150},{100,200},{50,200},{50,50},{100,50},{100,100},{150,100},{150,50},{100,0},{50,0}};
    int letra_solida[16][2] = {{150,100},{100,100},{150,50},{100,50},{100,0},{50,50},{50,0},{0,50},{50,200},{0,200},{50,250},{100,200},{100,250},{150,200},{100,150}, {150,150}};

    glLineWidth(5);
    if (tipo == 1)
    {   
        // LETRA WIREFRAME
        glBegin(GL_LINE_LOOP);
            glColor3ub(0,0,255);
            for (int i = 0; i < 16; i++)
            {
                glVertex2i(letra_wire[i][0] + base_x,letra_wire[i][1] + base_y);
            }
        glEnd();
    }else
    {
        // Letra Solida
        glBegin(GL_TRIANGLE_STRIP);
            glColor3ub(0,0,255);
            for (int i = 0; i < 16; i++)
            {
                glVertex2i(letra_solida[i][0] + base_x,letra_solida[i][1] + base_y);
            } 
        glEnd();
    }
}


void dibuja(){
    glClear(GL_COLOR_BUFFER_BIT);
    // Code
    
    int base_x = 245; // Mitad de la tabla menos mitad de dibujo
    int base_y = 115; // Mitad de la tabla menos mitad de dibujo


    dibuja_letra(0,base_x-100, base_y);
    dibuja_letra(1,base_x+100, base_y);


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