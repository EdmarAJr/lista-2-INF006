/**
* Considere as seguintes entrada e sáida abaixo:

*                       L2Q3.in

*    a 3 r 3 a 5 a 7 a 8 a 1 a 4 a 6 a 1 r 9 a 0 r 7
*    a 1 a 2 r 0 r 1

*                       L2Q3.out

*    0 (2 ) 1 (1 ) 1 (3 ) 4 (2 ) 5 (0 ) 6 (2 ) 8 (1 ) 9 (2 )
*    0 (1 ) 2 (0 )

* Cada linha representa as operações de adição e remoção em uma árvore vazia, onde a representa uma adição e r representa uma remoção (a menos que o nó a ser removido não exista, o que o transforma em uma adição!).

* Na sáida, cada nó aparece em ordem seguido de sua altura na árvore entre parêntesis.
 */

 #include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    int key;
    struct Node *left;
    struct Node *right;
    int height;
} Node;

Node *insert(Node **root, int key) {
    if (*root == NULL) {
        Node *new_node = (Node *)malloc(sizeof(Node));
        new_node->key = key;
        new_node->left = NULL;
        new_node->right = NULL;
        new_node->height = 0;
        *root = new_node;
        return new_node;
    }

    if (key < (*root)->key) {
        return insert(&(*root)->left, key);
    } else {
        return insert(&(*root)->right, key);
    }
}

Node *find(Node *root, int key) {
    while (root != NULL) {
        if (key < root->key) {
            root = root->left;
        } else if (key > root->key) {
            root = root->right;
        } else {
            return root;
        }
    }
    return NULL;
}

Node *min_value_node(Node *node) {
    while (node->left != NULL)
        node = node->left;
    return node;
}

Node *delete(Node **root, int key) {
    if (*root == NULL) return *root;

    if (key < (*root)->key) {
        (*root)->left = delete(&(*root)->left, key);
    } else if (key > (*root)->key) {
        (*root)->right = delete(&(*root)->right, key);
    } else {
        if ((*root)->left == NULL) {
            Node *temp = (*root)->right;
            free(*root);
            return temp;
        } else if ((*root)->right == NULL) {
            Node *temp = (*root)->left;
            free(*root);
            return temp;
        }

        Node *temp = min_value_node((*root)->right);
        (*root)->key = temp->key;
        (*root)->right = delete(&(*root)->right, temp->key);
    }
    return *root;
}

void update_heights(Node *root) {
    if (root == NULL) return;
    Node *queue[1024];
    int front = 0, rear = 0;
    queue[rear++] = root;
    root->height = 0;

    while (front < rear) {
        Node *current = queue[front++];
        if (current->left != NULL) {
            current->left->height = current->height + 1;
            queue[rear++] = current->left;
        }
        if (current->right != NULL) {
            current->right->height = current->height + 1;
            queue[rear++] = current->right;
        }
    }
}

void in_order(Node *root) {
    if (root == NULL) return;
    in_order(root->left);
    printf("%d (%d) ", root->key, root->height);
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
            char op = token[0];
            token = strtok(NULL, " \n");
            if (token == NULL) break;
            int key = atoi(token);
            if (op == 'a') {
                insert(&root, key);
            } else if (op == 'r') {
                if (find(root, key) == NULL) {
                    insert(&root, key);
                } else {
                    root = delete(&root, key);
                }
            }
            update_heights(root);
            token = strtok(NULL, " \n");
        }
        in_order(root);
        printf("\n");
        free_tree(root);
    }
    return 0;
}