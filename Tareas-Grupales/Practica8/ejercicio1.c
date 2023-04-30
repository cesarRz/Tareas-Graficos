
#ifdef __APPLE__
#define GL_SILENCE_DEPRECATION
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <stdlib.h>

int puntos[4][2];
int puntos_index = 0;


void ajusta(int ancho, int alto) {
    glClearColor(1.0,1.0,1.0,0.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, 640, 0, 480);
}

GLfloat ptosctl[4][3] = {{-6.0, 7.0, 0.0}, {9.0, -9.0, 0.0}, {-9.0, -9.0, 0.0}, {5.0, 8.0, 0.0}};
void inicializa(void)
{
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glMap1f(GL_MAP1_VERTEX_3, 0, 1, 3, 4, &ptosctl[0][0]);
    glEnable(GL_MAP1_VERTEX_3);
}

void raton(int boton, int estado, int x, int y){
    int alto_ventana=480;

    if(boton == GLUT_LEFT_BUTTON && estado == GLUT_DOWN)    {

        if (puntos_index < 4)
        {
            puntos[puntos_index][0] = x;
            puntos[puntos_index][1] = alto_ventana - y;
            puntos_index ++;
        }
        
    }
	glutPostRedisplay();
}

void teclado(unsigned char tecla, int x, int y){
    float clr_temp[3];
    switch(tecla) {
        case 27:	
            exit(0);		// Esc =>Salir del programa
            break;
        case 'n': 
            for (int i = 0; i < 4; i++) {
                for (int j = 0; j < 2; j++) {
                    puntos[i][j] = 0; 
                }
            }
            puntos_index = 0;
            break;

    }
    glutPostRedisplay();

}

void dibuja(void){
	int i;

	glClear(GL_COLOR_BUFFER_BIT);

    // Curva de Bezier
    glLineWidth(4);
    glColor3f(0.0, 0.0, 0.0);
    glMapGrid1f(30, 0, 1);
    glEvalMesh1(GL_LINE, 0, 30);

    // Puntos de Control
    for (int i = 0; i < 4; i++)
    {
        glColor3f(1,0,0);
        glPointSize(5);
        glBegin(GL_POINTS);
            glVertex2i(puntos[i][0], puntos[i][1]);
        glEnd();
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
    inicializa();
	glutKeyboardFunc(teclado);
	glutReshapeFunc(ajusta);
	glutMainLoop();
	return 0;
}