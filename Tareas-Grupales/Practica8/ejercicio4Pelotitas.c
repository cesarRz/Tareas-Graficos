#ifdef __APPLE__
#define GL_SILENCE_DEPRECATION
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#define GRAVEDAD -9.8
#define MASA 200 // masa de la pelota

struct ball {
    double velocityX;
    double velocityY;
    double velocityZ;
    double positionX;
    double positionY;
    double positionZ;
    double xForce;
    double zForce;
    GLubyte color[3];
};

// struct ball balls[2];
int numberOfBalls = 7;

struct ball balls[7] = {
    { 0, 0, 0, -3, 0, 0, 0.01, -0.02, {181, 23, 158} },
    { 0, 0, 0, -2, 0, 0, 0.04, -0.01, {114, 9, 183} },
    { 0, 0, 0, -1, 0, 0, 0.05, -0.03, {86, 11, 173} },
    { 0, 0, 0, 0, 0, 0, 0.02, -0.05, {72, 12, 168} },
    { 0, 0, 0, 1, 0, 0, 0.06, -0.04, {58, 12, 163} },
    { 0, 0, 0, 2, 0, 0, 0.03, -0.06, {63, 55, 201} },
    { 0, 0, 0, 3, 0, 0, 0.07, -0.07, {67, 97, 238} },
};

double h = 0.5;     // h incrementos de tiempo
double posicion[] = {0,0,0};
double velocidad[] = {0,0,0};

double fzaX = 0.02;
double fzaZ = -0.05;

GLboolean bx = GL_FALSE;
GLboolean by = GL_FALSE;
GLboolean bz = GL_FALSE;

void integraEuler(){
    for (int i = 0; i < numberOfBalls; i++)
    {
        //  v(t+h)=v(t)+F(t)/m*h
        if (bx) balls[i].velocityX += balls[i].xForce*h;
        if (by) balls[i].velocityY += GRAVEDAD/MASA*h;
        if (bz) balls[i].velocityZ += balls[i].zForce*h;

        // x(t+h)=x(t) + v(t+h)*h
        balls[i].positionX += balls[i].velocityX*h;
        balls[i].positionY += balls[i].velocityY*h;
        balls[i].positionZ += balls[i].velocityZ*h;
    }
}

void ajusta(int alto, int ancho){
    glClearColor(0.298, 0.788, 0.941, 0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60,(float)alto/ancho, 1, 100);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void dibuja(void){
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3ub(0,0,0);
    glLineWidth(2);
    glPushMatrix();
       glTranslatef(0,0,-16);
       glutWireCube(11);
       glColor3ub(0,0,255);
        for (int i = 0; i < numberOfBalls; i++)
        {
            glColor3ubv(balls[i].color);
            glPushMatrix();
                glTranslated(balls[i].positionX, balls[i].positionY, balls[i].positionZ);
                glutSolidSphere(0.4, 20, 20);
            glPopMatrix();
        }
    glPopMatrix();
    glutSwapBuffers();
}

void mueve(void){
    integraEuler();
    //colisiones
    for (int i = 0; i < numberOfBalls; i++)
    {
        if(balls[i].positionX>=5 || balls[i].positionX<=-5){ //X
            balls[i].xForce = -1*balls[i].xForce;
            balls[i].velocityX = 0;
            balls[i].positionX = (balls[i].positionX >= 5) ? 4.8 : -4.8;
        }
        if(balls[i].positionY >= 5){  //Y Arriba
            balls[i].velocityY = 0;
            balls[i].positionY = 4.2;
        }
        if(balls[i].positionY<=-5){  //Y Abajo
            balls[i].velocityY = 0.9;
            balls[i].positionY = -4.8;
        }
        if(balls[i].positionZ >= 5 || balls[i].positionZ <= -5){  //Z
            balls[i].zForce = -1 * balls[i].zForce;
            balls[i].velocityZ = 0;
            balls[i].positionZ = (balls[i].positionZ >= 5) ? 4.8 : -4.8;
        }
    }
    glutPostRedisplay();
}


void teclado(unsigned char key, int x, int y) {
    switch (key) {
      case 27:  exit(0);
      case 'x': bx = !bx ;break;
      case 'y': by = !by; break;
      case 'z': bz = !bz ;
    }
}


int main(int argc, char** argv){
    glutInitDisplayMode(GLUT_RGB|GLUT_DOUBLE);
    glutInit(&argc, argv);
    glutInitWindowSize(600, 600);
    glutCreateWindow("Bolitas");
    glutDisplayFunc(dibuja);
    glutReshapeFunc(ajusta);
    glutKeyboardFunc(teclado);
	glutIdleFunc(mueve);
    glutMainLoop();
    return 0;
}
