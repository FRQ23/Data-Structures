#include <stdio.h>
#include <stdlib.h>

// Estructura para representar un nodo en el árbol de búsqueda
typedef struct Node {
    int path_cost;     // Costo acumulado hasta este nodo
    int cost;          // Cota inferior del costo total
    int workerID;      // ID del empleado actual
    int taskID;        // ID de la tarea actual
    int* assigned;     // Tareas asignadas hasta ahora
    struct Node* parent; // Nodo padre en el árbol
} Node;

// Función para crear un nuevo nodo
Node* newNode(int* x_assigned, int path_cost, int cost, int workerID, int taskID, Node* parent, int N) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->assigned = (int*)malloc(N * sizeof(int));
    for (int i = 0; i < N; i++)
        node->assigned[i] = x_assigned[i];
    if (taskID != -1)
        node->assigned[taskID] = 1; // Asignar la tarea al empleado
    node->path_cost = path_cost;
    node->cost = cost;
    node->workerID = workerID;
    node->taskID = taskID;
    node->parent = parent;
    return node;
}

// Función para calcular la cota inferior
int calculateCost(int** costMatrix, int* x_assigned, int workerID, int N, int max_cost) {
    int cost = 0;
    int* available = (int*)malloc(N * sizeof(int));
    for (int i = 0; i < N; i++)
        available[i] = 1 - x_assigned[i];

    // Para los trabajadores restantes, sumamos el mínimo costo de las tareas disponibles
    for (int i = workerID + 1; i < N; i++) {
        int min = max_cost;
        for (int j = 0; j < N; j++) {
            if (available[j] && costMatrix[i][j] < min)
                min = costMatrix[i][j];
        }
        cost += min;
    }

    free(available);
    return cost;
}

// Cola de prioridad simple
typedef struct {
    Node* nodes[1000];
    int size;
} PriorityQueue;

void push(PriorityQueue* pq, Node* node) {
    pq->nodes[pq->size++] = node;
    // Reordenamos para mantener la prioridad (nodo con menor costo al final)
    for (int i = pq->size - 1; i > 0 && pq->nodes[i]->cost < pq->nodes[i - 1]->cost; i--) {
        Node* temp = pq->nodes[i];
        pq->nodes[i] = pq->nodes[i - 1];
        pq->nodes[i - 1] = temp;
    }
}

Node* pop(PriorityQueue* pq) {
    return pq->nodes[--pq->size];
}

int isEmpty(PriorityQueue* pq) {
    return pq->size == 0;
}

// Función para imprimir la matriz de costos
void printCostMatrix(int** costMatrix, int N) {
    printf("Matriz de costos:\n");
    printf("      ");
    for (int j = 0; j < N; j++)
        printf("T%d\t", j + 1);
    printf("\n");
    for (int i = 0; i < N; i++) {
        printf("E%d\t", i + 1);
        for (int j = 0; j < N; j++) {
            printf("%d\t", costMatrix[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

// Función principal para resolver el problema
void solve(int** costMatrix, int N, int max_cost) {
    // Imprimir la matriz de costos
    printCostMatrix(costMatrix, N);

    // Inicializar variables
    PriorityQueue pq;
    pq.size = 0;
    int* x_assigned = (int*)calloc(N, sizeof(int));
    Node* root = newNode(x_assigned, 0, 0, -1, -1, NULL, N);
    root->cost = calculateCost(costMatrix, root->assigned, -1, N, max_cost);
    push(&pq, root);

    int minCost = max_cost;
    Node* minNode = NULL;

    // Branch and Bound
    while (!isEmpty(&pq)) {
        Node* min = pop(&pq);

        // Si hemos asignado todas las tareas
        if (min->workerID == N - 1) {
            if (min->cost < minCost) {
                minCost = min->cost;
                minNode = min;
            } else {
                free(min->assigned);
                free(min); // Podar el nodo si no es la solución óptima
            }
            continue;
        }

        int workerID = min->workerID + 1;

        // Generar nodos hijos
        for (int j = 0; j < N; j++) {
            if (!min->assigned[j]) {
                Node* child = newNode(min->assigned, min->path_cost + costMatrix[workerID][j],
                                      min->cost, workerID, j, min, N);

                // Calcular la cota inferior
                child->cost = child->path_cost + calculateCost(costMatrix, child->assigned, child->workerID, N, max_cost);

                // Si la cota es menor que el costo mínimo actual, añadimos el nodo a la cola
                if (child->cost < minCost) {
                    push(&pq, child);
                } else {
                    free(child->assigned);
                    free(child); // Podamos el nodo
                }
            }
        }
    }

    // Imprimir la solución óptima
    if (minNode == NULL) {
        printf("Error: No se encontró una solución válida.\n");
        free(x_assigned);
        return;
    }

    printf("El costo mínimo es %d\n", minCost);

    // Reconstruir la asignación desde minNode
    int* result = (int*)malloc(N * sizeof(int));
    for (int i = 0; i < N; i++)
        result[i] = -1; // Inicializar el arreglo de resultados

    Node* temp = minNode;
    while (temp != NULL && temp->workerID != -1) {
        result[temp->workerID] = temp->taskID;
        temp = temp->parent;
    }

    // Imprimir las asignaciones
    for (int i = 0; i < N; i++) {
        if (result[i] != -1) {
            printf("Empleado %d asignado a la tarea %d\n", i + 1, result[i] + 1);
        } else {
            printf("Error: No se pudo asignar una tarea al empleado %d.\n", i + 1);
        }
    }

    // Liberar memoria de los nodos restantes
    while (!isEmpty(&pq)) {
        Node* node = pop(&pq);
        free(node->assigned);
        free(node);
    }
    free(minNode->assigned);
    free(minNode);
    free(x_assigned);
    free(result);
}

// Función principal
int main() {
    int N = 4; // Número de empleados y tareas
    int max_cost = 999; // Costo máximo permitido
    int** costMatrix = (int**)malloc(N * sizeof(int*));
    for (int i = 0; i < N; i++) {
        costMatrix[i] = (int*)malloc(N * sizeof(int));
    }

    // Inicializar la matriz de costos
    int initialMatrix[4][4] = {
        {9, 2, 7, 8},
        {6, 4, 3, 7},
        {5, 8, 1, 8},
        {7, 6, 9, 4}
    };

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            costMatrix[i][j] = initialMatrix[i][j];
        }
    }

    solve(costMatrix, N, max_cost);

    // Liberar la memoria de la matriz de costos
    for (int i = 0; i < N; i++) {
        free(costMatrix[i]);
    }
    free(costMatrix);

    return 0;
}
