#include "rbtree.h"
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define RED_COLOR   "\033[0;31m"
#define GREEN_COLOR "\033[0;32m"
#define YELLOW_COLOR "\033[0;33m"
#define BLUE_COLOR  "\033[0;34m"
#define RESET_COLOR "\033[0m"

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
    root->rotations=0;
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

int maxDepthValue(rbtree_Node* root) {
    // Se o nó atual for nulo, retornamos -1
    if (root == NULL) {
        return -1;
    }

    // Chamamos recursivamente a função para os filhos esquerdo e direito
    int leftDepth = maxDepthValue(root->left);
    int rightDepth = maxDepthValue(root->right);

    // Calculamos a altura do nó como o máximo entre as alturas dos filhos mais 1
    return 1 + (leftDepth > rightDepth ? leftDepth : rightDepth);
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

void replace_node(rbtree *t, rbtree_Node *parentNode, rbtree_Node *sonNode){
    if(parentNode->parent == NULL){
        //pai é null? parentNode é raiz
        //nova raiz é sonNode
        t->root = sonNode;
    }else{
         //sonNode no lugar de parentNode
        if(parentNode == parentNode->parent->left){
            parentNode->parent->left = sonNode;
        }else{
            parentNode->parent->right = sonNode;
        }
    }
    if(sonNode != NULL){
        //atualizando o pai
        sonNode->parent = parentNode->parent;
    }
}

void rotateLeft(rbtree *root, rbtree_Node * parent){
    rbtree_Node * son = parent->right;
    replace_node(root, parent, son);
    parent->right = son->left;
    if(son->left != NULL){
        son->left->parent = parent;
    }
    son->left = parent;
    parent->parent = son;
}

void rotateRight(rbtree *root, rbtree_Node * parent){
    rbtree_Node * son = parent->left;
    replace_node(root, parent, son);
    parent->left = son->right;
    if(son->right != NULL){
        son->right->parent = parent;
    }
    son->right = parent;
    parent->parent = son;
}

void insertRedBlack(rbtree *rbtree_root, int valor){
    rbtree_Node *newRB = rbtree_createNode(valor);
    if(rbtree_root->root == NULL){
        rbtree_root->root = newRB;
    }else{
        rbtree_Node *rb = rbtree_root->root;
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
    is_root(rbtree_root, newRB);
}

//caso raiz
void is_root(rbtree *root, rbtree_Node *rb){
    if(rb->parent == NULL){
        rb->color = BLACK;
    }else{
        insertCaso1(root, rb);
    }
}
//nós vermelhos adjacentes
//recolorir pai, tio e avô
void insertCaso1(rbtree *root, rbtree_Node *son){
    if(son->parent->color == BLACK) return;
    //pai é preto? a árvore está balanceada

    if(node_color(tio(son)) == BLACK){
        insertCaso2(root, son);
    }else{
        son->parent->color = BLACK;
        tio(son)->color = BLACK;
        avo(son)->color = RED;
        is_root(root, avo(son)); 
        /*chamada para trocar a cor do avô (raiz)
         de red para black, pela propriedade 2*/
    }
}

//rotação
void insertCaso2(rbtree *root, rbtree_Node *son){
    if(son == son->parent->right && son->parent == avo(son)->left){
        //Esquerdo-Direito
        rotateLeft(root, son->parent);
        son = son->left;
    }else if(son == son->parent->left && son->parent == avo(son)->right){
        //Direito-Esquerdo
        rotateRight(root, son->parent);
        son = son->right;
    }
    insertCaso3(root, son);
}

void insertCaso3(rbtree *root, rbtree_Node *son){
    son->parent->color = BLACK;
    avo(son)->color = RED;
    if(son == son->parent->left && son->parent == avo(son)->left){
        rotateRight(root, avo(son));
    }else{
        rotateLeft(root, avo(son));
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

void printPreOrderComCor(rbtree_Node *root){
    if(root != NULL){
        printf("(");
        if(root->color==RED){
            printf(RED_COLOR);
        }
        printf("%d", root->value);
        if(root->color==RED){
            printf(RESET_COLOR);
        }               
        printPreOrderComCor(root->left);        
        printPreOrderComCor(root->right);
        printf(")");     
    }else{
        printf("()");   
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
int buscar(rbtree_Node *root, int valor, int alturaAtual) {
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
        return buscar(root->left, valor, alturaAtual + 1);
    }
    // Se o valor procurado for maior que o valor do nó atual, recursivamente buscamos na subárvore direita
    else {
        return buscar(root->right, valor, alturaAtual + 1);
    }
}

// Função para encontrar um nó na árvore e retornar a altura em que se encontra
int alturaNo(rbtree_Node *root, int valor) {
    // Chamamos a função auxiliar passando a altura inicial como 0
    return buscar(root, valor, 0);
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