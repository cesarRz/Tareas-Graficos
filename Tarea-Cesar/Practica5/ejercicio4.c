#ifdef __APPLE__
#define GL_SILENCE_DEPRECATION
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <math.h>
#include <stdlib.h>

int g_ancho= 960; 
int g_alto = 600;
float asp;
float static_aspect = 1.6;


void ciclo2(){
    int a = 2;
    int b = 3;
    int c = 20;
    GLfloat x, y, z;
    glTranslatef(0,2,0);
    glRotatef(90,1.0,0.0,0.0);
    glBegin(GL_POINTS);
    glColor3ub(140,25,200);
    for (float i = 0; i < 2*M_PI; i+=0.0001)
    {
        x = (a*sin(c*i) + b)* cos(i);
        y = (a*sin(c*i) + b)* sin(i);
        z = a * cos(c*i);

        glVertex3f(x,y,z);
    }
    glEnd();
}

void ciclo3(){
    GLfloat y;
    glBegin(GL_LINE_STRIP);
    glColor3ub(140,25,200);
    for (float x = -10; x <= 10; x+=0.3){
        for (float z = -10; z <= 10; z+=0.3)
            {
            y = 12 * (sin(sqrt((x*x) + (z*z))) / sqrt((x*x) + (z*z)) );
            glVertex3f(x,y,z);
            }
    }
    glEnd();
}

void Bresenham(int centro_x, int centro_y, int radio){
    int x = 0;
    int y = radio;
    int e = 3 - 2 * radio;

    glBegin(GL_POINTS);
    while (x < y)
    {
        glVertex3i(centro_x + x, centro_y + y , 0);
        glVertex3i(centro_x + y, centro_y + x , 0);
        glVertex3i(centro_x - x, centro_y + y , 0);
        glVertex3i(centro_x - y, centro_y + x , 0);
        glVertex3i(centro_x + x, centro_y - y , 0);
        glVertex3i(centro_x + y, centro_y - x , 0);
        glVertex3i(centro_x - x, centro_y - y , 0);
        glVertex3i(centro_x - y, centro_y - x , 0);

        if (e > 0)
        {
            e = e + 4*(x-y) + 10;
            y = y-1;
        }else
        {
            e = e +4*x+6;
        }
            x = x+1;
    }
    if (x == y)
    {
        glVertex3i(centro_x + x, centro_y + y , 0);
        glVertex3i(centro_x + y, centro_y + x , 0);
        glVertex3i(centro_x - x, centro_y + y , 0);
        glVertex3i(centro_x - y, centro_y + x , 0);
        glVertex3i(centro_x + x, centro_y - y , 0);
        glVertex3i(centro_x + y, centro_y - x , 0);
        glVertex3i(centro_x - x, centro_y - y , 0);
        glVertex3i(centro_x - y, centro_y - x , 0);
    }


    glEnd();

}

void dibujaSeno(){
    // Creamos el eje
    glColor3f(0.0, 0.0, 0.0);
    glLineWidth(2);
    glBegin(GL_LINES);
        glVertex2f(-M_PI, 0);
        glVertex2f(M_PI, 0);
        glVertex2f(0, 1);
        glVertex2f(0, -1);
    glEnd();
    // Graficamos el seno
    glLineWidth(3);
    glColor3f(0.0, 0.0, 0.0);
    glBegin(GL_LINE_STRIP);
        for (float i = -3.1416; i <= 3.1416; i+= 0.1)
        {
            float x = i; 
            float y = sin(i);
            glVertex2f(x, y);
        }
    glEnd();
}

void dibuja(void)
{
    float alto, ancho;

    glClearColor(1.0, 1.0, 1.0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT);


        if (static_aspect <= asp)
        {
            alto = g_alto / 2;
            ancho = alto * static_aspect;
        }else{
            ancho = g_ancho /2;
            alto = ancho / static_aspect;
        }
    
        // Lineas
        glColor3f(1.0, 0.0, 0.0);
        glViewport(0, 0, g_ancho, g_alto);
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        gluOrtho2D(0,960,0, 600);
        glPointSize(5);

        glBegin(GL_LINES);
            glVertex3d(480, 0,0);
            glVertex3d(480, 600,0);
            
            glVertex3d(0, 300,0);
            glVertex3d(960, 300,0);
        glEnd();
        

        glColor3f(0.7, 0.0, 1.0);
        glLineWidth(3);

        // Arriba Izquierda
        glViewport(0, g_alto / 2, ancho, alto);
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        gluOrtho2D(-M_PI, M_PI, -1, 1);
        glPointSize(2);
        glPushMatrix();
            dibujaSeno();
        glPopMatrix();

        // Arriba Derecha
        glEnable(GL_DEPTH_TEST);
        glViewport(g_ancho/2, g_alto/2, ancho, alto);
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glOrtho(-15,15,-15,15,-30,30);
        
        glPushMatrix();
            glTranslatef(0.0, 0.0, -3);
            glRotated( 45, 1.0, 0.0, 0.0);
            glRotated( 20, 0.0, 1.0, 0.0);
            ciclo3();
        glPopMatrix();

        // Abajo Izquierda
        glEnable(GL_DEPTH_TEST);
        glViewport(0, 0, ancho, alto);
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glOrtho(-15,15,-15,15,-30,30);
        glPointSize(1);

        glPushMatrix();
            glRotatef(45.0, 1.0, 0.0, 0.0);
            // glRotatef(70.0, 0.0, 1.0, 0.0);
            glScalef(1.8, 1.8, 1.8);
            ciclo2();
        glPopMatrix();
        
        // Abajo derecha
        glViewport(g_ancho/2, 0, ancho, alto);
        glLoadIdentity();
        gluOrtho2D(0,480,0, 300);
        glPointSize(2);
        
        glPushMatrix();
            Bresenham(240,150,100);
        glPopMatrix();

   
    glFlush();
}

void ajusta(int ancho, int alto){
    float aspecto = (float)alto / ancho;
    if (aspecto > (float)ancho/alto)
        glViewport (0,0,ancho,ancho/aspecto);
    else
        glViewport (0,0,alto*aspecto,alto);

    g_ancho = ancho;
    g_alto = alto;
    asp = (float)ancho/alto;

}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(960, 600);
    glutInitWindowPosition(100, 150);
    glutCreateWindow("ejercicio 4");
    glutReshapeFunc(ajusta);
    glutDisplayFunc(dibuja);
    glutMainLoop();
    return 0;
}