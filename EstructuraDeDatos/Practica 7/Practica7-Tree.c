#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <math.h>

#define NUM_VARIABLES 26 // Número de variables posibles de 'a' a 'z'
#define MAX_EXPR_LEN 256

typedef struct ExprNode {
    char op;
    double value;
    struct ExprNode *left;
    struct ExprNode *right;
} ExprNode;

typedef struct {
    int top;
    ExprNode* items[MAX_EXPR_LEN];
} Stack;

ExprNode* createNode(char op, double value) {
    ExprNode* node = (ExprNode*)malloc(sizeof(ExprNode));
    node->op = op;
    node->value = value;
    node->left = NULL;
    node->right = NULL;
    return node;
}

void push(Stack *s, ExprNode* value) {
    s->items[++(s->top)] = value;
}

ExprNode* pop(Stack *s) {
    return s->items[(s->top)--];
}

int isEmpty(Stack *s) {
    return s->top == -1;
}

ExprNode* buildExpressionTree(char *expr, double vars[NUM_VARIABLES]);
double evaluateExpressionTree(ExprNode *root);
void freeExpressionTree(ExprNode *root);

double evaluateExpressionTree(ExprNode *root) {
    if (!root) return 0;

    if (!root->left && !root->right) {
        return root->value;
    }

    double left_val = evaluateExpressionTree(root->left);
    double right_val = evaluateExpressionTree(root->right);

    switch (root->op) {
        case '+': return left_val + right_val;
        case '-': return left_val - right_val;
        case '*': return left_val * right_val;
        case '/': return left_val / right_val;
        case '^': return pow(left_val, right_val);
        default: return 0;
    }
}

void freeExpressionTree(ExprNode *root) {
    if (!root) return;
    freeExpressionTree(root->left);
    freeExpressionTree(root->right);
    free(root);
}

int precedence(char op) {
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

ExprNode* buildExpressionTree(char *expr, double vars[NUM_VARIABLES]) {
    int i = 0;
    int len = strlen(expr);

    Stack values = { .top = -1 };
    Stack ops = { .top = -1 };

    for (i = 0; i < len; i++) {
        if (isspace(expr[i])) continue;

        if (isalpha(expr[i])) {
            push(&values, createNode('\0', vars[expr[i] - 'a']));
        } else if (isdigit(expr[i])) {
            double val = 0;
            while (i < len && isdigit(expr[i])) {
                val = (val * 10) + (expr[i] - '0');
                i++;
            }
            i--;
            push(&values, createNode('\0', val));
        } else if (expr[i] == '(') {
            push(&ops, createNode(expr[i], 0));
        } else if (expr[i] == ')') {
            while (!isEmpty(&ops) && ops.items[ops.top]->op != '(') {
                ExprNode* opNode = pop(&ops);
                opNode->right = pop(&values);
                opNode->left = pop(&values);
                push(&values, opNode);
            }
            pop(&ops); // Eliminar el '('
        } else {
            while (!isEmpty(&ops) && precedence(ops.items[ops.top]->op) >= precedence(expr[i])) {
                ExprNode* opNode = pop(&ops);
                opNode->right = pop(&values);
                opNode->left = pop(&values);
                push(&values, opNode);
            }
            push(&ops, createNode(expr[i], 0));
        }
    }

    while (!isEmpty(&ops)) {
        ExprNode* opNode = pop(&ops);
        opNode->right = pop(&values);
        opNode->left = pop(&values);
        push(&values, opNode);
    }

    return pop(&values);
}

int main() {
    char expr[MAX_EXPR_LEN] = "";
    double vars[NUM_VARIABLES] = {0};
    char var;
    double value;
    int opcion;
    int ret;

    while (1) {
        printf("\nMenu:\n");
        printf("0. Ingresar expresión\n");
        printf("1. Ingresar valores de variables\n");
        printf("2. Terminar programa\n");
        printf("Selecciona una opción: ");
        ret = scanf("%d", &opcion);
        if (ret != 1) {
            printf("Error al leer la opción. Por favor, intenta de nuevo.\n");
            while (getchar() != '\n'); // Limpiar el buffer de entrada
            continue;
        }

        switch (opcion) {
            case 0:
                printf("Introduce la expresión: ");
                getchar(); // Para consumir el newline previo
                if (fgets(expr, MAX_EXPR_LEN, stdin) == NULL) {
                    printf("Error al leer la expresión. Por favor, intenta de nuevo.\n");
                    continue;
                }
                expr[strcspn(expr, "\n")] = 0; // Eliminar el salto de línea
                break;
            case 1:
                if (strlen(expr) == 0) {
                    printf("Primero ingrese una expresión (opción 0).\n");
                    break;
                }
                printf("Introduce las variables y sus valores (ejemplo: a=3). Escribe 'fin' para terminar:\n");
                while (1) {
                    char input[10];
                    printf("Variable y valor (ejemplo: a=3) o 'fin' para terminar: ");
                    ret = scanf("%9s", input);
                    if (ret != 1) {
                        printf("Error al leer la entrada. Por favor, intenta de nuevo.\n");
                        while (getchar() != '\n'); // Limpiar el buffer de entrada
                        continue;
                    }
                    if (strcmp(input, "fin") == 0) break;

                    if (sscanf(input, "%c=%lf", &var, &value) == 2 && isalpha(var)) {
                        vars[var - 'a'] = value;
                    } else {
                        printf("Entrada no válida. Por favor, introduce una variable y un valor válido.\n");
                    }
                }
                ExprNode* root = buildExpressionTree(expr, vars);
                double result = evaluateExpressionTree(root);
                printf("El resultado de la expresión es: %f\n", result);
                freeExpressionTree(root);
                break;
            case 2:
                printf("Terminando programa.\n");
                return 0;
            default:
                printf("Opción no válida. Por favor, intenta de nuevo.\n");
        }
    }

    return 0;
}
