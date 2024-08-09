#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int value;
    struct Node* left;
    struct Node* right;
} Node;

Node* newNode(int value) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->value = value;
    node->left = NULL;
    node->right = NULL;
    return node;
}

void insert(Node** root, int value) {
    if (*root == NULL) {
        *root = newNode(value);
        return;
    }

    if (value < (*root)->value) {
        insert(&((*root)->left), value);
    } else {
        insert(&((*root)->right), value);
    }
}

void printInorder(Node* node) {
    if (node == NULL) {
        return;
    }
    printInorder(node->left);
    printf("%d ", node->value);
    printInorder(node->right);
}

int main() {
    Node* root = NULL;
    insert(&root, 5);
    insert(&root, 3);
    insert(&root, 7);
    insert(&root, 5);
    insert(&root, 7);
    printf("Inorder traversal of the binary tree: ");
    printInorder(root);
    return 0;
}

