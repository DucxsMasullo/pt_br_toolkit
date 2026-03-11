#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include<math.h>
#include"pt_br_toolkit.h"



//strings
static const char mapa_acentos[64] = {
    'a','a','a','a','a',0,0,'c',
    'e','e','e','e','i','i','i','i',
    0,0,'o','o','o','o','o',0,
    'u','u','u','u',0,0,0,0,

    'a','a','a','a','a',0,0,'c',
    'e','e','e','e','i','i','i','i',
    0,0,'o','o','o','o','o',0,
    'u','u','u','u',0,0,0,0
};

void remove_acentos(char palavra[]){
    for(int i = 0; palavra[i] != '\0'; i++){
        if((unsigned char)palavra[i] == 195 && palavra[i+1] != '\0'){
            unsigned char b = (unsigned char)palavra[i+1];
            if(b >= 128 && b <= 191){
                char repl = mapa_acentos[b - 128];
                if(repl){
                    palavra[i] = repl;
                    memmove(&palavra[i+1], &palavra[i+2], strlen(&palavra[i+2]) + 1);
                    i--;
                }
            }
        }
    }
}

void normaliza_palavra(char palavra[]){
    remove_acentos(palavra);

    for(int i = 0; palavra[i] != '\0'; i++){
        if(palavra[i] == '\n' || palavra[i] == ' '){
            palavra[i] = '\0';
            break;
        }
        else if(isalpha((unsigned char)palavra[i])){
            palavra[i] = tolower((unsigned char)palavra[i]);
        }
        else if(palavra[i] != '-'){
            memmove(&palavra[i], &palavra[i+1], strlen(&palavra[i+1]) + 1);
            i--;
        }
    }
}
//matematicas
unsigned long int faz_primo(unsigned long int valor){
    for(int i=2; i*i<=valor; i++){
        if(valor%i == 0){
            valor++;
            i = 2;
        }
    }
    return valor;
}
//conversores

//listas
Node* cria_novo_node(void){
    Node *newnode = calloc(1, sizeof(Node));
    if(newnode == NULL){
        printf("\n erro ao alocar");
        exit(EXIT_FAILURE);
    }
    return newnode;
}

void insere_dado_node(Node *current, char forma[],void *dado){
    if(forma[0] == 'd'){
        int i = *(int*)dado;
        void *temp = calloc(1, sizeof(i)+2);
        ((char*)temp)[0] = 2;
        ((char*)temp)[1] = 'd';
        memcpy(((char*)temp)+2,&i,sizeof(i));
        current->dado = temp;
    }
}
//pilhas

//filas

//arvores

//hashtables
