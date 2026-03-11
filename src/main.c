#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include "pt_br_toolkit.h"

int main() {
    Node *head = NULL;
    int i = 999;

    head = cria_novo_node();
    insere_dado_node(head,"d",&i);


    le_dado_node(head);
}
