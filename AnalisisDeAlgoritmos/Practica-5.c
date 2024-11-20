//
// Created by Fernando Rosales on 9/30/24.
//


#include <stdio.h>


void imprimirGrafo(int grafo[5][5]) {
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            printf("%d ", grafo[i][j]);
        }
        printf("\n");
    }
}

int main() {
    // Crear un grafo no dirigido con 5 nodos
    int grafo[5][5] = {
        {0, 1, 0, 0, 1},
        {1, 0, 1, 1, 1},
        {0, 1, 0, 1, 0},
        {0, 1, 1, 0, 1},
        {1, 1, 0, 1, 0}
    };

    // Imprimir la matriz de adyacencia del grafo
    imprimirGrafo(grafo);

    return 0;
}



