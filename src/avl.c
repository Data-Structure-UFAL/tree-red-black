#include "avl.h"
#include <stdlib.h>


// Função para criar um novo nó com um determinado valor
struct AVLNode {
    int key;
    struct AVLNode *left;
    struct AVLNode *right;
    int height;
};

// Função para criar um novo nó com um determinado valor
struct AVLNode* newNode(int key) {
    struct AVLNode* node = (struct AVLNode*)malloc(sizeof(struct AVLNode));
    node->key = key;
    node->left = NULL;
    node->right = NULL;
    node->height = 1; // Novo nó é adicionado como folha, sua altura é 1
    return node;
}

// Função para calcular a altura de um nó
int height(struct AVLNode *N) {
    if (N == NULL)
        return 0;
    return N->height;
}

// Função para retornar o máximo entre dois inteiros
int max(int a, int b) {
    return (a > b) ? a : b;
}

// Função auxiliar para encontrar o nó com o menor valor em uma árvore AVL
struct AVLNode* minValueNode(struct AVLNode* node) {
    struct AVLNode* current = node;

    // Percorrer a árvore até encontrar o nó mais à esquerda, que terá o menor valor
    while (current && current->left != NULL)
        current = current->left;

    return current;
}


// Função para realizar uma rotação simples à direita
struct AVLNode* rightRotate(struct AVLNode *y, int *count) {
    struct AVLNode *x = y->left;
    struct AVLNode *T2 = x->right;
    // Realizar a rotação
    x->right = y;
    y->left = T2;

    // Atualizar alturas
    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;

    // Incrementar o contador de rotações à direita
    (*count)++;
    // Retornar nova raiz
    return x;
}

// Função para realizar uma rotação simples à esquerda
struct AVLNode* leftRotate(struct AVLNode *x, int *count) {
    struct AVLNode *y = x->right;
    struct AVLNode *T2 = y->left;

    // Realizar a rotação
    y->left = x;
    x->right = T2;

    // Atualizar alturas
    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;

    // Incrementar o contador de rotações à esquerda

    (*count)++;
    // Retornar nova raiz
    return y;
}

// Função para obter o fator de balanceamento de um nó
int getBalance(struct AVLNode *N) {
    if (N == NULL)
        return 0;
    return height(N->left) - height(N->right);
}

// Função para inserir um novo valor em uma árvore AVL
struct AVLNode* insert(struct AVLNode* node, int key, int *count) {
    if (node == NULL)
        return newNode(key);

    if (key < node->key)
        node->left = insert(node->left, key, count);
    else if (key > node->key)
        node->right = insert(node->right, key, count);
    else
        return node; // Chaves iguais não são permitidas na árvore AVL

    // Atualizar a altura deste nó ancestral
    node->height = 1 + max(height(node->left), height(node->right));

    // Obter o fator de balanceamento deste nó ancestral para verificar se ele se tornou desequilibrado
    int balance = getBalance(node);

    // Se o nó se tornar desequilibrado, então há 4 casos possíveis

    // Caso esquerda-esquerda
    if (balance > 1 && key < node->left->key) {
        return rightRotate(node, count);
    }

    // Caso direita-direita
    if (balance < -1 && key > node->right->key) {
        return leftRotate(node, count);
    }

    // Caso esquerda-direita
    if (balance > 1 && key > node->left->key) {
        node->left = leftRotate(node->left, count);
        return rightRotate(node, count);
    }

    // Caso direita-esquerda
    if (balance < -1 && key < node->right->key) {
        node->right = rightRotate(node->right, count);
        return leftRotate(node, count);
    }

    return node;
}

// Função para remover um valor de uma árvore AVL
struct AVLNode* deleteNode(struct AVLNode* root, int key, int *count) {
    // Caso base: árvore vazia
    if (root == NULL)
        return root;

    // Se a chave a ser excluída for menor que a chave do nó atual, ela está na subárvore esquerda
    if (key < root->key)
        root->left = deleteNode(root->left, key, count);

    // Se a chave a ser excluída for maior que a chave do nó atual, ela está na subárvore direita
    else if (key > root->key)
        root->right = deleteNode(root->right, key, count);

    // Se a chave a ser excluída for igual à chave do nó atual, este é o nó a ser excluído
    else {
        // Nó com apenas um filho ou nenhum filho
        if ((root->left == NULL) || (root->right == NULL)) {
            struct AVLNode *temp = root->left ? root->left : root->right;

            // Caso sem filho
            if (temp == NULL) {
                temp = root;
                root = NULL;
            } else // Caso com um filho
                *root = *temp; // Copia os conteúdos do filho não vazio

            free(temp);
        } else {
            // Nó com dois filhos: obter o sucessor inOrder (menor nó da subárvore direita)
            struct AVLNode* temp = minValueNode(root->right);

            // Copiar o valor do sucessor inOrder para este nó
            root->key = temp->key;

            // Excluir o sucessor inOrder
            root->right = deleteNode(root->right, temp->key, count);
        }
    }

    // Se a árvore tinha apenas um nó, retornar
    if (root == NULL)
        return root;

    // Atualizar a altura deste nó atual
    root->height = 1 + max(height(root->left), height(root->right));

    // Obter o fator de balanceamento deste nó atual
    int balance = getBalance(root);

    // Caso esquerda-esquerda
    if (balance > 1 && getBalance(root->left) >= 0) {
        return rightRotate(root, count);
    }

    // Caso esquerda-direita
    if (balance > 1 && getBalance(root->left) < 0) {
        root->left = leftRotate(root->left, count);
        return rightRotate(root, count);
    }

    // Caso direita-direita
    if (balance < -1 && getBalance(root->right) <= 0) {
        return leftRotate(root, count);
    }

    // Caso direita-esquerda
    if (balance < -1 && getBalance(root->right) > 0) {
        root->right = rightRotate(root->right, count);
        return leftRotate(root, count);
    }

    return root;
}


// Função para realizar o percurso em ordem na árvore AVL
void inOrderTraversal(struct AVLNode *root) {
    if (root != NULL) {
        inOrderTraversal(root->left);
        printf("%d ", root->key);
        inOrderTraversal(root->right);
    }
}
