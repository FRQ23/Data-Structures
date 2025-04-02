//
// Created by Fernando Rosales on 4/1/25.
//

#include <stdio.h>
#include <stdlib.h>

#define INF 9999999  // Valor grande para representar "infinito"

// Función recursiva para explorar rutas
void tsp(int current, int count, int cost, int n, int** matrix, int* visited, int* route, int* bestCost, int* bestRoute) {
    // Caso base: se han visitado todas las ciudades
    if (count == n) {
        int totalCost = cost + matrix[current][0];  // Regresar a la ciudad de origen
        if (totalCost < *bestCost) {
            *bestCost = totalCost;
            // Copiar la ruta actual a la mejor ruta encontrada
            for (int i = 0; i < n; i++) {
                bestRoute[i] = route[i];
            }
        }
        return;
    }
    // Recorrer todas las ciudades para escoger la siguiente visita
    for (int city = 0; city < n; city++) {
        if (!visited[city]) {
            visited[city] = 1;
            route[count] = city;
            tsp(city, count + 1, cost + matrix[current][city], n, matrix, visited, route, bestCost, bestRoute);
            visited[city] = 0;  // Retroceder (backtracking)
        }
    }
}

int main() {
    int n;
    printf("Ingrese el número de ciudades: ");
    scanf("%d", &n);

    // Reservar memoria dinámica para la matriz de distancias
    int** matrix = (int**)malloc(n * sizeof(int*));
    for (int i = 0; i < n; i++) {
        matrix[i] = (int*)malloc(n * sizeof(int));
    }

    // Leer la matriz de distancias
    printf("Ingrese la matriz de distancias:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &matrix[i][j]);
        }
    }

    // Validar que la matriz sea simétrica
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (matrix[i][j] != matrix[j][i]) {
                printf("Error: La matriz no es simétrica.\n");
                for (int k = 0; k < n; k++) {
                    free(matrix[k]);
                }
                free(matrix);
                return 1;
            }
        }
    }

    // Reservar memoria para los arreglos de control
    int* visited = (int*)calloc(n, sizeof(int));
    int* route = (int*)malloc(n * sizeof(int));
    int* bestRoute = (int*)malloc(n * sizeof(int));
    int bestCost = INF;

    // Inicializar la ruta: se parte de la ciudad 0
    visited[0] = 1;
    route[0] = 0;

    // Ejecutar el algoritmo TSP
    tsp(0, 1, 0, n, matrix, visited, route, &bestCost, bestRoute);

    // Mostrar la solución óptima
    if (bestCost == INF) {
        printf("No se encontró una solución válida.\n");
    } else {
        printf("Ruta óptima: ");
        for (int i = 0; i < n; i++) {
            printf("%d -> ", bestRoute[i]);
        }
        printf("0\n");  // Regresar a la ciudad de origen
        printf("Distancia mínima: %d\n", bestCost);
    }

    // Liberar la memoria asignada
    for (int i = 0; i < n; i++) {
        free(matrix[i]);
    }
    free(matrix);
    free(visited);
    free(route);
    free(bestRoute);

    return 0;
}