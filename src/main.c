#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include "pt_br_toolkit.h"

int main() {
    Node *head = NULL;
    int i = 99;
    int w = 0;
    head = cria_novo_node();
    insere_dado_node(head,"d",&i);


    memcpy(&w,((char*)head->dado)+2,sizeof(int));
    printf("dado %d",w);
    scanf("%d", &i);
}
