#ifdef __APPLE__
#define GL_SILENCE_DEPRECATION
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <stdio.h>
#include <stdlib.h>
#include <math.h>


GLfloat mat_ambiente[] = {0.329, 0.223, 0.027, 1.0};
GLfloat mat_difuso[] = {0.780, 0.568, 0.113, 1.0};
GLfloat mat_especular[]= {0.992, 0.941, 0.807, 1.0};
GLfloat mat_brillo[] = {128*0.21794};
GLfloat no_mat[] = { 0.0, 0.0, 0.0, 1.0};
GLfloat ceros[] = { 0.0, 0.0, 0.0, 0};



GLUquadricObj *cilindro;
GLfloat  girax = 0, giray= 0, zoom=0;
GLboolean malla = GL_FALSE, ejes = GL_TRUE;

GLfloat paleta[4][4] = {{0.75, 0.75, 0.75, 1},
                      {1, 0, 0, 0.6},
                      {1, 1, 0, 0.6},
                      {0, 1, 0, 0.6}};

GLfloat color_rojo[4] = {0.75, 0.75, 0.75, 1};
GLfloat color_verde[4] = {0.75, 0.75, 0.75, 1};
GLfloat color_amarillo[4] = {0.75, 0.75, 0.75, 1};

int foco = 0;



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

void animaT(int v){

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
        foco ++;
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

        foco ++;
        break;

    case 2:
        color_verde[0] = paleta[0][0];
        color_verde[1] = paleta[0][1];
        color_verde[2] = paleta[0][2];
        color_verde[3] = paleta[0][3];

        glutTimerFunc(500, animaT, 0);

        foco ++;
        break;
    case 3:
        color_verde[0] = paleta[3][0];
        color_verde[1] = paleta[3][1];
        color_verde[2] = paleta[3][2];
        color_verde[3] = paleta[3][3];

        glutTimerFunc(500, animaT, 0);

        foco ++;
        break;

    case 4:
        color_verde[0] = paleta[0][0];
        color_verde[1] = paleta[0][1];
        color_verde[2] = paleta[0][2];
        color_verde[3] = paleta[0][3];

        glutTimerFunc(500, animaT, 0);

        foco ++;
        break;

    case 5:
        color_verde[0] = paleta[3][0];
        color_verde[1] = paleta[3][1];
        color_verde[2] = paleta[3][2];
        color_verde[3] = paleta[3][3];

        glutTimerFunc(500, animaT, 0);

        foco ++;
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

void dibuja_circulo(GLfloat base_x, GLfloat base_y, GLfloat color[4]){



    glPushMatrix();
        glMaterialfv(GL_FRONT, GL_AMBIENT, color);
        glMaterialfv(GL_FRONT, GL_DIFFUSE, color);
        glMaterialfv(GL_FRONT, GL_SPECULAR, color);

        if (color == paleta[3])
        {
            GLfloat emision_verde[] = {0,1,0,1};
            
            glMaterialfv(GL_FRONT, GL_EMISSION, emision_verde);
            glMaterialfv(GL_FRONT, GL_SHININESS, 50);
        }
        

        glTranslatef(base_x, base_y,-2.5);
        glScalef(0.1,0.06,0.2);
        glutSolidSphere(10, 200, 200);
    glPopMatrix();
}

void dibuja_cubo(){

    glPushMatrix();
        glScalef(1, 2, -0.5);

        glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, mat_ambiente);
        glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mat_difuso);
        glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mat_especular);
        glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, mat_brillo);
        glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, ceros);

        glutSolidCube(5);


        dibuja_circulo(0, 1.5, color_rojo);
        dibuja_circulo(0, 0, color_amarillo);
        dibuja_circulo(0, -1.5, color_verde);
    glPopMatrix();
    
}

void dibuja(void) {
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

    glPushMatrix();
        mover();
        dibuja_cubo();

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
    case 'p': glMatrixMode(GL_PROJECTION);
              glLoadIdentity();
              gluPerspective(45,1,10,100);
              zoom= -40;
			  break;
    case 'o': glMatrixMode(GL_PROJECTION);
              glLoadIdentity();
              glOrtho(-15,15,-15,15,-30,30);
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
	glClearColor(1.0,1.0,1.0,0.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();  
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45,1,10,100);
    zoom= -40;

    GLfloat PosDireccional[]={0.0, 3.0, -3.0, 0.0};   
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glLightfv(GL_LIGHT0, GL_POSITION, PosDireccional);
    glEnable(GL_NORMALIZE);
    glEnable(GL_DEPTH_TEST);
    
}
int main(int argc, char** argv) {
    glutInitDisplayMode(GLUT_RGB|GLUT_DOUBLE|GLUT_DEPTH);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(500, 500);
    glutInit(&argc, argv);
    glutCreateWindow("Ejercicio 2");
    glutDisplayFunc(dibuja);
    glutReshapeFunc(ajusta);
    glutKeyboardFunc(teclado);
    glutSpecialFunc(rotar);
    glutTimerFunc(2, animaT, 0);
    glutMainLoop();
    return 0;
}
