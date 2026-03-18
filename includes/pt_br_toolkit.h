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

int retorna_int_node(Node *current, int pos);//retorna o enessimo valor int encontrado.

//lista
void torna_node_proximo(Node **root, Node *current);//torna current o proximo de root

void torna_node_anterior(Node **root, Node *current);//torna current o anterior de root

void troca_node_proximo(Node **root, Node *current);//troca proximo de root com current

void troca_node_proximo_lde(Node **root, Node *current);//troca proximo e atualiza campo "anterior"

void troca_head(Node **root, Node *current);//troca a head por current

void troca_head_lde(Node **root, Node *current);//troca head e atualiza campo "anterior"

void remove_head(Node **root);//autoexplicativo

//pilha

void push(Node **root, char forma[]);//

void* pop(Node **root);//devolve um ponteiro para uma copia de dado

void* peek(Node **root);//apenas devolve ponteiro

//filas

void enqueue(Node **root,char forma[]);//

void* dequeue(Node **root);//

void* front(Node **root);//

//arvores

void insere_node_arvore(Node **root, Node *current);//insere current ja em ordem

void imprime_arvore(Node **root);//autoexplicativo

void remove_node_arvore(Node **root);//remove um node preservando a estrutura


#endif // PT_BR_TOOLKIT_H
