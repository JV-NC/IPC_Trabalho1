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

typedef struct { //no para fila de prioridade, com coordenada do seu antecessor;
    int x, y, dist, px, py;
}Node;

void setTextColor(int textColor, int backgroundColor); //altera a cor do texto e do fundo;
int counter(char *name, int *lin, int *col); //conta a quantidade de linhas e colunas do arquivo;
int readMatrix(char *name, char ***map, int *lin, int *col); //le o arquivo e preenche a matriz;
void printMatrix(char** map, int lin, int col); //imprime matriz;
void freeMatrix(char **map, int lin); //libera memoria matriz;
int findHumanZone(char **map, int lin, int col, int *hx, int *hy, int *zx, int *zy); //encontra o humano e a zona segura na matriz;
int isValid(char **map, int lin, int col, int x, int y, int **visited); //verifica se a posi��o da matriz � v�lida para o caminho;
int bfs(char ***map, int lin, int col, int startX, int startY, int endX, int endY); //busca em largura, retorna dist�ncia e preenche caminho;
int fuga_humana(char ***map,int lin, int col); //aplica findHumanZone e bfs;

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
    int dist = fuga_humana(&map,lin,col);
    if(dist==-1){
    	printf("Caminho nao encontrado");
	}else{
		printf("\tdistancia = %d\n",dist);
		printMatrix(map,lin,col);
	}
    
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
	for(c=fgetc(arq);c!=EOF;c=fgetc(arq)){ //conta linhas e caracteres da primeira linha;
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
        return 0; //falha abrir arquivo;
    }
    
    *map = (char**)malloc((*lin)*sizeof(char*)); //alocacao de memoria do mapa;
	for(int i=0;i<(*lin);i++){
		(*map)[i]=(char*)malloc(((*col)+1)*sizeof(char));
	}
	for(int i=0;i<(*lin);i++){ //ler arquivo na matriz;
		fgets((*map)[i],((*col)+1),arq);
		fgetc(arq);
		(*map)[i][strlen((*map)[i])-1]='\0';
		for(int j=0;j<(*col);j++){ //limpa caracteres n�o esperados, substituindo por ' ';
			if((*map)[i][j]!=' ' && (*map)[i][j]!='R' && (*map)[i][j]!='Z' && (*map)[i][j]!='H'){
				(*map)[i][j]=' ';
			}
		}
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
    printf("\n");
}

void freeMatrix(char **map, int lin){
    for(int i=0;i<lin;i++){
        free(map[i]);
    }
    free(map);
}

int findHumanZone(char **map, int lin, int col, int *hx, int *hy, int *zx, int *zy){
	int findH=0,findZ=0;
	for(int i=0;i<lin;i++){
		for(int j=0;j<col;j++){
			if(map[i][j]=='H'){ //encontra humano;
				*hx = i;
				*hy = j;
				findH=1;
			}else if(map[i][j]=='Z'){ //encontra zona;
				*zx = i;
				*zy = j;
				findZ = 1;
			}
			if(findH && findZ){ //retorna sucesso;
				return 1;
			}
		}
	}
	return 0; //nao encontrado;
}

int isValid(char **map, int lin, int col, int x, int y, int **visited){ //verifica se x e y no intervalo, se vazio ou zona e se j� foi visitado;
	return (x>=0 && x<lin && y>=0 && y<col && (map[x][y]==' ' || map[x][y]=='Z') && !visited[x][y]);
}

int bfs(char ***map, int lin, int col, int startX, int startY, int endX, int endY){
	int **visited = (int**)calloc(lin,sizeof(int*)); //aloca memoria para a matriz de visitados;
	for(int i=0;i<lin;i++){
		visited[i] = (int*)calloc(col,sizeof(int));
	}
	int dir[4] = {-1,1,0,0}; //direcoes possiveis de uma coordenada;
	
	Node *queue = (Node*)malloc(lin*col*sizeof(Node)); //aloca 'fila' de nos/coordenadas para visitar;
	int first = 0, last = 0;
	
	queue[last++] = (Node){startX, startY, 0, -1, -1}; //inicia pelo humano;
	visited[startX][startY] = 1;
	
	Node aux;
	while(first<last){ //enquanto houver caminho;
		aux = queue[first++];
		if(aux.x == endX && aux.y == endY){ //encontrou destino;
			//recontroi caminho encontrado
			int cx = aux.x, cy = aux.y;
			while(aux.px!=-1 && aux.py!=-1){ //enquanto nao for o inicio;
				if((*map)[cx][cy]!='Z'){ //se nao for a zona, marca caminho
					(*map)[cx][cy] = '*';
				}
				
				for(int i=0;i<last;i++){ //procura antecessor da coordenada atual;
					if(queue[i].x==aux.px && queue[i].y==aux.py){
						aux = queue[i];
						cx = aux.x;
						cy= aux.y;
						break;
					}
				}
			}
			//liberar memoria
			for (int i = 0; i < lin; i++) {
				free(visited[i]);
			}
			free(visited);
			free(queue);
			return queue[first-1].dist; //retorna distancia;
		}
		
		for(int i=0;i<4;i++){
			int nx = aux.x + dir[i];
			int ny = aux.y + dir[3-i]; //percorre de tras para frente;
			if(isValid(*map,lin,col,nx,ny,visited)){
				visited[nx][ny] = 1; //marca visita;
				queue[last++] = (Node){nx,ny,aux.dist+1,aux.x,aux.y}; //adiciona na fila;
			}
		}
	}

	//liberar memoria
	for (int i = 0; i < lin; i++) {
		free(visited[i]);
	}
	free(visited);
	free(queue);
	
	return -1;
}

int fuga_humana(char ***map,int lin, int col){
	int hx,hy,zx,zy;
	if(!findHumanZone(*map,lin,col,&hx,&hy,&zx,&zy)){ //verifica se ha humano e zona na matriz;
		return -1;
	}

	int result = bfs(map,lin,col,hx,hy,zx,zy); //chama busca em largura e recebe a distancia;
	
	return result;
}
