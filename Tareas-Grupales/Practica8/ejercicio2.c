#ifdef __APPLE__
#define GL_SILENCE_DEPRECATION
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <stdlib.h>

GLfloat ptosctl[4][4][3] = {
    {{-8, 0, 8}, {-2, -7.5, 8.0}, {2, -7.5, 8}, {8, 0, 8}},
    {{-9, 0, 2}, {-2, -7.5, 2.0}, {2, -7.5, 2}, {9, 0, 2}},
    {{-9, 0, -2}, {-2, 4.5, -2.0}, {2, 4.5, -2}, {9, 0, -2}},
    {{-8, 0, -8}, {-2, 4.5, -8.0}, {2, 4.5, -8}, {8, 0, -8}}};

int px, py = 0;

GLboolean puntos = GL_TRUE;
GLboolean edit = GL_FALSE;
char eje_edit = 'x';

GLfloat girax = 0, giray = 0, zoom = 0;
void mover(void)
{
    glTranslated(0, 0, zoom);
    glRotated(giray, 0.0, 1.0, 0.0);
    glRotated(girax, 1.0, 0.0, 0.0);
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

void inicializa(void)
{
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glMap2f(GL_MAP2_VERTEX_3, 0, 1, 3, 4, 0, 1, 12, 4, &ptosctl[0][0][0]);
    glEnable(GL_MAP2_VERTEX_3);
}
void dibuja(void)
{
    int i, j;
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 0.0, 0.0);

    glPushMatrix();
    mover();
    creaEjes();
    glRotatef(30.0, 1.0, 0.0, 0.0);

    // Superficie de Bezier
    glColor3f(1.0, 0.0, 0.0);
    glLineWidth(2);
    glMapGrid2f(20, 0, 1, 10, 0, 1);
    glEvalMesh2(GL_LINE, 0, 20, 0, 10);

    // Puntos de control
    if (puntos){
        glPointSize(7.0);
        glBegin(GL_POINTS);
        for (i = 0; i < 4; i++)
        {
            for (j = 0; j < 4; j++)
            {
                if (px == j && py == i)
                {
                    glColor3f(0.0, 0.0, 1.0);
                }
                else
                {
                    glColor3f(0.0, 0.0, 0.0);
                }

                glVertex3fv(&ptosctl[i][j][0]);
            }
        }
        glEnd();
    }

    glPopMatrix();
    glFlush();
}
void ajusta(int ancho, int alto)
{
    glViewport(0, 0, ancho, alto);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-12.0, 12.0, -12.0, 12.0, -12.0, 12.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void change_coordenates(int mov){

    if (eje_edit == 'x'){
        ptosctl[py][px][0] =  ptosctl[py][px][0] + mov;
    }
    else if (eje_edit == 'y'){
        ptosctl[py][px][1] =  ptosctl[py][px][1] + mov;
    }
    else if (eje_edit == 'z'){
        ptosctl[py][px][2] =  ptosctl[py][px][2] + mov;
    }
    inicializa();
}

// Funciones con Teclas
void teclado(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 27:
        exit(0);
    case '+':
        change_coordenates(1);
        break;
    case '-':
        change_coordenates(-1);
        break;
    case 'p':
        puntos = !puntos;
        break;
    case 'o':
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glOrtho(-15, 15, -15, 15, -30, 30);
        zoom = 0;
    case 'w':
        girax -= 15;
        break;
    case 's':
        girax += 15;
        break;
    case 'a':
        giray -= 15;
        break;
    case 'd':
        giray += 15;
        break;
    case 'x':
        eje_edit = 'x';
        break;
    case 'y':
        eje_edit = 'y';
        break;
    case 'z':
        eje_edit = 'z';
        break;
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
        if (px > 0)
        {
            px--;
        }
        break;
    case GLUT_KEY_RIGHT:
        if (px < 3)
        {
            px++;
        }
        break;
    case GLUT_KEY_UP:
        if (py < 3)
        {
            py++;
        }
        break;
    case GLUT_KEY_DOWN:

        if (py > 0)
        {
            py--;
        }

        break;
    }
    glutPostRedisplay();
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(10, 10);
    glutCreateWindow("Superficie de Bezier");
    inicializa();
    glutReshapeFunc(ajusta);
    glutDisplayFunc(dibuja);
    glutKeyboardFunc(teclado);
    glutSpecialFunc(rotar);
    glutMainLoop();
    return 0;
}
