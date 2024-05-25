#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <math.h>
#include <errno.h>

typedef struct Node {
    char operator;
    double value;
    struct Node *left;
    struct Node *right;
} Node;

typedef struct VarNode {
    char var;
    struct VarNode *next;
} VarNode;

Node* createNode(char operator, double value) {
    Node *newNode = (Node*)malloc(sizeof(Node));
    newNode->operator = operator;
    newNode->value = value;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

void pushVar(VarNode** top, char var) {
    VarNode* newNode = (VarNode*)malloc(sizeof(VarNode));
    newNode->var = var;
    newNode->next = *top;
    *top = newNode;
}

int isInVarStack(VarNode* top, char var) {
    while (top != NULL) {
        if (top->var == var) return 1;
        top = top->next;
    }
    return 0;
}

void freeVarStack(VarNode* top) {
    VarNode* temp;
    while (top != NULL) {
        temp = top;
        top = top->next;
        free(temp);
    }
}

typedef struct StackNode {
    Node* treeNode;
    struct StackNode *next;
} StackNode;

void push(StackNode** top, Node* treeNode) {
    StackNode* newNode = (StackNode*)malloc(sizeof(StackNode));
    newNode->treeNode = treeNode;
    newNode->next = *top;
    *top = newNode;
}

Node* pop(StackNode** top) {
    if (*top == NULL) return NULL;
    StackNode* temp = *top;
    Node* treeNode = temp->treeNode;
    *top = (*top)->next;
    free(temp);
    return treeNode;
}

int isOperator(char c) {
    return (c == '+' || c == '-' || c == '*' || c == '/' || c == '^');
}

Node* constructExpressionTree(char* postfix, VarNode** varStack) {
    StackNode* stack = NULL;
    for (int i = 0; postfix[i] != '\0'; i++) {
        if (postfix[i] == ' ') continue;
        if (isOperator(postfix[i])) {
            Node* operatorNode = createNode(postfix[i], 0);
            operatorNode->right = pop(&stack);
            operatorNode->left = pop(&stack);
            push(&stack, operatorNode);
        } else if (isalnum(postfix[i])) {
            if (!isInVarStack(*varStack, postfix[i])) {
                pushVar(varStack, postfix[i]);
            }
            push(&stack, createNode(postfix[i], 0));
        }
    }
    return pop(&stack);
}

void infixToPostfix(char* infix, char* postfix) {
    int i, j = 0;
    StackNode* stack = NULL;
    for (i = 0; infix[i] != '\0'; i++) {
        if (infix[i] == ' ') continue;
        if (isalnum(infix[i])) {
            while (isalnum(infix[i])) {
                postfix[j++] = infix[i++];
            }
            postfix[j++] = ' ';
            i--;
        } else if (infix[i] == '(') {
            push(&stack, createNode(infix[i], 0));
        } else if (infix[i] == ')') {
            while (stack != NULL && stack->treeNode->operator != '(') {
                postfix[j++] = pop(&stack)->operator;
                postfix[j++] = ' ';
            }
            pop(&stack);
        } else if (isOperator(infix[i])) {
            while (stack != NULL && stack->treeNode->operator != '(' &&
                   ((infix[i] == '+' || infix[i] == '-') ||
                    (infix[i] == '*' || infix[i] == '/') ||
                    (infix[i] == '^' && stack->treeNode->operator != '^'))) {
                postfix[j++] = pop(&stack)->operator;
                postfix[j++] = ' ';
            }
            push(&stack, createNode(infix[i], 0));
        }
    }
    while (stack != NULL) {
        postfix[j++] = pop(&stack)->operator;
        postfix[j++] = ' ';
    }
    postfix[j] = '\0';
}

typedef struct EvalStackNode {
    double value;
    struct EvalStackNode *next;
} EvalStackNode;

void pushEval(EvalStackNode** top, double value) {
    EvalStackNode* newNode = (EvalStackNode*)malloc(sizeof(EvalStackNode));
    newNode->value = value;
    newNode->next = *top;
    *top = newNode;
}

double popEval(EvalStackNode** top) {
    if (*top == NULL) return 0;
    EvalStackNode* temp = *top;
    double value = temp->value;
    *top = (*top)->next;
    free(temp);
    return value;
}

double evaluateExpressionTree(Node* root, double x, double y, double a, double b, double c, double d) {
    if (!root) return 0;

    StackNode* stack = NULL;
    EvalStackNode* evalStack = NULL;
    Node* current = root;

    while (current != NULL || stack != NULL) {
        while (current != NULL) {
            push(&stack, current);
            current = current->left;
        }

        current = pop(&stack);

        if (current->right != NULL) {
            push(&stack, current);
            current = current->right;
            continue;
        }

        double rightValue = (evalStack != NULL) ? popEval(&evalStack) : 0;
        double leftValue = (evalStack != NULL) ? popEval(&evalStack) : 0;

        switch (current->operator) {
            case 'x': pushEval(&evalStack, x); break;
            case 'y': pushEval(&evalStack, y); break;
            case 'a': pushEval(&evalStack, a); break;
            case 'b': pushEval(&evalStack, b); break;
            case 'c': pushEval(&evalStack, c); break;
            case 'd': pushEval(&evalStack, d); break;
            case '+': pushEval(&evalStack, leftValue + rightValue); break;
            case '-': pushEval(&evalStack, leftValue - rightValue); break;
            case '*': pushEval(&evalStack, leftValue * rightValue); break;
            case '/': pushEval(&evalStack, leftValue / rightValue); break;
            case '^': pushEval(&evalStack, pow(leftValue, rightValue)); break;
            default: pushEval(&evalStack, current->value); break;
        }

        current = NULL;
    }
    return popEval(&evalStack);
}

void freeExpressionTree(Node* root) {
    StackNode* stack = NULL;
    Node* current = root;

    while (current != NULL || stack != NULL) {
        while (current != NULL) {
            if (current->right != NULL) {
                push(&stack, current->right);
            }
            push(&stack, current);
            current = current->left;
        }

        current = pop(&stack);

        if (stack != NULL && current->right != NULL && stack->treeNode == current->right) {
            pop(&stack);
            push(&stack, current);
            current = current->right;
        } else {
            free(current);
            current = NULL;
        }
    }
}

int main() {
    char infix[100];
    char postfix[100];
    int option;
    Node *expressionTree = NULL;
    VarNode *varStack = NULL;

    do {
        printf("Menu:\n");
        printf("[0] Ingresar expresion\n");
        printf("[1] Capturar valores y evaluar\n");
        printf("[2] Salir\n");
        printf("Selecciona una opcion: ");

        char input[10];
        if (fgets(input, sizeof(input), stdin)) {
            char *endptr;
            errno = 0;
            option = strtol(input, &endptr, 10);
            if (errno != 0 || endptr == input || *endptr != '\n') {
                printf("Opcion no valida. Intenta de nuevo.\n");
                continue;
            }
        } else {
            printf("Opcion no valida. Intenta de nuevo.\n");
            continue;
        }

        switch(option) {
            case 0:
                printf("Ingresa la expresion: ");
                fgets(infix, sizeof(infix), stdin);
                infix[strcspn(infix, "\n")] = '\0';  // Remove newline character
                infixToPostfix(infix, postfix);
                expressionTree = constructExpressionTree(postfix, &varStack);
                printf("Arbol de expresion creado.\n");
                break;
            case 1:
                if (expressionTree) {
                    VarNode* temp = varStack;
                    double x = 0, y = 0, a = 0, b = 0, c = 0, d = 0;
                    while (temp != NULL) {
                        printf("Ingresa el valor de %c: ", temp->var);
                        if (fgets(input, sizeof(input), stdin)) {
                            char *endptr;
                            errno = 0;
                            double value = strtod(input, &endptr);
                            if (errno != 0 || endptr == input || *endptr != '\n') {
                                printf("Entrada no valida. Intenta de nuevo.\n");
                                continue;
                            }
                            if (temp->var == 'x') x = value;
                            else if (temp->var == 'y') y = value;
                            else if (temp->var == 'a') a = value;
                            else if (temp->var == 'b') b = value;
                            else if (temp->var == 'c') c = value;
                            else if (temp->var == 'd') d = value;
                        }
                        temp = temp->next;
                    }
                    double result = evaluateExpressionTree(expressionTree, x, y, a, b, c, d);
                    printf("Resultado: %.2f\n", result);
                } else {
                    printf("Por favor, ingresa una expresion valida primero.\n");
                }
                break;
            case 2:
                freeExpressionTree(expressionTree);
                freeVarStack(varStack);
                printf("Memoria liberada. Saliendo del programa.\n");
                break;
            default:
                printf("Opcion no valida. Intenta de nuevo.\n");
        }
    } while (option != 2);

    return 0;
}
