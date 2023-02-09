// 1. Toma como base el programa de est_interacción.c, para trazar líneas que unan los puntos (dibuja lineas y puntos). Usa una lista ligada y maneja al menos 4 colores.

#ifdef __APPLE__
#define GL_SILENCE_DEPRECATION
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <stdlib.h>

struct Punto{
   int cx;
   int cy;
   float color[3];
   int tamanio;
   struct Punto *sig;
};

typedef struct Punto Punto;

// Funciones para manejo de estructuras
struct Punto *ultimaPunto(Punto *lista){
    Punto *p;
    p = lista;
    while (p->sig != NULL)
    {
        p = p->sig;
    }
    return p;
}
void agregaPunto(Punto *anterior, Punto *nuevo){
    if (anterior->sig == NULL)
    {
        anterior->sig = nuevo;
        nuevo->sig = NULL;
    }
    else
    {
        nuevo->sig = anterior->sig;
        anterior->sig = nuevo;
    }
}
Punto *creaPunto(int cx, int cy,float color[3], int tamanio){
    Punto *p;
    p = (Punto *)malloc(sizeof(Punto));
    p->cx = cx;
    p->cy = cy;
    p->color[0] = color[0];
    p->color[1] = color[1];
    p->color[2] = color[2];
    p->tamanio = tamanio;
    p->sig = NULL;
    return p;
}


struct Punto *p = NULL;
int puntos=0;
int tam=4;  // tama�o inicial del punto
GLboolean mostrar=GL_TRUE; //mostrar o no los puntos
float color[3] = {1,0,0};

void ajusta(int ancho, int alto) {
    glClearColor(1.0,1.0,1.0,0.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, 640, 0, 480);
}
void raton(int boton, int estado, int x, int y){
    int alto_ventana=480;
    Punto *nuevo;

    if(boton == GLUT_LEFT_BUTTON && estado == GLUT_DOWN)    {

        // float clr[3] = {(rojo)?1:0,0,(rojo)?0:1};

        nuevo = creaPunto(x, alto_ventana-y, color, tam);
        
        if (p == NULL){
                p = nuevo;
        }
        agregaPunto(ultimaPunto(p), nuevo);

        // p[puntos].cx = x;
        // p[puntos].cy = alto_ventana - y;
        // p[puntos].tamanio = tam;
        // p[puntos].color[0]=(rojo)?1:0;   //rojo
        // p[puntos].color[1]=0;
        // p[puntos].color[2]=(rojo)?0:1;   // azul
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
        case 27:	
            exit(0);		// Esc =>Salir del programa
            break;
        case 'r':
                color[0] = 1;
                color[1] = 0;
                color[2] = 0;  //rojo
			    break;
        case 'b':	
                color[0] = 0;
                color[1] = 0;
                color[2] = 1;  //azul
			    break;
        case 'g':	
                color[0] = 0;
                color[1] = 1;
                color[2] = 0;  //verde
			    break;
        case 'o':	
                color[0] = 1;
                color[1] = 0.6471;
                color[2] = 0;  //naranja
			    break;
        case 'm':	mostrar=!mostrar;
    }
}
void dibuja(void){
	int i;
    Punto *a;
    a = p;
	glClear(GL_COLOR_BUFFER_BIT);
    if (a != NULL )
    {
        if (mostrar){
            glBegin(GL_LINE_STRIP);
            for (i=0 ; i< puntos; i++)	{
                glColor3fv(a->color);
                glPointSize(a->tamanio);
                    glVertex2i(a->cx, a->cy);
                a = a->sig;
            }
            glEnd();

            a = p;
            for (i=0 ; i< puntos; i++)	{
                glColor3fv(a->color);
                glPointSize(a->tamanio);
                glBegin(GL_POINTS);
                    glVertex2i(a->cx, a->cy);
                    a = a->sig;
                glEnd();
            }
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
