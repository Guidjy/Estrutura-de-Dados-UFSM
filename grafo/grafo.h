#ifndef _GRAFO_H_
#define _GRAFO_H_

#include <stdbool.h>

typedef struct _grafo *Grafo;

// cria um grafo vazio
Grafo grafo_cria();

// Nós

// insere um nó no grafo e retorna o id do novo nó
int grafo_insere_no(Grafo self, int dado);

// remove um nó do grafo e as arestas incidentes nesse nó
// a identificação dos nós remanescentes é alterada, como se esse nó nunca tivesse existido
void grafo_remove_no(Grafo self, int no_id);

// altera o valor associado a um nó
void grafo_altera_valor_no(Grafo self, int no_id, int valor_no);

// retorna o valor do nó
int grafo_valor_no(Grafo self, int no_id);

// retorna o número de nós no grafo
int grafo_nnos(Grafo self);

// Arestas

// altera o valor da aresta que interliga o nó origem ao nó destino
// caso a aresta não exista, deve ser criada
// caso "valor" seja -1, a aresta deve ser removida
void grafo_altera_valor_aresta(Grafo self, int origem, int destino, int valor);

// coloca em pdado (se não for NULL) o valor associado à aresta, se existir
// retorna true se a aresta entre os nós origem e destino existir, e false se não existir
bool grafo_valor_aresta(Grafo self, int origem, int destino, void *pdado);

// inicia uma consulta a arestas que partem do nó origem
// as próximas chamadas a 'grafo_proxima_aresta' devem retornar os valores correspondentes
//   à cada aresta que parte desse nó
void grafo_arestas_que_partem(Grafo self, int origem);

// Algoritmos

// imprime o grafo
void grafo_imprime(Grafo self);


#endif
