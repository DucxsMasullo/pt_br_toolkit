#include <stdio.h>
#include <stdlib.h>
#include "pt_br_toolkit.h"

int main() {
    unsigned char teste = 0;
    for(int i = 0;i <= 255;i++){
        teste = i;
        printf("%c valor : %d  tamanho:%d\n", teste, teste,sizeof(teste));

    }
}
