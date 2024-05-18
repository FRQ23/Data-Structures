#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

// Definición de la estructura de nodo para el árbol de expresión
typedef struct node {
    char op;
    double value;
    struct node* left;
    struct node* right;
} Node;

// Función para crear un nuevo nodo
Node* createNode(char op, double value) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->op = op;
    newNode->value = value;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// Función para verificar si un carácter es un operador
int isOperator(char c) {
    return (c == '+' || c == '-' || c == '*' || c == '/' || c == '^');
}

// Función para obtener la precedencia de un operador
int getPrecedence(char op) {
    switch (op) {
        case '+':
        case '-':
            return 1;
        case '*':
        case '/':
            return 2;
        case '^':
            return 3;
        default:
            return 0;
    }
}

// Función para validar la expresión matemática
int isValidExpression(const char* expression) {
    int i, length = strlen(expression);
    int parenthesesCount = 0;

    for (i = 0; i < length; i++) {
        char c = expression[i];

        if (c == '(') {
            parenthesesCount++;
        } else if (c == ')') {
            if (parenthesesCount == 0)
                return 0;
            parenthesesCount--;
        } else if (isalpha(c) || isOperator(c)) {
            continue;
        } else {
            return 0;
        }
    }

    return (parenthesesCount == 0);
}

// Función para construir el árbol de expresión a partir de la expresión válida
Node* buildExpressionTree(const char* expression) {
    Node* stack[100];
    int top = -1;
    int i, length = strlen(expression);

    for (i = 0; i < length; i++) {
        char c = expression[i];

        if (isalpha(c)) {
            stack[++top] = createNode(c, 0.0);
        } else if (c == '(') {
            // Ignorar los paréntesis de apertura
        } else if (c == ')') {
            // Construir el subárbol cuando se encuentra un paréntesis de cierre
            Node* right = stack[top--];
            Node* operator = stack[top--];
            Node* left = stack[top--];

            operator->left = left;
            operator->right = right;

            stack[++top] = operator;
        } else if (isOperator(c)) {
            while (top >= 0 && getPrecedence(stack[top]->op) >= getPrecedence(c)) {
                Node* right = stack[top--];
                Node* operator = stack[top--];
                Node* left = stack[top--];

                operator->left = left;
                operator->right = right;

                stack[++top] = operator;
            }

            stack[++top] = createNode(c, 0.0);
        }
    }

    while (top > 0) {
        Node* right = stack[top--];
        Node* operator = stack[top--];
        Node* left = stack[top--];

        operator->left = left;
        operator->right = right;

        stack[++top] = operator;
    }

    return stack[top];
}

// Función para solicitar los valores de las variables en postorden
void getVariableValues(Node* root) {
    if (root == NULL)
        return;

    getVariableValues(root->left);
    getVariableValues(root->right);

    if (isalpha(root->op)) {
        printf("Ingrese el valor de la variable '%c': ", root->op);
        scanf("%lf", &(root->value));
    }
}

// Función para evaluar el árbol de expresión
double evaluateExpressionTree(Node* root) {
    if (root == NULL)
        return 0;

    if (isalpha(root->op))
        return root->value;

    double leftValue = evaluateExpressionTree(root->left);
    double rightValue = evaluateExpressionTree(root->right);

    switch (root->op) {
        case '+':
            return leftValue + rightValue;
        case '-':
            return leftValue - rightValue;
        case '*':
            return leftValue * rightValue;
        case '/':
            return leftValue / rightValue;
        case '^':
            return pow(leftValue, rightValue);
    }

    return 0;
}

// Función para liberar la memoria utilizada por el árbol de expresión
void freeExpressionTree(Node* root) {
    if (root == NULL)
        return;

    freeExpressionTree(root->left);
    freeExpressionTree(root->right);
    free(root);
}

int main() {
    int option;
    char expression[100];
    Node* root = NULL;

    do {
        printf("Menú:\n");
        printf("[0] Ingresar expresión matemática\n");
        printf("[1] Ingresar valores de variables y evaluar expresión\n");
        printf("[2] Salir\n");
        printf("Ingrese una opción: ");
        scanf("%d", &option);

        switch (option) {
            case 0:
                printf("Ingrese la expresión matemática: ");
                scanf("%s", expression);

                if (isValidExpression(expression)) {
                    root = buildExpressionTree(expression);
                    printf("Árbol de expresión creado correctamente.\n");
                } else {
                    printf("La expresión ingresada no es válida.\n");
                }
                break;
            case 1:
                if (root == NULL) {
                    printf("No se ha ingresado una expresión válida.\n");
                } else {
                    getVariableValues(root);
                    double result = evaluateExpressionTree(root);
                    printf("Resultado: %.2lf\n", result);
                }
                break;
            case 2:
                freeExpressionTree(root);
                printf("Memoria liberada. Programa terminado.\n");
                break;
            default:
                printf("Opción inválida.\n");
        }
    } while (option != 2);

    return 0;
}