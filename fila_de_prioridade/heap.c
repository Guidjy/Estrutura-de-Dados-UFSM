#include <stdio.h>
#include <stdlib.h>
#include "heap.h"


// estrutura de um heap binário
struct heap
{
    int nos[TAM_HEAP];   // vetor com os nós do heap
    int n_nos;           // número de nós no vetor
};


heap_t heap_cria()
{
    // aloca memória para a estrutura de um heap
    heap_t novo = (heap_t) malloc(sizeof(struct heap));
    if (novo == NULL)
    {
        printf("ERRO NA ALOCAÇÃO DE MEMÓRIA\n");
        return NULL;
    }
    novo->n_nos = 0;
    return novo;
}


// percorre o caminho ascendente desde o ponto de inserção em direção à raiz,
// deslocando os valores para baixo até encontrar um que tenha prioridade superior à do nó inserido.
// usado na inserção
static void heap_corrige_subindo(heap_t self, int pos)
{
    // se o nó em pos é a raíz, não precisa corrigir
    if (pos == 0)
    {
        return;
    }
    // posição do nó pai do nó em pos
    int pos_pai = (pos - 1) / 2;
    // verifica se a prioridade do nó pós é maior do que a de seu pai
    if (self->nos[pos] > self->nos[pos_pai])
    {
        // se sim, troca os dados entre o pai e seu filho
        int temp = self->nos[pos_pai];
        self->nos[pos_pai] = self->nos[pos];
        self->nos[pos] = temp;
        // chama a função novamente para continuar o caminho ascendente até a raiz
        heap_corrige_subindo(self, pos_pai);
    }
}


void heap_insere(heap_t self, int dado)
{
    // verifica se o heap está cheio
    if (self->n_nos >= TAM_HEAP)
    {
        printf("FILA CHEIA\n");
        return;
    }
    // insere o nó na primeira posição após o final atual do vetor
    self->nos[self->n_nos] = dado;
    // A inserção nesse local pode invalidar a característica heap da árvore,
    // caso esse nó tenha prioridade superior ao nó pai.
    // A árvore deve então ser verificada e corrigida caso necessário.
    heap_corrige_subindo(self, self->n_nos);
    // incrementa o número de nós na fila
    self->n_nos++;
}


// para corrigir o heap, parte-se da raiz (a qual perdeu o seu dado na remoção),
// escolhendo para colocar nela o dado com maior prioridade entre seus filhos e o dado sendo relocado.
// Se for escolhido o dado de algum dos filhos, continua-se com a mesma operação nesse nó,
// e continua dessa forma até que seja escolhido o dado sendo relocado.
static void heap_corrige_descendo(heap_t self, int pos)
{
    int pos_maior_prioridade = pos;
    int pos_filho_esquerdo = pos * 2 + 1;
    int pos_filho_direito = pos * 2 + 1;
}


int heap_remove(heap_t self)
{
    // verifica se a fila está vazia
    if (self->n_nos == 0)
    {
        printf("FILA VAZIA\n");
        return 0;
    }
    // guarda o dado da raiz para retornar
    int raiz_dado = self->nos[o];
    // Na remoção, o valor a remover está na raiz, mas a árvore deve perder o último nó pra continuar com a forma correta.
    // O dado que está no último nó deve ser colocado em outro local da árvore,
    // mas deve ser um local em que a ordem heap não seja violada.
    int pos_no_relocado = self->n_nos - 1;
    // se a heap não tiver ficado vazia com a remoção da raiz
    if (pos_no_relocado != 0)
    {
        // coloca o dado do nó final na raiz
        self->nos[0] = self->nos[pos_no_relocado];
        // decrementa o número de nós na fila
        self->n_nos--;
        // corrige o heap a partir da raiz
        heap_corrige_descendo(self, 0);
    }
}