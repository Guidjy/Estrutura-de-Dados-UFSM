#include <stdio.h>
#include <unistd.h>
#include <stdbool.h>
#include "heap.h"


void impime_menu();


int main()
{
    heap_t fp = heap_cria();
    bool continuar = true;

    while(continuar)
    {
        impime_menu();

        int opcao;
        scanf("%d", &opcao);

        switch (opcao)
        {
            case 1:
                printf("> Elemento a inserir: \n");
                int no;
                scanf("%d", &no);
                heap_insere(fp, no);
                break;
            case 2:
                int removido = heap_remove(fp);
                printf("> Elemento removido: %d", removido);
                sleep(2);
                break;
            case 3:
                heap_imprime(fp);
                sleep(2);
                break;
            case 4:
                continuar = false;
                break;
            default:
                break;
        }
        printf("\n\n");
    }

    return 0;
}


void impime_menu()
{
    printf("+------------------+\n");
    printf("|      Opcoes      |\n");
    printf("+------------------+\n");
    printf("| 1) Insercao      |\n");
    printf("| 2) Remocao       |\n");
    printf("| 3) Impressao     |\n");
    printf("| 4) Encerrar      |\n");
    printf("+------------------+\n");
    printf(">>> Opcao: \n");
}
