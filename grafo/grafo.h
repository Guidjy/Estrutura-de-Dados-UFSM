#ifndef _GRAFO_H_
#define _GRAFO_H_

typedef struct _grafo *Grafo;

// cria um grafo vazio
Grafo grafo_cria();

// Nós

// retorna o número de nós no grafo
int grafo_nnos(Grafo self);

// insere um nó no grafo e retorna o id do novo nó
int grafo_insere_no(Grafo self);

// remove um nó do grafo e as arestas incidentes nesse nó
// a identificação dos nós remanescentes é alterada, como se esse nó nunca tivesse existido
void grafo_remove_no(Grafo self, int no_id);

// Arestas

// altera o valor da aresta que interliga o nó origem ao nó destino
// caso a aresta não exista, deve ser criada
// caso "peso" seja -1, a aresta deve ser removida
void grafo_altera_valor_aresta(Grafo self, int origem, int destino, int peso);

// imprime o grafo
void grafo_imprime(Grafo self);


#endif
