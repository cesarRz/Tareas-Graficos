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
Punto *creaPunto(int cx, int cy,float clr[3], int tamanio){
    Punto *p;
    p = (Punto *)malloc(sizeof(Punto));
    p->cx = cx;
    p->cy = cy;
    p->color[0] = clr[0];
    p->color[1] = clr[1];
    p->color[2] = clr[2];
    p->tamanio = tamanio;
    p->sig = NULL;
    return p;
}


struct Punto *p = NULL;
int tam=4;  // tama�o inicial del punto
GLboolean mostrar=GL_TRUE; //mostrar o no los puntos
GLboolean edit = GL_FALSE;
float color[3] = {1,0,0};
char tecla_global;

void cambiaColor(float clr[3]){

    if (edit)
    {
        Punto *a = ultimaPunto(p);
        a->color[0] = clr[0];
        a->color[1] = clr[1];
        a->color[2] = clr[2];
    }else{
        color[0] = clr[0];
        color[1] = clr[1];
        color[2] = clr[2];
    }
    glutPostRedisplay();

    
}

void aumentaTam(){

    if (edit)
    {
        Punto *a = ultimaPunto(p);
        a->tamanio ++;
    }else{
        tam++;
    }
    glutPostRedisplay();
}

void reduceTam(){

    if (edit)
    {
        Punto *a = ultimaPunto(p);
        a->tamanio --;
    }else{
        tam--;
    }
    glutPostRedisplay();
}

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

        nuevo = creaPunto(x, alto_ventana-y, color, tam);
        
        if (p == NULL){
                p = nuevo;
        }
        agregaPunto(ultimaPunto(p), nuevo);
    }
	glutPostRedisplay();
}
void pageUp_Down(int tecla, int x, int y) {
    switch(tecla) {
        case GLUT_KEY_PAGE_UP:   aumentaTam();
                               break;
        case GLUT_KEY_PAGE_DOWN: reduceTam();
                               break;
        case GLUT_KEY_HOME: p = NULL;
                               break;
    }
}

void teclado(unsigned char tecla, int x, int y){
    float clr_temp[3];
    switch(tecla) {
        case 27:	
            exit(0);		// Esc =>Salir del programa
            break;
        case 'r':
            clr_temp[0] = 1;
            clr_temp[1] = 0;
            clr_temp[2] = 0; 
            cambiaColor(clr_temp);
		    break;
        case 'b':
            clr_temp[0] = 0;
            clr_temp[1] = 0;
            clr_temp[2] = 1;  //azul
            cambiaColor(clr_temp);
			break;
        case 'g':
            clr_temp[0] = 0;
            clr_temp[1] = 1;
            clr_temp[2] = 0;  //verde
            cambiaColor(clr_temp);
            break;
        case 'o':
            clr_temp[0] = 1;
            clr_temp[1] = 0.6471;
            clr_temp[2] = 0;  //naranja
            cambiaColor(clr_temp);
            break;
        case 'm':	
            mostrar=!mostrar;                
            break;
        case 'e':
            edit = (edit)?GL_FALSE:GL_TRUE;

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
            while(a != NULL){
                glColor3fv(a->color);
                glPointSize(a->tamanio);
                    glVertex2i(a->cx, a->cy);
                a = a->sig;
            }
            glEnd();

            a = p;
            while(a != NULL){
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
