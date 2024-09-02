#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "listag.h"


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
struct _no_listag
{
    void *dado;               // ponteiro para o dado armazenado pelo nó
    int tam_dado;             // tamanho (em bytes) do dado
    Tipo_do_dado tipo_dado;   // contém o tipo do dado armazenado pelo nó (usado para impressão)
    struct _no_listag *prox;  // ponteiro para o próximo nó da lista
    struct _no_listag *ant;   // ponteiro para o elemento anterior da lista
};
typedef struct _no_listag *No_listag;


// estrutura do descritor da lista
struct _listag
{
    int n_elem;     // número de elementos na lista
    No_listag pri;  // ponteiro para o primeiro nó da lista
    No_listag ult;  // ponteiro para o último nó da lista
};
// typedef struct _listag *ListaG; >>> listag.h


// cria uma lista genérica vazia
ListaG listag_cria()
{
    // aloca memória para o descritor da lista
    ListaG nova_lista = (ListaG) malloc(sizeof(struct _listag));
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
void listag_destroi(ListaG self)
{
    // percorre a lista, liberando cada nó
    No_listag p = self->pri;
    while (p != NULL)
    {
        No_listag temp = p->prox;
        free(p->dado);
        free(p);
        p = temp;
    }

    // libera o descritor da lista
    free(self);
}


// verifica se uma lista está vazia
bool listag_vazia(ListaG self)
{
    return self->n_elem == 0;
}


// retorna o número de elementos de uma lista
int listag_len(ListaG self)
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
static No_listag cria_no(void *pdado, int tam_dado, char *tipo_dado)
{
    // aloca memória para um nó
    No_listag novo_no = (No_listag) malloc(sizeof(struct _no_listag));
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
void listag_insere(ListaG self, void *pdado, int tam_dado, char *tipo_dado)
{
    // aloca memória para um novo nó
    No_listag novo_no = cria_no(pdado, tam_dado, tipo_dado);
    if (novo_no == NULL) return;

    // insere o nó no início da lista
    novo_no->prox = self->pri;
    if (listag_vazia(self))
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
void listag_remove(ListaG self, void *removido)
{
    // verifica se a lista está vazia
    if (listag_vazia(self))
    {
        printf("Lista vazia, não se pode remover elementos\n");
        return;
    }

    // guarda um ponteiro para o primeiro nó da lista
    No_listag no_removido = self->pri;

    // desencadeia o primeiro nó da lista
    self->pri = self->pri->prox;

    // decrementa o número de elementos da lista
    self->n_elem--;

    // se a lista ficou vazia após a remoção
    if (listag_vazia(self)) 
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


// enfilera um elemento (insere no final da lista)
void listag_enqueue(ListaG self, void *pdado, int tam_dado, char *tipo_dado)
{
    // aloca memória para um novo nó
    No_listag novo_no = cria_no(pdado, tam_dado, tipo_dado);
    if (novo_no == NULL) return;

    // insere o nó no final da lista
    novo_no->ant = self->ult;
    if (listag_vazia(self))
    {
        self->pri = novo_no;
    }
    else
    {
        self->ult->prox = novo_no;
    }
    self->ult = novo_no;

    // incrementa o número de elementos na lista
    self->n_elem++;
}


// "desenfilera" a lista (remove o primeiro elemento)
// e copia o dado desenfilerado para um ponteiro (se não for nulo)
void listag_dequeue(ListaG self, void *removido)
{
    listag_remove(self, removido);
    // 0-0
}


// "empilha" um elemento (insere no final da lista)
void listag_push(ListaG self, void *pdado, int tam_dado, char *tipo_dado)
{
    listag_enqueue(self, pdado, tam_dado, tipo_dado);
    /*                                                                           
                        ..,///(((#####((#((/,.                                
                 ./#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%##(*.                         
             ,/#%%##%%%%%%%%%%%%%%%%%%%%%%%%%#########%##(*.                    
           ./####%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%##(,                   
           ,(#####%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%#(/*.                  
           ./###(/*,,...  ..*(#%%####%%%###(*,.    .....,,***.                  
            ..    .,, .*(*.     ,/##%%#/.     ,*. ./.                          
            ./#%%%##(((#####(*..*(###########(((((((#%%%%#/.                    
              /#%###%%%%%#%%#(***(###################%%#*                       
              ./###%%%%%%##/,    .*(##%############%#(,                         
               .*(####%#(*           .,/(#%%########*                           
                ...            ./(((###((((/*,,,*,                             
                                                  .//,.                        
                                              .,,,,,,,,.                        
                               .**********,.    .**,,.                        
                                            .,,/(((/,.                          
                               ....,,,*****((###(/,.                          
                             ,*(%%#%%%#(//**###((/****,.                       
                           .*((###%%##(((((#%%##(///((#(/*.                    
                         .*(##%%#######((#######((((########((//*,.            
                         .*(###%#############((((((((##########((((((((/*      
                        .,*(((####%%%%%%%%%%%%%%%%%%%%%%%%%%%%%######(/*      
                       .,*(((#####%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%####(/***.     
                      .,*(####%%###%%%%%%%%%%%%%%%%%%%%%%#((/**,.  ...         
                          .,/((#####((############((##((*,.        ,**,.        
                            ,**///////(((((//*,,**,..           .,*(#(/*,,      
                                /*.......,,,,,*,,.               .*//*,   
                                                              ..*(###(*,        
                                                             .,*(###(/,         
                                                             ,/(((((/,      
    */
}


// "desempilha" a lista (remove o último elemento)
// e copia o dado desenfilerado para um ponteiro (se não for nulo)
void listag_pop(ListaG self, void *removido)
{
    // verifica se a lista está vazia
    if (listag_vazia(self))
    {
        printf("Lista vazia, não se pode remover elementos\n");
        return;
    }

    // guarda um ponteiro para o último nó da lista
    No_listag no_removido = self->ult;

    // decrementa o número de elementos da lista
    self->n_elem--;

    // se a lista fica vazia após a remoção
    if (listag_vazia(self))
    {
        // quando a lista tinha exatamente um elemento
        self->pri = NULL;
        self->ult = NULL;
    }
    else
    {
        // quando a lista tinha mais de um elemento
        self->ult = self->ult->ant;
        self->ult->prox = NULL;
    }
    
    // copia o dado do nó removido para o ponteiro (se não for nulo) e libera o nó
    if (removido != NULL) memmove(removido, no_removido->dado, no_removido->tam_dado);
    free(no_removido->dado);
    free(no_removido);
}



// imprime uma lista genérica
void listag_imprime(ListaG self)
{
    // imprime "[]" se a lista estiver vazia
    if (listag_vazia(self))
    {
        printf("[]\n");
        return;
    }

    // ponteiro para percorrer a lista
    No_listag p = self->pri;
    printf("[");
    // percorre a lista imprimindo o dado de cada nó
    while (p != NULL)
    {
        switch(p->tipo_dado)
        {
            case CHAR:
                printf("%c, ", *(char*)p->dado);
                break;
            case SIGNED_CHAR:
                printf("%c, ", *(signed char*)p->dado);
                break;
            case UNSIGNED_CHAR:
                printf("%c, ", *(unsigned char*)p->dado);
                break;
            case SHORT_INT:
                printf("%hd, ", *(short int*)p->dado);
                break;
            case UNSIGNED_SHORT_INT:
                printf("%hu, ", *(unsigned short int*)p->dado);
                break;
            case INT:
                printf("%d, ", *(int*)p->dado);
                break;
            case UNSIGNED_INT:
                printf("%u, ", *(unsigned int*)p->dado);
                break;
            case LONG_INT:
                printf("%ld, ", *(long int*)p->dado);
                break;
            case UNSIGNED_LONG_INT:
                printf("%lu, ", *(unsigned long int*)p->dado);
                break;
            case LONG_LONG_INT:
                printf("%lld, ", *(long long int*)p->dado);
                break;
            case UNSIGNED_LONG_LONG_INT:
                printf("%llu, ", *(unsigned long long int*)p->dado);
                break;
            case FLOAT:
                printf("%.2f, ", *(float*)p->dado);
                break;
            case DOUBLE:
                printf("%.4lf, ", *(double*)p->dado);
                break;
            case LONG_DOUBLE:
                printf("%.6Lf, ", *(long double*)p->dado);
                break;
            case TAD:
                printf("TAD, ");
                break;
        }
        p = p->prox;
    }
    printf("]\n");
}
