#ifdef __APPLE__
#define GL_SILENCE_DEPRECATION
#include <GLUT/glut.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <ctype.h>
#else
#include <GL/glut.h>
#endif

#define anchoTextura 8
#define altoTextura 8

int paleta[6][3] = {{0,255,0},{0,0,255}};
GLubyte tablero[altoTextura][anchoTextura]={
    {0,1,0,1,0,1,0,1},
    {1,0,1,0,1,0,1,0},
    {0,1,0,1,0,1,0,1},
    {1,0,1,0,1,0,1,0},
    {0,1,0,1,0,1,0,1},
    {1,0,1,0,1,0,1,0},
    {0,1,0,1,0,1,0,1},
    {1,0,1,0,1,0,1,0}
    };

#define anchoTextura 8
#define altoTextura 8


GLubyte imagen[altoTextura][anchoTextura][3];
void creaTexturas(void)
{
    for (int i = 0; i < altoTextura; i++)
        for (int j = 0; j < anchoTextura; j++)
        {
            imagen[i][j][0] = (i < altoTextura && j < anchoTextura) ? paleta[tablero[i][j]][0] : paleta[0][0];
            imagen[i][j][1] = paleta[(i < altoTextura && j < anchoTextura) ? tablero[i][j] : 0][1];
            imagen[i][j][2] = paleta[(i < altoTextura && j < anchoTextura) ? tablero[i][j] : 0][2];
        }
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, anchoTextura, altoTextura,
                 0, GL_RGB, GL_UNSIGNED_BYTE, imagen);
}
void dibuja(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
	
    glBegin(GL_QUADS);
		// Tablero
		glTexCoord2f(0.0, 0.0); glVertex2f(-1.0, 4.0);
		glTexCoord2f(0.0, 1.0); glVertex2f(-1.0, 1.0);
		glTexCoord2f(1.0, 1.0); glVertex2f(-4.0, 1.0);
		glTexCoord2f(1.0, 0.0); glVertex2f(-4.0, 4.0);
	glEnd();    
		
    // Tablero Derecha
    glBegin(GL_QUADS);
		glTexCoord2f(0.0, 0.0); glVertex2f(4.0, 4.0);
		glTexCoord2f(0.0, 2.0); glVertex2f(4.0, 1.0);
		glTexCoord2f(2.0, 2.0); glVertex2f(1.0, 1.0);
		glTexCoord2f(2.0, 0.0); glVertex2f(1.0, 4.0);
	glEnd();    

    // Tablero abajo
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T,GL_CLAMP);
    glBegin(GL_QUADS);
        glTexCoord2f(0.0, 0.0); glVertex2f(4.0, -1.0);
		glTexCoord2f(0.0, 2.0); glVertex2f(4.0, -4.0);
		glTexCoord2f(3.0, 2.0); glVertex2f(-4.0, -4.0);
		glTexCoord2f(3.0, 0.0); glVertex2f(-4.0, -1.0);

	glEnd();    

    glFlush();
}
void ajusta(int w, int h)
{
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-4.5, 4.5, -4.5, 4.5);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glEnable(GL_TEXTURE_2D);
}
int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(400, 400);
    glutCreateWindow("Textura procedural");
    creaTexturas();
    glutReshapeFunc(ajusta);
    glutDisplayFunc(dibuja);
    glutMainLoop();
    return 0;
}