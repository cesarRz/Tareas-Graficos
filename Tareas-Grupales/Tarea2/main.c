#ifdef __APPLE__
#define GL_SILENCE_DEPRECATION
#include <GLUT/glut.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
#include <math.h>
#else
#include <GL/glut.h>
#endif

#include "pixelart.h"
#include "circulo.h"

FILE *fp;

// Figuras de Art
#define ALTO 30
#define ANCHO 30
GLubyte paleta_basketball[6][4] = {{255,255,255,0},{255,140,0,255}, {0,0,0, 255}};
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

GLubyte paleta_soccer[6][4] = {{255,255,255,0},{255,255,255,255}, {0,0,0, 255}};
GLubyte soccer[ALTO][ANCHO] = {{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,1,1,2,2,2,2,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,1,1,1,1,2,2,2,2,1,1,1,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,1,1,1,1,1,1,2,2,2,2,1,1,1,1,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,1,1,1,1,1,1,1,2,2,2,2,1,1,1,1,1,0,0,0,0,0,0,0},
{0,0,0,0,0,0,1,1,1,1,1,1,1,2,1,1,1,1,2,1,1,1,1,0,0,0,0,0,0,0},
{0,0,0,0,0,0,2,1,1,1,1,1,2,1,1,1,1,1,2,1,1,1,1,1,0,0,0,0,0,0},
{0,0,0,0,0,0,1,2,1,1,1,1,2,1,1,1,1,1,2,1,1,1,1,1,0,0,0,0,0,0},
{0,0,0,0,0,1,1,1,2,2,2,2,1,1,1,1,1,1,1,2,2,2,2,2,1,0,0,0,0,0},
{0,0,0,0,0,1,1,1,2,2,2,2,1,1,1,1,1,1,1,2,2,2,2,2,1,0,0,0,0,0},
{0,0,0,0,0,1,1,1,2,2,2,2,1,1,1,1,1,1,1,2,2,2,2,2,1,0,0,0,0,0},
{0,0,0,0,0,1,1,1,2,2,2,2,1,1,1,1,1,1,1,2,2,2,2,2,1,0,0,0,0,0},
{0,0,0,0,0,0,1,2,1,1,1,1,2,1,1,1,1,1,2,1,1,1,1,1,0,0,0,0,0,0},
{0,0,0,0,0,0,2,1,1,1,1,1,2,1,1,1,1,1,2,1,1,1,1,1,0,0,0,0,0,0},
{0,0,0,0,0,0,1,1,1,1,1,1,1,2,2,2,2,2,1,1,1,1,1,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,1,1,1,1,1,1,2,2,2,2,2,1,1,1,1,1,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,1,1,1,1,1,2,2,2,2,2,1,1,1,1,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,1,1,1,1,2,2,2,2,2,1,1,1,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,1,1,2,1,1,1,1,1,2,1,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}};


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

void dibujaCoseno(){
    // Creamos el eje
    glColor3f(0.0, 0.0, 0.0);
    glLineWidth(2);
    glBegin(GL_LINES);
        glVertex2i(463, 360);
        glVertex2i(602, 360);
        glVertex2i(533, 436);
        glVertex2i(533, 284);
    glEnd();
    // Graficamos el coseno
    glLineWidth(3);
    glBegin(GL_LINE_STRIP);
        for (float i = -3.1416; i <= 3.1416; i+= 0.1)
        {
            float x = 20*i + 533; 
            float y = 50 * cos(i) + 360;
            glVertex2f(x, y);
        }
    glEnd();
}

