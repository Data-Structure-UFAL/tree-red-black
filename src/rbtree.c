#include "rbtree.h"
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

// Função para criar um novo nó
rbtree_Node* rbtree_createNode(int value) {
    rbtree_Node* newNode = (rbtree_Node*)malloc(sizeof(rbtree_Node));
    newNode->value = value;
    newNode->color = RED; // Novos nós sempre são vermelhos
    newNode->parent = NULL;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

rbtree * createRoot(){
    rbtree * root = malloc(sizeof(rbtree));
    root->root = NULL;
    return root;
}

color node_color(rbtree_Node *n){
    return n == NULL ? BLACK : n->color;
}

rbtree_Node * raiz(rbtree * root){
    return root->root;
}

rbtree_Node * maxNode(rbtree_Node *rb){
    while(rb->right != NULL){
        rb = rb->right;
    }
    return rb;
}

rbtree_Node * avo(rbtree_Node *n){
    return n->parent->parent;
}

rbtree_Node * irmao(rbtree_Node *n){
    if(n == n->parent->left){
        return n->parent->right;
    }else{
        return n->parent->left;
    }
}

rbtree_Node *tio(rbtree_Node *n){
    return irmao(n->parent);
}

void replace_node(rbtree *t, rbtree_Node *oldN, rbtree_Node *newN){
    if(oldN->parent == NULL){
        t->root = newN;
    }else{
        if(oldN == oldN->parent->left){
            oldN->parent->left = newN;
        }else{
            oldN->parent->right = newN;
        }
    }
    if(newN != NULL){
        newN->parent = oldN->parent;
    }
}

void rotateLeft(rbtree *root, rbtree_Node * rb){
    rbtree_Node * r = rb->right;
    replace_node(root, rb, r);
    rb->right = r->left;
    if(r->left != NULL){
        r->left->parent = rb;
    }
    r->left = rb;
    rb->parent = r;
}

void rotateRight(rbtree *root, rbtree_Node * rb){
    rbtree_Node * r = rb->left;
    replace_node(root, rb, r);
    rb->left = r->right;
    if(r->right != NULL){
        r->right->parent = rb;
    }
    r->right = rb;
    rb->parent = r;
}

void insertRedBlack(rbtree *root, int valor){
    rbtree_Node *newRB = rbtree_createNode(valor);
    if(root->root == NULL){
        root->root = newRB;
    }else{
        rbtree_Node *rb = root->root;
        while(1){
            if(valor == rb->value){
                free(newRB);
                return;
            }else if(valor<rb->value){
                if(rb->left == NULL){
                    rb->left = newRB;
                    break;
                }else{
                    rb = rb->left;
                }
            }else{
                if(rb->right == NULL){
                    rb->right = newRB;
                    break;
                }else{
                    rb = rb->right;
                }
            }
        }
        newRB->parent = rb;
    }
    insertCaso1(root, newRB);
}

//caso raiz
void insertCaso1(rbtree *root, rbtree_Node *rb){
    if(rb->parent == NULL){
        rb->color = BLACK;
    }else{
        insertCaso2(root, rb);
    }
}


void insertCaso2(rbtree *root, rbtree_Node *rb){
    if(rb->parent->color == BLACK){
        return; //raiz é preta? a árvore está balanceada
    }else{
        insertCaso3(root, rb);
    }
}

//nós vermelhos adjacentes
//recolorir pai, tio e avô

void insertCaso3(rbtree *root, rbtree_Node *rb){
    if(node_color(tio(rb)) == BLACK){
        insertCaso4(root, rb);
    }else{
        printf("\n");
        printf("Pai e filho vermelhos\n");
        printf("Balanceando e ajustando cores do pai(%d), tio(%d) e avô(%d)...\n", rb->parent->value, tio(rb)->value, avo(rb)->value);
        printf("\n");
        rb->parent->color = BLACK;
        tio(rb)->color = BLACK;
        avo(rb)->color = RED;
        if(avo(rb)->parent==NULL){
            printf("Vôzinho é a raiz e ele é ");
            if(avo(rb)->color == RED){
                printf("RED(%d)\n", avo(rb)->value);
            }else{
                printf("BLACK(%d), então fere a propriedade 2\nTrocando cor...\n", avo(rb)->value);
            }   
        }
        insertCaso1(root, avo(rb)); //chamada para trocar a cor do avô (raiz) de red para black, pela propriedade 2
    }
}

//rotação
void insertCaso4(rbtree *root, rbtree_Node *rb){
    printf("\n");
    //printf("Rotacionando para que o pai(%d) e o tio(%d, ", rb->parent->value, tio(rb)->value);
    //tio(rb)->color == BLACK ? printf("BLACK)\n") : printf("RED)\n");
    printf("\n");
    if(rb == rb->parent->right && rb->parent == avo(rb)->left){
        //Esquerdo-Direito
        printf("\n");
        printf("%d é filho a direita do pai(%d), e o pai é filho a esquerda do avo(%d)\n", rb->value, rb->parent->value, avo(rb)->value);
        printf("Rotacionando a esquerda...\n");
        printf("\n");
        rotateLeft(root, rb->parent);
        rb = rb->left;
    }else if(rb == rb->parent->left && rb->parent == avo(rb)->right){
        //Direito-Esquerdo
        printf("\n");
        printf("%d é filho a esquerda do pai(%d), e o pai é filho a direita do avo(%d)\n", rb->value, rb->parent->value, avo(rb)->value);
        printf("Rotacionndo a direita...\n");
        printf("\n");
        rotateRight(root, rb->parent);
        rb = rb->right;
    }
    insertCaso5(root, rb);
}

void insertCaso5(rbtree *root, rbtree_Node *rb){
    rb->parent->color = BLACK;
    avo(rb)->color = RED;
    if(rb == rb->parent->left && rb->parent == avo(rb)->left){
        printf("\n");
        printf("%d é filho a esquerda do pai(%d), e o pai é filho a esquerda do avo(%d)\n", rb->value, rb->parent->value, avo(rb)->value);
        printf("Rotacionando a direita...\n");
        printf("Nova raiz (pai): %d\n", rb->parent->value);
        printf("Novo filho a esquerda: %d\n", rb->value);
        printf("Novo filho a direita: %d\n", avo(rb)->value);
        printf("\n");
        rotateRight(root, avo(rb));
    }else{
        printf("\n");
        printf("%d é filho a direita do pai(%d), e o pai é filho a direita do avo(%d)\n", rb->value, rb->parent->value, avo(rb)->value);
        printf("Rotacionando a esquerda...\n");
        printf("Nova raiz (pai): %d\n", rb->parent->value);
        printf("Novo filho a esquerda: %d\n", avo(rb)->value);
        printf("Novo filho a direita: %d\n", rb->value);
        printf("\n");
        rotateLeft(root, avo(rb));
    }
}

void printOrder(rbtree_Node *root){
    if(root != NULL){
        printOrder(root->left);
        printf("[%d, ", root->value);        
        if(root->color == RED){
            printf("RED]\n");
        }else{
            printf("BLACK]\n");
        }         
        printOrder(root->right);        
    }
}

void printPosOrder(rbtree_Node *root){
    if(root != NULL){
        printPosOrder(root->left);        
        printPosOrder(root->right);
        printf("[%d, ", root->value);        
        if(root->color == RED){
            printf("RED]\n");
        }else{
            printf("BLACK]\n");
        }        
    }
}

void printPreOrder(rbtree_Node *root){
    if(root != NULL){
        printf("[%d, ", root->value); 
        if(root->color == RED){
            printf("RED]\n");
        }else{
            printf("BLACK]\n");
        }         
        printPreOrder(root->left);        
        printPreOrder(root->right);       
    }
}

rbtree_Node *busca(rbtree *root, int valor){
    rbtree_Node * rb = root->root;
    while(rb!=NULL){
        if(valor==rb->value){
            return rb;
        }else if(valor<rb->value){
            rb = rb->left;
        }else{
            rb = rb->right;
        }
    }
    return rb;
}

void removeRedBlack(rbtree *root, int valor){
    rbtree_Node * filho;
    rbtree_Node * rb = busca(root, valor);
    if(rb==NULL){
        return;
    }

    if(rb->left != NULL && rb->right != NULL){
        rbtree_Node * max = maxNode(rb->left);
        rb->value = max->value;
        rb = max;
    }

    filho = rb->right == NULL ? rb->left : rb->right;

    if(rb->color == BLACK){
        rb->color = node_color(filho);
        removeCaso1(root, rb);
    }

    replace_node(root, rb, filho);
    if(rb->parent == NULL && filho != NULL){
        filho->color = BLACK;
    }
    free(rb);
}

void removeCaso1(rbtree * root, rbtree_Node * rb){
    if(rb->parent == NULL){
        return;
    }else{
        removeCaso2(root, rb);
    }
}

void removeCaso2(rbtree * root, rbtree_Node * rb){
    if(irmao(rb)->color == RED){
        rb->parent->color = RED;
        irmao(rb)->color = BLACK;
        if(rb == rb->parent->left){
            rotateLeft(root, rb->parent);
        }else{
            rotateRight(root, rb->parent);
        }
    }
    removeCaso3(root, rb);
}

void removeCaso3(rbtree * root, rbtree_Node * rb){
    if(node_color(rb->parent)==BLACK && node_color(irmao(rb)) == BLACK && node_color(irmao(rb)->left) == BLACK && node_color(irmao(rb)->right) == BLACK){
        irmao(rb)->color = RED;
        removeCaso1(root, rb->parent);
    }else{
        removeCaso4(root, rb);
    }
}

void removeCaso4(rbtree * root, rbtree_Node * rb){
    if(node_color(rb->parent)==RED && node_color(irmao(rb)) == BLACK && node_color(irmao(rb)->left) == BLACK && node_color(irmao(rb)->right) == BLACK){
        irmao(rb)->color = RED;
        rb->parent->color = BLACK;
    }else{
        removeCaso5(root, rb);
    }
}

void removeCaso5(rbtree * root, rbtree_Node * rb){
    if(rb == rb->parent->left && node_color(irmao(rb)) == BLACK && node_color(irmao(rb)->left) == RED && node_color(irmao(rb)->right) == BLACK){
        irmao(rb)->color = RED;
        irmao(rb)->left->color = BLACK;
        rotateRight(root, irmao(rb));
    }else if(rb == rb->parent->right && node_color(irmao(rb)) == BLACK && node_color(irmao(rb)->right) == RED && node_color(irmao(rb)->left) == BLACK){
        irmao(rb)->color = RED;
        irmao(rb)->right->color = BLACK;
        rotateLeft(root, irmao(rb));
    }
    removeCaso6(root, rb);
}

void removeCaso6(rbtree * root, rbtree_Node * rb){
    irmao(rb)->color = node_color(rb->parent);
    rb->parent->color = BLACK;
    if(rb == rb->parent->left){
        irmao(rb)->right->color = BLACK;
        rotateLeft(root, rb->parent);
    }else{
       irmao(rb)->left->color = BLACK;
        rotateRight(root, rb->parent); 
    }
}

// Função auxiliar recursiva para encontrar um nó na árvore e retornar a altura
int encontrarAltura(rbtree_Node *root, int valor, int alturaAtual) {
    // Se o nó atual for nulo, retornamos -1, indicando que o valor não foi encontrado
    if (root == NULL) {
        return -1;
    }
    
    // Se o valor do nó atual for igual ao valor procurado, retornamos a altura atual
    if (root->value == valor) {
        return alturaAtual;
    }
    
    // Se o valor procurado for menor que o valor do nó atual, recursivamente buscamos na subárvore esquerda
    if (valor < root->value) {
        return encontrarAltura(root->left, valor, alturaAtual + 1);
    }
    // Se o valor procurado for maior que o valor do nó atual, recursivamente buscamos na subárvore direita
    else {
        return encontrarAltura(root->right, valor, alturaAtual + 1);
    }
}

// Função para encontrar um nó na árvore e retornar a altura em que se encontra
int alturaNo(rbtree_Node *root, int valor) {
    // Chamamos a função auxiliar passando a altura inicial como 0
    return encontrarAltura(root, valor, 0);
}


int alturaBlack(rbtree_Node *root) {
    rbtree_Node *node = root;
    int alturaNegra = 0;
    while (node != NULL) {
        if (node->color == BLACK) {
            alturaNegra++;
        }
        node = node->left;
    }
    alturaNegra++;
    return alturaNegra;
}