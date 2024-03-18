#include <stdio.h>
#include <stdlib.h>
#include "rbtree.c"

int main(){
    rbtree *t = createRoot();
    int op, n;
    while(1){
        printf("Olá, coleguinha!\n");
        printf("\nO que deseja?\n");
        printf("1.Inserir\n");
        printf("2.Remover\n");
        printf("3.Árvore em Ordem\n");
        printf("4.Árvore em pré-ordem\n");
        printf("5.Árvore em pós-ordem\n");
        printf("5.Buscar\n");
        printf("7.Sair\n");
        scanf("%d",&op);

        switch (op){
            case 1:
                printf("\nValor inserido: ");
                scanf("%d", &n);
                insertRedBlack(t, n);
                printf("\n%d inserido com sucesso!\n\n", n);
                break;
            case 2:
                printf("\nValor deletado: ");
                scanf("%d", &n);
                removeRedBlack(t, n);
                printf("\n%d removido com sucesso!\n\n", n);
                break;
            case 3:
                printf("\n");
                printOrder(t->root);
                printf("\n");
                break;
            case 4:
                printf("\n");
                printPreOrder(t->root);
                printf("\n");
                printPreOrderComCor(t->root);
                printf("\n\n");
                break;
            case 5:
                printf("\n");
                printPosOrder(t->root);
                printf("\n");
                break;
            case 6:
                printf("Valor buscado: ");
                scanf("%d", &n);
                int altura = alturaNo(t->root, n);
                if(altura == -1){
                    printf("Valor não econtrado.\n");
                }else{
                    printf("%d foi encontrado na profundidade %d\n\n", n, altura);
                }
                break;
            case 7:
                printf("\nSaindo......\n");
                exit(1);
                break;
            default:
                printf("Valor inválido!\n");
                break;
    }


    }




    return 0;
}