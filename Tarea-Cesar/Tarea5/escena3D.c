#ifdef __APPLE__
#define GL_SILENCE_DEPRECATION
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

GLUquadricObj *cilindro;
GLfloat girax = 0, giray = 0, zoom = 0;
GLboolean malla = GL_FALSE, ejes = GL_TRUE;

//   Rotacion XY y Zoom
void mover(void)
{
    glTranslated(0, 0, zoom);
    glRotated(giray, 0.0, 1.0, 0.0);
    glRotated(girax, 1.0, 0.0, 0.0);
}
//  Malla y Ejes
void creaMalla(int long_eje)
{
    glColor3f(1.0, 0.0, 0.0);
    glBegin(GL_LINES);
    int i;
    for (i = -long_eje; i <= long_eje; i++)
    {
        glVertex3f(i, 0, -long_eje);
        glVertex3f(i, 0, long_eje);
        glVertex3f(-long_eje, 0, i);
        glVertex3f(long_eje, 0, i);
    }
    glEnd();
}
void creaEjes(void)
{
    glColor3f(0.0, 0.0, 0.0);
    glBegin(GL_LINES);
    glVertex3f(0.0, 0.0, 0.0);
    glVertex3f(11.0, 0.0, 0.0);
    glVertex3f(0.0, 0.0, 0.0);
    glVertex3f(0.0, 11.0, 0.0);
    glVertex3f(0.0, 0.0, 0.0);
    glVertex3f(0.0, 0.0, 11.0);
    glEnd();
    glBegin(GL_TRIANGLES);
    glVertex3f(11.0, 0.0, 0.0); /* eje x */
    glVertex3f(10.5, 0.0, -.50);
    glVertex3f(10.5, 0.0, .50);
    glColor3f(0.25, 1, 0.25); /* eje y */
    glVertex3f(0.0, 11.0, 0.0);
    glVertex3f(-.50, 10.5, 0.0);
    glVertex3f(.50, 10.5, 0.0);
    glColor3f(0.25, 0.25, 1.0); /* eje z */
    glVertex3f(0.0, 0.0, 11.0);
    glVertex3f(-.50, 0.0, 10.5);
    glVertex3f(.50, 0.0, 10.5);
    glEnd();
}


