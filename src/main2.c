#include <stdio.h>
#include <stdlib.h>
#include "avl.c" // Incluindo o cabeçalho da árvore AVL
#include "rbtree.c" // Incluindo o cabeçalho da árvore Rubro-Negra
#include <time.h>

int random_int(int min, int max) {
    return min + rand() % (max - min + 1);
}

// Função para calcular a quantidade de rotações em uma árvore AVL ao inserir um valor
// Função para calcular a quantidade de rotações em uma árvore AVL ao inserir um valor
int avl_insert_rotation_count(struct AVLNode **root, int *values, int size) {
    int rotation_count = 0;

    for (int i = 0; i < size; i++) {
        //int previous_height = (*root)->height;
        *root = insert(*root, values[i], &rotation_count);
        //if ((*root)->height != previous_height){
            //rotation_count++;
        //} // Se a altura mudou, uma rotação foi realizada
            
    }

    return rotation_count;
}

// Função para calcular a quantidade de rotações em uma árvore AVL ao remover um valor
int avl_remove_rotation_count(struct AVLNode **root, int *values, int size) {
    int rotation_count = 0;

    for (int i = 0; i < size; i++) {
        //int previous_height = (*root)->height;
        *root = deleteNode(*root, values[i], &rotation_count);
        //if ((*root)->height != previous_height){
        //} // Se a altura mudou, uma rotação foi realizada
           
    }

    return rotation_count;
}


// Função para calcular a quantidade de rotações em uma árvore Rubro-Negra ao inserir um valor
int rb_insert_rotation_count(rbtree **tree, int *values, int size) {
    int rotation_count = 0;

    for (int i = 0; i < size; i++) {
        insertRedBlack(*tree, values[i]);
        rotation_count += (*tree)->rotations;
        (*tree)->rotations = 0;
    }

    return rotation_count;
}

// Função para calcular a quantidade de rotações em uma árvore Rubro-Negra ao remover um valor
int rb_remove_rotation_count(rbtree **tree, int *values, int size) {
    int rotation_count = 0;

    for (int i = 0; i < size; i++) {
        removeRedBlack(*tree, values[i]);
        rotation_count += (*tree)->rotations;
        (*tree)->rotations = 0;
    }

    return rotation_count;
}

int main(int argc, char const *argv[]){
    srand(time(NULL));

    int n = 200; // Número de elementos a serem inseridos/removidos nas árvores
    int values[n];
    int values2[n];

    // Gerar valores aleatórios para inserção/remoção nas árvores
    for (int i = 0; i < n; i++) {
        values[i] = random_int(1, 200);
    }

    // Criar as árvores AVL e Rubro-Negra
    struct AVLNode *avl_root = NULL;
    rbtree *rb_tree = createRoot();

    // Calcular o número de rotações para inserir/remover os valores nas árvores AVL e Rubro-Negra
    int avl_insert_rotations = avl_insert_rotation_count(&avl_root, values, n);
    int avl_remove_rotations = avl_remove_rotation_count(&avl_root, values, n);
    int rb_insert_rotations = rb_insert_rotation_count(&rb_tree, values, n);
    int rb_remove_rotations = rb_remove_rotation_count(&rb_tree, values, n);

    // Escrever os dados em um arquivo para plotagem
    FILE *fp = fopen("rotations_data.txt", "w");
    if (fp == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return 1;
    }

    fprintf(fp, "AVL Insert Rotations\tAVL Remove Rotations\tRed-Black Insert Rotations\tRed-Black Remove Rotations\n");
    fprintf(fp, "%d\t%d\t%d\t%d\n", avl_insert_rotations, avl_remove_rotations, rb_insert_rotations, rb_remove_rotations);

    fclose(fp);

    printf("Número de rotações em AVL (Inserção): %d\n", avl_insert_rotations);
    printf("Número de rotações em AVL (Remoção): %d\n", avl_remove_rotations);
    printf("Número de rotações em Red-Black (Inserção): %d\n", rb_insert_rotations);
    printf("Número de rotações em Red-Black (Remoção): %d\n", rb_remove_rotations);
    
    return 0;
}
