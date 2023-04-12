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

int paleta[4][4] = {{192, 192, 192, 255}, {255, 0, 0, 255}, {255, 255, 0, 255}, {0, 255, 0, 255}};
int color_rojo[4] = {192, 192, 192, 255};
int color_verde[4] = {192, 192, 192, 255};
int color_amarillo[4] = {192, 192, 192, 255};

int foco = 0;

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

void animaT(int v)
{

    switch (foco)
    {
    case 0:
        color_amarillo[0] = paleta[0][0];
        color_amarillo[1] = paleta[0][1];
        color_amarillo[2] = paleta[0][2];
        color_amarillo[3] = paleta[0][3];

        color_rojo[0] = paleta[1][0];
        color_rojo[1] = paleta[1][1];
        color_rojo[2] = paleta[1][2];
        color_rojo[3] = paleta[1][3];
        glutTimerFunc(2000, animaT, 0);
        foco++;
        break;
    case 1:
        color_rojo[0] = paleta[0][0];
        color_rojo[1] = paleta[0][1];
        color_rojo[2] = paleta[0][2];
        color_rojo[3] = paleta[0][3];

        color_verde[0] = paleta[3][0];
        color_verde[1] = paleta[3][1];
        color_verde[2] = paleta[3][2];
        color_verde[3] = paleta[3][3];

        glutTimerFunc(2000, animaT, 0);
        glutPostRedisplay();

        foco++;
        break;

    case 2:
        color_verde[0] = paleta[0][0];
        color_verde[1] = paleta[0][1];
        color_verde[2] = paleta[0][2];
        color_verde[3] = paleta[0][3];

        glutTimerFunc(500, animaT, 0);

        foco++;
        break;
    case 3:
        color_verde[0] = paleta[3][0];
        color_verde[1] = paleta[3][1];
        color_verde[2] = paleta[3][2];
        color_verde[3] = paleta[3][3];

        glutTimerFunc(500, animaT, 0);

        foco++;
        break;

    case 4:
        color_verde[0] = paleta[0][0];
        color_verde[1] = paleta[0][1];
        color_verde[2] = paleta[0][2];
        color_verde[3] = paleta[0][3];

        glutTimerFunc(500, animaT, 0);

        foco++;
        break;

    case 5:
        color_verde[0] = paleta[3][0];
        color_verde[1] = paleta[3][1];
        color_verde[2] = paleta[3][2];
        color_verde[3] = paleta[3][3];

        glutTimerFunc(500, animaT, 0);

        foco++;
        break;
    case 6:
        foco = 0;

        color_verde[0] = paleta[0][0];
        color_verde[1] = paleta[0][1];
        color_verde[2] = paleta[0][2];
        color_verde[3] = paleta[0][3];

        color_amarillo[0] = paleta[2][0];
        color_amarillo[1] = paleta[2][1];
        color_amarillo[2] = paleta[2][2];
        color_amarillo[3] = paleta[2][3];

        glutTimerFunc(1000, animaT, 0);

        break;

    default:
        break;
    }

    glutPostRedisplay();
}

void dibuja_circulo(GLfloat base_x, GLfloat base_y, int color[4])
{

    glColor4ub(color[0], color[1], color[2], color[3]);

    glPushMatrix();
    glTranslatef(base_x, base_y, -2.5);
    glScalef(0.1, 0.06, 0.2);
    glutSolidSphere(10, 200, 200);
    glPopMatrix();
}

void dibuja_cubo()
{
    glColor3ub(255, 172, 51);
    glPushMatrix();
    mover();
    glScalef(1, 2, -0.5);
    glutSolidCube(5);
    dibuja_circulo(0, 1.5, color_rojo);
    dibuja_circulo(0, 0, color_amarillo);
    dibuja_circulo(0, -1.5, color_verde);
    glPopMatrix();
}

void dibuja(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glPushMatrix();
    GLUquadricObj *quadratic;
    quadratic = gluNewQuadric();

    mover();
    if (malla) creaMalla(10);    
    if (ejes) creaEjes();
        

    // Tubo base con dos discos de tapa
    // glPushMatrix();
    glTranslatef(0, 11, 0);
    glRotatef(90.0, 1, 0, 0);
    gluQuadricDrawStyle(quadratic, GLU_FILL); // Set the drawing style to GLU_FILL
    gluCylinder(quadratic, 0.5, 0.5, 11, 10, 10);
    gluDisk(quadratic, 0, 0.5, 10, 1); // Draw a disk at the bottom of the cylinder
    glTranslatef(0, 0, 8); // Move to the top of the cylinder
    gluDisk(quadratic, 0, 0.5, 10, 1); // Draw a disk at the top of the cylinder
    // glPopMatrix();

    // Tubos pequeños de abajo
        // Tubo derecho
        glPushMatrix();
            glTranslatef(0, 0, -5);
            glRotatef(135.0, 0, 1, 0);
            gluCylinder(quadratic, 0.15, 0.15, 4, 10, 10);
        glPopMatrix();
        
        // Tubo izquierdo
        glPushMatrix();
            glTranslatef(0, 0, -5);
            glRotatef(-135.0, 1, 0, 0);
            gluCylinder(quadratic, 0.15, 0.15, 4, 10, 10);
        glPopMatrix();

    // Tubos horizontales

        // Tubo izquierdo
        glPushMatrix();
            glTranslatef(0, 0, -7.7);
            glRotatef(90.0, -1, 0, 0);
            gluCylinder(quadratic, 0.25, 0.25, 4.5, 10, 10);
        glPopMatrix();
        
        // Tubo derecho
        glPushMatrix();
            glTranslatef(0, 0, -7.7);
            glRotatef(90.0, -1, 0, 0);
            glRotatef(90.0, 0, 1, 0);
            gluCylinder(quadratic, 0.25, 0.25, 4.5, 10, 10);
        glPopMatrix();

    // Tubos Superiores

        // Tubo izquierdo
        glPushMatrix();
            // glTranslatef(0, 0, -7.7);
            glRotatef(90.0, -1, 0, 0);
            glRotatef(45.0, 0, 1, 0);
            gluCylinder(quadratic, 0.25, 0.25, 4.5, 10, 10);
        glPopMatrix();
        
        // // Tubo derecho
        // glPushMatrix();
        //     glTranslatef(0, 0, -7.7);
        //     glRotatef(90.0, -1, 0, 0);
        //     glRotatef(90.0, 0, 1, 0);
        //     gluCylinder(quadratic, 0.25, 0.25, 4.5, 10, 10);
        // glPopMatrix();


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
    GLfloat PosDireccional[] = {0.0, 8.0, -2.0, 0.0};
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
    glutTimerFunc(2, animaT, 0);
    glutMainLoop();

    return 0;
}
