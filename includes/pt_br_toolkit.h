#ifndef PT_BR_TOOLKIT_H
#define PT_BR_TOOLKIT_H

typedef struct no{
    void *dado;
    struct no *anterior;
    struct no *proximo;
    int altura;
    int fator;
}Node;



//string
void normaliza_palavra(char palavra[]);//normaliza para ascii minusculo.

void remove_acentos(char palavra[]);//remove chars acentuados.

void limpa_buffer(void);
//matematicas
unsigned long int faz_primo(unsigned long int valor);//cria valor primo >= valor

int tamanho_dado_node(Node *current);//determina tamanho do dado

unsigned long long int completa_qword(unsigned long long int valor);//torna tamanho multiplo de 8

//conversores
Node* cria_novo_node(void);//autoexplicativo

void insere_dado_node(Node *current, char forma[],void *dado);//recebe o note alvo o dado e a forma como o dado deve ser inserido

void le_dado_node(Node *current);//autoexplicativo

int retorna_int_node(Node *current, int pos);

//lista
void torna_node_proximo(Node **root, Node *current);

void torna_node_anterior(Node **root, Node *current);

void troca_node_proximo(Node **root, Node *current);

void troca_node_proximo_lde(Node **root, Node *current);

void troca_head(Node **root, Node *current);

void troca_head_lde(Node **root, Node *current);

void remove_head(Node **root);

//pilha

void push(Node **root, char forma[]);

void* pop(Node **root);

void* peek(Node **root);

//filas

void enqueue(Node **root,char forma[]);

void* dequeue(Node **root);

void* front(Node **root);

//arvores

void insere_node_arvore(Node **root, Node *current);
void imprime_arvore(Node **root);
void remove_node_arvore(Node **root);


#endif // PT_BR_TOOLKIT_H
