#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lista.h"


// estrutura de um nó da lista
struct _no_lista
{
    void *dado;              // ponteiro para o dado armazenado no nó
    struct _no_lista *prox;  // ponteiro para o próximo nó da lista
};
typedef struct _no_lista *No_lista;


// estrutura do descritor da lista
struct _lista
{
    int n_elem;    // número de elementos na lista
    int tam_dado;  // tamanho (em bytes) do dado armazenado na lista
    No_lista pri;  // ponteiro para o primeiro nó da lista
};
// typedef struct _lista *Lista; >>> lista.h


// inicializa uma lista de dados de tamanho "tam_dado"
Lista lista_cria(int tam_dado)
{
    // aloca memória para o descritor da lista
    Lista nova_lista = (Lista) malloc(sizeof(struct _lista));
    if (nova_lista == NULL)
    {
        printf("Erro na alocação de memória para o descritor da lista\n");
        return NULL;
    }
    // inicializa os descritores da lista
    nova_lista->n_elem = 0;
    nova_lista->tam_dado = tam_dado;
    nova_lista->pri = NULL;

    return nova_lista;
}


// retorna true se uma lista estiver vazia, false caso contrário
bool lista_vazia(Lista self)
{
    return self->n_elem == 0;
}


// retorna o número de elementos na lista
int lista_len(Lista self)
{
    return self->n_elem;
}


// cria um nó para a lista
static No_lista cria_no(void *pdado, int tam_dado)
{
    // aloca memória para um novo nó
    No_lista novo_no = (No_lista) malloc(sizeof(struct _no_lista));
    if (novo_no == NULL)
    {
        printf("Erro na alocação de memória para nó da lista\n");
        return NULL;
    }
    novo_no->dado = malloc(tam_dado);
    if (novo_no->dado == NULL)
    {
        printf("Erro na alocação de memória para nó da lista\n");
        free(novo_no);
        return NULL;
    }

    // copia o dado em *pdado para o nó
    memmove(novo_no->dado, pdado, tam_dado);
    novo_no->prox == NULL;

    return novo_no;
}


// insere um elemento no início da lista
void lista_insere(Lista self, void *pdado)
{
    // verifica se o dado passado é válido
    if (pdado == NULL)
    {
        printf("Dado inválido para inserção\n");
        return;
    }

    // cria um novo nó e encadea-o na lista
    No_lista novo_no = cria_no(pdado, self->tam_dado);
    if (novo_no == NULL) return;
    novo_no->prox = self->pri;
    self->pri = novo_no;

    // incrementa o número de elementos da lista
    self->n_elem++;
}


// remove o elemento no início da lista e retorna um ponteiro para ele
void *lista_remove(Lista self)
{
    // verifica se a lista está vazia
    if (lista_vazia(self))
    {
        printf("Lista vazia, não se pode remover elementos\n");
        return NULL;
    }

    // guarda um ponteiro para o dado no início da lista
    void *removido = malloc(self->tam_dado);
    if (removido == NULL)
    {
        printf("Erro na remoção\n");
        return NULL;
    }
    memmove(removido, self->pri->dado, self->tam_dado);

    // desencadeia o primeiro nó e libera-o
    No_lista temp = self->pri;
    self->pri = self->pri->prox;
    free(temp->dado);
    free(temp);

    // decrementa o número de elementos na lista
    self->n_elem--;

    // retorna o elemento removido
    return removido;
}


// verifica se n1 é maior que n2
static bool valor_maior(void *n1, void *n2)
{
    float a = *(float*)n1;
    float b = *(float*)n2;
    return a >= b;
}


// libera toda a memória alocada para uma lista
void lista_destroi(Lista self)
{
    // percorre a lista, liberando cada nó
    No_lista p = self->pri;
    while (p != NULL)
    {
        No_lista temp = p->prox;
        free(p->dado);
        free(p);
        p = temp;
    }
    // libera o descritor da lista
    free(self);
}


// funções abaixo são usadas na função de sort da lista
// https://www.geeksforgeeks.org/merge-sort-for-linked-list/


static void front_back_split(No_lista origem, No_lista *p_dianteiro, No_lista *p_traseiro)
{
    /* Split the nodes of the given list into front and back halves,
    and return the two lists using the reference parameters.
    If the length is odd, the extra node should go in the front list.
    Uses the fast/slow pointer strategy. */

    No_lista fast;
    No_lista slow;
    slow = origem;
    fast = origem->prox;

    /* Advance 'fast' two nodes, and advance 'slow' one node */
    while (fast != NULL)
    {
        fast = fast->prox;
        if (fast != NULL)
        {
            slow = slow->prox;
            fast = fast->prox;
        }
    }

    /* 'slow' is before the midpoint in the list, so split it in two at that point. */
    *p_dianteiro = origem;
    *p_traseiro = slow->prox;
    slow->prox = NULL;
}


No_lista sorted_merge(No_lista a, No_lista b)
{
    No_lista result = NULL;

    /* Base cases */
    if (a == NULL) return b;
    if (b == NULL) return a;

    /* Pick either a or b, and recur */
    if (valor_maior(a->dado, b->dado))
    {
        result = b;
        result->prox = sorted_merge(a, b->prox);
    }
    else
    {
        result = a;
        result->prox = sorted_merge(a->prox, b);
    }
    return(result);
}


static void merge_sort(No_lista *ponteiro_cabeca)
{
    // ponteiros para nós
    No_lista cabeca = *ponteiro_cabeca;
    No_lista a;
    No_lista b;

    /* Base case -- length 0 or 1 */
    if (cabeca == NULL || cabeca->prox == NULL)
    {
        return;
    }

    /* Split head into 'a' and 'b' sublists */
    front_back_split(cabeca, &a, &b);

    /* Recursively sort the sublists */
    merge_sort(&a);
    merge_sort(&b);

    /* answer = merge the two sorted lists together */
    *ponteiro_cabeca = sorted_merge(a, b);
}


// organiza os elementos da lista em ordem crescente
void lista_sort(Lista self)
{
    merge_sort(&self->pri);
}
