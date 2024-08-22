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

// insere um elemento no índice pos da lista
void lista_insere_pos(Lista self, void *pdado, int pos);

// remove o elemento no início da lista
// copia o dado do elemento removido para o ponteiro passado
void lista_remove(Lista self, void *removido);

// remove o elemento no indice pos da lista
// copia o dado do elemento removido para o ponteiro passado
void lista_remove_pos(Lista self, void *removido, int pos);

// organiza os elementos da lista em ordem crescente
void lista_sort(Lista self);

// libera toda a memória alocada para uma lista
void lista_destroi(Lista self);

// imprime uma lista (apoio para "char", "str", "int" e "float")
void lista_imprime(Lista self, char *tipo);

#endif
