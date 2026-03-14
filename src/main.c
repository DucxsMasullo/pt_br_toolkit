#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include "pt_br_toolkit.h"

int main() {
    Node *head = NULL;
    int i = 1;
    char w[] = "casa";

    head = cria_novo_node();
    insere_dado_node(head,"d",&i);
    insere_dado_node(head,"s",&w);


    le_dado_node(head);
    scanf("%d", &w);
}
