#include <stdio.h>
#include <stdlib.h>
#include "grafo.h"


int main()
{
    // cria um grafo vazio
    Grafo g1 = grafo_cria();

    // insere um nó no grafo
    int id = grafo_insere_no(g1);
    printf("inserido: %d\n", id);

    // insere 3 nós
    for (int i = 0; i < 3; i++)
    {
        id = grafo_insere_no(g1);
        printf("inserido: %d\n", id);
    }

    // imprime o grafo
    grafo_imprime(g1);

    // insere algumas arestas (peso 10 pra tudo)
    // deve ficar:
    // 0 -> [1, 2]
    // 1 -> [3]
    // 2 -> []
    // 3 -> [2]
    grafo_altera_valor_aresta(g1, 0, 1, 10);
    grafo_altera_valor_aresta(g1, 0, 2, 10);
    grafo_altera_valor_aresta(g1, 1, 3, 10);
    grafo_altera_valor_aresta(g1, 3, 2, 10);
    grafo_imprime(g1);

    // remove o nó 1
    // deve ficar:
    // 0 -> [1]
    // 1 -> []
    // 2 -> [1]
    grafo_remove_no(g1, 1);
    grafo_imprime(g1);

    // remove tudo
    while (grafo_nnos(g1) > 0)
    {
        grafo_remove_no(g1, 0);
    }
    grafo_imprime(g1);

    // insere os 4 nós e suas arestas denovo
    grafo_insere_no(g1);
    grafo_insere_no(g1);
    grafo_insere_no(g1);
    grafo_insere_no(g1);
    grafo_altera_valor_aresta(g1, 0, 1, 10);
    grafo_altera_valor_aresta(g1, 0, 2, 10);
    grafo_altera_valor_aresta(g1, 1, 3, 10);
    grafo_altera_valor_aresta(g1, 3, 2, 10);
    grafo_imprime(g1);



    return 0;
}
