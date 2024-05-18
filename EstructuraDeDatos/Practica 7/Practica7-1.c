//
// Created by Fernando Rosales on 4/29/24.
//


#include <stdio.h>
#include <stdlib.h>
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
    Stack values, ops;
    values.top = ops.top = -1;

    for (int i = 0; expr[i] != '\0'; i++) {
        if (isspace(expr[i])) continue;

        if (isalpha(expr[i])) {
            push(&values, vars[expr[i] - 'a']);
        } else if (isdigit(expr[i])) {
            double val = 0;
            while (i < strlen(expr) && isdigit(expr[i])) {
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
    char expr[MAX_EXPR_LEN];
    double vars[NUM_VARIABLES] = {0};
    char var;
    double value;

    printf("Introduce la expresión: ");
    fgets(expr, MAX_EXPR_LEN, stdin);
    expr[strcspn(expr, "\n")] = 0; // Eliminar el salto de línea

    // Pedir al usuario los valores de las variables
    printf("Introduce las variables y sus valores (ejemplo: a=3). Escribe 'fin' para terminar:\n");
    while (1) {
        scanf(" %c", &var);
        if (var == 'f') break; // 'fin'
        scanf("=%lf", &value);
        vars[var - 'a'] = value;
    }

    double result = evaluateExpression(expr, vars);
    printf("El resultado de la expresión es: %f\n", result);

    return 0;
}

// Ejemplo de entrada:
// Introduce la expresión: (a+2)*b
// Introduce las variables y sus valores (ejemplo: a=3). Escribe 'fin' para terminar:
// a=3
// b=4
// fin
// El resultado de la expresión es: 20.000000
