#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fila.h"


// estrutura do nó da fila
struct _no_fila
{
    void *dado;             // ponteiro para o dado do nó
    struct _no_fila *prox;  // ponteiro para o próximo elemento na fila
};
typedef struct _no_fila *No_fila;


// estrutura do descritor da fila
struct _fila
{
    int n_elem;    // número de elementos na fila
    int tam_dado;  // tamanho (em bytes) do dado armazenado na fila
    No_fila pri;   // ponteiro para o primeiro elemento da fila
    No_fila ult;   // ponteiro para o último elemento da fila
};
// typedef struct _fila *Fila; >>> fila.h


// inicializa uma fila de dados de tamanho "tam_dado"
Fila fila_cria(int tam_dado)
{
    // aloca memória para o descritor da fila
    Fila nova_fila = (Fila) malloc(sizeof(struct _fila));
    if (nova_fila == NULL)
    {
        printf("Erro na alocação de memória para o descritor da fila\n");
        return NULL;
    }

    // inicializa os descritores da fila
    nova_fila->n_elem = 0;
    nova_fila->tam_dado = tam_dado;
    nova_fila->pri = NULL;
    nova_fila->ult = NULL;

    return nova_fila;
}


// libera toda a memória alocada para uma fila
void fila_destroi(Fila self)
{
    // libera a memória alocada aos nós
    No_fila p = self->pri;
    while (p != NULL)
    {
        No_fila temp = p->prox;
        free(p->dado);
        free(p);
        p = temp;
    }

    // libera a memória alocada ao descritor da fila
    free(self);
}


// verifica se uma fila está vazia
bool fila_vazia(Fila self)
{
    return self->n_elem == 0;
}


// retorna o número de elementos de uma fila
int fila_len(Fila self)
{
    return self->n_elem;
}


static No_fila cria_no(void *pdado, int tam_dado)
{
    // aloca memória para um nó da fila
    No_fila novo_no = (No_fila) malloc(sizeof(struct _no_fila));
    if (novo_no == NULL)
    {
        printf("Erro na alocação de memória para um nó da fila\n");
        return NULL;
    }
    novo_no->dado = malloc(tam_dado);
    if (novo_no->dado == NULL)
    {
        printf("Erro na alocação de memória para um nó da fila\n");
        free(novo_no);
        return NULL;
    }
    // copia o dado de pdado para o nó
    memmove(novo_no->dado, pdado, tam_dado);
    novo_no->prox = NULL;

    return novo_no;
}


// enfilera um elemento na fila
void fila_enqueue(Fila self, void *pdado)
{
    // verifica se o dado a inserir é valido
    if (pdado == NULL)
    {
        printf("Dado de inserção inválido\n");
        return;
    }

    // aloca memória para um novo nó da fila
    No_fila novo_no = cria_no(pdado, self->tam_dado);
    if (novo_no == NULL) return;

    // enfilera o nó
    if (fila_vazia(self))
    {
        self->pri = novo_no;
    }
    else
    {
        self->ult->prox = novo_no;
    }
    self->ult = novo_no;
    self->n_elem++;
}


// desenfileta a fila e copia o dado desenfilerado para um ponteiro
void fila_dequeue(Fila self, void *desenfilerado)
{
    // verifica se a fila está vazia
    if (fila_vazia(self))
    {
        printf("Fila vazia, não se pode desenfilerar\n");
        return;
    }

    if (desenfilerado != NULL)
    {
        memmove(desenfilerado, self->pri->dado, self->tam_dado);
    }

    // desencadeia o primeiro nó da fila
    No_fila temp = self->pri;
    self->pri = self->pri->prox;
    free(temp->dado);
    free(temp);
    
    self->n_elem--;
}


// imprime uma fila (apoio para os principais tipos de dados)
void fila_imprime(Fila self, char* tipo)
{
    if (fila_vazia(self))
    {
        printf("[]\n");
        return;
    }

    No_fila p = self->pri;
    printf("[");
    
    if (strcmp(tipo, "char") == 0)
    {
        while (p->prox != NULL)
        {
            printf("%c, ", *(char*)p->dado);
            p = p->prox;
        }
        printf("%c]\n", *(char*)p->dado);
    }
    else if (strcmp(tipo, "str") == 0)
    {
        while (p->prox != NULL)
        {
            printf("%s, ", (char*)p->dado);
            p = p->prox;
        }
        printf("%s]\n", (char*)p->dado);
    }
    else if (strcmp(tipo, "int") == 0)
    {
        while (p->prox != NULL)
        {
            printf("%d, ", *(int*)p->dado);
            p = p->prox;
        }
        printf("%d]\n", *(int*)p->dado);
    }
    else if (strcmp(tipo, "float") == 0)
    {
        while (p->prox != NULL)
        {
            printf("%.1f, ", *(float*)p->dado);
            p = p->prox;
        }
        printf("%.1f]\n", *(float*)p->dado);
    }
}
