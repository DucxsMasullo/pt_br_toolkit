#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include "pt_br_toolkit.h"

 int main() {
    Node *head = NULL;
    void *p;
    int cntrl = 0;
    int a = 10;
    int b = 20;


    head = cria_novo_node();
    insere_dado_node(head,"d",&a);
    insere_dado_node(head,"d",&b);

    int saida = 0;
    saida = retorna_int_node(head,2);
    printf("%d",saida);



    while(((char*)p)[cntrl] == 2){
        switch(((char*)p)[cntrl + 1]){
            case 'd':
            printf("%d",*(int*)((char*)p + 2 + sizeof(long int) + cntrl));
            break;
            case 'f':
            printf("%f",*(float*)((char*)p + 2 + sizeof(long int) + cntrl));
            break;
            case 'c':
            printf("%c",((char*)p)[2+sizeof(long int) + cntrl]);
            break;
            case 's':
            printf("%s",((char*)p + 2 + sizeof(long int) + cntrl));
            break;
        }
        cntrl += (*(int*)((char*)p + 2+cntrl)+2+sizeof(long int));
    }
}

