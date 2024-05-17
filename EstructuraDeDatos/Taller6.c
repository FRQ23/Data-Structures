//
// Created by Fernando Rosales on 4/16/24.
//

#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* left;
    struct Node* right;
} Node;

void preOrder(Node* root) {
    if (root == NULL) {
        return;
    }
    printf("%d ", root->data);
    preOrder(root->left);
    preOrder(root->right);
}

void inOrder(Node* root) {
    if (root == NULL) {
        return;
    }
    inOrder(root->left);
    printf("%d ", root->data);
    inOrder(root->right);
}

void postOrder(Node* root) {
    if (root == NULL) {
        return;
    }
    postOrder(root->left);
    postOrder(root->right);
    printf("%d ", root->data);
}

void mirror(Node* node) {
    if (node == NULL) {
        return;
    }
    else {
        struct Node* temp;
        mirror(node->left);
        mirror(node->right);
        temp = node->left;
        node->left = node->right;
        node->right = temp;
    }
}

Node* minValueNode(Node* node) {
    Node* current = node;
    while (current && current->left != NULL)
        current = current->left;
    return current;
}

Node* deleteNode(Node* root, int data) {
    if (root == NULL) return root;
    if (data < root->data)
        root->left = deleteNode(root->left, data);
    else if (data > root->data)
        root->right = deleteNode(root->right, data);
    else {
        if (root->left == NULL) {
            Node* temp = root->right;
            free(root);
            return temp;
        }
        else if (root->right == NULL) {
            Node* temp = root->left;
            free(root);
            return temp;
        }
        Node* temp = minValueNode(root->right);
        root->data = temp->data;
        root->right = deleteNode(root->right, temp->data);
    }
    return root;
}

int main() {
    Node* root = NULL; // Raíz del árbol
    int choice, value;

    while(1) {
        printf("\n1. Preorden\n");
        printf("2. Enorden\n");
        printf("3. Postorden\n");
        printf("4. Espejo\n");
        printf("5. Eliminar nodo\n");
        printf("6. Salir\n");
        printf("Ingrese su elección: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1:
                preOrder(root);
                break;
            case 2:
                inOrder(root);
                break;
            case 3:
                postOrder(root);
                break;
            case 4:
                mirror(root);
                break;
            case 5:
                printf("Ingrese el valor del nodo a eliminar: ");
                scanf("%d", &value);
                root = deleteNode(root, value);
                break;
            case 6:
                exit(0);
            default:
                printf("Opción inválida\n");
        }
    }

    return 0;
}