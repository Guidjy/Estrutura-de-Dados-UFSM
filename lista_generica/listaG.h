#ifndef _LISTAG_H_
#define _LISTAG_H_

#include <stdbool.h>

typedef struct _listaG *ListaG;

// cria uma lista genérica vazia
ListaG listaG_cria();

// libera toda a memória alocada para uma lista genérica
void listaG_destroi(ListaG self);

// verifica se uma lista está vazia
bool listaG_vazia(ListaG self);

// retorna o número de elementos de uma lista
int listaG_len(ListaG self);

// funções de inserção e remoção de elementos

// insere um elemento de tamanho "tam_dado", e tipo "tipo_dado" no início da lista
// - obs1: o dado a ser inserido deve ser passado por referência
// - obs2: a string contendo o tipo do dado deve ser escrita igual a 
// syntaxe de declaração de uma variável desse tipo (exceto TAD)
void listaG_insere(ListaG self, void *pdado, int tam_dado, char *tipo_dado);

// remove o primeiro elemento da lista e copia seu dado para um ponteiro
// (se ele não for nulo)
void listaG_remove(ListaG self, void *removido);


#endif
