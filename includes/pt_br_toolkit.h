#ifndef PT_BR_TOOLKIT_H
#define PT_BR_TOOLKIT_H

typedef struct no{
    void *dado;
    struct no *anterior;
    struct no *proximo;
    int altura;
    int fator;
}Node;

//STX = 2
//ETX = 3 dec start e end
//[STX][TIPO][dado][dado][dado][dado][ETX]

//string
void normaliza_palavra(char palavra[]);//normaliza para ascii minusculo.
void remove_acentos(char palavra[]);//remove chars acentuados.
//matematicas
unsigned long int faz_primo(unsigned long int valor);
void insere_dado_node(Node *current, char forma[],void *dado);//beta
Node* cria_novo_node(void);//beta
void le_dado_node(Node *current);
#endif // PT_BR_TOOLKIT_H
