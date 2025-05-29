#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX 40 

int verificar_palindromo(char *s, int n); //funcao verificar palindromo, retorna 1(True) se verdadeiro, 0(False) caso falso;
void lower_string(char* s, int n); //funcao que torna todos os caracteres minusculos;
void clean_punctuation(char *s, int n); //funcao que limpa a pontuacao e espaco da string;
void reverse_string(char *s, int n); //funcao que inverte a string;

int main(){
    char *s = (char*)malloc(MAX*sizeof(char));

    printf("Digite uma string:\n");
    fgets(s,MAX,stdin);
    s[strlen(s)-1] = '\0'; //demarca fim da string;
    fflush(stdin); //limpa buffer;

    int check = verificar_palindromo(s,MAX);

    if(check){ //tratamento do resultado de 'verificar_palindromo';
        printf("True\n");
    }else{
        printf("False\n");
    }
    return 0;
}

int verificar_palindromo(char *s, int n){
    char *first, *final; //inicializa strings inicial e final;
    first = (char*)malloc(n*sizeof(char)); 
    final = (char*)malloc(n*sizeof(char));

    strcpy(first,s);
    lower_string(first,n);
    clean_punctuation(first,n); //trata string inicial;
    strcpy(final,first);
    reverse_string(final,n); //trata string final;
    //printf("F1: %s\nF2: %s\n",first,final); //print para verificar ambas as strings;
    if(strcmp(first,final)==0){
        return 1;
    }
    return 0;

}

void lower_string(char* s, int n){
    int i=0;
    while(s[i]!='\0'){
        s[i] = tolower(s[i]);
        i++;
    }
}

void clean_punctuation(char *s, int n){
    int i=0, j=0;

    while(s[i]!='\0'){
        if(!ispunct(s[i]) && !isspace(s[i])){ //se nao for pontuacao ou espaco vazio, mantem na string;
            s[j++] = s[i];
        }
        i++;
    }
    s[j] = '\0'; //demarca o novo fim da string;
}

void reverse_string(char *s, int n){
    int start=0,end = strlen(s)-1;

    while(start<end){ //troca os caracteres das pontas de lugar;
        char temp = s[start];
        s[start] = s[end];
        s[end] = temp;

        start++;
        end--;
    }
}
