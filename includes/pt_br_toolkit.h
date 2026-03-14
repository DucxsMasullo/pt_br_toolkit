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

//matematicas
unsigned long int faz_primo(unsigned long int valor);//cria valor primo >= valor

int tamanho_dado_node(Node *current);//determina tamanho do dado

unsigned long long int completa_qword(unsigned long long int valor);//torna tamanho multiplo de 8

//conversores
Node* cria_novo_node(void);//autoexplicativo

void insere_dado_node(Node *current, char forma[],void *dado);//recebe o note alvo o dado e a forma como o dado deve ser inserido

void le_dado_node(Node *current);//autoexplicativo


#endif // PT_BR_TOOLKIT_H
