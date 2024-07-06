#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "grafo.h"


// estrutura de um nó do grafo
struct _no_grafo
{
    int no_id;               // identificação do nó
    int valor_no;            // valor associado ao nó
    int valor_aresta;        // peso da aresta que liga os nós
    struct _no_grafo *prox;  // ponteiro para o próximo nó na lista de adjacência
};
typedef struct _no_grafo *No_grafo;


// estrutura do grafo
struct _grafo
{
    int n_nos;                       // número de nós no grafo
    int cap;                         // capacidade máxima do vetor
    No_grafo *listas_de_adjacencia;  // vetor de listas de adjacências
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
    novo_grafo->cap = 10;
    // aloca memória para o vetor de listas de adjacência
    novo_grafo->listas_de_adjacencia = (No_grafo*) malloc(novo_grafo->cap * sizeof(No_grafo));
    if (novo_grafo->listas_de_adjacencia == NULL)
    {
        printf("ERRO NA ALOCAÇÃO DE MEMÓRIA PARA O VETOR DE LISTAS DE ADJACÊNCIA\n");
        free(novo_grafo);
        return NULL;
    }
    // retorna o grafo criado
    return novo_grafo;
}


// Funções de manipulação de nós (vértices)


// cria um nó do grafo
static No_grafo no_grafo_cria(int id, int valor_aresta)
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
    novo_no->valor_no = 0;
    novo_no->valor_aresta = valor_aresta;
    novo_no->prox = NULL;
    // retorna o nó criado
    return novo_no;
}


int grafo_nnos(Grafo self)
{
    return self->n_nos;
}


// aloca ou realoca memória para o vetor de listas de adjacências baseado no número de nós no grafo
static void aloca_vetor_listas_adjacencia(Grafo self)
{
    self->listas_de_adjacencia = (No_grafo*) realloc(self->listas_de_adjacencia, self->cap * sizeof(No_grafo));
    if (self->listas_de_adjacencia == NULL)
    {
        printf("ERRO NA ALOCAÇÃO DE MEMÓRIA PARA O VETOR DE LISTAS DE ADJACÊNCIA\n");
        return;
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
    // se o número de nós for igual a capacidade máxima
    if (self->n_nos == self->cap)
    {
        // dobra a capacidade do vetor de listas de adjacência
        self->cap *= 2;
        // aloca mais memória para o vetor de listas de adjacência
        aloca_vetor_listas_adjacencia(self);
    }
    if (self->listas_de_adjacencia == NULL)
    {
        return -1;
    }
    // insere o nó no vetor de listas de adjacências
    self->listas_de_adjacencia[grafo_nnos(self) - 1] = novo_no;
    return novo_no->no_id;
}


// remove um nó do grafo e as arestas incidentes nesse nó
// a identificação dos nós remanescentes é alterada, como se esse nó nunca tivesse existido
void grafo_remove_no(Grafo self, int no_id)
{
    // verifica se o grafo está vazio
    if (grafo_nnos(self) == 0)
    {
        printf("GRAFO VAZIO, NÃO SE PODE REMOVER NÓS\n");
        return;
    }

    // percorre o vetor de listas de adjacências
    for (int i = 0; i < grafo_nnos(self); i++)
    {
        // ponteiros para percorrer as listas de adjacência
        No_grafo p = self->listas_de_adjacencia[i];
        No_grafo p_ant = NULL;
        // conta o número de nós em uma lista de adjacência
        int cont = 0;
        // percorre a lista de adjacência no índice i até o final ou até achar o nó a ser removido
        while(p != NULL && p->no_id != no_id)
        {
            p_ant = p;
            p = p->prox;
            cont++;
        }
        // se achou o nó a ser removido e ele não for o primeiro nó da lista
        // (a remoção da própria lista de adjacências do nó a ser removido será tratada depois)
        if (p != NULL && cont != 0)
        {
            // remove o nó
            p_ant->prox = p->prox;
            free(p);
        }
    }

    // corrige a indentificação dos nós
    // "a identificação dos nós remanescentes é alterada, como se esse nó nunca tivesse existido"
    for (int i = 0; i < grafo_nnos(self); i++)
    {
        No_grafo p = self->listas_de_adjacencia[i];
        while (p != NULL)
        {
            if (p->no_id > no_id)
            {
                p->no_id--;
            }
            p = p->prox;
        }
    }

    // libera a lista de adjacência do nó a ser removido
    No_grafo p = self->listas_de_adjacencia[no_id];
    while (p != NULL)
    {
        No_grafo temp = p->prox;
        free(p);
        p = temp;
    }

    // ajusta a posição das listas de adjacência no vetor
    for (int i = no_id; i < self->n_nos - 1; i++)
    {
        self->listas_de_adjacencia[i] = self->listas_de_adjacencia[i + 1];
    }

    // decrementa o número de nós no grafo
    self->n_nos--;

    // realoca memória para o vetor de listas de adjacência, se necessário
    if (grafo_nnos(self) < self->cap / 2 && self->cap / 2 > 10)
    {
        // reduz a capacidade do vetor de listas de adjacências pela metade
        self->cap /= 2;
        aloca_vetor_listas_adjacencia(self);
    }
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
    // se o grafo estiver vazio
    if (grafo_nnos(self) == 0)
    {
        printf("[]\n");
        printf("n_nos: %d\n", self->n_nos);
        printf("cap:   %d\n", self->cap);
        printf("\n\n");
        return;
    }
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
    printf("n_nos: %d\n", self->n_nos);
    printf("cap:   %d\n", self->cap);
    printf("\n\n");
}
