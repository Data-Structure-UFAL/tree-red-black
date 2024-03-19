#ifndef AVL_TREE_H
#define AVL_TREE_H

// Definição da estrutura do nó da árvore AVL
// Protótipos das funções
struct AVLNode* newNode(int key);
int height(struct AVLNode *node);
int max(int a, int b);
struct AVLNode* rightRotate(struct AVLNode *y, int *count);
struct AVLNode* leftRotate(struct AVLNode *x, int *count);
int getBalance(struct AVLNode *node);
struct AVLNode* insert(struct AVLNode* node, int key, int *count);
void inOrderTraversal(struct AVLNode *root);
struct AVLNode* deleteNode(struct AVLNode* root, int key, int *count);
struct AVLNode* minValueNode(struct AVLNode* node);
#endif /* AVL_TREE_H */