void polilineas (const char name[20], const char name2[20] ) {
    glColor3f(1.0, 0.5, 0.3);
    glLineWidth(2);
    unsigned short numLineas, vertices;
    float x, y;
    fp = fopen(name, "r");
    if (fp == NULL)
    {
        // printf("\nError al intentar abrir el archivo %s\n", name);
        exit(1); 
    }

    fscanf(fp, "%hu", &numLineas);
    // printf("\nNúmero de líneas - %hu\n", numLineas);
    for (int i = 0; i < numLineas; i++)
    {
        glBegin(GL_LINE_STRIP);
            fscanf(fp, "%hu", &vertices);
            // printf("\nLinea %d - %hu vertices ", i + 1, vertices);
            for (int j = 0; j < vertices; j++)
            {
                fscanf(fp, "%f %f", &x, &y);
                // printf("(%.3f, %.3f) ", x, -y);
                glVertex2i(x, 460 - y);
            }
        glEnd();
    }
    fclose(fp);
    // Dibujamos el nombre
    char c[15]= "Robles Braun";
    glRasterPos2i(130, 250);
    for(int i = 0; i < strlen(c); i++){
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_10, c[i]);
    }

    // Pixel art Cesar
    glColor3f(0.0, 0.5, 0.8);
    glLineWidth(2);
    numLineas = 0;
    vertices = 0;
    fp = fopen(name2, "r");
    if (fp == NULL)
    {
        // printf("\nError al intentar abrir el archivo %s\n", 2);
        exit(1); 
    }

    fscanf(fp, "%hu", &numLineas);
    // printf("\nNúmero de líneas - %hu\n", numLineas);
    for (int i = 0; i < numLineas; i++)
    {
        glBegin(GL_LINE_STRIP);
            fscanf(fp, "%hu", &vertices);
            // printf("\nLinea %d - %hu vertices ", i + 1, vertices);
            for (int j = 0; j < vertices; j++)
            {
                fscanf(fp, "%f %f", &x, &y);
                // printf("(%.3f, %.3f) ", x, -y);
                glVertex2i(x + 450, 10 - y);
            }
        glEnd();
    }
    fclose(fp);
    // Dibujamos el nombre
    char n[15] = "Cesar Roman";
    glRasterPos2i(550, 10);
    for(int i = 0; i < strlen(n); i++){
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_10, n[i]);
    }
}

void curva() {
    int x0 = 319;
    int y0 = 200;
    int x1 = 326;
    int y1 = 120;
    //Dibujamos los ejes
    glColor3f(0.0, 0.8, 0.3);
    glBegin(GL_LINE_STRIP);
        glVertex2i(250, 120);
        glVertex2i(319, 120);
        glVertex2i(319, 40);
    glEnd();
    glBegin(GL_LINE_STRIP);
        glVertex2i(398, 120);
        glVertex2i(319, 120);
        glVertex2i(319, 200);
    glEnd();
    glBegin(GL_LINES);
        glColor3f(0.0, 0.8, 0.3);
        for (int i = 0; i < 10; i++)
        {
            glVertex2i(x0, y0);
            glVertex2i(x1, y1);
            y0 = y0 - 8;
            x1 = x1 + 8;
        }
        glColor3f(0.0, 0.5, 0.7);
        x0 = 319;
        y0 = 200;
        x1 = 326;
        y1 = 120;
        for (int i = 0; i < 10; i++)
        {
            glVertex2i(x0, y0);
            glVertex2i(x1, y1);
            printf("poli: %d %d -> %d %d\n", x0, y0, x1, y1);
            y0 = y0 - 8;
            x1 = x1 - 8;
        }
        glColor3f(0.0, 0.8, 0.3);
        x0 = 319;
        y0 = 40;
        x1 = 326;
        y1 = 120;
        for (int i = 0; i < 10; i++)
        {
            glVertex2i(x0, y0);
            glVertex2i(x1, y1);
            y0 = y0 + 8;
            x1 = x1 - 8;
        }
        x0 = 319;
        y0 = 40;
        x1 = 326;
        y1 = 120;
        glColor3f(0.0, 0.5, 0.7);
        for (int i = 0; i < 10; i++)
        {
            glVertex2i(x0, y0);
            glVertex2i(x1, y1);
            y0 = y0 + 8;
            x1 = x1 + 8;
        }
    glEnd();
}

void dibuja(void)
{
    float c[3] = {1.0, 0.0, 0.0};
    glClear(GL_COLOR_BUFFER_BIT);
    glLineWidth(3);
    // Dibujamos tablero
    glBegin(GL_LINES);
        glVertex2i(0, 240);
        glVertex2i(640, 240);
        glVertex2i(213, 480);
        glVertex2i(213, 0);
        glVertex2i(426, 480);
        glVertex2i(426, 0);
    glEnd();
    // Dibujamos coseno
    dibujaCoseno();
    //Dibujamos polilineas
    polilineas("polilineas.dat", "doggo.dat");
    // Dibujamos estrella
    curva();
    //dibujamos pixel art
    pixelArt(basketaball, paleta_basketball, -15, 130, 5);
    pixelArt(soccer, paleta_soccer, 80, 250, 5);
    // Circulo
    float col_circ[3] = {1,0,0};
    circulo(50, 320, 350,col_circ);
    glFlush();
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(640,480);
    glutInitWindowPosition(100, 150);
    glutCreateWindow("Tarea 2");
    glutReshapeFunc(ajusta);
    glutDisplayFunc(dibuja);
    glutMainLoop();
    return 0;
}