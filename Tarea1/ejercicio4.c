#include <stdio.h>
#include <ctype.h>

int main(){
	char c;
	int renglones=1;
	int car=0;
	int espacios=0;
	
	FILE *fp;
	fp=fopen("dibujo_cesar.txt","r");
    
    if(fp==NULL) {
		printf("No se puede leer archivo");
	}else{

        while((c=fgetc(fp)) != EOF){
            printf("%c",c);
            if(c=='\n'){
                renglones++;
            }
            if(isspace(c)){
                espacios++;	
            } else {
                car++;
            }
        }
        printf("\nReglones: %i\n",renglones);
        printf("Caracteres: %i\n",car);
        printf("Espacios: %i\n",espacios);
        fclose(fp);
    }
	
}