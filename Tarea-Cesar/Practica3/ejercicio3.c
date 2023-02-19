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

int base_x = 245; // Mitad de la tabla menos mitad de dibujo
int base_y = 115; // Mitad de la tabla menos mitad de dibujo

int letra_solida[16][2] = {{150,100},{100,100},{150,50},{100,50},{100,0},{50,50},{50,0},{0,50},{50,200},{0,200},{50,250},{100,200},{100,250},{150,200},{100,150}, {150,150}};

void dibuja_letra(int tipo, int base_x, int base_y){
    glLineWidth(5);
    // Letra Solida
    glBegin(GL_TRIANGLE_STRIP);
        glColor3ub(0,0,255);
        for (int i = 0; i < 16; i++)
        {
            glVertex2i(letra_solida[i][0] + base_x,letra_solida[i][1] + base_y);
        } 
    glEnd();
}


void mueve_letra(int tecla, int x1, int y1) {
    switch(tecla) {
        case GLUT_KEY_UP:
            if ((letra_solida[12][1] + base_y) <= 480) {
               base_y = base_y + 10;
            }
            break;
        case GLUT_KEY_DOWN:
            if ((letra_solida[6][1] + base_y) >= 0) {
               base_y = base_y - 10;
            }
            break;
        case GLUT_KEY_LEFT:
            if ((letra_solida[7][0] + base_x) >= -40) {
                base_x = base_x - 10;
            }
            else
            {
                base_x = 480+160;
            }
            break;
        case GLUT_KEY_RIGHT:
            if ((letra_solida[15][0] + base_x) <= 680) {
                base_x = base_x + 10;
            }
            else
            {
                base_x = -150;
            }
            
            break;
    }
    glutPostRedisplay();
}


void dibuja(){
    glClear(GL_COLOR_BUFFER_BIT);

    // Code
    dibuja_letra(1,base_x, base_y);

    glutSwapBuffers();
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(640,480);
    glutInitWindowPosition(100, 150);
    glutCreateWindow("Ejercicio 3: Letra");
    glutReshapeFunc(ajusta);
    glutDisplayFunc(dibuja);
    glutSpecialFunc(mueve_letra);
    glutMainLoop();
    return 0;
}