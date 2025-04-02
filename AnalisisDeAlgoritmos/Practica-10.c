//
// Created by Fernando Rosales on 4/1/25.
//

#include <stdio.h>
#include <stdlib.h>


#define INT_MAX 9999999


// Estructura para representar un nodo en el árbol de búsqueda
typedef struct Node {
    int level;
    int cost;
    int* path;
    int* visited;
    struct Node* parent;
} Node;

// Cola de prioridad
typedef struct {
    Node* nodes[1000];
    int size;
} PriorityQueue;


//Prototipos de funciones

Node* newNode(int level, int cost, const int* parentPath, const int* parentVisited, Node* parent, int N);
void freeNode(Node* node);
void push(PriorityQueue* pq, Node* node);
Node* pop(PriorityQueue* pq);
int isEmpty(PriorityQueue* pq);
int isSymmetric(int** dist, int N);
void solveTSP(int** dist, int N);



// Función para crear un nuevo nodo
Node* newNode(int level, int cost, const int* parentPath, const int* parentVisited, Node* parent, int N) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->level = level;
    node->cost = cost;
    node->path = (int*)malloc(N * sizeof(int));
    node->visited = (int*)malloc(N * sizeof(int));

    if (parentPath && parentVisited) {
        for (int i = 0; i < N; i++) {
            node->path[i] = parentPath[i];
            node->visited[i] = parentVisited[i];
        }
    }
    node->parent = parent;
    return node;
}

// Función para liberar un nodo
void freeNode(Node* node) {
    if (node) {
        free(node->path);
        free(node->visited);
        free(node);
    }
}



void push(PriorityQueue* pq, Node* node) {
    pq->nodes[pq->size++] = node;
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

// Verifica si la matriz es simétrica
int isSymmetric(int** dist, int N) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (dist[i][j] != dist[j][i]) return 0;
        }
    }
    return 1;
}

// Resolver el problema del viajante usando Branch and Bound
void solveTSP(int** dist, int N) {
    if (!isSymmetric(dist, N)) {
        printf("Error: La matriz de distancias no es simétrica.\n");
        return;
    }

    PriorityQueue pq = { .size = 0 };
    int* path = (int*)malloc(N * sizeof(int));
    int* visited = (int*)calloc(N, sizeof(int));
    path[0] = 0;
    visited[0] = 1;

    Node* root = newNode(1, 0, path, visited, NULL, N);
    push(&pq, root);

    int minCost = INT_MAX;
    Node* bestNode = NULL;

    while (!isEmpty(&pq)) {
        Node* min = pop(&pq);

        if (min->level == N) {
            int totalCost = min->cost + dist[min->path[N - 1]][0];
            if (totalCost < minCost) {
                minCost = totalCost;
                if (bestNode) freeNode(bestNode);
                bestNode = min;
            } else {
                freeNode(min);
            }
            continue;
        }

        int lastCity = min->path[min->level - 1];
        for (int i = 0; i < N; i++) {
            if (!min->visited[i]) {
                Node* child = newNode(min->level + 1, min->cost + dist[lastCity][i], min->path, min->visited, min, N);
                child->path[min->level] = i;
                child->visited[i] = 1;
                push(&pq, child);
            }
        }
        freeNode(min);
    }

    // Imprimir la mejor ruta encontrada
    if (bestNode) {
        printf("Ruta optima: ");
        for (int i = 0; i < N; i++) {
            printf("%d -> ", bestNode->path[i]);
        }
        printf("0\n");
        printf("Distancia minima: %d\n", minCost);
        freeNode(bestNode);
    }

    free(path);
    free(visited);
}

int main() {
    int N;
    printf("Ingrese el numero de ciudades: ");
    scanf("%d", &N);

    int** dist = (int**)malloc(N * sizeof(int*));
    for (int i = 0; i < N; i++) {
        dist[i] = (int*)malloc(N * sizeof(int));
    }

    printf("Ingrese la matriz de distancias:\n");
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            scanf("%d", &dist[i][j]);
        }
    }

    solveTSP(dist, N);

    for (int i = 0; i < N; i++) {
        free(dist[i]);
    }
    free(dist);

    return 0;
}
