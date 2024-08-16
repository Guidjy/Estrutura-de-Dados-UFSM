#ifndef _FILA_H_
#define _FILA_H_

#include <stdbool.h>

// define um tipo de fila como um ponteiro para um descritor da fila
typedef struct _fila *Fila;

// inicializa uma fila de dados de tamanho "tam_dado"
Fila fila_cria(int tam_dado);

// libera toda a memória alocada para uma fila
void fila_destroi(Fila self);

// verifica se uma fila está vazia
bool fila_vazia(Fila self);

// retorna o número de elementos de uma fila
int fila_len(Fila self);

// enfilera um elemento na fila
// obs: o dado a ser inserido deve ser passado por referência
void fila_enqueue(Fila self, void *pdado);

// desenfileta a fila e retorna um ponteiro para o dado desenfilerado
// obs: deve-se fazer o casting e liberação desse ponteiro
void *fila_dequeue(Fila self);

#endif
