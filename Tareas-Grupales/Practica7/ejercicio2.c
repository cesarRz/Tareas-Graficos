#ifdef __APPLE__
#define GL_SILENCE_DEPRECATION
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <ctype.h>


#define anchoTextura 32
#define altoTextura 32

GLubyte paleta[6][4] = {{255,255,255,255},{255,140,0,255}, {0,0,0, 255}};
GLubyte basketaball[30][30] = {{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
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
    
int angle = 0;


GLfloat  girax = 0, giray= 0, zoom=0;
GLboolean malla = GL_FALSE, ejes = GL_TRUE;

GLboolean animate = GL_FALSE;
GLboolean building = GL_TRUE;
GLubyte imagen[altoTextura][anchoTextura][3];

void mover(void) {
    glTranslated( 0, 0, zoom);
    glRotated( giray, 0.0, 1.0, 0.0);
    glRotated( girax, 1.0, 0.0, 0.0);
}


void creaTexturas(void)
{
    for (int i = 0; i < altoTextura; i++)
        for (int j = 0; j < anchoTextura; j++)
        {
            imagen[i][j][0] = (i < altoTextura && j < anchoTextura) ? paleta[basketaball[i][j]][0] : paleta[0][0];
            imagen[i][j][1] = paleta[(i < altoTextura && j < anchoTextura) ? basketaball[i][j] : 0][1];
            imagen[i][j][2] = paleta[(i < altoTextura && j < anchoTextura) ? basketaball[i][j] : 0][2];
        }
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, anchoTextura, altoTextura,
                 0, GL_RGB, GL_UNSIGNED_BYTE, imagen);
}

void buildCube (int num) {
    if (animate == GL_TRUE)
    {
        if (building == GL_TRUE)
        {
            if (angle != 90)
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
    glutTimerFunc(20, buildCube, 1);
    glutPostRedisplay();
}

void startAnimation (int button, int state, int x, int y) {
    if (button == GLUT_LEFT && state == GLUT_DOWN) {
        animate = !animate;
    }
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

void dibuja(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //Limpiamos frame buffer y z-buffer
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glEnable(GL_DEPTH_TEST); // Habilitamos el z-buffer
    glOrtho(-5, 5, -5, 5, -5, 5);

    gluLookAt(-0.8, 1, -1, 0, 0, 0, 0, 1, 0);
    glPushMatrix();
        mover();
        axis();
    glPopMatrix();

    //Cara azul, base 
    glPushMatrix();
        mover();
        glColor3ub(150, 150, 200);
        glBegin(GL_QUADS);
            glTexCoord2f(0.0, 0.0); glVertex3f(0.5, 0, 0.5);
            glTexCoord2f(0.0, 1.0); glVertex3f(-0.5, 0, 0.5);
            glTexCoord2f(2.0, 1.0); glVertex3f(-0.5, 0, -0.5);
            glTexCoord2f(2.0, 0.0); glVertex3f(0.5, 0, -0.5);
        glEnd();
    glPopMatrix();

    //Cara verde claro
    glPushMatrix();
        mover();
        // Aplico transformaciones
        glTranslatef(0.5, 0, 0);
        glRotatef(angle, 0, 0, 1);
        glTranslatef(0.5, 0, 0);
        glBegin(GL_QUADS);
            glTexCoord2f(0.0, 0.0); glVertex3f(0.5, 0, 0.5);
            glTexCoord2f(0.0, 1.0); glVertex3f(-0.5, 0, 0.5);
            glTexCoord2f(3.0, 1.0); glVertex3f(-0.5, 0, -0.5);
            glTexCoord2f(3.0, 0.0); glVertex3f(0.5, 0, -0.5);
        glEnd();
    glPopMatrix();

    //Cara amarilla
    glPushMatrix();
        mover();
        // glColor3ub(245, 196, 74);
        //Aplico transformaciones
        glTranslatef(0, 0, -0.5);
        glRotatef(angle, 1, 0, 0);
        glTranslatef(0, 0, -0.5);
        glBegin(GL_QUADS);
            glTexCoord2f(0.0, 0.0); glVertex3f(0.5, 0, 0.5);
            glTexCoord2f(0.0, 2.0); glVertex3f(-0.5, 0, 0.5);
            glTexCoord2f(2.0, 2.0); glVertex3f(-0.5, 0, -0.5);
            glTexCoord2f(2.0, 0.0); glVertex3f(0.5, 0, -0.5);
        glEnd();
    glPopMatrix();

    //Cara morada
    glPushMatrix();
        mover();
        // glColor3ub(200, 0, 255);
        glLineWidth(2);
        // Regreso a donde quiero poner la cara
        glTranslatef(-0.5, 0, 0);
        // Roto la figura
        glRotatef(-angle, 0, 0, 1);
        // Muevo al origen
        glTranslatef(-0.5, 0, 0);
        glBegin(GL_QUADS);
            glTexCoord2f(0.0, 0.0); glVertex3f(0.5, 0, 0.5);
            glTexCoord2f(0.0, 3.0); glVertex3f(-0.5, 0, 0.5);
            glTexCoord2f(3.0, 3.0); glVertex3f(-0.5, 0, -0.5);
            glTexCoord2f(3.0, 0.0); glVertex3f(0.5, 0, -0.5);
        glEnd();
    glPopMatrix();

    //Cara gris
    glPushMatrix();
        mover();
        // glColor3ub(200, 200, 200);
        glLineWidth(2);
        //Aplico transformaciones
        // Muevo a la posicion donde quiero la cara
        glTranslatef(0, 0, 0.5);
        // Se rota la figura
        glRotatef(-angle, 1, 0, 0);
        // Muevo al origen
        glTranslatef(0, 0, 0.5);
        glBegin(GL_QUADS);
            glTexCoord2f(0.0, 0.0); glVertex3f(0.5, 0, 0.5);
            glTexCoord2f(0.0, 2.0); glVertex3f(-0.5, 0, 0.5);
            glTexCoord2f(3.0, 2.0); glVertex3f(-0.5, 0, -0.5);
            glTexCoord2f(3.0, 0.0); glVertex3f(0.5, 0, -0.5);
        glEnd();
        // Cara azul claro
        glPushMatrix();
            
            // glColor3ub(66, 245, 203);
            // Aplico transformaciones
            // Muevo a la posicion donde quiero la cara
            glTranslatef(0, 0, 0.5);
            // Se rota la figura
            glRotatef(-angle, 1, 0, 0);
            // Muevo al origen
            glTranslatef(0, 0, 0.5);
            glBegin(GL_QUADS);
                glTexCoord2f(0.0, 0.0); glVertex3f(0.5, 0, 0.5);
                glTexCoord2f(0.0, 1.0); glVertex3f(-0.5, 0, 0.5);
                glTexCoord2f(1.0, 1.0); glVertex3f(-0.5, 0, -0.5);
                glTexCoord2f(1.0, 0.0); glVertex3f(0.5, 0, -0.5);
            glEnd();
        glPopMatrix();
    glPopMatrix();

    
    // Dibujo un punto en el origen
    glPushMatrix();
        mover();
        glColor3ub(0, 0, 0);
        glPointSize(5);
        glBegin(GL_POINTS);
            glVertex2f(0, 0);
        glEnd();
    glPopMatrix();
    glutSwapBuffers();
}

void teclado (unsigned char key, int x, int y)
{
    switch (key) {
        case 27: 
            exit(0);
    }
}

void ajusta(int ancho, int alto) {
    glClearColor(1.0, 1.0, 1.0, 0.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glEnable(GL_DEPTH_TEST); // Habilitamos el z-buffer
    glOrtho(-5, 5, -5, 5, -5, 5);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glEnable(GL_TEXTURE_2D);

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


int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH); // GLU DEPTH es el z-buffer
    glutInitWindowSize(700, 700);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Armado de un cubo");
    creaTexturas();
    glutDisplayFunc(dibuja);
    glutReshapeFunc(ajusta);
    glutKeyboardFunc(teclado);
    glutMouseFunc(startAnimation);
    glutSpecialFunc(rotar);
    glutTimerFunc(20, buildCube, 1);
    glutMainLoop();
    return 0;
}