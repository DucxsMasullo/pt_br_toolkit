#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include "pt_br_toolkit.h"

int main() {
    Node *head = NULL;
    char i[9] = "casa\n";
    int w = 9;

    head = cria_novo_node();
    insere_dado_node(head,"s",&i);
    insere_dado_node(head,"d",&w);


    le_dado_node(head);
}
