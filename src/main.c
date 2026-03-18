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


    
    //insere_node_arvore precisa de caso string caso char caso float!!!

    Node *new = NULL;
    int primo = 31;

    for(int i = 0; i<15; i++){
        Node *new = cria_novo_node();
        int imput;
        scanf("%d",&imput);
        limpa_buffer();
        insere_dado_node(new,"d",&imput);
        insere_node_arvore(&head,new);
    }

    remove_node_arvore(&head);
    

    imprime_arvore(&head);
    scanf("%d",&primo);

    
}

