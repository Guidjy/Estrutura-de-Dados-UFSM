#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "grafo.h"


// estrutura de um nó do grafo
struct _no_grafo
{
    int no_id;               // identificação do nó
    int aresta_peso;         // peso da aresta que liga os nós
    struct _no_grafo *prox;  // ponteiro para o próximo nó na lista de adjacência
};
typedef struct _no_grafo *No_grafo;


// estrutura do grafo
struct _grafo
{
    int n_nos;
    No_grafo *listas_de_adjacencia;
};
// typedef struct _grafo *Grafo; >>: grafo.h


Grafo grafo_cria()
{
    // aloca memória para a estrutura de um grafo
    Grafo novo_grafo = (Grafo) malloc(sizeof(struct _grafo));
    if (novo_grafo == NULL)
    {
        printf("ERRO NA ALOCAÇÃO DE MEMÓRIA PARA O GRAFO\n");
        return NULL;
    }
    // inicializa os descritores
    novo_grafo->n_nos = 0;
    novo_grafo->listas_de_adjacencia = NULL;
    // retorna o grafo criado
    return novo_grafo;
}


// Funções de manipulação de nós (vértices)


// cria um nó do grafo
static No_grafo no_grafo_cria(int id, int aresta_peso)
{
    // aloca memória para a estrutura de um nó
    No_grafo novo_no = (No_grafo) malloc(sizeof(struct _no_grafo));
    if (novo_no == NULL)
    {
        printf("ERRO NA ALOCAÇÃO DE MEMÓRIA PARA UM NOVO NÓ DO GRAFO\n");
        return NULL;
    }
    // preenche os descritores do nó
    novo_no->no_id = id;
    novo_no->aresta_peso = aresta_peso;
    novo_no->prox = NULL;
    // retorna o nó criado
    return novo_no;
}


int grafo_nnos(Grafo self)
{
    return self->n_nos;
}


// aloca ou realoca memória para o vetor de listas de adjacências
static void aloca_vetor_listas_adjacencia(Grafo self)
{
    // se não tiver memória alocada para o vetor de listas de adjacências
    if (self->listas_de_adjacencia == NULL)
    {
        // aloca memória para ele
        self->listas_de_adjacencia = (No_grafo*) malloc(sizeof(No_grafo));
        if (self->listas_de_adjacencia == NULL)
        {
            printf("ERRO NA ALOCAÇÃO DE MEMÓRIA PARA O VETOR DE LISTAS DE ADJACÊNCIA\n");
            return;
        }
    }
    // se ja tiver memória alocada
    else
    {
        // realoca a memória alocada para o vetor
        self->listas_de_adjacencia = (No_grafo*) realloc(self->listas_de_adjacencia, grafo_nnos(self) * sizeof(No_grafo));
        if (self->listas_de_adjacencia == NULL)
        {
            printf("ERRO NA ALOCAÇÃO DE MEMÓRIA PARA O VETOR DE LISTAS DE ADJACÊNCIA\n");
            return;
        }
    }
}


int grafo_insere_no(Grafo self)
{
    // cria um novo nó para ser inserido no grafo
    // 0-0: os nós são indentificados pela sua ordem de inserção, começando do 0
    No_grafo novo_no = no_grafo_cria(grafo_nnos(self), 0);
    if (novo_no == NULL)
    {
        return -1;
    }
    // incrementa o número de nós no grafo
    self->n_nos++;
    // aloca mais memória para o vetor de listas de adjacência
    aloca_vetor_listas_adjacencia(self);
    if (self->listas_de_adjacencia == NULL)
    {
        return -1;
    }
    // insere o nó no vetor de listas de adjacências
    self->listas_de_adjacencia[grafo_nnos(self) - 1] = novo_no;
    return novo_no->no_id;
}


void grafo_remove_no(Grafo self, int no_id)
{
    
}


// Funções de manipulação de arestas


void grafo_altera_valor_aresta(Grafo self, int origem, int destino, int peso)
{
    // verifica se os índices de origem e destino são válidos
    if (origem >= grafo_nnos(self) || destino >= grafo_nnos(self))
    {
        printf("ÍNDICES DE ORIGEM OU DESTINO INVÁLIDOS\n");
        return;
    }
    // cria um nó com o peso da aresta
    No_grafo novo_no = no_grafo_cria(destino, peso);
    if (novo_no == NULL)
    {
        return;
    }
    // encadeia o nó na lista de adjacências
    No_grafo p = self->listas_de_adjacencia[origem];
    while (p->prox != NULL)
    {
        p = p->prox;
    }
    p->prox = novo_no;
}


// Algoritmos


void grafo_imprime(Grafo self)
{
    // percorre o vetor de listas de adjacências
    for (int i = 0; i < grafo_nnos(self); i++)
    {
        printf("%d -> [ ", self->listas_de_adjacencia[i]->no_id);
        // ponteiro para percorrer a lista de adjacências
        No_grafo p = self->listas_de_adjacencia[i]->prox;
        // imprime a lista de adjacências
        if (p == NULL)
        {
            printf("]\n");
        }
        else
        {
            while (p->prox != NULL)
            {
                printf("%d, ", p->no_id);
                p = p->prox;
            }
            printf("%d ]\n", p->no_id);
        }
    }
}
