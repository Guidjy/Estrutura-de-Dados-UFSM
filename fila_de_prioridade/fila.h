#ifndef _FILA_H_
#define _FILA_H_
#include <stdbool.h>

// define o tipo de dado fila
typedef struct _fila *Fila;

// cria uma fila vazia
Fila fila_cria();

// retorna true se uma fila estiver vazia
bool fila_vazia(Fila self);

// enfileira um elemento
void fila_enqueue(Fila self, int dado);

// desenfilera a fila e retorna um ponteiro para o dado removido
int fila_dequeue(Fila self);

// retorna true se uma fila estiver vazia
bool fila_vazia(Fila self);

// imprime uma fila
void fila_imprime(Fila self);

// libera a memória alocada para uma fila e seus nós
void fila_libera(Fila self);

#endif
