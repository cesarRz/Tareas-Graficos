#ifdef __APPLE__
#define GL_SILENCE_DEPRECATION
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif


int paleta[4][4]={{192, 192, 192, 255},{255, 0, 0, 255},{255, 255, 0, 255},{0, 255, 0, 255}};
int color_rojo[4] = {192, 192, 192, 255};
int color_verde[4] = {192, 192, 192, 255};
int color_amarillo[4] = {192, 192, 192, 255};

int foco = 0;

void ajusta () {
    glClearColor(0.9, 0.9, 0.9, 0.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, 640, 0, 480);
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


void dibuja_triangulo(int base_x, int base_y, int color[4]){

    glColor4ub(color[0], color[1], color[2], color[3]);

    glBegin(GL_TRIANGLES);
        glVertex2i(base_x, base_y);
        glVertex2i(base_x + 50, base_y);
        glVertex2i(base_x + 25, base_y + 50);
    glEnd();
}

void dibuja(){
    glClear(GL_COLOR_BUFFER_BIT);

    dibuja_triangulo(300, 340, color_rojo);
    dibuja_triangulo(300, 240, color_amarillo);
    dibuja_triangulo(300, 140, color_verde);
    
    glFlush();
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(640,480);
    glutInitWindowPosition(100, 150);
    glutCreateWindow("Ejercicio 4");
    glutReshapeFunc(ajusta);
    glutDisplayFunc(dibuja);
    glutTimerFunc(2, animaT, 0);
    glutMainLoop();
    return 0;
}