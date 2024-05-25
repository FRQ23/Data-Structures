//
// Created by Fernando Rosales on 4/29/24.
//

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#define MAX_EXPR_LEN 256
#define NUM_VARIABLES 26 // Número de variables posibles de 'a' a 'z'

// Estructura para representar una pila
typedef struct {
    int top;
    double items[MAX_EXPR_LEN];
} Stack;

// Prototipo de funciones
double evaluateExpression(char *expr, double vars[NUM_VARIABLES]);
void push(Stack *s, double value);
double pop(Stack *s);
int isEmpty(Stack *s);
int precedence(char op);
double operate(double a, double b, char op);

// Funciones para manejar la pila
void push(Stack *s, double value) {
    s->items[++(s->top)] = value;
}

double pop(Stack *s) {
    return s->items[(s->top)--];
}

int isEmpty(Stack *s) {
    return s->top == -1;
}

// Función para determinar la precedencia de los operadores
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

// Función para evaluar una operación
double operate(double a, double b, char op) {
    switch (op) {
        case '+': return a + b;
        case '-': return a - b;
        case '*': return a * b;
        case '/': return a / b;
        case '^': return pow(a, b);
        default: return 0;
    }
}

// Función para evaluar la expresión
double evaluateExpression(char *expr, double vars[NUM_VARIABLES]) {
    Stack values = { .top = -1 };  // Inicializar la pila
    Stack ops = { .top = -1 };     // Inicializar la pila

    for (int i = 0; expr[i] != '\0'; i++) {
        if (isspace(expr[i])) continue;

        if (isalpha(expr[i])) {
            push(&values, vars[expr[i] - 'a']);
        } else if (isdigit(expr[i])) {
            double val = 0;
            while (i < (int)strlen(expr) && isdigit(expr[i])) {
                val = (val * 10) + (expr[i] - '0');
                i++;
            }
            i--;
            push(&values, val);
        } else if (expr[i] == '(') {
            push(&ops, expr[i]);
        } else if (expr[i] == ')') {
            while (!isEmpty(&ops) && ops.items[ops.top] != '(') {
                double val2 = pop(&values);
                double val1 = pop(&values);
                char op = pop(&ops);
                push(&values, operate(val1, val2, op));
            }
            pop(&ops); // Eliminar el '('
        } else {
            while (!isEmpty(&ops) && precedence(ops.items[ops.top]) >= precedence(expr[i])) {
                double val2 = pop(&values);
                double val1 = pop(&values);
                char op = pop(&ops);
                push(&values, operate(val1, val2, op));
            }
            push(&ops, expr[i]);
        }
    }

    while (!isEmpty(&ops)) {
        double val2 = pop(&values);
        double val1 = pop(&values);
        char op = pop(&ops);
        push(&values, operate(val1, val2, op));
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
                double result = evaluateExpression(expr, vars);
                printf("El resultado de la expresión es: %f\n", result);
                break;
            case 2:
                printf("Terminando programa.\n");
                return 0;
            default:
                printf("Opción no válida. Por favor, intenta de nuevo.\n");
        }
    }

    //return 0;
}
