#ifndef PT_BR_TOOLKIT_H
#define PT_BR_TOOLKIT_H

typedef struct no{
    char palavra[100];
    struct no *proximo;
}Texto;


void normaliza_palavra(char palavra[]);//normaliza para ascii minusculo.
void remove_acentos(char palavra[]);//remove chars acentuados.
void arquivo_para_texto(Texto **texto, char arquivo[]);
void init_tool_kit();

#endif // PT_BR_TOOLKIT_H
