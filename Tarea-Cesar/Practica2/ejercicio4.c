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
Punto *creaPunto(int cx, int cy,float clr[3]){
    Punto *p;
    p = (Punto *)malloc(sizeof(Punto));
    p->cx = cx;
    p->cy = cy;
    p->color[0] = clr[0];
    p->color[1] = clr[1];
    p->color[2] = clr[2];
    p->sig = NULL;
    return p;
}


struct Punto *p = NULL;
float color[3] = {1,0,0};

int L = 3;


void ajusta(int ancho, int alto) {
    glClearColor(1.0,1.0,1.0,0.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, 640, 0, 480);
}


void raton(int boton, int estado, int x, int y){
    Punto *nuevo;
    int alto_ventana=480;
    if(boton == GLUT_LEFT_BUTTON && estado == GLUT_DOWN){
        nuevo = creaPunto(x, alto_ventana-y, color);
        
        if (p == NULL){
                p = nuevo;
        }
        agregaPunto(ultimaPunto(p), nuevo);
    }
    glutPostRedisplay();
}

void dibuja(void){
	Punto *a;
    a = p;
    int x0, y0, y_sig, x_sig = 0;

	glClear(GL_COLOR_BUFFER_BIT);
    if (a != NULL ){
            
            while(a != NULL){
                x0 = a->cx;
                y0 = a->cy;
                for (int i = 0; i < 10000; i++)
                {
                    x_sig = (40*(1 + 2*L)) - y0 + abs(x0 - 120);
                    y_sig = x0;
                    glColor3fv(a->color);
                    glPointSize(2);
                    glBegin(GL_POINTS);
                        glVertex2i(x_sig, y_sig);
                    glEnd();
                    x0 = x_sig;
                    y0 = y_sig; 
                }
                a = a->sig;
            }
    }
    
    glFlush();
}
void teclado(unsigned char tecla, int x, int y){
    float clr_temp[3];
    switch(tecla) {
        case 27:	
            exit(0);		// Esc =>Salir del programa
            break;
        case 'r':
            color[0] = 1;
            color[1] = 0;
            color[2] = 0; 
            
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
    }

}


int main(int argc, char** argv){
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
	glutInitWindowSize(640,480);
	glutInitWindowPosition(100, 150);
	glutCreateWindow("Ejercicio 4");
	glutDisplayFunc(dibuja);
	glutMouseFunc(raton);
	glutReshapeFunc(ajusta);
    glutKeyboardFunc(teclado);
	glutMainLoop();
	return 0;
}
