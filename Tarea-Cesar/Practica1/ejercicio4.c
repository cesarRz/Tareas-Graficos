#ifdef __APPLE__
#define GL_SILENCE_DEPRECATION
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 7


void ajusta () {
    glClearColor(0.9, 0.9, 0.9, 0.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, 640, 0, 480);
}


void dibuja_ascii(int base_x, int base_y){

    char c;
    int y = base_y; 
    int x = base_x;
	
	FILE *fp;
	fp=fopen("ascii.txt","r");
    
    if(fp==NULL) {
		printf("No se puede leer archivo");
	}else{

        while((c=fgetc(fp)) != EOF){
            glRasterPos2i(x,y); 
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);
            x += 10;
            if(c=='\n'){
                y = y - 20;
                x = base_x;
            }
        
            
        }

    }
	
}


int *fill_array() {
   int i, j, num;
   int check;
   static int arr[SIZE];

   
   srand(time(NULL));

   for (i = 0; i < SIZE; i++) {
      do {
         check = 1;
         num = rand() % 8;
         for (j = 0; j < i; j++) {
            if (arr[j] == num) {
               check = 0;
               break;
            }
         }
      } while (!check);

      arr[i] = num;
   }

   return arr;
}

void dibuja(){

   int color[8][3] = {
      {255, 0, 0},    // rojo
      {0, 255, 0},    // verde
      {0, 0, 255},    // azul
      {255, 255, 0},  // amarillo
      {255, 0, 255},  // magenta
      {0, 255, 255},  // cian
      {128, 128, 128},// gris
      {255, 255, 255} // blanco
   };

    glClear(GL_COLOR_BUFFER_BIT);

    // Code    
    int base_x = 50;
    int base_y = 400;
    int y = base_y; 
    int x = base_x;
    int *arr = fill_array();
    int r;
    int a=0;

    for (int j = 1; j <= 2; j++)
    {
        for (int i = 1; i <= 3; i++)
        {
            r = arr[a];
            printf("%d\n",color[r][0]);
            printf("%d\n",color[r][1]);
            printf("%d\n",color[r][2]);
            glColor3ub(color[r][0], color[r][1], color[r][2]);
            dibuja_ascii(x, y);
            y-= 100;
            a +=1;
        }
        x = base_x + 350;
        y = base_y;
    }
    
    


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
    glutMainLoop();
    return 0;
}