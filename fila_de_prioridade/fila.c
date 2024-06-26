#include <stdio.h>
#include <stdlib.h>
#include "fila.h"


// estrutura de um nó da fila
struct _no
{
    int dado;            // ponteiro genêrico para o dado do nó
    struct _no *prox;    // ponteiro para o próximo nó
    struct _no *ant;     // ponteiro para o nó anterior
};
// define um tipo que é um ponteiro para a estrutura do nó
typedef struct _no *No;


// estrutura de um descritor da fila
struct _fila
{
    int n_elem;     // número de elementos na fila
    No pri;         // ponteiro para o primeiro elemento da fila
    No ult;         // ponteiro para o último elemento da fila
};


Fila fila_cria()
{
    // aloca memória para a etrutura da fila
    Fila nova = (Fila)malloc(sizeof(struct _fila));
    if (nova == NULL)
    {
        printf("ERRO NA ALOCAÇÃO DE MEMÓRIA\n");
        return NULL;
    }
    // inicializa os descritores da fila
    nova->n_elem = 0;
    nova->pri = NULL;
    nova->ult = NULL;
    return nova;
}


static No no_cria(int dado)
{
    // aloca memória para o nó
    No novo = (No) malloc(sizeof(struct _no));
    if (novo == NULL)
    {
        printf("ERRO NA ALOCAÇÃO DE MEMÓRIA\n");
        return NULL;
    }
    // inicializa os descritores
    novo->dado = dado;
    novo->prox = NULL;
    novo->ant = NULL;
    return novo;
}


void fila_enqueue(Fila self, int dado)
{
    // aloca memória para um novo nó
    No novo = no_cria(dado);
    if (novo == NULL)
    {
        return;
    }
    // encadeia o novo nó
    if (fila_vazia(self))
    {
        self->pri = novo;
        self->ult = novo;
    }
    else
    {
        novo->ant = self->ult;
        self->ult->prox = novo;
        self->ult = novo;
    }
    self->n_elem++;
}


int fila_dequeue(Fila self)
{
    // verifica se a fila está vazia
    if (fila_vazia(self))
    {
        printf("LISTA VAZIA, NÃO SE PODE REMOVER ELEMENTOS\n");
        return 1;
    }
    // guarda um ponteiro para o nó a ser removido
    No removido = self->pri;
    // guarda o dado do nó a ser removido 
    int valor_de_retorno = removido->dado;
    // desencadeia o primeiro nó e o libera
    if (self->n_elem == 1)
    {
        self->pri = NULL;
        self->ult = NULL;
    }
    else
    {
        self->pri = self->pri->prox;
        self->pri->ant = NULL;
    }
    free(removido);
    self->n_elem--;
    return valor_de_retorno;
}


bool fila_vazia(Fila self)
{
    return self->n_elem == 0;
}


int fila_n_elem(Fila self)
{
    return self->n_elem;
}


void fila_libera(Fila self)
{
    // ponteiro para percorrer a fila
    No p = self->pri;
    // libera os nós
    while(p != NULL)
    {
        No temp = p->prox;
        free(p);
        p = temp;
    }
    // libera o descritor
    free(self);
}
