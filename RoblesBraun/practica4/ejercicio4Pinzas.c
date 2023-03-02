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

int x = 0;
int open = 0;
int rotate = 0;

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


void move(int tecla, int x1, int y1) {
    switch(tecla) {
        case GLUT_KEY_LEFT:
            x = x - 1;
            break;
        case GLUT_KEY_RIGHT:
            x = x + 1;
            break;
        case GLUT_KEY_F1: // open
            if (open > 0){
                open = open -2;
            }
            break;
        case GLUT_KEY_F2: // close
            if (open < 40){
                open = open + 2;
            }
            break;
        case GLUT_KEY_F5: // rotate
            rotate = rotate + 5;
            break;
    }
    glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y){
    switch(key) {
        case 27:
            exit(0);// Esc =>Salir del programa
            break;
    }
    glutPostRedisplay();
}

void dibuja(void)
{
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    glColor3f(1,0,0);

    glPushMatrix();
        glTranslatef(x, 0, 0);
        glRotatef(rotate, 0, 1, 0);
        glPushMatrix(); //Cuerpo
            GLUquadricObj *quadratic;
            quadratic = gluNewQuadric();
            glTranslatef(0, 10, 0);
            //glRotatef(90.0, 0, 1, 0);
            glRotatef(90.0, 1, 0, 0);
            gluCylinder(quadratic, 0.5, 0.5, 12, 32, 32);
        glPopMatrix();
        glPushMatrix();
            glColor3f(0, 0, 1);
            glPushMatrix(); //Primera parte de la pinza
                glTranslatef(0.2, -1.5, 0);
                glRotatef(open, 0, 0, 1);
                glTranslatef(0, -1.5, 0);
                glScalef(0.25, 3, 0.7);
                glutSolidCube(1);
            glPopMatrix();
            glColor3f(0, 1 ,0);
            glPushMatrix(); //Segunda parte de la pinza
                glTranslatef(-0.2, -1.5, 0);
                glRotatef(-open, 0, 0, 1);
                glTranslatef(0, -1.5, 0);
                glScalef(0.25, 3, 0.7);
                glutSolidCube(1);
            glPopMatrix();
        glPopMatrix();
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
    glutKeyboardFunc(keyboard);
    glutSpecialFunc(move);
    glutMainLoop();
    return 0;
}