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

GLUquadricObj *cilindro;
GLfloat  girax = 0, giray= 0, zoom=0;
GLboolean malla = GL_FALSE, ejes = GL_TRUE;


//   Rotacion XY y Zoom
void mover(void) {
    glTranslated( 0, 0, zoom);
    glRotated( giray, 0.0, 1.0, 0.0);
    glRotated( girax, 1.0, 0.0, 0.0);
}
//  Malla y Ejes
void creaMalla(int long_eje) {
    glColor3f(1.0,0.0,0.0);
    glBegin(GL_LINES);
    int i;
      for(i= -long_eje; i<=long_eje; i++) {
          glVertex3f (i,0,-long_eje);
          glVertex3f (i,0,long_eje);
          glVertex3f (-long_eje,0,i);
          glVertex3f (long_eje,0,i);
      }
    glEnd();
}
void creaEjes(void) {
    glColor3f(0.0,0.0,0.0);
    glBegin( GL_LINES );
        glVertex3f (0.0,0.0,0.0); glVertex3f (11.0,0.0,0.0);
        glVertex3f (0.0,0.0,0.0); glVertex3f (0.0,11.0,0.0);
        glVertex3f (0.0,0.0,0.0); glVertex3f (0.0,0.0,11.0);
    glEnd();
    glBegin( GL_TRIANGLES );
        glVertex3f (11.0,0.0,0.0); /* eje x */
        glVertex3f (10.5,0.0,-.50);
        glVertex3f (10.5,0.0,.50);
        glColor3f(0.25,1,0.25);  	/* eje y */
        glVertex3f (0.0,11.0,0.0);
        glVertex3f (-.50,10.5,0.0);
        glVertex3f (.50,10.5,0.0);
        glColor3f(0.25,0.25,1.0);  	/* eje z */
        glVertex3f (0.0,0.0,11.0);
        glVertex3f (-.50,0.0,10.5);
        glVertex3f (.50,0.0,10.5);
    glEnd();
}

void dibuja(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //Limpiamos frame buffer y z-buffer
    glColor3ub(0, 0, 255);
    glLineWidth(2);

    //ejes
    glPushMatrix();
        mover();
        if (malla) creaMalla(10);    
        if (ejes) creaEjes();
    glPopMatrix();

    glPopMatrix();

    //Cara azul
    glPushMatrix();
        mover();
        glRotatef(-90, 1, 0, 0);
        glBegin(GL_QUADS);
            glVertex2f(0, 1);
            glVertex2f(1, 1);
            glVertex2f(1, 0);
            glVertex2f(0, 0);
        glEnd();
    glPopMatrix();

    //Cara verde
    glPushMatrix();
        mover();
        glColor3ub(0, 255, 0);
        //glRotatef(45, 0, 1, 0);
        glBegin(GL_QUADS);
            glVertex2f(-1, 0);
            glVertex2f(0, 0);
            glVertex2f(0, -1);
            glVertex2f(-1, -1);
        glEnd();
    glPopMatrix();

    //Cara amarillo
    glPushMatrix();
        mover();
        glColor3ub(245, 196, 74);
        //glRotatef(45, 0, 1, 0);
        glBegin(GL_QUADS);
            glVertex2f(0, 0);
            glVertex2f(1, 0);
            glVertex2f(1, -1);
            glVertex2f(0, -1);
        glEnd();
    glPopMatrix();

    glPushMatrix();
        mover();
        glColor3ub(255, 0, 0);
        glPointSize(4);
        glBegin(GL_POINTS);
            glVertex2f(0, 0);
        glEnd();
    glPopMatrix();
    glutSwapBuffers();
}

// Funciones con Teclas
void teclado(unsigned char key, int x, int y) {
  switch(key) {
    case 27:  exit (0);
    case '+': zoom ++; break;
    case '-': zoom --; break;
    case 'm': malla = !malla; break;
    case 'e': ejes = !ejes;  break;
    case 'p': glMatrixMode(GL_PROJECTION);
              glLoadIdentity();
              gluPerspective(45,1,10,100);
              zoom= -40;
			  break;
    case 'o': glMatrixMode(GL_PROJECTION);
              glLoadIdentity();
            //   glOrtho(-5, 5, -5, 5, -5, 5);
              zoom=0;
    default: break;
  }
  glutPostRedisplay();
}


void rotar(int key, int x, int y) {
  switch(key) {
    case GLUT_KEY_LEFT: giray-= 15; break;
    case GLUT_KEY_RIGHT:giray+= 15; break;
    case GLUT_KEY_UP:   girax -= 15; break;
    case GLUT_KEY_DOWN: girax += 15; break;
  }
  glutPostRedisplay();
}


void ajusta(int ancho, int alto) {
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glEnable(GL_DEPTH_TEST); // Habilitamos el z-buffer
    glOrtho(-5, 5, -5, 5, -5, 5);
}



int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH); // GLU DEPTH es el z-buffer
    glutInitWindowSize(700, 700);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Armado de un cubo");
    glutDisplayFunc(dibuja);
    glutReshapeFunc(ajusta);
    glutKeyboardFunc(teclado);
    glutSpecialFunc(rotar);
    glutMainLoop();
    return 0;
}