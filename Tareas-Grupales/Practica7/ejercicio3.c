#ifdef __APPLE__
#define GL_SILENCE_DEPRECATION
#include <GLUT/glut.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#else
#include <GL/glut.h>
#endif

GLuint texturas[3]; //4 texturas
GLubyte pixeles[32][32][3]; //Para textura pixeles (tux)
GLubyte proced[64][64][3]; //Para textura procedural (
GLubyte paleta[6][3]={{230,50,50},{0,0,0},{80,80,80},{255,125,0},{255,255,0},{255,255,255}};

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
    glBindTexture(GL_TEXTURE_2D, texturas[0]);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    // Primera textura
    glBegin(GL_QUADS); 
        glTexCoord2f(0.0,0.0); glVertex2f(-6, 6);
        glTexCoord2f(1.0,0.0); glVertex2f(-2, 6);
        glTexCoord2f(1.0,1.0); glVertex2f(-2, 2);
        glTexCoord2f(0.0,1.0); glVertex2f(-6, 2);
    glEnd();

    // Segunda textura
    glBindTexture(GL_TEXTURE_2D, texturas[1]);
    glBegin(GL_QUADS); // Superior
        glTexCoord2f(0.0,0.0); glVertex2f(-2, 6);
        glTexCoord2f(1.0,0.0); glVertex2f(2, 6);
        glTexCoord2f(1.0,1.0); glVertex2f(2, 2);
        glTexCoord2f(0.0,1.0); glVertex2f(-2, 2);
    glEnd();

    // tercer textura
    glBindTexture(GL_TEXTURE_2D, texturas[2]);
    glBegin(GL_QUADS); // Superior
        glTexCoord2f(0.0,0.0); glVertex2f(2, 6);
        glTexCoord2f(1.0,0.0); glVertex2f(6, 6);
        glTexCoord2f(1.0,1.0); glVertex2f(6, 2);
        glTexCoord2f(0.0,1.0); glVertex2f(2, 2);
    glEnd();

    // Segunda linea
    // Primera textura
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_BLEND);
    glBindTexture(GL_TEXTURE_2D, texturas[0]);
    glBegin(GL_QUADS); 
        glTexCoord2f(0.0, 1.0); glVertex2f(-6, 2);
        glTexCoord2f(1.0, 1.0); glVertex2f(-2, 2);
        glTexCoord2f(1.0, 0.0); glVertex2f(-2, -2);
        glTexCoord2f(0.0, 0.0); glVertex2f(-6, -2);
    glEnd();

    // Segunda textura
    glBindTexture(GL_TEXTURE_2D, texturas[1]);
    glBegin(GL_QUADS); // Superior
        glTexCoord2f(0.0, 1.0); glVertex2f(-2, 2);
        glTexCoord2f(1.0, 1.0); glVertex2f(2, 2);
        glTexCoord2f(1.0, 0.0); glVertex2f(2, -2);
        glTexCoord2f(0.0, 0.0); glVertex2f(-2, -2);
    glEnd();

    // tercer textura
    glBindTexture(GL_TEXTURE_2D, texturas[2]);
    glBegin(GL_QUADS); // Superior
        glTexCoord2f(0.0, 1.0); glVertex2f(2, 2);
        glTexCoord2f(1.0, 1.0); glVertex2f(6, 2);
        glTexCoord2f(1.0, 0.0); glVertex2f(6, -2);
        glTexCoord2f(0.0, 0.0); glVertex2f(2, -2);
    glEnd();

    // Tercera linea
    // Primera textura
    glColor3ub(0, 0, 255);
    // Fondo
    glBegin(GL_QUADS); 
        glTexCoord2f(1.0, 0.0); glVertex2f(-6, -2);
        glTexCoord2f(1.0, 1.0); glVertex2f(-2, -2);
        glTexCoord2f(0.0, 1.0); glVertex2f(-2, -6);
        glTexCoord2f(0.0, 0.0); glVertex2f(-6, -6);
    glEnd();
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_ADD);
    glBindTexture(GL_TEXTURE_2D, texturas[0]);
    glBegin(GL_QUADS); 
        glTexCoord2f(1.0, 0.0); glVertex2f(-6, -2);
        glTexCoord2f(1.0, 1.0); glVertex2f(-2, -2);
        glTexCoord2f(0.0, 1.0); glVertex2f(-2, -6);
        glTexCoord2f(0.0, 0.0); glVertex2f(-6, -6);
    glEnd();

    // Segunda textura
    glColor3ub(0, 255, 255);
    // Fondo
    glBegin(GL_QUADS); // Superior
        glTexCoord2f(1.0, 0.0); glVertex2f(-2, -2);
        glTexCoord2f(1.0, 1.0); glVertex2f(2, -2);
        glTexCoord2f(0.0, 1.0); glVertex2f(2, -6);
        glTexCoord2f(0.0, 0.0); glVertex2f(-2, -6);
    glEnd();
    glBindTexture(GL_TEXTURE_2D, texturas[1]);
    glBegin(GL_QUADS); // Superior
        glTexCoord2f(1.0, 0.0); glVertex2f(-2, -2);
        glTexCoord2f(1.0, 1.0); glVertex2f(2, -2);
        glTexCoord2f(0.0, 1.0); glVertex2f(2, -6);
        glTexCoord2f(0.0, 0.0); glVertex2f(-2, -6);
    glEnd();

    // tercer textura
    glColor3ub(255, 100, 0);
    glBegin(GL_QUADS); // Superior
        glTexCoord2f(1.0, 0.0); glVertex2f(2, -2);
        glTexCoord2f(1.0, 1.0); glVertex2f(6, -2);
        glTexCoord2f(0.0, 1.0); glVertex2f(6, -6);
        glTexCoord2f(0.0, 0.0); glVertex2f(2, -6);
    glEnd();
    glBindTexture(GL_TEXTURE_2D, texturas[2]);
    glBegin(GL_QUADS); // Superior
        glTexCoord2f(1.0, 0.0); glVertex2f(2, -2);
        glTexCoord2f(1.0, 1.0); glVertex2f(6, -2);
        glTexCoord2f(0.0, 1.0); glVertex2f(6, -6);
        glTexCoord2f(0.0, 0.0); glVertex2f(2, -6);
    glEnd();

    glFlush();
}

void ajusta(int ancho,int alto) {
    glClearColor(.5,.5,.5,1);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-6, 6,-6, 6,-4,4);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void carga_texturas(){
    cargaTextura_raw(500, 500, "./textureImages/texture1raw.data", &texturas[0], 0);
    cargaTextura_raw(1024, 1024, "./textureImages/texture2raw.data", &texturas[1], 1);
    cargaTextura_raw(1024, 1024, "./textureImages/texture3raw.data", &texturas[2], 2);
}


void salir(unsigned char key,int x,int y){
    if (key==27) {
        for( int i=0; i<4; i++) glDeleteTextures( i, &texturas[i] );
        exit(0);
    }
}


int main(int argc,char **argv) {
    glutInit(&argc,argv);
    glutInitWindowSize(600, 600);
    glutInitDisplayMode(GLUT_RGB|GLUT_SINGLE);
    glutCreateWindow("Practica 7 - Ejercicio 3");
    carga_texturas();
    glutDisplayFunc(dibuja);
    glutReshapeFunc(ajusta);
    glutKeyboardFunc(salir);
    glutMainLoop();
    return 0;
}