#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#define BLACK 0
#define BLUE 1
#define GREEN 2
#define RED 4
#define YELLOW 6
#define WHITE 7
#define ARCHIVE "matrix.txt"

void setTextColor(int textColor, int backgroundColor);
int counter(char *name, int *lin, int *col);
int readMatrix(char *name, char ***map, int *lin, int *col);
void printMatrix(char** map, int lin, int col);
void freeMatrix(char **map, int lin);
int fuga_humana(char ***map,int lin, int col);
int bfs(char ***map, int lin, int col, int startX, int startY, int endX, int endY);

int main(){
    char **map;
    int lin,col;
    if(!counter(ARCHIVE,&lin,&col)){
    	printf("Falha ler arquivo!\n");
    	return -1;
	}
    if(!readMatrix(ARCHIVE,&map,&lin,&col)){
    	printf("Falha ler arquivo!\n");
    	return -1;
    }
    
    printMatrix(map,lin,col);
    freeMatrix(map,lin);

    return 0;
}

void setTextColor(int textColor, int backgroundColor){
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE); //obtem o identificador do console de saida;
    
    int color = textColor + (backgroundColor * 16); //combina a cor do texto e do fundo em hexadecimal;
    
    SetConsoleTextAttribute(hConsole, color); //define as cores no console;
}

int counter(char *name, int *lin, int *col){
	FILE *arq = fopen(name,"r");
	if(arq==NULL){
		return 0;
	}
	char c;
	*lin=0;
	*col=0;
	for(c=fgetc(arq);c!=EOF;c=fgetc(arq)){
		if(c=='\n'){
			(*lin)++;
		}
		if(*lin==0){
			(*col)++;
		}
	}
	if((*col)==0 || (*lin)==0){
		return -1; //arquivo vazio ou invalido;
	}
	(*lin)++;
	fclose(arq);
	return 1;
}

int readMatrix(char *name, char ***map, int *lin, int *col){
    FILE *arq = fopen(name,"r");
    if(arq == NULL){
        return 0;
    }
    
    *map = (char**)malloc((*lin)*sizeof(char*));
	for(int i=0;i<(*lin);i++){
		(*map)[i]=(char*)malloc(((*col)+1)*sizeof(char));
	}
	for(int i=0;i<(*lin);i++){
		fgets((*map)[i],((*col)+1),arq);
		fgetc(arq);
		(*map)[i][strlen((*map)[i])-1]='\0';
	}
    
    fclose(arq);

    return 1;
}

void printMatrix(char** map, int lin, int col){
	printf("\n");
    for(int i=0;i<lin;i++){
    	printf("   ");
        for(int j=0;j<col;j++){
            if(map[i][j]=='H'){
                setTextColor(BLACK,BLUE);
                printf(" H ");
                setTextColor(WHITE,BLACK);
            }
            else if(map[i][j]=='R'){
                setTextColor(BLACK,RED);
                printf(" R ");
                setTextColor(WHITE,BLACK);
            }
            else if(map[i][j]=='Z'){
                setTextColor(BLACK,GREEN);
                printf(" Z ");
                setTextColor(WHITE,BLACK);
            }
            else if(map[i][j]=='*'){
                setTextColor(BLACK,YELLOW);
                printf(" * ");
                setTextColor(WHITE,BLACK);
            }
            else{
                setTextColor(BLACK,WHITE);
                printf("   ");
                setTextColor(WHITE,BLACK);
            }
        }
        printf("\n");
    }
}

void freeMatrix(char **map, int lin){
    for(int i=0;i<lin;i++){
        free(map[i]);
    }
    free(map);
}

int fuga_humana(char ***map,int lin, int col){
	
}
