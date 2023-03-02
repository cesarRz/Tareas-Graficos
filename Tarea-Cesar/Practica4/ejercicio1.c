#ifdef __APPLE__
#define GL_SILENCE_DEPRECATION
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "matriz.h"

int tamano_lateral = 100;
float coordenadas[4][3];

void assign_base(int base_x, int base_y){
    coordenadas[0][0] = base_x;
    coordenadas[0][1] = base_y;
    coordenadas[0][2] = 1;
    coordenadas[1][0] = base_x + tamano_lateral;
    coordenadas[1][1] = base_y;
    coordenadas[1][2] = 1;
    coordenadas[2][0] = ((tamano_lateral * 0.2) + base_x + tamano_lateral);
    coordenadas[2][1] = (base_y + (tamano_lateral / 2));
    coordenadas[2][2] = 1;
    coordenadas[3][0] = ((tamano_lateral * 0.2) + base_x);
    coordenadas[3][1] = (base_y + (tamano_lateral / 2));
    coordenadas[3][2] = 1;
}

float Traslacion[3][3];
float Escalamiento[3][3];

void creaT(float dx, float dy) {

    for(int i = 0; i < 3; i++) {
        for(int j = 0; j < 3; j++) {
            if(i == j) {
                Traslacion[i][j] = 1.0;
            } else {
                Traslacion[i][j] = 0.0;
            }
        }
    }

    Traslacion[0][2] = dx;
    Traslacion[1][2] = dy;
}


void assign_escalamiento(float x, float y) 
{
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (i == 0  && j == 0)
                Escalamiento[i][j] = x;
            else if (i == 1 && j == 1)
                Escalamiento[i][j] = y;
            else if ((i == 2 && j == 2))
                Escalamiento[i][j] = 1;
            else
                Escalamiento[i][j] = 0;

}

void dibuja_romboide(){

    glColor3ub(0,0,255);

    glBegin(GL_QUADS);

    for (int i = 0; i < 4; i++){
        glVertex2d(coordenadas[i][0], coordenadas[i][1]);
    }

    glEnd();

}

void ajusta () {
    glClearColor(0.9, 0.9, 0.9, 0.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, 640, 0, 480);
}

void mueve_y(){

       // Cambia las coordenadas de la figura
    for (int i = 0; i < 4; i++)
        if (coordenadas[i][1] != 0)
            coordenadas[i][0] = -coordenadas[i][0];

    creaT(400,0);
    float mr[4][1];
    float m[1][3];
    for (int i = 0; i < 4; i++)
    {
        m[0][0] = coordenadas[i][0];
        m[0][1] = coordenadas[i][1];
        m[0][2] = 1;
        multiplica(1,3,3,Traslacion, m, mr);
        coordenadas[i][0] = mr[0][0];
        coordenadas[i][1] = mr[0][1];
    }


}

void mueve_x(){

    // Cambia las coordenadas de la figura
    for (int i = 0; i < 4; i++)
        if (coordenadas[i][1] != 0)
            coordenadas[i][1] = -coordenadas[i][1];
         
    // Crea Matriz de Traslacion
    creaT(0,400);
    imprime(3,3,Traslacion);

    // Multiplica matrices
    float mr[4][1];
    float m[1][3];
    for (int i = 0; i < 4; i++)
    {
        m[0][0] = coordenadas[i][0];
        m[0][1] = coordenadas[i][1];
        m[0][2] = 1;
        multiplica(1,3,3,Traslacion, m, mr);
        coordenadas[i][0] = mr[0][0];
        coordenadas[i][1] = mr[0][1];
    }
    printf("Coordenadas nuevas\n");
    imprime(4,2,coordenadas);
    
}

void teclado(unsigned char tecla, int x, int y){
    switch (tecla)
    {
    case 'x':
        mueve_x();    
        break;
    case 'y':
        mueve_y();
        break;
    
    default:
        break;
    }
    glutPostRedisplay();
}

void teclado_especial(int tecla, int x, int y){
    
    
    switch (tecla)
    {
    case GLUT_KEY_DOWN:
        assign_escalamiento(0.8, 0.8);
        printf("Coordenadas\n");
        imprime(4,2,coordenadas);
        printf("Escalamiento\n");
        imprime(3,3,Escalamiento);
        multiplica(3,4,3,coordenadas, Escalamiento, coordenadas);
        
        printf("Coordenadas\n");
        imprime(4,2,coordenadas);

    break;

    case GLUT_KEY_UP:

        assign_escalamiento(1.2, 1.2);
        printf("Coordenadas\n");
        imprime(4,2,coordenadas);
        printf("Escalamiento\n");
        imprime(3,3,Escalamiento);
        multiplica(3,4,3,coordenadas, Escalamiento, coordenadas);
        
        printf("Coordenadas\n");
        imprime(4,3,coordenadas);

    break;
    }

    glutPostRedisplay();
}

void dibuja(){
    glClear(GL_COLOR_BUFFER_BIT);
    dibuja_romboide();
    glFlush();
}

int main(int argc, char** argv)
{

    const int base_x = 200;
    const int base_y = 200;
    assign_base(base_x, base_y);
    imprime(4,2,coordenadas);

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(640,480);
    glutInitWindowPosition(100, 150);
    glutCreateWindow("Ejercicio 1");
    glutKeyboardFunc(teclado);
    glutSpecialFunc(teclado_especial);
    glutReshapeFunc(ajusta);
    glutDisplayFunc(dibuja);
    glutMainLoop();
    return 0;
}