void dibuja(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glPushMatrix();
        GLUquadricObj *quadratic;
        quadratic = gluNewQuadric();

        mover();
        if (malla) creaMalla(10);    
        if (ejes) creaEjes();

        // Tubo base con dos discos de tapa
        glPushMatrix();
            glColor4ub(0,0,0,255);
            glTranslatef(0, 11, 0);
            glRotatef(90.0, 1, 0, 0);
            gluCylinder(quadratic, 0.5, 0.5, 11, 10, 10);
            gluDisk(quadratic, 0, 0.5, 10, 1); 
            glTranslatef(0, 0, 8); 
            gluDisk(quadratic, 0, 0.5, 10, 1);
        glPopMatrix();

        // Tubos pequeños de abajo
            // Tubo derecho
            glPushMatrix();
                glTranslatef(0, 8, 0);
                glRotatef(-45.0, 1, 0, 0);
                gluCylinder(quadratic, 0.15, 0.15, 4, 10, 10);
            glPopMatrix();
            
            // Tubo izquierdo
            glPushMatrix();
                glTranslatef(0, 8, 0);
                glRotatef(90.0, 0, 1, 0);
                glRotatef(-45.0, 1, 0, 0);
                gluCylinder(quadratic, 0.15, 0.15, 4, 10, 10);
            glPopMatrix();

        // Tubos horizontales

            // Tubo izquierdo
            glPushMatrix();
                glTranslatef(0,10.9, 0);
                gluCylinder(quadratic, 0.25, 0.25, 4.5, 10, 10);
            glPopMatrix();
            
            // Tubo derecho
            glPushMatrix();
                glTranslatef(0,10.9, 0);
                glRotatef(90.0, 0, 1, 0);
                gluCylinder(quadratic, 0.25, 0.25, 4.5, 10, 10);
            glPopMatrix();

        // Tubos Superiores

            // Tubo izquierdo
            glPushMatrix();
                glTranslatef(0,10.9, 0);
                glRotatef(40.0, -1, 0, 0);
                gluCylinder(quadratic, 0.25, 0.25, 6, 10, 10);
            glPopMatrix();
            
            // Tubo derecho
            glPushMatrix();
                glTranslatef(0,10.9, 0);
                glRotatef(90.0, 0, 1, 0);
                glRotatef(40.0, -1, 0, 0);
                gluCylinder(quadratic, 0.25, 0.25, 6, 10, 10);
            glPopMatrix();


        // Tablero 
        glPushMatrix();
            glColor4ub(0,0,0,90);
                glTranslatef(2.3,13,2.3);
                glRotated(45,0,1,0);
                glScaled(10,5,0.35);
                glutSolidCube(1);
        glPopMatrix();

        // Cuadro
        glPushMatrix();
            glColor4ub(255,255,255,255);
                glTranslatef(2.35,13,2.35);
                glRotated(45,0,1,0);
                glScaled(2,2,0.35);
                glutWireCube(1);
        glPopMatrix();

        // Aro de la canasta
        glPushMatrix();
                glColor4ub(255,165,0,255);
                glTranslatef(3.2,12,3.2);
                glRotated(90,1,0,0);
                gluCylinder(quadratic, 1, 1, 0.2, 10, 10);
        glPopMatrix();

        // Red de la canasta
        glPushMatrix();
                glColor4ub(255,255,255,255);
                glTranslatef(3.2,12,3.2);
                glRotated(90,1,0,0);
                gluQuadricDrawStyle(quadratic, GLU_LINE);
                gluCylinder(quadratic, 1, 0.6, 1.5, 10, 10);
        glPopMatrix();

        // Pelota
        glPushMatrix();
            glTranslatef(5,15,5);
            glColor4ub(255,165,0,255);
            gluQuadricDrawStyle(quadratic, GLU_FILL);
            gluSphere(quadratic,0.8,10,10);

            glColor4ub(0,0,0,255);
            gluQuadricDrawStyle(quadratic, GLU_LINE);
            gluSphere(quadratic,0.8,10,10);
        glPopMatrix();


    glPopMatrix();

    glutSwapBuffers();
}

// Funciones con Teclas
void teclado(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 27:
        exit(0);
    case '+':
        zoom++;
        break;
    case '-':
        zoom--;
        break;
    case 'm':
        malla = !malla;
        break;
    case 'e':
        ejes = !ejes;
        break;
    case 'p':
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        gluPerspective(45, 1, 10, 100);
        zoom = -40;
        break;
    case 'o':
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glOrtho(-15, 15, -15, 15, -30, 30);
        zoom = 0;
    default:
        break;
    }
    glutPostRedisplay();
}
void rotar(int key, int x, int y)
{
    switch (key)
    {
    case GLUT_KEY_LEFT:
        giray -= 15;
        break;
    case GLUT_KEY_RIGHT:
        giray += 15;
        break;
    case GLUT_KEY_UP:
        girax -= 15;
        break;
    case GLUT_KEY_DOWN:
        girax += 15;
        break;
    }
    glutPostRedisplay();
}
void ajusta(int ancho, int alto)
{
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    GLfloat PosDireccional[] = {8.0, 8.0, 8.0, 0.0};
    glLightfv(GL_LIGHT0, GL_POSITION, PosDireccional);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHTING);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_DEPTH_TEST);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45, 1, 10, 100);
    zoom = -40;
}
int main(int argc, char **argv)
{

    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(500, 500);
    glutInit(&argc, argv);
    glutCreateWindow("Ejercicio 1");
    glutDisplayFunc(dibuja);
    glutReshapeFunc(ajusta);
    glutKeyboardFunc(teclado);
    glutSpecialFunc(rotar);
    glutMainLoop();

    return 0;
}
