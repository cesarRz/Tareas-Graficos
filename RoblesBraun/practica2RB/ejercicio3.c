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

// Arreglo de 8 colores
float colors[8][3] = {
    {1.0, 0.0, 0.0},
    {0.0, 1.0, 0.0},
    {0.0, 0.0, 1.0},
    {1.0, 1.0, 0.0},
    {0.5, 0.0, 0.5},
    {0.0, 1.0, 1.0},
    {1.0, 0.6470588235, 0.0},
    {1.0, 0.7529411765, 0.8}
};

void ajusta () {
    glClearColor(0.9, 0.9, 0.9, 0.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, 640, 0, 480);
}

void dibujaTexto(void *tipo, char *s) {
    for (int i = 0; i < strlen(s); i++)
        glutBitmapCharacter(tipo, s[i]);
}

int getRandomNumber() {
    return rand() % 8;
}

void leerArchivo(int x, int y) {
    char c;
    FILE * fp;
    fp = fopen("../tarea1/logoRB.txt", "r");

    if(fp == NULL) {
        printf("No se puede leer archivo");
    }
    else
    {
        while((c = fgetc(fp)) != EOF){
            // printf("%c", c);
            if(c == '\n'){
                y = y - 18;
                glRasterPos2i(x, y);
            }
            dibujaTexto(GLUT_BITMAP_HELVETICA_18, &c);
        }
        fclose(fp);
    }
}

void dibuja(void)
{
    int x = 50;
    int y = 260;
    int rnd = 0;
    float c[3] = {1.0, 0.0, 0.0};
    glClear(GL_COLOR_BUFFER_BIT);
    srand(time(NULL));
    for (int i = 0; i < 6; i++)
    {
        rnd = getRandomNumber();
        printf("%d \n", rnd);
        c[0] = colors[rnd][0];
        c[1] = colors[rnd][1];
        c[2] = colors[rnd][2];
        glColor3fv(c);
        glRasterPos2i(x, y);
        leerArchivo(x, y);
        x = x + 100;
    }
    glFlush();
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(640,480);
    glutInitWindowPosition(100, 150);
    glutCreateWindow("Practica 1 - Ejercicio 4");
    glutReshapeFunc(ajusta);
    glutDisplayFunc(dibuja);
    glutMainLoop();
    return 0;
}