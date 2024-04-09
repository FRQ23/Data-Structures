//
// Created by Fertronic on 4/8/2024.
//

#include "stdio.h"
#include "stdlib.h"

typedef struct Node {
    int data;
    struct Node* left;
    struct Node* right;
} Node;

Node* insert_node(Node* root, int data) {
    if (root == NULL) {
        root = (Node*)malloc(sizeof(Node));
        root->data = data;
        root->left = root->right = NULL;
    } else if (data <= root->data) {
        root->left = insert_node(root->left, data);
    } else {
        root->right = insert_node(root->right, data);
    }
    return root;
}

int calculate_level(Node* root, int data, int level) {
    if (root == NULL) {
        return -1;
    }
    if (root->data == data) {
        return level;
    }
    int left = calculate_level(root->left, data, level + 1);
    if (left != -1) {
        return left;
    }
    return calculate_level(root->right, data, level + 1);
}

int num_elements(Node* root) {
    if (root == NULL) {
        return 0;
    } else {
        return num_elements(root->left) + num_elements(root->right) + 1;
    }
}

int calculate_depth(Node* root) {
    if (root == NULL) {
        return 0;
    } else {
        int leftDepth = calculate_depth(root->left);
        int rightDepth = calculate_depth(root->right);
        return (leftDepth > rightDepth) ? (leftDepth + 1) : (rightDepth + 1);
    }
}

void print_tree(Node* node, int level) {
    int i;
    if (node != NULL) {
        printf(" %d", node->data);
        if(node->right != NULL) {
            printf("\n");
            for (i = 0; i < level+1; i++) {
                if(i == level)
                    printf(" |____R ");
                else
                    printf(" |      ");
            }
            print_tree(node->right, level + 1);
        }
        if(node->left != NULL) {
            printf("\n");
            for (i = 0; i < level+1; i++) {
                printf(" |      ");
            }
            printf("\n");
            for (i = 0; i < level+1; i++) {
                if(i == level)
                    printf(" |____L ");
                else
                    printf(" |      ");
            }
            print_tree(node->left, level + 1);
        }
    }
}

//int main() {
//    Node* root = NULL;
//    int data;
//
//    printf("Enter integers (enter a non-integer to stop):\n");
//    while (scanf("%d", &data) == 1) {
//        root = insert_node(root, data);
//    }
//
//    printf("Tree:\n");
//    print_tree(root, 0);
//
//    printf("Nivel: %d")
//
//    return 0;
//}


//int main() {
//    Node* root = NULL;
//
//    root = insert_node(root, 10);
//    root = insert_node(root, 8);
//    root = insert_node(root, 5);
//    root = insert_node(root, 6);
//    root = insert_node(root, 9);
//    root = insert_node(root, 4);
//    root = insert_node(root, 1);
//
//    printf("Tree:\n");
//    print_tree(root, 0);
//
//    return 0;
//}

int main() {
    Node* root = NULL;
    int data;
    char input[10];

    printf("Enter integers (enter 'n' to stop):\n");
    while (scanf("%s", input) && input[0] != 'n') {
        data = atoi(input);
        root = insert_node(root, data);
    }

    printf("Tree:\n");
    print_tree(root, 0);

    int data_for_level;
    printf("\n Enter the value for which you want to calculate the level:\n");
    scanf("%d", &data_for_level);
    int level = calculate_level(root, data_for_level, 0);

    int elements = num_elements(root);
    int depth = calculate_depth(root);

    printf("Level of data %d: %d\n", data_for_level, level);
    printf("Number of elements: %d\n", elements);
    printf("Depth of tree: %d\n", depth);

    return 0;
}