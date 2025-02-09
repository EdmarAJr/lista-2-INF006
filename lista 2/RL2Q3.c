/*************************************** 
* Equipe: Deivisson Vinicius França de Jesus
*         Edmar Amorim dos Santos Junior
* 
***************************************/

/**
* Considere as seguintes entrada e sáida abaixo:

*                             L2Q3.in
    |-----------------------------------------------------------|
*   |      a 3 r 3 a 5 a 7 a 8 a 1 a 4 a 6 a 1 r 9 a 0 r 7      |
*   |      a 1 a 2 r 0 r 1                                      |
    |-----------------------------------------------------------|
*                            L2Q3.out
    |-------------------------------------------------------------------|
*   |     0 (2 ) 1 (1 ) 1 (3 ) 4 (2 ) 5 (0 ) 6 (2 ) 8 (1 ) 9 (2 )       |
*   |     0 (1 ) 2 (0 )                                                 |
    |-------------------------------------------------------------------|
* Cada linha representa as operações de adição e remoção em uma árvore vazia, onde a representa uma adição e r representa uma remoção (a menos que o nó a ser removido não exista, o que o transforma em uma adição!).

* Na saída, cada nó aparece em ordem seguido de sua altura na árvore entre parêntesis.
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
void process_line_q3(char *line, FILE *output);
Node* insert_q3(Node *root, int key);
Node* remove_node(Node *root, int key, bool *removed);
Node* find_min(Node *root);
void update_heights(Node *node, int current_height);
void in_order_print_q3(Node *node, FILE *output);
void free_tree(Node *root);

int main() {
    start();
    return 0;
}

void start() {
    FILE *input = fopen("L2Q3.in", "r");
    FILE *output = fopen("L2Q3.out", "w");
    
    if (!input || !output) {
        perror("Error opening files.");
        return;
    }
    
    char line[LINE_SIZE];
    while (fgets(line, LINE_SIZE, input)) {
        process_line_q3(line, output);
    }
    
    fclose(input);
    fclose(output);
}

void process_line_q3(char *line, FILE *output) {
    Node *root = NULL;
    char *token = strtok(line, " \n");
    
    while (token != NULL) {
        char op = token[0];
        token = strtok(NULL, " \n");
        if (token == NULL) break;
        int key = atoi(token);
        
        if (op == 'a') {
            root = insert_q3(root, key);
        } else if (op == 'r') {
            bool removed = false;
            root = remove_node(root, key, &removed);

            if (!removed) {
                root = insert_q3(root, key);
            }
        }
        token = strtok(NULL, " \n");
    }
    
    update_heights(root, 0);
    in_order_print_q3(root, output);
    fprintf(output, "\n");
    
    free_tree(root);
}

Node* insert_q3(Node *root, int key) {
    if (root == NULL) {
        Node *new_node = malloc(sizeof(Node));
        new_node->key = key;
        new_node->left = new_node->right = NULL;
        new_node->parent = NULL;
        new_node->height = 0; 
        return new_node;
    }

    if (key < root->key) {
        root->left = insert_q3(root->left, key);
        if (root->left)
            root->left->parent = root;
    } else {
        root->right = insert_q3(root->right, key);
        if (root->right)
            root->right->parent = root;
    }
    return root;
}

Node* remove_node(Node *root, int key, bool *removed) {
    if (root == NULL) {
        *removed = false;
        return NULL;
    }
    if (key < root->key) {
        root->left = remove_node(root->left, key, removed);
        return root;
    } else if (key > root->key) {
        root->right = remove_node(root->right, key, removed);
        return root;
    } else {
        *removed = true;
        if (root->left == NULL) {
            Node *temp = root->right;
            free(root);
            return temp;
        } else if (root->right == NULL) {
            Node *temp = root->left;
            free(root);
            return temp;
        }
       
        Node *succ = find_min(root->right);
        root->key = succ->key; 
        bool dummy = false;
        root->right = remove_node(root->right, succ->key, &dummy);
        return root;
    }
}

Node* find_min(Node *root) {
    while (root && root->left != NULL)
        root = root->left;
    return root;
}

void update_heights(Node *node, int current_height) {
    if (node) {
        node->height = current_height;
        update_heights(node->left, current_height + 1);
        update_heights(node->right, current_height + 1);
    }
}

void in_order_print_q3(Node *node, FILE *output) {
    if (node == NULL)
        return;
    in_order_print_q3(node->left, output);
    fprintf(output, "%d (%d) ", node->key, node->height);
    in_order_print_q3(node->right, output);
}

void free_tree(Node *root) {
    if (root) {
        free_tree(root->left);
        free_tree(root->right);
        free(root);
    }
}
