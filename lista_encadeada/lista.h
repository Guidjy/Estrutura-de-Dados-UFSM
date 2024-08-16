#ifndef _LISTA_H_
#define _LISTA_H_

#include <stdbool.h>

// define um tipo de lista como um ponteiro para descritor
typedef struct _lista *Lista;

// inicializa uma lista de dados de tamanho "tam_dado"
Lista lista_cria(int tam_dado);

// retorna true se uma lista estiver vazia, false caso contrário
bool lista_vazia(Lista self);

// retorna o número de elementos na lista
int lista_len(Lista self);

// insere um elemento no início da lista
// obs: o dado a ser inserido deve ser passado por referência
void lista_insere(Lista self, void *pdado);

// remove o elemento no início da lista e retorna um ponteiro para ele 
// (retorna NULL se a lista estiver vazia)
// obs: tem que fazer casting do ponteiro e libera-lo devidamente
void *lista_remove(Lista self);

// organiza os elementos da lista em ordem crescente
void lista_sort(Lista self);

// libera toda a memória alocada para uma lista
void lista_destroi(Lista self);

// imprime uma lista
void lista_imprime(Lista self);

#endif
