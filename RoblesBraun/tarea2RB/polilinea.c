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

FILE *fp;

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

void leer (const char name[20]) {
    glColor3f(1.0, 0.5, 0.3);
    glLineWidth(2);
    unsigned short numLineas, vertices;
    float x, y;
    fp = fopen(name, "r");
    if (fp == NULL)
    {
        printf("\nError al intentar abrir el archivo %s\n", name);
        exit(1); 
    }

    fscanf(fp, "%hu", &numLineas);
    printf("\nNúmero de líneas - %hu\n", numLineas);
    for (int i = 0; i < numLineas; i++)
    {
        glBegin(GL_LINE_STRIP);
            fscanf(fp, "%hu", &vertices);
            printf("\nLinea %d - %hu vertices ", i + 1, vertices);
            for (int j = 0; j < vertices; j++)
            {
                fscanf(fp, "%f %f", &x, &y);
                printf("(%.3f, %.3f) ", x, -y);
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
    // Leemos archivo de polilineas
    leer("polilineas.dat");
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