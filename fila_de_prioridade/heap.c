#include <stdio.h>
#include <stdlib.h>
#include "heap.h"
#include "fila.h"


// estrutura de um heap binário
struct heap
{
    int nos[TAM_HEAP];   // vetor com os nós do heap
    int n_nos;           // número de nós no vetor
};


heap_t heap_cria()
{
    // aloca memória para a estrutura de um heap
    heap_t novo = (heap_t) malloc(sizeof(struct heap));
    if (novo == NULL)
    {
        printf("ERRO NA ALOCAÇÃO DE MEMÓRIA\n");
        return NULL;
    }
    novo->n_nos = 0;
    return novo;
}


// percorre o caminho ascendente desde o ponto de inserção em direção à raiz,
// deslocando os valores para baixo até encontrar um que tenha prioridade superior à do nó inserido.
// usado na inserção
static void heap_corrige_subindo(heap_t self, int pos)
{
    // se o nó em pos é a raíz, não precisa corrigir
    if (pos == 0)
    {
        return;
    }
    // posição do nó pai do nó em pos
    int pos_pai = (pos - 1) / 2;
    // verifica se a prioridade do nó pós é maior do que a de seu pai
    if (self->nos[pos] > self->nos[pos_pai])
    {
        // se sim, troca os dados entre o pai e seu filho
        int temp = self->nos[pos_pai];
        self->nos[pos_pai] = self->nos[pos];
        self->nos[pos] = temp;
        // chama a função novamente para continuar o caminho ascendente até a raiz
        heap_corrige_subindo(self, pos_pai);
    }
}


void heap_insere(heap_t self, int dado)
{
    // verifica se o heap está cheio
    if (self->n_nos >= TAM_HEAP)
    {
        printf("FILA CHEIA\n");
        return;
    }
    // insere o nó na primeira posição após o final atual do vetor
    self->nos[self->n_nos] = dado;
    // A inserção nesse local pode invalidar a característica heap da árvore,
    // caso esse nó tenha prioridade superior ao nó pai.
    // A árvore deve então ser verificada e corrigida caso necessário.
    heap_corrige_subindo(self, self->n_nos);
    // incrementa o número de nós na fila
    self->n_nos++;
}


// para corrigir o heap, parte-se da raiz (a qual perdeu o seu dado na remoção),
// escolhendo para colocar nela o dado com maior prioridade entre seus filhos e o dado sendo relocado.
// Se for escolhido o dado de algum dos filhos, continua-se com a mesma operação nesse nó,
// e continua dessa forma até que seja escolhido o dado sendo relocado.
static void heap_corrige_descendo(heap_t self, int pos)
{
    int pos_maior_prioridade = pos;
    int pos_filho_esquerdo = pos * 2 + 1;
    int pos_filho_direito = pos * 2 + 2;

    // se o nó em pos tiver um filho esquerdo
    // e se a prioridade desse filho for maior do que a de seu pai
    if (pos_filho_esquerdo < self->n_nos &&
        self->nos[pos_filho_esquerdo] > self->nos[pos_maior_prioridade])
    {
        // a posição do nó de maior prioridade passa a ser a do filho esquerdo
        pos_maior_prioridade = pos_filho_esquerdo;
    }
    // se o nó em pos tiver um filho direito
    // e se a prioridade desse filho for maior do que a de seu pai
    if (pos_filho_direito < self->n_nos &&
        self->nos[pos_filho_direito] > self->nos[pos_maior_prioridade])
    {
        pos_maior_prioridade = pos_filho_direito;
    }
    // se algum desses casos ocorreu
    if (pos_maior_prioridade != pos)
    {
        // troca os dados entre o pai e o filho
        int temp = self->nos[pos];
        self->nos[pos] = self->nos[pos_maior_prioridade];
        self->nos[pos_maior_prioridade] = temp;
        // continua a verificação no nó filho
        heap_corrige_descendo(self, pos_maior_prioridade);
    }
}


int heap_remove(heap_t self)
{
    // verifica se a fila está vazia
    if (self->n_nos == 0)
    {
        printf("FILA VAZIA\n");
        return 0;
    }
    // guarda o dado da raiz para retornar
    int raiz_dado = self->nos[0];
    // Na remoção, o valor a remover está na raiz, mas a árvore deve perder o último nó pra continuar com a forma correta.
    // O dado que está no último nó deve ser colocado em outro local da árvore,
    // mas deve ser um local em que a ordem heap não seja violada.
    int pos_no_relocado = self->n_nos - 1;   // guarda a posição do último nó
    // decrementa o número de nós na fila
    self->n_nos--;
    // se a heap não tiver ficado vazia com a remoção da raiz
    if (pos_no_relocado != 0)
    {
        // copia o dado do último nó para a raiz
        self->nos[0] = self->nos[pos_no_relocado];
        // corrige o heap a partir da raiz
        heap_corrige_descendo(self, 0);
    }
    return raiz_dado;
}


void heap_imprime(heap_t self)
{
    // se o heap estiver vazio
    if (self->n_nos == 0)
    {
        printf("FILA VAZIA\n");
        return;
    }

    // realiza um percurso em largura para imprimir o heap
    Fila fila_de_nos = fila_cria();  // fila com os nós de um nível
    int pos = 0;
    fila_enqueue(fila_de_nos, pos);

    while (!fila_vazia(fila_de_nos))
    {
        pos = fila_dequeue(fila_de_nos);
        printf("No [%d]: ", self->nos[pos]);

        int pos_filho_esquerdo = pos * 2 + 1;
        int pos_filho_direito = pos * 2 + 2;

        if (pos_filho_esquerdo < self->n_nos)
        {
            fila_enqueue(fila_de_nos, pos_filho_esquerdo);
            printf("filho esq: [%d], ", self->nos[pos_filho_esquerdo]);
        }
        else
        {
            printf("filho esq: [VAZIO],");
        }

        if (pos_filho_direito < self->n_nos)
        {
            fila_enqueue(fila_de_nos, pos_filho_direito);
            printf("filho dir: [%d]", self->nos[pos_filho_direito]);
        }
        else
        {
            printf("filho dir: [VAZIO]");
        }
        printf("\n");
    }
    fila_libera(fila_de_nos);
}
