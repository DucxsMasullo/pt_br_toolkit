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
unsigned long long int completa_byte(unsigned long long int valor){
    unsigned long long int novo = valor;
    if(novo % 8 == 0){
        return valor += 8;
    }
    else{
        return valor += (8 - (novo % 8));
    }
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
    unsigned long int size;
    unsigned long int previous_size = 0;
    unsigned long int size_onbyte;
    switch(forma[0]){
        case 'd':
        size = sizeof(int);
        break;
        case 'f':
        size = sizeof(float);
        break;
        case 'c':
        size = sizeof(char);
        break;
        case 's':
        size = strlen(dado);
        break;
    }
    if(current->dado != NULL){
        previous_size = tamanho_dado_node (current);
    }
    size_onbyte = completa_byte(size+sizeof(long int)+2 + previous_size);
    void *temp = calloc(1, size_onbyte);



     //consetar as condicionais aqui

    ((char*)temp)[0+previous_size] = 2;
    ((char*)temp)[1+previous_size] = forma[0];
    memcpy((char*)temp + 2 + previous_size, &size, sizeof(long int));
    memcpy((char*)temp + 2 + sizeof(long int)+previous_size,dado,size)
}

void le_dado_node(Node *current){
    int cntrl = 0;
    while(((char*)current->dado)[cntrl] == 2){
        switch(((char*)current->dado)[cntrl + 1]){
            case 'd':
            printf("%d",*(int*)((char*)current->dado + 2 + sizeof(long int)+cntrl));
            break;
            case 'f':
            printf("%f",*(float*)((char*)current->dado + 2 + sizeof(long int)+cntrl));
            break;
            case 'c':
            printf("%c",((char*)current->dado)[2+sizeof(long int)+cntrl]);
            break;
            case 's':
            printf("%s",((char*)current->dado + 2 + sizeof(long int)+cntrl));
            break;
        }
        cntrl = (*(int*)((char*)current->dado + 2)+2+sizeof(long int));
    }
}

int tamanho_dado_node(Node *current){
    unsigned long int size = 0;
    int cntrl = 0;
    while(((char*)current->dado)[cntrl] != 0){
        size += *(int*)((char*)current->dado + 2);
        size += 2;
        cntrl = cntrl + 2 + (*(int*)((char*)current->dado +2 ));
    }
    return size;
}
//pilhas

//filas

//arvores

//hashtables
