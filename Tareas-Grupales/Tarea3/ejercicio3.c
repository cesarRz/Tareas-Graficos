#ifdef __APPLE__
#define GL_SILENCE_DEPRECATION
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <math.h>

double n = 10000;


void teclado(unsigned char tecla, int x, int y){
    switch(tecla) {
        case 27:	
            exit(0);		// Esc =>Salir del programa
            break;
        case 43:
            n += 10000;
            glutPostRedisplay();
            break;
        case 45:
            n -= 10000;
            glutPostRedisplay();
            break;
        
    }
}

int aleatorio(int min, int max) {
    int random_number = (rand() % (max - min + 1)) + min;
    return random_number;
}

void printtext(char c[]){
    glRasterPos2i(500, 240);
    for(int i = 0; i < strlen(c); i++){
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_10, c[i]);
    }
}


void Bresenham(int centro_x, int centro_y, int radio){
    int x = 0;
    int y = radio;
    int e = 3 - 2 * radio;

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

void ajusta () {
    glClearColor(0.9, 0.9, 0.9, 0.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, 640, 0, 480);
}

void base_ejercicio(){

    glColor3ub(255,0,0);
    glBegin(GL_LINES);
        glVertex2i(480, 0);
        glVertex2i(480,480);
    glEnd();
    glColor3ub(0,0,255);
    Bresenham(240, 240, 240);
}


void dibuja(){
    glClear(GL_COLOR_BUFFER_BIT);
    glPointSize(3);

    base_ejercicio();

    int x_centro = 480 / 2;
    int y_centro = 480 / 2;
    int radio = 240;
    double puntos_dentro = 0;
    double pi = 0;

    for (int i = 0; i < n; i++)
    {
        int x = aleatorio(0,480);
        int y = aleatorio(0,480);
        GLboolean dentro = GL_FALSE;

        printf("%d, %d", x, y);

        glBegin(GL_POINTS);
            if (pow(x - x_centro,2) + pow(y - y_centro,2) < pow(radio,2))
            {
                dentro = GL_TRUE;
                puntos_dentro ++;
                glColor3ub(0,255,0);
            }else
            {
                glColor3ub(255,0,0);
            }
            
            
            glVertex2i(x, y);
        glEnd();

    }

    glColor3ub(0,0,0);
    pi = 4*(puntos_dentro/n);

    char pi_char[20];
    sprintf(pi_char,"PI = %f", pi);

    printtext(pi_char);

    
    glFlush();
}

int main(int argc, char** argv)
{
    srand(time(NULL));

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(640,480);
    glutInitWindowPosition(100, 150);
    glutCreateWindow("Titulo");
    glutReshapeFunc(ajusta);
    glutDisplayFunc(dibuja);
    glutKeyboardFunc(teclado);
    glutMainLoop();
    return 0;
}