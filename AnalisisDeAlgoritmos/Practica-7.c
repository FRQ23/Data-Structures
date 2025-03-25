// Fernando Rosales Quiñones 1299440

#include <stdio.h>
#include <stdlib.h>

// Estructura para representar un nodo en el árbol de búsqueda
typedef struct Nodo {
    int costo_ruta;     // Costo acumulado hasta este nodo
    int costo;          // Cota inferior del costo total
    int id_empleado;    // ID del empleado actual
    int id_tarea;       // ID de la tarea actual
    int* asignadas;     // Tareas asignadas hasta ahora
    struct Nodo* padre; // Nodo padre en el árbol
} Nodo;


// Pila para DFS
typedef struct {
    Nodo* nodos[1000];
    int tamano;
} Pila;

// Función para crear un nuevo nodo
Nodo* nuevoNodo(int* tareas_asignadas, int costo_ruta, int costo, int id_empleado, int id_tarea, Nodo* padre, int N) {
    Nodo* nodo = (Nodo*)malloc(sizeof(Nodo));
    nodo->asignadas = (int*)malloc(N * sizeof(int));
    for (int i = 0; i < N; i++)
        nodo->asignadas[i] = tareas_asignadas[i];
    if (id_tarea != -1)
        nodo->asignadas[id_tarea] = 1; // Asignar la tarea al empleado
    nodo->costo_ruta = costo_ruta;
    nodo->costo = costo;
    nodo->id_empleado = id_empleado;
    nodo->id_tarea = id_tarea;
    nodo->padre = padre;
    return nodo;
}

// Función para calcular la cota inferior
int calcularCosto(int** matriz_costos, int* tareas_asignadas, int id_empleado, int N, int costo_maximo) {
    int costo = 0;
    int* disponibles = (int*)malloc(N * sizeof(int));
    for (int i = 0; i < N; i++)
        disponibles[i] = 1 - tareas_asignadas[i];

    // Para los empleados restantes, sumamos el mínimo costo de las tareas disponibles
    for (int i = id_empleado + 1; i < N; i++) {
        int minimo = costo_maximo;
        for (int j = 0; j < N; j++) {
            if (disponibles[j] && matriz_costos[i][j] < minimo)
                minimo = matriz_costos[i][j];
        }
        costo += minimo;
    }

    free(disponibles);
    return costo;
}



void apilar(Pila* pila, Nodo* nodo) {
    pila->nodos[pila->tamano++] = nodo;
}

Nodo* desapilar(Pila* pila) {
    return pila->nodos[--pila->tamano];
}

int estaVacia(Pila* pila) {
    return pila->tamano == 0;
}

// Función para imprimir la matriz de costos
void imprimirMatrizCostos(int** matriz_costos, int N) {
    printf("Matriz de costos:\n");
    printf("      ");
    for (int j = 0; j < N; j++)
        printf("T%d\t", j + 1);
    printf("\n");
    for (int i = 0; i < N; i++) {
        printf("E%d\t", i + 1);
        for (int j = 0; j < N; j++) {
            printf("%d\t", matriz_costos[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

// Función principal para resolver el problema usando DFS
void resolverDFS(int** matriz_costos, int N, int costo_maximo) {
    // Imprimir la matriz de costos
    imprimirMatrizCostos(matriz_costos, N);

    // Inicializar variables
    Pila pila;
    pila.tamano = 0;
    int* tareas_asignadas = (int*)calloc(N, sizeof(int));
    Nodo* raiz = nuevoNodo(tareas_asignadas, 0, 0, -1, -1, NULL, N);
    raiz->costo = calcularCosto(matriz_costos, raiz->asignadas, -1, N, costo_maximo);
    apilar(&pila, raiz);

    int costoMinimo = costo_maximo;
    Nodo* nodoMinimo = NULL;

    // DFS con Branch and Bound
    while (!estaVacia(&pila)) {
        Nodo* actual = desapilar(&pila);

        // Si hemos asignado todas las tareas
        if (actual->id_empleado == N - 1) {
            if (actual->costo < costoMinimo) {
                costoMinimo = actual->costo;
                nodoMinimo = actual;
            } else {
                free(actual->asignadas);
                free(actual); // Podar el nodo si no es la solución óptima
            }
            continue;
        }

        int id_empleado = actual->id_empleado + 1;

        // Generar nodos hijos
        for (int j = 0; j < N; j++) {
            if (!actual->asignadas[j]) {
                Nodo* hijo = nuevoNodo(actual->asignadas, actual->costo_ruta + matriz_costos[id_empleado][j],
                                       actual->costo, id_empleado, j, actual, N);

                // Calcular la cota inferior
                hijo->costo = hijo->costo_ruta + calcularCosto(matriz_costos, hijo->asignadas, hijo->id_empleado, N, costo_maximo);

                // Si la cota es menor que el costo mínimo actual, añadimos el nodo a la pila
                if (hijo->costo < costoMinimo) {
                    apilar(&pila, hijo);
                } else {
                    free(hijo->asignadas);
                    free(hijo); // Podamos el nodo
                }
            }
        }
    }

    // Imprimir la solución óptima
    if (nodoMinimo == NULL) {
        printf("Error: No se encontró una solución válida.\n");
        free(tareas_asignadas);
        return;
    }

    printf("El costo mínimo es %d\n", costoMinimo);

    // Reconstruir la asignación desde nodoMinimo
    int* resultado = (int*)malloc(N * sizeof(int));
    for (int i = 0; i < N; i++)
        resultado[i] = -1; // Inicializar el arreglo de resultados

    Nodo* temp = nodoMinimo;
    while (temp != NULL && temp->id_empleado != -1) {
        resultado[temp->id_empleado] = temp->id_tarea;
        temp = temp->padre;
    }

    // Imprimir las asignaciones
    for (int i = 0; i < N; i++) {
        if (resultado[i] != -1) {
            printf("Empleado %d asignado a la tarea %d\n", i + 1, resultado[i] + 1);
        } else {
            printf("Error: No se pudo asignar una tarea al empleado %d.\n", i + 1);
        }
    }

    // Liberar memoria de los nodos restantes
    while (!estaVacia(&pila)) {
        Nodo* nodo = desapilar(&pila);
        free(nodo->asignadas);
        free(nodo);
    }
    free(nodoMinimo->asignadas);
    free(nodoMinimo);
    free(tareas_asignadas);
    free(resultado);
}

// Función principal
int main() {
    int N = 4; // Número de empleados y
    int costo_maximo = 999; // Costo máximo permitido
    int** matriz_costos = (int**)malloc(N * sizeof(int*));
    for (int i = 0; i < N; i++) {
        matriz_costos[i] = (int*)malloc(N * sizeof(int));
    }

    // Inicializar la matriz de costos
    int matrizInicial[4][4] = {
            {9, 2, 7, 8},
            {6, 4, 3, 7},
            {5, 8, 1, 8},
            {7, 6, 9, 4}
    };

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            matriz_costos[i][j] = matrizInicial[i][j];
        }
    }

    resolverDFS(matriz_costos, N, costo_maximo);

    // Liberar la memoria de la matriz de costos
    for (int i = 0; i < N; i++) {
        free(matriz_costos[i]);
    }
    free(matriz_costos);

    return 0;
}
