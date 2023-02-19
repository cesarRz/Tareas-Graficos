#ifdef __APPLE__
#define GL_SILENCE_DEPRECATION
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
#include <math.h>

int lados = 20;

float xc=50, yc=125, velX=5, velY=5, radio=25;
GLubyte paleta[3][3]={ {0,0,0},{255,0,0},{0,0,255} };
enum colores{negro, rojo, azul};
enum colores col=negro;
GLenum modo=GL_POLYGON;    // wireframe o solida
void circulo(float x, float y, int seg){
   int i;
   glBegin(modo);
     for(i=0; i<=360; i+=360/seg)
         glVertex2i(x+radio*cos(i*M_PI/180),y+radio*sin(i*M_PI/180));
   glEnd();
}
void ajusta(int ancho, int alto){
   glClearColor(1.0,1.0,1.0,0.0);
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   gluOrtho2D(0, 640, 0, 480);
}
void dibuja(void){
   glClear(GL_COLOR_BUFFER_BIT);
   glColor3ubv(paleta[col]);
   circulo(xc,yc,lados);
   glutSwapBuffers();
}
void anima(void){
   if (xc+radio >= 640 || xc-radio <= 0) velX = -velX;
   if (yc+radio >= 480 || yc-radio <= 0) velY = -velY;
   xc += velX;   yc += velY;
   glutPostRedisplay();
}
void cambia(int opcion){
   switch(opcion){
        case 10 : modo = GL_POLYGON; break;
        case 5 : modo = GL_LINE_LOOP; break;
        case 3:
            lados = 3;
            break;
        case 8:
            lados = 8;
            break;
        case 12:
            lados = 12;
            break;
        case 18:
            lados = 18;
            break;
        case 20:
            lados = 20;
            break;
      case 100 : exit(0);
   }
   glutPostRedisplay();
}
void pinta(unsigned char tecla, int x, int y) {
    switch(tecla) {
      case 'n':	col= negro; break;
      case 'r':	col = rojo; break;
      case 'a':	col= azul;
    }
    glutPostRedisplay();
}

int main(int argc, char** argv){
   glutInit(&argc, argv);
   glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
   glutInitWindowSize(640,480);
   glutInitWindowPosition(100, 150);
   glutCreateWindow("Pelotita");
   glutReshapeFunc(ajusta);
   glutIdleFunc(anima);
   glutDisplayFunc(dibuja);
   glutKeyboardFunc(pinta);
   glutCreateMenu(cambia);
    glutAddMenuEntry("Solido",10);
    glutAddMenuEntry("Wireframe",5);
    glutAddMenuEntry("3 lados", 3);
    glutAddMenuEntry("8 lados", 8);
    glutAddMenuEntry("12 lados", 12);
    glutAddMenuEntry("18 lados", 18);
    glutAddMenuEntry("20 lados", 20);
    glutAddMenuEntry("Salir", 100);
   glutAttachMenu(GLUT_RIGHT_BUTTON);
   glutMainLoop();
   return 0;
}
