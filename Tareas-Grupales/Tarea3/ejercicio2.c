#ifdef __APPLE__
#define GL_SILENCE_DEPRECATION
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>


int puntos_fin[2];
int pos_x[60], pos_y[60];
int puntos = 0;
GLboolean fin = GL_FALSE;


void ajusta(int ancho, int alto)
{
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, 640.0, 0.0, 480.0);
}
void raton(int boton, int estado, int x, int y)
{
    int alto_ventana = 480;

        if (boton == GLUT_LEFT_BUTTON && estado == GLUT_DOWN)
        {
            if (fin)
            { 
                puntos_fin[0] = x;
                puntos_fin[1] = alto_ventana - y;

            }else{
                pos_x[puntos] = x;
                pos_y[puntos] = alto_ventana - y; // voltea la coordenada y
                puntos++;
            }
            
        }
        glutPostRedisplay();
}

void delete_last() {
    if (puntos > 0) {
            puntos--;
        }
        glutPostRedisplay();
}

void termina(int tecla, int x, int y)
{
    switch (tecla)
    {
    case GLUT_KEY_UP:
        fin = GL_TRUE;
        break;
    case GLUT_KEY_DOWN:
        puntos = 0;
        fin = GL_FALSE;
        break;
    case GLUT_KEY_LEFT:
        if (!fin)
            delete_last();
    }
    glutPostRedisplay();
}
void teclado(unsigned char tecla, int x, int y)
{
    if (tecla == 27)
        exit(0); // Esc =>Salir del programa
}

bool ccw(int a, int b, int c)
{
    if (fin)
    {
        double area2 = (pos_x[b] - pos_x[a]) * (puntos_fin[1] - pos_y[a]) - (pos_y[b] - pos_y[a]) * (puntos_fin[0] - pos_x[a]);
        return area2 >= 0;
    }else
    {
        double area2 = (pos_x[b] - pos_x[a]) * (pos_y[c] - pos_y[a]) - (pos_y[b] - pos_y[a]) * (pos_x[c] - pos_x[a]);
        return area2 >= 0;
    }
    
}
    
void dibuja(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0, 0, 0);
    glPointSize(4);
    int i;
    if (puntos > 2)
    {
        i = 0;
        while (ccw(i % puntos, (i + 1) % puntos, (i + 2) % puntos) && i < puntos + 2)
            i++;
        (i == puntos + 2) ? glColor3f(0, 1, 0) : glColor3f(1, 0, 0);
    }
    glBegin(GL_POINTS);
    for (i = 0; i < puntos; i++)
        glVertex2i(pos_x[i], pos_y[i]);
    glEnd();
    glBegin(fin ? GL_LINE_LOOP : GL_LINE_STRIP);
    for (i = 0; i < puntos; i++)
        glVertex2i(pos_x[i], pos_y[i]);
    glEnd();


    

    // Dibuja puntos extras
        glBegin(GL_POINTS);
    if (fin){
            
        if (puntos > 2)
        {
            i = 0;
            while (ccw(i % puntos, (i + 1) % puntos, (i + 2) % puntos) && i < puntos + 2)
                i++;
            (i == puntos + 2) ? glColor3f(0, 1, 0) : glColor3f(1, 0, 0);
        }
            
        glVertex2i(puntos_fin[0], puntos_fin[1]);
    }
        glEnd();


    glFlush();
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
    glutInitWindowSize(640, 480);
    glutInitWindowPosition(100, 150);
    glutCreateWindow("Poligono convexo");
    // Registro de funciones
    glutDisplayFunc(dibuja);
    glutMouseFunc(raton);
    glutKeyboardFunc(teclado);
    glutSpecialFunc(termina);
    glutReshapeFunc(ajusta);
    glutMainLoop();
    return 0;
}