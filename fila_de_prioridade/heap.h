#ifndef _HEAP_H_
#define _HEAP_H_

// número de nós máximos no heap
#define TAM_HEAP 63

typedef struct heap *heap_t;

// cria uma fila de prioridade
heap_t heap_cria();

// insere um elemento na fila de prioridade
void heap_insere(heap_t self, int dado);

// remove o nó de maior prioridade (nó raiz)
int heap_remove(heap_t self);

// imprime o heap binário
void heap_imprime(heap_t self);

#endif
