/*************************************** 
* Equipe: Deivisson Vinicius França de Jesus
*         Edmar Amorim dos Santos Junior
* 
***************************************/

/**
* Considere as seguintes entrada e sáida abaixo:

*                  L2Q1.in
  |---------------------------------------------|
  |             8 −1 4 6 9 11 15                |
  |             5 6 7 6 5 4                     |
  |---------------------------------------------|
*                  L2Q1.out
   |---------------------------------------------|
   |     0 1 1 2 2 2 3 4 max 15 a l t 4 pred 11  |
   |     0 1 2 3 2 1 max 7 a l t 2 pred 6        |
   |---------------------------------------------| 
* Cada linha da entrada consiste em uma lista de números inteiros a ser inserida em árvore binária inicialmente vazia. O número mı́nimo de arestas de um nó à raiz define a altura deste nó. O nó raiz, portanto, tem altura zero. A cada adição de nó, se registra a altura deste. Nós com chave menor se posicionam à esquerda de seu nó pai, aqueles com chave maior ou igual à do nó pai à sua direita.

* Na saída, você deve registrar a altura de cada nó inserido na sequência informada, o nó com chave máxima, sua altura e seu predecessor (não havendo predecessor, imprima NaN).
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define LINE_SIZE 1024
#define MAX_NODES 50

typedef struct Node {
    int key;
    struct Node *left;
    struct Node *right;
    struct Node *parent;
    int height;
} Node;

typedef struct BSTResult {
    int heights[LINE_SIZE];
    int count;
    int max_key;
    int max_height;
    int predecessor;
} BSTResult;

void start();
void process_line(char *line, BSTResult *result);
Node* insert(Node **root, int key);
Node* find_predecessor(Node *root, int key);
Node* find_max(Node *root);
void free_tree(Node *root);

int main() {
    start();
    return 0;
}

void start() {
    FILE *input = fopen("L2Q1.in", "r");
    FILE *output = fopen("L2Q1.out", "w");
        
    if (!input || !output) {
        perror("Error opening files.");
        return;
    }
        
    char line[LINE_SIZE];
    BSTResult result;
    while (fgets(line, LINE_SIZE, input)) {
        if (line[0] == '\n')
            continue;
        result.count = 0;
        process_line(line, &result);
        
        for (int i = 0; i < result.count; i++) {
            fprintf(output, "%d ", result.heights[i]);
        }
        fprintf(output, "max %d a l t %d pred %d\n", result.max_key, result.max_height, result.predecessor);
    }
    
    fclose(input);
    fclose(output);
}

void process_line(char *line, BSTResult *result) {
    Node *root = NULL;
    char *token = strtok(line, " \n");
    
    while (token != NULL) {
        int key = atoi(token);
        Node *new_node = insert(&root, key);
        
        result->heights[result->count++] = new_node->height;
        
        token = strtok(NULL, " \n");
    }
    
    Node *max_node = find_max(root);
    if (max_node) {
        result->max_key = max_node->key;
        result->max_height = max_node->height;
        Node *pred = find_predecessor(root, max_node->key);
        result->predecessor = pred ? pred->key : -1;
    }
    
    free_tree(root);
}

Node* insert(Node **root, int key) {
    Node *new_node = malloc(sizeof(Node));
    new_node->key = key;
    new_node->left = new_node->right = new_node->parent = NULL;
    new_node->height = 0;

    if (*root == NULL) {
        *root = new_node;
        return new_node;
    }

    Node *current = *root;
    Node *parent = NULL;
    
    while (current) {
        parent = current;
        if (key < current->key) {
            current = current->left;
        } else {
            current = current->right;
        }
    }

    new_node->parent = parent;
    new_node->height = parent->height + 1;
    
    if (key < parent->key) 
        parent->left = new_node;
    else 
        parent->right = new_node;

    return new_node;
}

Node* find_max(Node *root) {
    if (!root) return NULL;
    while (root->right) 
        root = root->right;
    return root;
}

Node* find_predecessor(Node *root, int key) {
    Node *current = root;
    Node *pred = NULL;

    while (current && current->key != key) {
        if (key < current->key) {
            current = current->left;
        } else {
            pred = current;
            current = current->right;
        }
    }

    if (!current) return NULL;
    if (current->left) {
        current = current->left;
        while (current->right) 
            current = current->right;
        return current;
    }
    return pred;
}

void free_tree(Node *root) {
    if (root) {
        free_tree(root->left);
        free_tree(root->right);
        free(root);
    }
}