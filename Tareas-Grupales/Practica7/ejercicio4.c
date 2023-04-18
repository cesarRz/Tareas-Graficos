#ifdef __APPLE__
#define GL_SILENCE_DEPRECATION
#include <GLUT/glut.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#else
#include <GL/glut.h>
#endif

GLuint texturas[5]; //4 texturas
GLubyte pixeles[32][32][3]; //Para textura pixeles (tux)
GLubyte proced[64][64][3]; //Para textura procedural (
GLubyte paleta[6][3]={{230,50,50},{0,0,0},{80,80,80},{255,125,0},{255,255,0},{255,255,255}};

// Funcion para generar texturas random
int t0 = 3;
int t1 = 1;
int t2 = 2;

int counter = 0;

// Dibujar texto ganador
void win(void *tipo, char *s, float x, float y){
    glRasterPos2f(x, y);
    for (int i = 0; i < strlen(s); i++)
        glutBitmapCharacter(tipo, s[i]);
}

//Carga imagen de archivo raw a textura OpenGL
void cargaTextura_raw(int ancho, int alto, const char *archivo, GLuint *text, int id_textura){
    unsigned char * datos;
    FILE * file = fopen( archivo, "rb" );
    if ( file == NULL ){
        printf("archivo no encontrado");
        exit(-1);
    }
    datos = (unsigned char *)malloc(ancho*alto*3);
    fread( datos, ancho * alto * 3, 1, file);
    fclose( file );
    glGenTextures(id_textura, text);
    glBindTexture(GL_TEXTURE_2D, *text);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D,0,GL_RGB,ancho,alto,0,GL_RGB,GL_UNSIGNED_BYTE,datos);
}


void dibuja(void) {

    glClear(GL_COLOR_BUFFER_BIT);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texturas[t0]);
    glBegin(GL_QUADS); 
        glTexCoord2f(0.0, 0.0); glVertex2f(-7, 2);
        glTexCoord2f(1.0, 0.0); glVertex2f(-3, 2);
        glTexCoord2f(1.0, 1.0); glVertex2f(-3, -2);
        glTexCoord2f(0.0, 1.0); glVertex2f(-7, -2);
    glEnd();

    // Segunda textura
    glBindTexture(GL_TEXTURE_2D, texturas[t1]);
    glBegin(GL_QUADS); // Superior
        glTexCoord2f(0.0, 0.0); glVertex2f(-2, 2);
        glTexCoord2f(1.0, 0.0); glVertex2f(2, 2);
        glTexCoord2f(1.0, 1.0); glVertex2f(2, -2);
        glTexCoord2f(0.0, 1.0); glVertex2f(-2, -2);
    glEnd();

    // tercer textura
    glBindTexture(GL_TEXTURE_2D, texturas[t2]);
    glBegin(GL_QUADS); // Superior
        glTexCoord2f(0.0, 0.0); glVertex2f(3, 2);
        glTexCoord2f(1.0, 0.0); glVertex2f(7, 2);
        glTexCoord2f(1.0, 1.0); glVertex2f(7, -2);
        glTexCoord2f(0.0, 1.0); glVertex2f(3, -2);
    glEnd();
    glDisable(GL_TEXTURE_2D);
    //Dibujamos texto cuando se gana...
    if (t0 == t1 && t1 == t2)
    {
        //glColor3ub(0, 0, 0);
        win(GLUT_BITMAP_HELVETICA_18, "You won!", -1, 3);
    }
    glFlush();
}

void ajusta(int ancho,int alto) {
    glClearColor(.5,.5,.5,1);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-8, 8,-8, 8,-4,4);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void carga_texturas(){
    cargaTextura_raw(1024, 1024, "./textureImages/texture4raw.data", &texturas[0], 0);
    cargaTextura_raw(1024, 1024, "./textureImages/texture5raw.data", &texturas[1], 1);
    cargaTextura_raw(1024, 1024, "./textureImages/texture6raw.data", &texturas[2], 2);
    cargaTextura_raw(1024, 1024, "./textureImages/texture7raw.data", &texturas[3], 3);
    cargaTextura_raw(1024, 1024, "./textureImages/texture8raw.data", &texturas[4], 4);
}

void changeTextures (int num) {

    switch (num)
    {
    case 0:
        t0 = rand()%5;
        counter++;
        break;
    case 1:
        t1 = rand()%5;
        counter++;
        break;
    case 2:
        t2 = rand()%5;
        counter++;
        break;
    default:
        break;
    }

    if (counter == 3)
    {
        glutTimerFunc(0, NULL, 0);
        counter = 0;
    } else
    {
        glutTimerFunc(500, changeTextures, counter);
    }
    glutPostRedisplay();
}

void teclado(unsigned char key,int x,int y){
    
    if (key==27) {
        for( int i=0; i<4; i++) glDeleteTextures( i, &texturas[i] );
        exit(0);
    }

    if (key=='p') {
        glutTimerFunc(500, changeTextures, counter);
    }
}


int main(int argc,char **argv) {
    glutInit(&argc,argv);
    glutInitWindowSize(600, 600);
    glutInitDisplayMode(GLUT_RGB|GLUT_SINGLE);
    glutCreateWindow("Practica 7 - Ejercicio 4");
    carga_texturas();
    glutDisplayFunc(dibuja);
    glutReshapeFunc(ajusta);
    glutKeyboardFunc(teclado);
    glutMainLoop();
    return 0;
}