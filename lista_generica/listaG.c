#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "listaG.h"


// enum com os principais tipos de dados de C
enum _tipos_de_dados
{
    CHAR,
    SIGNED_CHAR,
    UNSIGNED_CHAR,
    SHORT_INT,
    UNSIGNED_SHORT_INT,
    INT,
    UNSIGNED_INT,
    LONG_INT,
    UNSIGNED_LONG_INT,
    LONG_LONG_INT,
    UNSIGNED_LONG_LONG_INT,
    FLOAT,                   
    DOUBLE,
    LONG_DOUBLE,
    TAD,  // Tipo Abstrato de Dado
    TIPO_INVALIDO
};
typedef enum _tipos_de_dados Tipo_do_dado;


// estrutura de um nó da lista generica
struct _no_listaG
{
    void *dado;               // ponteiro para o dado armazenado pelo nó
    int tam_dado;             // tamanho (em bytes) do dado
    Tipo_do_dado tipo_dado;   // contém o tipo do dado armazenado pelo nó (usado para impressão)
    struct _no_listaG *prox;  // ponteiro para o próximo nó da lista
    struct _no_listaG *ant;   // ponteiro para o elemento anterior da lista
};
typedef struct _no_listaG *No_listaG;


// estrutura do descritor da lista
struct _listaG
{
    int n_elem;     // número de elementos na lista
    No_listaG pri;  // ponteiro para o primeiro nó da lista
    No_listaG ult;  // ponteiro para o último nó da lista
};
// typedef struct _listaG *ListaG; >>> listaG.h


// cria uma lista genérica vazia
ListaG listaG_cria()
{
    // aloca memória para o descritor da lista
    ListaG nova_lista = (ListaG) malloc(sizeof(struct _listaG));
    if (nova_lista == NULL)
    {
        printf("Erro na alocação de memória para o descritor da lista\n");
        return NULL;
    }

    // inicializa os dados do descritor
    nova_lista->n_elem = 0;
    nova_lista->pri = NULL;
    nova_lista->ult = NULL;

    return nova_lista;
}


// libera toda a memória alocada para uma lista genérica
void listaG_destroi(ListaG self)
{
    // TODO
}


// verifica se uma lista está vazia
bool listaG_vazia(ListaG self)
{
    return self->n_elem == 0;
}


// retorna o número de elementos de uma lista
int listaG_len(ListaG self)
{
    return self->n_elem;
}


static Tipo_do_dado retorna_tipo(const char *tipo_dado) 
{
    if (strcmp(tipo_dado, "char") == 0) return CHAR;
    if (strcmp(tipo_dado, "signed char") == 0) return SIGNED_CHAR;
    if (strcmp(tipo_dado, "unsigned char") == 0) return UNSIGNED_CHAR;
    if (strcmp(tipo_dado, "short int") == 0) return SHORT_INT;
    if (strcmp(tipo_dado, "unsigned short int") == 0) return UNSIGNED_SHORT_INT;
    if (strcmp(tipo_dado, "int") == 0) return INT;
    if (strcmp(tipo_dado, "unsigned int") == 0) return UNSIGNED_INT;
    if (strcmp(tipo_dado, "long int") == 0) return LONG_INT;
    if (strcmp(tipo_dado, "unsigned long int") == 0) return UNSIGNED_LONG_INT;
    if (strcmp(tipo_dado, "long long int") == 0) return LONG_LONG_INT;
    if (strcmp(tipo_dado, "unsigned long long int") == 0) return UNSIGNED_LONG_LONG_INT;
    if (strcmp(tipo_dado, "float") == 0) return FLOAT;
    if (strcmp(tipo_dado, "double") == 0) return DOUBLE;
    if (strcmp(tipo_dado, "long double") == 0) return LONG_DOUBLE;
    if (strcmp(tipo_dado, "TAD") == 0) return TAD;
    return TIPO_INVALIDO;
}


// cria um nó para a lista genérica
static No_listaG cria_no(void *pdado, int tam_dado, char *tipo_dado)
{
    // aloca memória para um nó
    No_listaG novo_no = (No_listaG) malloc(sizeof(struct _no_listaG));
    if (novo_no == NULL)
    {
        printf("Erro na alocação de memória para um nó da lista\n");
        return NULL;
    }

    // aloca memória para o ponteiro do nó
    novo_no->dado = malloc(tam_dado);
    if (novo_no->dado == NULL)
    {
        printf("Erro na alocação de memória para um nó da lista\n");
        free(novo_no);
        return NULL;    
    }

    // inicializa os dados do nó
    memmove(novo_no->dado, pdado, tam_dado);
    novo_no->prox = NULL;
    novo_no->ant = NULL;
    novo_no->tam_dado = tam_dado;
    novo_no->tipo_dado = retorna_tipo(tipo_dado);
    if (novo_no->tipo_dado == TIPO_INVALIDO)
    {
        printf("Tipo de dado inválido\n");
        free(novo_no->dado);
        free(novo_no);
        return NULL;
    }

    return novo_no;
}


// insere um elemento de tamanho "tam_dado", e tipo "tipo_dado" no início da lista
void listaG_insere(ListaG self, void *pdado, int tam_dado, char *tipo_dado)
{
    // aloca memória para um novo nó
    No_listaG novo_no = cria_no(pdado, tam_dado, tipo_dado);
    if (novo_no == NULL) return;

    // insere o nó no início da lista
    novo_no->prox = self->pri;
    if (listaG_vazia(self))
    {
        self->ult = novo_no;
    }
    else
    {
        self->pri->ant = novo_no;
    }
    self->pri = novo_no;

    // incrementa o número de elementos na lista
    self->n_elem++;
}


// remove o primeiro elemento da lista e copia seu dado para um ponteiro
// (se ele não for nulo)
void listaG_remove(ListaG self, void *removido)
{
    // verifica se a lista está vazia
    if (listaG_vazia(self))
    {
        printf("Lista vazia, não se pode remover elementos\n");
        return;
    }

    // guarda um ponteiro para o primeiro nó da lista
    No_listaG no_removido = self->pri;

    // desencadeia o primeiro nó da lista
    self->pri = self->pri->prox;

    // decrementa o número de elementos da lista
    self->n_elem--;

    // se a lista ficou vazia após a remoção
    if (listaG_vazia(self)) 
    {
        self->pri = NULL;  // deve ser redundante mas é bom pra prevenir cagada
        self->ult = NULL;
    }
    else 
    {
        self->pri->ant = NULL;
    }

    // copia o dado do nó removido para o ponteiro (se não for nulo) e libera o nó
    if (removido != NULL) memmove(removido, no_removido->dado, no_removido->tam_dado);
    free(no_removido->dado);
    free(no_removido);
}
