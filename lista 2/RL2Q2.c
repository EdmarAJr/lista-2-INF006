/**
* Considere as seguintes entrada e sáida abaixo:

*                             L2Q2.in
            |---------------------------------------------|
*           |         15 2 5 19 2 22 4 9 0 3 4 5          |   
*           |         0 2 4 5 1                           |
*           |         4                                   |
            |---------------------------------------------| 
*                             L2Q2.out
   |--------------------------------------------------------------------|
*  |  0 (0 ) 2 (21) 3 (0 ) 4 (−3) 5 (2 ) 9 (0 ) 15 (18) 19 (22) 22 (0 ) |
*  |  0 (12) 1 (0 ) 2 (8 ) 4 (5 ) 5 (0 )                                |
*  |  4 (0 )                                                            |
   |--------------------------------------------------------------------|

* Cada linha da entrada consiste em uma lista de números inteiros a ser inserida em árvore binária inicialmente vazia. O número mı́nimo de arestas de um nó à raiz define a altura deste nó. O nó raiz, portanto, tem altura zero. A cada adição de nó, se registra a altura deste. Nós com chave menor se posicionam à esquerda de seu nó pai, aqueles com chave maior ou igual à do nó pai à sua direita. Porém, nesta questão, árvores não admitirão nós duplicados.

* Na saída, cada nó, em ordem, registrará a diferença entre a soma dos nós à direita menos a soma dos nós à esquerda (nesta ordem).
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define LINE_SIZE 1024

typedef struct Node {
    int key;
    struct Node *left;
    struct Node *right;
    struct Node *parent;
    int height;
} Node;

void start();
void process_line_q2(char *line, FILE *output);
Node* insert_q2(Node *root, int key);
int subtree_sum(Node *node);
void in_order_print_q2(Node *node, FILE *output);
void free_tree(Node *root);

int main() {
    start();
    return 0;
}

void start() {
    FILE *input = fopen("L2Q2.in", "r");
    FILE *output = fopen("L2Q2.out", "w");
    
    if (!input || !output) {
        perror("Error opening files.");
        return;
    }
        
    char line[LINE_SIZE];
    while (fgets(line, LINE_SIZE, input)) {
        if (line[0] == '\n')
            continue;
        process_line_q2(line, output);
    }
    
    fclose(input);
    fclose(output);
}

void process_line_q2(char *line, FILE *output) {
    Node *root = NULL;
    char *token = strtok(line, " \n");
    
    while (token != NULL) {
        int key = atoi(token);
        root = insert_q2(root, key);
        token = strtok(NULL, " \n");
    }
    
    in_order_print_q2(root, output);
    fprintf(output, "\n");
    
    free_tree(root);
}

Node* insert_q2(Node *root, int key) {
    if (root == NULL) {
        Node *new_node = malloc(sizeof(Node));
        new_node->key = key;
        new_node->left = new_node->right = NULL;
        new_node->parent = NULL;
        new_node->height = 0; 
        return new_node;
    }
    
    if (key == root->key)
        return root;
    
    if (key < root->key) {
        root->left = insert_q2(root->left, key);
        if (root->left)
            root->left->parent = root;
    } else { 
        root->right = insert_q2(root->right, key);
        if (root->right)
            root->right->parent = root;
    }
    return root;
}

int subtree_sum(Node *node) {
    if (node == NULL)
        return 0;
    return node->key + subtree_sum(node->left) + subtree_sum(node->right);
}

void in_order_print_q2(Node *node, FILE *output) {
    if (node == NULL)
        return;
    in_order_print_q2(node->left, output);
    
    int left_sum = subtree_sum(node->left);
    int right_sum = subtree_sum(node->right);
    int diff = right_sum - left_sum;
    fprintf(output, "%d (%d) ", node->key, diff);
    
    in_order_print_q2(node->right, output);
}

void free_tree(Node *root) {
    if (root) {
        free_tree(root->left);
        free_tree(root->right);
        free(root);
    }
}
