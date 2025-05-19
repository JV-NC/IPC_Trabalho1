#include <stdio.h>
#include <stdlib.h>

int busca_fibonacci(int n, int x); //calcula n termos de fibonacci e busca x entre os termos, retorna indice de x ou -1 caso não encontrar;
int binary_search(long *v, int n, long x); //busca binária do termo x no vetor;

int main(){
    int n,x;
    do{
        printf("Digite, respectivamente, quantidade n de valores de fibonacci e o numero x a ser buscado:\n");
        scanf("%d %d",&n,&x);

        if(n<=0 || x<0){
            printf("Valores invalidos!\n");
        }
    }while(n<=0 || x<0); //repetição até obter valores viáveis;
    
    int i = busca_fibonacci(n,x);
    printf("Indice = %d",i);
    return 0;
}

int busca_fibonacci(int n, int x){
    if(n<=0){
        return -1; //valor n inválido;
    }

    long *v = (long*)malloc(n*sizeof(long));
    v[0]=0;
    if(n>1){ //caso maior que 1;
        v[1]=1;
    }

    for(int i=2;i<n;i++){ //enquanto i<n, soma os termos anteriores para novo fibonacci;
        v[i]=v[i-1]+v[i-2];
    }

    return binary_search(v,n,x); //chama busca binária;
}

int binary_search(long *v, int n, long x){
    int middle,left = 0,right = n-1;

    while(left<=right){ //enquanto houver vetor;
        middle = left + (right-left)/2; //calcula meio do vetor;

        if(v[middle] == x){
            return middle; //se x estiver em meio, retorna meio;
        }
        if(v[middle] < x){
            left = middle + 1; //escolhe lado maior;
        }
        else{
            right = middle - 1; //escolhe lado menor;
        }
    }
    return -1;
}