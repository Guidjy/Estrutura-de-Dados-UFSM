#include <stdio.h>
#include <stdlib.h>
#include "grafo.h"


int main()
{
    // cria um grafo vazio
    Grafo g1 = grafo_cria();

    // insere os 4 nós e suas arestas
    grafo_insere_no(g1, 0);
    grafo_insere_no(g1, 5);
    grafo_insere_no(g1, 7); // 0-0
    grafo_insere_no(g1, 0);
    grafo_altera_valor_aresta(g1, 0, 1, 10);
    grafo_altera_valor_aresta(g1, 0, 2, 30);
    grafo_altera_valor_aresta(g1, 1, 3, 10);
    grafo_altera_valor_aresta(g1, 3, 2, 10);
    grafo_imprime(g1);

    // testa remoçaõ de adjacências com grafo_altera_valor_aresta()
    grafo_altera_valor_aresta(g1, 0, 1, -1);
    grafo_imprime(g1);

    // testa grafo_valor_aresta()
    void *valor_aresta = malloc(sizeof(int));
    bool tem_aresta = grafo_valor_aresta(g1, 0, 2, valor_aresta);
    if (tem_aresta)
    {
        printf("Valor da aresta 0 -> 2: %d\n", *(int*)valor_aresta);
    }

    return 0;
}
