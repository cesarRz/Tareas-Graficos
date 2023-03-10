#ifdef __APPLE__
#define GL_SILENCE_DEPRECATION
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <stdlib.h>
#include "pixelart.h"

// Figuras de Art
#define ALTO 30
#define ANCHO 30
GLubyte paleta_basketball[6][4] = {{255,255,255,0},{255,140,0,255}, {0,0,0, 255}};
GLubyte paleta_basketball_20[6][4] = {{255,255,255,0},{0,0,0,255}, {255,255,255,255}};
GLubyte basketaball[ALTO][ANCHO] = {{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,1,1,2,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,1,1,1,1,2,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,2,1,1,1,1,1,2,1,1,1,1,1,2,1,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,1,1,2,1,1,1,1,2,1,1,1,1,2,1,1,1,0,0,0,0,0,0,0},
{0,0,0,0,0,0,1,1,1,1,2,1,1,1,2,1,1,1,2,1,1,1,1,0,0,0,0,0,0,0},
{0,0,0,0,0,0,1,1,1,1,1,2,2,2,2,2,2,2,1,1,1,1,1,1,0,0,0,0,0,0},
{0,0,0,0,0,0,1,1,1,1,1,1,1,1,2,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0},
{0,0,0,0,0,1,1,1,1,1,1,1,1,1,2,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0},
{0,0,0,0,0,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,0,0,0,0,0},
{0,0,0,0,0,1,1,1,1,1,1,1,1,1,2,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0},
{0,0,0,0,0,1,1,1,1,1,1,1,1,1,2,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0},
{0,0,0,0,0,0,1,1,1,1,1,1,1,1,2,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0},
{0,0,0,0,0,0,1,1,1,1,1,1,1,1,2,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0},
{0,0,0,0,0,0,1,1,1,1,1,2,2,2,2,2,2,2,1,1,1,1,1,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,1,1,1,2,1,1,1,2,1,1,1,2,1,1,1,1,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,1,2,1,1,1,1,2,1,1,1,1,2,1,1,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,1,1,1,1,1,2,1,1,1,1,1,2,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,1,1,1,1,2,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,1,1,2,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}};


int base_x = 320;
int base_y = 240;

GLboolean paleta = GL_TRUE;


void ajusta(int ancho, int alto) {
    glClearColor(1.0,1.0,1.0,0.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, 640, 0, 480);
}

void pageUp_Down(int tecla, int x, int y) {
    switch(tecla) {
        case GLUT_KEY_UP:   
        base_y+= 10;
        paleta = !paleta;
        break;
        case GLUT_KEY_DOWN: 
        base_y-= 10;
        paleta = !paleta;
        break;
        case GLUT_KEY_RIGHT: 
        base_x+= 10;
        paleta = !paleta;
        break;
        case GLUT_KEY_LEFT: 
        base_x-= 10;
        paleta = !paleta;
        break;
    }
    glutPostRedisplay();
}

void dibuja(void){
	glClear(GL_COLOR_BUFFER_BIT);
    if (paleta)
    {
        pixelArt(basketaball, paleta_basketball, base_x, base_y, 5);
    }else
    {
        pixelArt(basketaball, paleta_basketball_20, base_x, base_y, 5);
    }
    
    
    glFlush();
}
int main(int argc, char** argv){
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
	glutInitWindowSize(640,480);
	glutInitWindowPosition(100, 150);
	glutCreateWindow("Dibujando puntos estructuras");
	glutDisplayFunc(dibuja);
	glutSpecialFunc(pageUp_Down);
	glutReshapeFunc(ajusta);
	glutMainLoop();
	return 0;
}
