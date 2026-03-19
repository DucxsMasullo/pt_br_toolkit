#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include<math.h>
#include"pt_br_toolkit.h"



//strings

const char mapa_acentos[64] = {
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
    newnode->altura = 1;
    return newnode;
}

void deleta_node(Node *current){
    if(current == NULL){
        return;
    }

    free(current->dado);
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
void insere_anterior(Node **root, Node *current){
    if(*root == NULL){
        *root = current;
    }
    else{
        (*root)->anterior = current;
    }
}

void insere_proximo(Node **root, Node *current){
    if(*root == NULL){
        *root = current;
    }
    else{
        (*root)->proximo = current;
    }
}

Node** minimo_ptr(Node **root){
    while((*root)->anterior != NULL){
        root = &(*root)->anterior;
    }
    return root;
}

void remove_node_arvore(Node **root){
    if(root == NULL || *root == NULL) return;

    Node *node = *root;

    if(node->anterior == NULL && node->proximo == NULL){
        deleta_node(node);
        *root = NULL;
    }
    else if(node->anterior == NULL){
        *root = node->proximo;
        deleta_node(node);
    }
    else if(node->proximo == NULL){
        *root = node->anterior;
        deleta_node(node);
    }
    else{
        Node **succ_ptr = minimo_ptr(&(node->proximo));
        void *temp = node->dado;
        node->dado = (*succ_ptr)->dado;
        (*succ_ptr)->dado = temp;
        remove_node_arvore(succ_ptr);
    }
}

void insere_node_arvore(Node **root, Node *current){
    int data_old = 0;
    int data_new = 0;

    if(*root == NULL){
        *root = current;
        return;
    }

    data_old = retorna_int_node(*root, 1);
    data_new = retorna_int_node(current, 1);

    if(data_new > data_old){
        if((*root)->proximo == NULL){
            insere_proximo(root, current);
            return;
        }
        else{
            insere_node_arvore(&(*root)->proximo,current);
            return;
        }
    }
    else if(data_new < data_old){
        if((*root)->anterior == NULL){
            insere_anterior(root, current);
            return;
        }
        else{
            insere_node_arvore(&(*root)->anterior, current);
            return;
        }
    }
    else{
        deleta_node(current);
        printf("valor repetido\n");
    }
}

void imprime_arvore(Node **root){
    if((*root)->anterior != NULL){
        imprime_arvore(&(*root)->anterior);
    }
    printf("valor do dado : %d\n", retorna_int_node(*root,1));
    if((*root)->proximo != NULL){
        imprime_arvore(&(*root)->proximo);
    }
}

int max(int a, int b) {
    return (a > b) ? a : b;
}

void attdados(Node *root){
int leftHeight  = root->anterior ? root->anterior->altura : 0;
int rightHeight = root->proximo  ? root->proximo->altura  : 0;

root->altura = max(leftHeight, rightHeight) + 1;
root->fator = leftHeight - rightHeight;
}

void rr(Node **root){
    Node *newroot = (*root)->proximo;
            (*root)->proximo = newroot->anterior;
            newroot->anterior = *root;

            attdados(*root);
            attdados(newroot);

            *root = newroot;
}

void ll(Node **root) {
    Node *newRoot = (*root)->anterior;
    (*root)->anterior = newRoot->proximo;
    newRoot->proximo = *root;

    attdados(*root);
    attdados(newRoot);

    *root = newRoot;
}

void rl(Node **root){
    ll(&(*root)->proximo);
    rr(root);
}

void lr(Node **root){
    rr(&(*root)->anterior);
    ll(root);
}

void balancear_node(Node **root){
    if((*root)->fator == -2){
        if((*root)->proximo->fator <= 0){
            rr(root);
        }
        else if((*root)->proximo->fator > 0){
            rl(root);
        }
    }
    else if ((*root)->fator == 2){
        if((*root)->anterior->fator >= 0){
            ll(root);
        }
        else if((*root)->anterior->fator <0){
            lr(root);
        }
    }
}


void insere_node_arvore_balanceada(Node **root, Node *current){
    if(*root == NULL){
        *root = current;
        return;
    }

    int a = retorna_int_node(*root,1);
    int b = retorna_int_node(current,1);

    if(a==b){
        deleta_node(current);
        return;
    }

    if(b<a){
        if((*root)->anterior == NULL){
            (*root)->anterior = current;
        }
        else{
            insere_node_arvore_balanceada(&(*root)->anterior, current);
        }
    }
    else{
        if((*root)->proximo == NULL){
            (*root)->proximo = current;
        }
        else{
            insere_node_arvore_balanceada(&(*root)->proximo, current);
        }
    }
    
    attdados(*root);
    if((*root)->fator < -1 || (*root)->fator >1){
        balancear_node(root);
    }
}

//hashtables
