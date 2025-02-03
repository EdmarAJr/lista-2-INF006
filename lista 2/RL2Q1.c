/**
* Considere as seguintes entrada e sáida abaixo:

*             L2Q1.in

         5 8 −1 4 6 9 11 15
         5 6 7 6 5 4

*                L2Q1.out

     0 1 1 2 2 2 3 4 max 15 a l t 4 pred 11
     0 1 2 3 2 1 max 7 a l t 2 pred 6

* Cada linha da entrada consiste em uma lista de números inteiros a ser inserida em árvore binária inicialmente vazia. O número mı́nimo de arestas de um nó à raiz define a altura deste nó. O nó raiz, portanto, tem altura zero. A cada adição de nó, se registra a altura deste. Nós com chave menor se posicionam à esquerda de seu nó pai, aqueles com chave maior ou igual à do nó pai à sua direita.

* Na sáida, você deve registrar a altura de cada nó inserido na sequência informada, o nó com chave máxima, sua altura e seu predecessor (não havendo predecessor, imprima NaN).
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    int key;
    struct Node *left;
    struct Node *right;
    struct Node *parent;
    int height;
} Node;

Node *insert(Node **root, int key) {
    Node *new_node = (Node *)malloc(sizeof(Node));
    new_node->key = key;
    new_node->left = NULL;
    new_node->right = NULL;
    new_node->parent = NULL;
    new_node->height = 0;

    if (*root == NULL) {
        *root = new_node;
        return new_node;
    }

    Node *current = *root;
    Node *parent = NULL;

    while (current != NULL) {
        parent = current;
        if (key < current->key) {
            current = current->left;
        } else {
            current = current->right;
        }
    }

    new_node->parent = parent;
    new_node->height = parent->height + 1;

    if (key < parent->key) {
        parent->left = new_node;
    } else {
        parent->right = new_node;
    }

    return new_node;
}

Node *predecessor(Node *node) {
    if (node == NULL) return NULL;

    if (node->left != NULL) {
        Node *current = node->left;
        while (current->right != NULL)
            current = current->right;
        return current;
    } else {
        Node *current = node;
        Node *parent = current->parent;
        while (parent != NULL && current == parent->left) {
            current = parent;
            parent = current->parent;
        }
        return parent;
    }
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
        Node **insert_order = NULL;
        int count = 0;
        char *token = strtok(line, " \n");

        while (token != NULL) {
            int key = atoi(token);
            Node *new_node = insert(&root, key);
            insert_order = realloc(insert_order, (count + 1) * sizeof(Node *));
            insert_order[count++] = new_node;
            token = strtok(NULL, " \n");
        }

        for (int i = 0; i < count; i++) {
            printf("%d ", insert_order[i]->height);
        }

        Node *max_node = root;
        while (max_node && max_node->right) {
            max_node = max_node->right;
        }

        if (max_node) {
            Node *pred = predecessor(max_node);
            printf("max %d alt %d pred ", max_node->key, max_node->height);
            if (pred) {
                printf("%d\n", pred->key);
            } else {
                printf("NaN\n");
            }
        } else {
            printf("max NaN alt NaN pred NaN\n");
        }

        free(insert_order);
        free_tree(root);
    }
    return 0;
}