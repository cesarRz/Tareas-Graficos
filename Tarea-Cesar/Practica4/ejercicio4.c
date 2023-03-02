#ifdef __APPLE__
#define GL_SILENCE_DEPRECATION
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

int base_x = 0;
int angulo = 0;
int rotacion = 0;

void ajusta(int ancho, int alto)
{
    glClearColor(1.,1.,1.,0.);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-10, 10, -10, 10, 10, -10);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glEnable(GL_DEPTH_TEST);
}


void teclado_especial(int tecla, int x1, int y1) {
    switch(tecla) {
        case GLUT_KEY_LEFT:
            base_x = base_x - 1;
            break;
        case GLUT_KEY_RIGHT:
            base_x = base_x + 1;
            break;
        case GLUT_KEY_UP: 
            if (angulo > 0){
                angulo = angulo -2;
            }
            break;
        case GLUT_KEY_DOWN: 
            if (angulo < 40){
                angulo = angulo + 2;
            }
            break;
        case GLUT_KEY_F5: 
            rotacion = rotacion + 5;
            break;
    }
    glutPostRedisplay();
}

void dibuja_cilindro(){

    glTranslatef(base_x, 0, 0);
        glRotatef(rotacion, 0, 1, 0);
        glPushMatrix(); //Cuerpo
            GLUquadricObj *quadratic;
            quadratic = gluNewQuadric();
            glTranslatef(0, 10, 0);
            glRotatef(90.0, 1, 0, 0);
            gluCylinder(quadratic, 0.5, 0.5, 12, 32, 32);
        glPopMatrix();

}

void dibuja_garra(int opening){
            glPushMatrix();
            if (opening < 0) 
                glTranslatef(-0.2, -1.5, 0);
            else
                glTranslatef(0.2, -1.5, 0);

                glRotatef(opening, 0, 0, 1);
                glTranslatef(0, -1.5, 0);
                glScalef(0.25, 3, 0.7);
                glutSolidCube(1);
            glPopMatrix();
}

void dibuja(void)
{
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    glColor3f(1,0,0);

    glPushMatrix();

        dibuja_cilindro();
        glColor3f(0, 0, 1);
        dibuja_garra(angulo);
        glColor3f(0, 1 ,0);
        dibuja_garra(-angulo);

        
    glPopMatrix();
    glutSwapBuffers();
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowSize(640, 480);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Pinzas");
    glutDisplayFunc(dibuja);
    glutReshapeFunc(ajusta);
    glutSpecialFunc(teclado_especial);
    glutMainLoop();
    return 0;
}