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


    ///retorna_int_node precisa de alteraçãode parada!!!
    //insere_node_arvore precisa de caso string caso char caso float!!!

    Node *new = NULL;
    int primo = 31;

    for(int i = 0; i<5; i++){
        Node *new = cria_novo_node();
        primo = primo*i*i%10;
        insere_dado_node(new, "d", &primo);
    }



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

