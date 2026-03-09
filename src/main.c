#include <stdio.h>
#include <stdlib.h>
#include "pt_br_toolkit.h"
#include <windows.h>

int main() {
    Texto *texto = NULL;
    arquivo_para_texto(&texto, "arquivo.txt");
    FILE *arq = fopen("saida.txt","r");
    while(texto != NULL){
        fprintf(arq, "%s\n",texto->proximo);
    }
    scanf("%d", &texto);
}