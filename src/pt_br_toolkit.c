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

void limpa_buffer(void){
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
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

unsigned long long int completa_qword(unsigned long long int valor){
    unsigned long long int novo = valor;
    if(novo % 8 == 0){
        return valor += 8;
    }
    else{
        return valor += (8 - (novo % 8));
    }
}

int tamanho_dado_node(Node *current){
    unsigned long int size = 0;
    int cntrl = 0;
    void *aux = current->dado;
    while(((char*)aux)[cntrl]!= '\0'){
        size += 2 + sizeof(long int) + *(int*)(aux +2);
        cntrl += 2 + sizeof(long int) + *(int*)(aux +2);
    }
    return size;
}

//conversores

Node* cria_novo_node(void){
    Node *newnode = calloc(1, sizeof(Node));
    if(newnode == NULL){
        printf("\n erro ao alocar");
        exit(EXIT_FAILURE);
    }
    return newnode;
}

void deleta_node(Node *current){
    if(current->dado != NULL){
        free(current->dado);
    }
    free(current);
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
    size_onbyte = completa_qword(size + sizeof(long int) + 2 + previous_size);
    void *temp = calloc(1, size_onbyte);
    if(current->dado != NULL){
        memcpy(temp,current->dado, previous_size);
        free(current->dado);
    }


    ((char*)temp)[0+previous_size] = 2;
    ((char*)temp)[1+previous_size] = forma[0];
    memcpy((char*)temp + 2 + previous_size, &size, sizeof(long int));
    memcpy((char*)temp + 2 + sizeof(long int) + previous_size,dado,size);
    current->dado = temp;
}

void le_dado_node(Node *current){
    int cntrl = 0;
    while(((char*)current->dado)[cntrl] == 2){
        switch(((char*)current->dado)[cntrl + 1]){
            case 'd':
            printf("%d",*(int*)((char*)current->dado + 2 + sizeof(long int) + cntrl));
            break;
            case 'f':
            printf("%f",*(float*)((char*)current->dado + 2 + sizeof(long int) + cntrl));
            break;
            case 'c':
            printf("%c",((char*)current->dado)[2+sizeof(long int) + cntrl]);
            break;
            case 's':
            printf("%s",((char*)current->dado + 2 + sizeof(long int) + cntrl));
            break;
        }
        cntrl += (*(int*)((char*)current->dado + 2+cntrl)+2+sizeof(long int));
    }
}

void placeholder(void){
    return; ///preciso fazer um extrator de dado int para comparar os dados na arvore.
}

int retorna_int_node(Node *current, int pos){
    if(current == NULL){
        exit(EXIT_FAILURE);
    }


    int cntrl = 0;
    int actualpos = 0;
    while(((char*)current->dado)[cntrl] == 2){
        switch(((char*)current->dado)[cntrl + 1]){
            case 'd':
            actualpos++;
            if(actualpos == pos){
                return *(int*)((char*)current->dado + 2 + sizeof(long int) + cntrl);
            }
            break;

            default:
            break;
        }
        cntrl += (*(int*)((char*)current->dado + 2+cntrl)+2+sizeof(long int));
    }
}

//listas

void torna_node_proximo(Node **root, Node *current){
    if(*root == NULL){
        *root = current;
    }
    else{
        (*root)->proximo = current;
    }
}

void torna_node_anterior(Node **root, Node *current){
    if(*root == NULL){
        *root = current;
    }
    else{
        (*root)->anterior = current;
    }
}

void troca_node_proximo(Node **root, Node *current){
    if(*root == NULL){
        *root = current;
    }
    else{
        current->proximo = (*root)->proximo;
        (*root)->proximo = current;
    }
}

void troca_node_proximo_lde(Node **root, Node *current){
    if(*root == NULL){
        *root = current;
    }
    else{
        current->proximo = (*root)->proximo;
        (*root)->proximo = current;
        current->anterior = *root;
        if(current->proximo != NULL){
            current->proximo->anterior = current;
        }
    }
}

void remove_node_proximo(Node **root){
    if((*root)->proximo != NULL){
        Node *remover = (*root)->proximo;
        (*root)->proximo = (*root)->proximo->proximo;
        deleta_node(remover);
    }
    else{
        return;
    }
    if((*root)->proximo->anterior != NULL){
        (*root)->proximo->anterior = *root;
    }
}

void troca_head(Node **root, Node *current){
    if(*root == NULL){
        *root = current;
    }
    else{
        current->proximo = *root;
        *root = current;
    }
}

void troca_head_lde(Node **root, Node *current){
    if(*root == NULL){
        *root = current;
    }
    else{
        current->proximo = *root;
        (*root)->anterior = current;
        *root = current;
    }
}

void remove_head(Node **root){
    if(*root != NULL){
        if((*root)->proximo != NULL){
            Node *remover = *root;
            *root = (*root)->proximo;
            deleta_node(remover);
        }
        else{
            deleta_node(*root);
            *root = NULL;
        }
    }
}


//pilhas

void push(Node **root,char forma[]){
    void *dado = NULL;
    Node *current = cria_novo_node();

    switch(forma[0]){
        case 's':
        char buffer[100];
        printf("\n insira string:");
        fgets(buffer,sizeof(buffer),stdin);
        dado = buffer;
        break;

        case 'd':
        int inteiro;
        printf("\ninsira inteiro:");
        scanf("%d",&inteiro);
        limpa_buffer();
        dado = &inteiro;
        break;

        case 'f':
        float decimal;
        printf("\ninsira decimal:");
        scanf("%f",&decimal);
        limpa_buffer();
        dado = &decimal;
        break;

        case 'c':
        char caractere;
        printf("\n insira um caractere:");
        scanf("%c",&caractere);
        limpa_buffer();
        dado = &caractere;
        break;

        default:
        exit(EXIT_FAILURE);
    }

    insere_dado_node(current, forma, dado);
    troca_head(root,current);
}

void* pop(Node **root){
    if(*root == NULL){
        exit(EXIT_FAILURE);
    }
    int size = tamanho_dado_node(*root);
    void *dados = calloc(1, size);
    memcpy(dados,(*root)->dado,size);
    remove_head(root);
    return dados;
}

void* peek(Node **root){
    if(*root == NULL){
        exit(EXIT_FAILURE);
    }
    int size = tamanho_dado_node(*root);
    void *dados = calloc(1, size);
    memcpy(dados,(*root)->dado,size);
    return dados;
}
//filas
void enqueue(Node **root,char forma[]){
    void *dado = NULL;
    Node *current = cria_novo_node();

    switch(forma[0]){
        case 's':
        char buffer[100];
        printf("\n insira string:");
        fgets(buffer,sizeof(buffer),stdin);
        dado = buffer;
        break;

        case 'd':
        int inteiro;
        printf("\ninsira inteiro:");
        scanf("%d",&inteiro);
        limpa_buffer();
        dado = &inteiro;
        break;

        case 'f':
        float decimal;
        printf("\ninsira decimal:");
        scanf("%f",&decimal);
        limpa_buffer();
        dado = &decimal;
        break;

        case 'c':
        char caractere;
        printf("\n insira um caractere:");
        scanf("%c",&caractere);
        limpa_buffer();
        dado = &caractere;
        break;

        default:
        exit(EXIT_FAILURE);
    }

    insere_dado_node(current, forma, dado);

    if(*root == NULL){
        torna_node_proximo(root, current);
    }
    else if((*root)->proximo == NULL){
        torna_node_proximo(root, current);
    }
    else{
        Node *temp = *root;
        while(temp->proximo != NULL){
            temp = temp->proximo;
        }
        torna_node_proximo(&temp,current);
    }
}

void* dequeue(Node **root){
    int size = tamanho_dado_node(*root);
    void *dados = calloc(1, size);
    memcpy(dados,(*root)->dado,size);
    remove_head(root);
    return dados;
}

void* front(Node **root){
    int size = tamanho_dado_node(*root);
    void *dados = calloc(1, size);
    memcpy(dados,(*root)->dado,size);
    return dados;
}

//arvores
void insere_esquerda(Node **root, Node *current){
    if(*root == NULL){
        *root = current;
    }
    else{
        (*root)->anterior = current;
    }
}

void insere_direita(Node **root, Node *current){
    if(*root == NULL){
        *root = current;
    }
    else{
        (*root)->proximo = current;
    }
}



//hashtables
