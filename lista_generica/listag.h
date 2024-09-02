#ifndef _LISTAG_H_
#define _LISTAG_H_

#include <stdbool.h>

typedef struct _listag *ListaG;

// cria uma lista genérica vazia
ListaG listag_cria();

// libera toda a memória alocada para uma lista genérica
void listag_destroi(ListaG self);

// verifica se uma lista está vazia
bool listag_vazia(ListaG self);

// retorna o número de elementos de uma lista
int listag_len(ListaG self);

// funções de inserção e remoção de elementos

// insere um elemento de tamanho "tam_dado", e tipo "tipo_dado" no início da lista
// - obs1: o dado a ser inserido deve ser passado por referência
// - obs2: a string contendo o tipo do dado deve ser escrita igual a 
// syntaxe de declaração de uma variável desse tipo (exceto TAD)
void listag_insere(ListaG self, void *pdado, int tam_dado, char *tipo_dado);

// remove o primeiro elemento da lista e copia seu dado para um ponteiro
// (se ele não for nulo)
void listag_remove(ListaG self, void *removido);

// funcionalidades de fila

// "enfilera" um elemento (insere no final da lista)
void listag_enqueue(ListaG self, void *pdado, int tam_dado, char *tipo_dado);

// "desenfilera" a lista (remove o primeiro elemento)
// e copia o dado desenfilerado para um ponteiro (se não for nulo)
void listag_dequeue(ListaG self, void *removido);

// funcionalidades de pilha

// "empilha" um elemento (insere no final da lista)
void listag_push(ListaG self, void *pdado, int tam_dado, char *tipo_dado);

// "desempilha" a lista (remove o último elemento)
// e copia o dado desenfilerado para um ponteiro (se não for nulo)
void listag_pop(ListaG self, void *removido);

// imprime uma lista genérica
void listag_imprime(ListaG self);


#endif
