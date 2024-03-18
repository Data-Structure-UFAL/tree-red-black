#include <stdio.h>
#include <stdlib.h>
#include "rbtree.c"

void openPNG(const char *filename) {
    char command[100];
    sprintf(command, "xdg-open %s", filename);
    system(command);
}


void generatePNG(const char *dotFilename, const char *pngFilename) {
    char command[1000]; // Tamanho do comando pode variar de acordo com o sistema operacional
    sprintf(command, "dot -Tpng %s -o %s", dotFilename, pngFilename);
    system(command);
}

void writeNode(FILE *file, rbtree_Node *node) {
    if (node != NULL) {
        fprintf(file, "%d [label=\"%d\", color=%s];\n", node->value, node->value, node->color == RED ? "red" : "black");
        if (node->left != NULL) {
            fprintf(file, "%d -> %d;\n", node->value, node->left->value);
            writeNode(file, node->left);
        }
        if (node->right != NULL) {
            fprintf(file, "%d -> %d;\n", node->value, node->right->value);
            writeNode(file, node->right);
        }
    }else{
        fprintf(file, "Adiciona pelo menos um nó na árvore, na moralzinha :)\n");
    }
}

void generateDotFile(rbtree_Node *root, const char *filename) {
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo para escrita.");
        return;
    }

    fprintf(file, "digraph RedBlackTree {\n");
    writeNode(file, root);
    fprintf(file, "}\n");

    fclose(file);
}

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
        printf("7.Sair e gerar visualização da árvore\n");
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
                generateDotFile(t->root, "arvore.dot");
                generatePNG("arvore.dot", "arvore.png");
                printf("\nGerando a árvore em PNG...\n");
                openPNG("arvore.png");
                exit(1);
                break;
            default:
                printf("Valor inválido!\n");
                break;
    }

    }





    return 0;
}