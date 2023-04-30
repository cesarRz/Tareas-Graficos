#ifdef __APPLE__
#define GL_SILENCE_DEPRECATION
#include <stdio.h>
#include <stdlib.h>
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif


GLfloat ctrlPoints[7][3];
int points = 0;

void inicializa(void){
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glMap1f(GL_MAP1_VERTEX_3, 0, 1, 3, points, &ctrlPoints[0][0]);
    glEnable(GL_MAP1_VERTEX_3);
}

void raton(int button, int state, int x, int y){
    if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN){
        ctrlPoints[points][0] = x;
        ctrlPoints[points][1] = 480 - y;
        ctrlPoints[points][2] = 0;
        points++;
    }
    if(points == 7){
        glutMouseFunc(NULL);
        glutKeyboardFunc(NULL);
    }
    glutPostRedisplay();
}

void teclado(unsigned char tecla, int x, int y){
    switch(tecla) {
        // Salir del programa
        case 27:
            exit(0);
            break;
        // Para borrar puntos
        case 127:
            points--;
            glutPostRedisplay();
            break;
        // Dejar de poner puntos
        case 'f': 
            glutMouseFunc(NULL);
            glutKeyboardFunc(NULL);
    }
}

void dibuja(void){
    inicializa();
    glClear(GL_COLOR_BUFFER_BIT);
    //Se dibuja la curva
    glLineWidth(2);
    glColor3ub(114, 9, 183);
    if(points > 1) {
        glMapGrid1f(50, 0, 1);
        glEvalMesh1(GL_LINE, 0, 50);
    }
    // puntos de control
    glPointSize(4);
    glColor3ub(67, 97, 238);
    glBegin(GL_POINTS);
    for (int i = 0; i < points; i++){
        glVertex3fv(&ctrlPoints[i][0]);
    }
    glEnd();
    glFlush();
}

void ajusta(int height, int width){
    glViewport(0, 0, height, width);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, height, 0, width, -2, 2);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

int main(int argc, char** argv){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(550, 480);
    glutInitWindowPosition (100, 100);
    glutCreateWindow("Bezier interactivo");
    glutDisplayFunc(dibuja);
    glutReshapeFunc(ajusta);
    glutMouseFunc(raton);
    glutKeyboardFunc(teclado);
    glutMainLoop();
    return 0;
}
