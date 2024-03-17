# Red-Black Tree (Árvore Rubro-Negra)

## Resumo

A árvore rubro-negra é uma estrutura de dados de árvore binária de busca balanceada que garante um tempo de busca, inserção e remoção de O(log n), onde n é o número de elementos na árvore. Essa estrutura de dados mantém o equilíbrio por meio de regras de coloração e rotações, garantindo que a altura da árvore seja sempre O(log n).

## Principais Características

- **Balanceamento:** A árvore rubro-negra é uma árvore binária de busca balanceada, garantindo que a altura da árvore seja O(log n).
  
- **Propriedades:**
    1. *Propriedade 1:* Um nó é vermelho ou preto.
    2. *Propriedade 2:* A raiz é sempre preta.
    3. *Propriedade 3:* Todos os nós nulos (folhas) são pretos.
    4. *Propriedade 4:* Se um nó é vermelho, seus filhos devem ser pretos.
    5. *Propriedade 5:* Para cada nó, todos os caminhos de qualquer nó para todos os nós nulos devem ter o mesmo número de nós pretos.

- **Rotações:**
    - *Rotação à esquerda:* Uma rotação de um nó para a esquerda.
    - *Rotação à direita:* Uma rotação de um nó para a direita.

## Principais Comandos no Código

- **rbtree_createNode(int value):** Cria um novo nó com o valor especificado e retorna um ponteiro para esse nó.

- **createRoot():** Cria uma nova árvore rubro-negra (RBTree) com a raiz inicializada como nula e retorna um ponteiro para essa árvore.

- **insertRedBlack(rbtree *root, int valor):** Insere um novo valor na árvore rubro-negra e mantém o balanceamento.

- **removeRedBlack(rbtree *root, int valor):** Remove um valor da árvore rubro-negra e mantém o balanceamento.

- **alturaNo(rbtree_Node *root, int valor):** Retorna a altura em que um nó específico com o valor dado está localizado na árvore.

- **alturaBlack(rbtree_Node *root):** Retorna a altura negra da árvore, ou seja, o número de nós pretos ao longo do caminho mais longo da raiz a uma folha.

- **printOrder(rbtree_Node *root):** Imprime os valores da árvore em ordem.

- **printPosOrder(rbtree_Node *root):** Imprime os valores da árvore em pós-ordem.

- **printPreOrder(rbtree_Node *root):** Imprime os valores da árvore em pré-ordem.

Estes são alguns dos principais comandos no código fornecido, responsáveis pela manipulação e manutenção de uma árvore rubro-negra.

## Como Contribuir

Se você quiser contribuir para este projeto, siga estas etapas:

1. Faça um fork do repositório.
2. Crie uma branch com uma nova funcionalidade (`git checkout -b feature/nova-feature`).
3. Faça commit de suas alterações (`git commit -am 'Adicionando nova feature'`).
4. Faça push para a branch (`git push origin feature/nova-feature`).
5. Crie um novo Pull Request.

## Licença

Este projeto está licenciado sob a licença [MIT](LICENSE.md) - veja o arquivo LICENSE.md para detalhes.


