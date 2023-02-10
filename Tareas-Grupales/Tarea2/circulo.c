#ifdef __APPLE__
#define GL_SILENCE_DEPRECATION
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <math.h>

void ajusta () {
    glClearColor(0.9, 0.9, 0.9, 0.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, 640, 0, 480);
}


void circulo(int r, int centro_x, int centro_y, float color[3]){
  
	int coord[15][2];
	
	int x, y, c, i, j, theta;
	float rad= M_PI/180;
	
	c=0;
	//Fijar puntos
	for(theta=0; theta<360; theta+=(360/15)){
		//cambia r para cambiar el tama�o de la circunferencia
		x= centro_x + (r*(cos(theta*rad)));
		y= centro_y + (r*(sin(theta*rad)));
		coord[c][0]= x;
		coord[c][1]= y;
		c++;
	}
	
	glColor3fv(color);
	glLineWidth(1);
	//Lineas
	for(i=0;i<15;i++){
		c=i+1; //empieza en el punto siguiente
		for(j=0;j<15;j++){
			
			if(c>=15){
				c=0;
			}
			glBegin(GL_LINES);
			glVertex2i(coord[i][0],coord[i][1]);
			glVertex2i(coord[c][0],coord[c][1]);
			glEnd();
			c++;
		}
	}
}

void dibuja(){
    glClear(GL_COLOR_BUFFER_BIT);
    glPointSize(5);
    glBegin(GL_POINTS);
        float c[3] = {1,0,0};
        circulo(50, 320, 240,c);
    glEnd();
    glFlush();
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(640,480);
    glutInitWindowPosition(100, 150);
    glutCreateWindow("Titulo");
    glutReshapeFunc(ajusta);
    glutDisplayFunc(dibuja);
    glutMainLoop();
    return 0;
}