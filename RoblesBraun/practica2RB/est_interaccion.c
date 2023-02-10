#ifdef __APPLE__
#define GL_SILENCE_DEPRECATION
#include <GLUT/glut.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
#else
#include <GL/glut.h>
#endif

struct Punto{
   int cx;
   int cy;
   float color[3];
   int tamanio;
};
struct Punto p[60];
int puntos=0;
int tam=4;  // tama�o inicial del punto
GLboolean mostrar=GL_TRUE; //mostrar o no los puntos
GLboolean rojo=GL_TRUE;    // elecci�n de color

void ajusta(int ancho, int alto) {
    glClearColor(1.0,1.0,1.0,0.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, 640, 0, 480);
}
void raton(int boton, int estado, int x, int y){
    int alto_ventana=480;
    if(boton == GLUT_LEFT_BUTTON && estado == GLUT_DOWN)    {
        p[puntos].cx = x;
        p[puntos].cy = alto_ventana - y;
        p[puntos].tamanio = tam;
        p[puntos].color[0]=(rojo)?1:0;   //rojo
        p[puntos].color[1]=0;
        p[puntos].color[2]=(rojo)?0:1;   // azul
        puntos++;
    }
	glutPostRedisplay();
}
void pageUp_Down(int tecla, int x, int y) {
    switch(tecla) {
      case GLUT_KEY_PAGE_UP:   tam++;
                               break;
      case GLUT_KEY_PAGE_DOWN: tam--;
                               break;
      case GLUT_KEY_HOME: puntos=0;
    }
}
void teclado(unsigned char tecla, int x, int y){
    switch(tecla) {
      case 27:	exit(0);		// Esc =>Salir del programa
      case 'r':	rojo=GL_TRUE;  //rojo
			    break;
      case 'a':	rojo=GL_FALSE;  //azul
			    break;
      case 'm':	mostrar=!mostrar;
    }
}
void dibuja(void){
	int i;
	glClear(GL_COLOR_BUFFER_BIT);
    if (mostrar){
        for (i=0 ; i< puntos; i++)	{
            glPointSize(p[i].tamanio);
            glColor3fv(p[i].color);
            glBegin(GL_POINTS);
                glVertex2i(p[i].cx, p[i].cy);
            glEnd();
        }
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
	glutMouseFunc(raton);
	glutKeyboardFunc(teclado);
	glutSpecialFunc(pageUp_Down);
	glutReshapeFunc(ajusta);
	glutMainLoop();
	return 0;
}
