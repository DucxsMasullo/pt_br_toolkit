#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include<math.h>
#include <windows.h>
#include"pt_br_toolkit.h"

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
            unsigned char b = palavra[i+1];
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

void init_tool_kit(){
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);
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

void insere_texto(Texto **texto, char palavra[]){
    Texto *newnode = (Texto*)malloc(sizeof(Texto));
    Texto *current = *texto;
    if(newnode == NULL){
        exit(EXIT_FAILURE);
    }
    newnode->proximo = NULL;
    strncpy(newnode->palavra, palavra, sizeof(newnode->palavra));

    if(*texto == NULL){
        *texto = newnode;
        return;
    }
    while(current->proximo != NULL){
        current = current->proximo;
    }
    current->proximo = newnode;
}

void arquivo_para_texto(Texto **texto, char arquivo[]){
    FILE *arq = fopen(arquivo,"r");
    if(arq == NULL){
        exit(EXIT_FAILURE);
    }
    char line[1000];
    char buffer[100];
    int cntrl = 0;
    int linha = 0;
    while(fgets(line, sizeof(line), arq) != NULL){
        linha++;
        for(int i=0;line[i]!= '\n' && line[i]!= '\0';i++){
            if(line[i+1] == ' '||line[i+1] == '\n'||line[i+1] == '\0'){
                buffer[cntrl] = line[i];
                normaliza_palavra(buffer);
                insere_texto(texto, buffer);
                cntrl = 0;
                memset(buffer, 0,sizeof(buffer));
                i++;
            }
            else{
                buffer[cntrl] = line[i];
                cntrl++;
            }
        }
    }

}