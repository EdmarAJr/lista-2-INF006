/**
* Considere as seguintes entrada e sáida abaixo:

*          L2Q2.in

*    15 2 5 19 2 22 4 9 0 3 4 5
*    0 2 4 5 1
*    4

*                      L2Q2.out

*    0 (0 ) 2 (21) 3 (0 ) 4 (−3) 5 (2 ) 9 (0 ) 15 (18) 19 (22) 22 (0 )
*    0 (12) 1 (0 ) 2 (8 ) 4 (5 ) 5 (0 )
*    4 (0 )

* Cada linha da entrada consiste em uma lista de números inteiros a ser inserida em árvore binária inicialmente vazia. O número mı́nimo de arestas de um nó à raiz define a altura deste nó. O nó raiz, portanto, tem altura zero. A cada adição de nó, se registra a altura deste. Nós com chave menor se posicionam à esquerda de seu nó pai, aqueles com chave maior ou igual à do nó pai à sua direita. Porém, nesta questão, árvores não admitirão nós duplicados.

* Na sáida, cada nó, em ordem, registrará a diferença entre a soma dos nós à direita menos a soma dos nós à esquerda (nesta ordem).
*/

 #include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    int key;
    struct Node *left;
    struct Node *right;
    int left_sum;
    int right_sum;
} Node;

Node *insert(Node **root, int key) {
    if (*root == NULL) {
        Node *new_node = (Node *)malloc(sizeof(Node));
        new_node->key = key;
        new_node->left = NULL;
        new_node->right = NULL;
        new_node->left_sum = 0;
        new_node->right_sum = 0;
        *root = new_node;
        return new_node;
    }

    if (key < (*root)->key) {
        return insert(&(*root)->left, key);
    } else if (key > (*root)->key) {
        return insert(&(*root)->right, key);
    }
    return *root;
}

int compute_sums(Node *node) {
    if (node == NULL) return 0;
    node->left_sum = compute_sums(node->left);
    node->right_sum = compute_sums(node->right);
    return node->key + node->left_sum + node->right_sum;
}

void in_order(Node *root) {
    if (root == NULL) return;
    in_order(root->left);
    printf("%d (%d) ", root->key, root->right_sum - root->left_sum);
    in_order(root->right);
}

void free_tree(Node *root) {
    if (root == NULL) return;
    free_tree(root->left);
    free_tree(root->right);
    free(root);
}

int main() {
    char line[1024];
    while (fgets(line, sizeof(line), stdin)) {
        Node *root = NULL;
        char *token = strtok(line, " \n");
        while (token != NULL) {
            int key = atoi(token);
            insert(&root, key);
            token = strtok(NULL, " \n");
        }
        compute_sums(root);
        in_order(root);
        printf("\n");
        free_tree(root);
    }
    return 0;
}