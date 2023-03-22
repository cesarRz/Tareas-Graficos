
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

#include <stdbool.h>


int angle = 0;
int angulo_deseado = 60;

GLboolean animate = GL_FALSE;
GLboolean building = GL_TRUE;

GLUquadricObj *cilindro;
GLfloat  girax = 0, giray= 0, zoom=0;
GLboolean malla = GL_FALSE, ejes = GL_TRUE;


void mover(void) {
    glTranslated( 0, 0, zoom);
    glRotated( giray, 0.0, 1.0, 0.0);
    glRotated( girax, 1.0, 0.0, 0.0);
}

void arma (int num) {
    if (animate == GL_TRUE)
    {
        if (building == GL_TRUE)
        {
            if (angle != angulo_deseado)
            {
                angle += 1;
            }
            else
            {
                animate = GL_FALSE;
                building = GL_FALSE;
            }
        } else
        {
            if (angle > 0)
            {
                angle -= 1;
            }
            else
            {
                animate = GL_FALSE;
                building = GL_TRUE;
            }
        }
        
    }
    glutTimerFunc(20, arma, 1);
    glutPostRedisplay();
}

void axis () {
    glLineWidth(2);
    glBegin(GL_LINES);
        //Eje x
        glColor3ub(255, 0, 0);
        glVertex3f(-5, 0, 0);
        glVertex3f(5, 0, 0);
        //Eje y
        glColor3ub(0, 0, 255);
        glVertex3f(0, -5, 0);
        glVertex3f(0, 5, 0);
        //Eje z
        glColor3ub(0, 255, 0);
        glVertex3f(0, 0, -5);
        glVertex3f(0, 0, 5);
    glEnd();
}

void anima (int button, int state, int x, int y) {
    if (button == GLUT_LEFT && state == GLUT_DOWN) {
        animate = !animate;
    }
    
}

void triangulo(int direccion, bool eje){

    if (direccion > 0)
    {
        /* code */
        glColor3f(1,0,0);
    }else{
        glColor3f(0,0,1);

    }

    if (eje == true)
    {
        glBegin(GL_TRIANGLES);
            glVertex3f(-0.5 * direccion, 0, -0.5 * direccion);
            glVertex3f(0, 0, 0.5 * direccion);
            glVertex3f(0.5 * direccion, 0, -0.5 * direccion);
        glEnd();
    }
    else{

        glBegin(GL_TRIANGLES);
            glVertex3f(-0.5 * direccion, 0, 0);
            glVertex3f(0.5 * direccion, 0, 0.5 * direccion);
            glVertex3f(0.5 * direccion, 0,-0.5 * direccion);
        glEnd();

    }
    


}



void dibuja(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //Limpiamos frame buffer y z-buffer
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glEnable(GL_DEPTH_TEST); // Habilitamos el z-buffer
    glOrtho(-5, 5, -5, 5, -5, 5);
    gluLookAt(-0.8, 1, -1,   0, 0, 0,    0, 1, 0);
    glPushMatrix();
        mover();
        axis();

        glPushMatrix();
            
            glRotatef(angle, 1, 0,0);
            glTranslatef(0,0,-0.5);
            triangulo(1, true);

            glPushMatrix();

                glTranslatef(0,0,-0.5);
                glRotatef(angle, 1, 0,0);
                glTranslatef(0,0,-0.5);
                triangulo(-1, true);
            glPopMatrix();

        glPopMatrix();
        
        glPushMatrix();
            
            glRotatef(-angle, 1, 0,0);
            glTranslatef(0,0,0.5);
            triangulo(-1, true);

            glPushMatrix();

                glTranslatef(0,0,0.5);
                glRotatef(-angle, 1, 0,0);
                glTranslatef(0,0,0.5);
                triangulo(1, true);
            glPopMatrix();

        glPopMatrix();

        glPushMatrix();
            
            glRotatef(angle, 0, 0,1);
            glTranslatef(0.5,0,0);
            triangulo(1, false);

            glPushMatrix();

                glTranslatef(0.5,0,0);
                glRotatef(angle, 0, 0,1);
                glTranslatef(0.5,0,0);
                triangulo(-1, false);
            glPopMatrix();

        glPopMatrix();

        glPushMatrix();
            
            glRotatef(-angle, 0, 0,1);
            glTranslatef(-0.5,0,0);
            triangulo(-1, false);

            glPushMatrix();

                glTranslatef(-0.5,0,0);
                glRotatef(-angle, 0, 0,1);
                glTranslatef(-0.5,0,0);
                triangulo(1, false);
            glPopMatrix();

        glPopMatrix();

    glPopMatrix();
   
    glutSwapBuffers();
}

// Funciones con Teclas
void teclado(unsigned char key, int x, int y) {
  switch(key) {
    case 27:  exit (0);
    case '+': zoom ++; break;
    case '-': zoom --; break;
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
    glutMouseFunc(anima);
    glutTimerFunc(20, arma, 1);
    glutMainLoop();
    return 0;
}