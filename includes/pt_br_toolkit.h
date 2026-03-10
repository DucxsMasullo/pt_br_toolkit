#ifndef PT_BR_TOOLKIT_H
#define PT_BR_TOOLKIT_H

typedef struct no{
    char *dado;
    struct no *anterior;
    struct no *proximo;
    int altura;
    int fator;
}Node;

//string
void normaliza_palavra(char palavra[]);//normaliza para ascii minusculo.
void remove_acentos(char palavra[]);//remove chars acentuados.
//matematicas
unsigned long int faz_primo(unsigned long int valor);
#endif // PT_BR_TOOLKIT_H
