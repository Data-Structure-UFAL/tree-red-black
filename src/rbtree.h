#ifndef RBTREE_H
#define RBTREE_H

// RED = 0 / BLACK = 1
enum node_color { RED, BLACK };

typedef struct rbtree_Node {
    int value;
    struct rbtree_Node* left;
    struct rbtree_Node* right;
    struct rbtree_Node* parent;
    enum node_color color;
} rbtree_Node;

// Definição da árvore
typedef struct rbtree {
    struct rbtree_Node * root;
} rbtree;

typedef enum node_color color;

// Funções públicas da árvore rubro-negra
rbtree_Node* rbtree_createNode(int value);
rbtree * createRoot();
color node_color(rbtree_Node *n);
rbtree_Node * avo(rbtree_Node *n);
rbtree_Node * irmao(rbtree_Node *n);
rbtree_Node *tio(rbtree_Node *n);
rbtree_Node * maxNode(rbtree_Node *rb);
rbtree_Node * raiz(rbtree * root);

void replace_node(rbtree *t, rbtree_Node *oldN, rbtree_Node *newN);
void rotateLeft(rbtree *root, rbtree_Node * rb);
void rotateRight(rbtree *root, rbtree_Node * rb);

void insertCaso1(rbtree *root, rbtree_Node *rb);
void insertCaso2(rbtree *root, rbtree_Node *rb);
void insertCaso3(rbtree *root, rbtree_Node *rb);
void insertCaso4(rbtree *root, rbtree_Node *rb);
void insertCaso5(rbtree *root, rbtree_Node *rb);
void printOrder(rbtree_Node *root);
void printPosOrder(rbtree_Node *root);
void printPreOrder(rbtree_Node *root);
void removeRedBlack(rbtree *root, int valor);
void removeCaso1(rbtree *root, rbtree_Node *rb);
void removeCaso2(rbtree *root, rbtree_Node *rb);
void removeCaso3(rbtree *root, rbtree_Node *rb);
void removeCaso4(rbtree *root, rbtree_Node *rb);
void removeCaso5(rbtree *root, rbtree_Node *rb);
void removeCaso6(rbtree *root, rbtree_Node *rb);

void insertRedBlack(rbtree *root, int valor);
int alturaBlack(rbtree_Node *root);
void removeRedBlack(rbtree *root, int valor);
int encontrarAltura(rbtree_Node *root, int valor, int alturaAtual);
int alturaNo(rbtree_Node *root, int valor);
//void rbtree_insert(rbtree *tree, void* value);
//void rbtree_inorder(rbtree_Node *root);



#endif 
