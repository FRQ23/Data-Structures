//Fernando Rosales Quiñones 1299440
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_STR 100 // Max size para strings
// Struct para manejar los gastos
typedef struct {

    char categoria[MAX_STR]; // Tipo de gasto (categoría)

    char concepto[MAX_STR]; // Qué compraste (concepto)

    float costo;
// Cuánto te costó (costo)
} Gasto;
// Prototipos de funciones
void insercion(Gasto *gastos, int n); // Sort por inserción
void seleccion(Gasto *gastos, int n); // Sort por selección
void burbuja(Gasto *gastos, int n); // Sort tipo burbuja
void capturarGasto(Gasto **gastos, int *n); // Función para capturar un gasto
void mostrarGastos(Gasto *gastos, int n, const char *categoria, void (*ordenar)(Gasto*, int), int ascendente); // Función para mostrar gastos
//filtrados por categoría
int main(void) {

    Gasto *gastos = NULL; // Puntero dinámico para los gastos

    int n = 0; // Cuántos gastos tienes guardados

    int opcion; // La opción que eliges del menú

// Loop principal del menú

    do {

        printf("\nMenu:\n");

        printf("1. Capturar gasto\n");

        printf("2. Mostrar gasto en alimentos (orden por insercion)\n");

        printf("3. Mostrar gasto en diversion (orden por seleccion)\n");

        printf("4. Mostrar gasto en pagos_fijos (orden por burbuja)\n");

        printf("5. Salir\n");

        printf("Seleccione una opcion: ");

        scanf("%d", &opcion);

// Dependiendo de la opción, hacemos algo diferente

        switch(opcion) {

            case 1:

                capturarGasto(&gastos, &n); // Guardas un gasto nuevo

                break;

            case 2:

                mostrarGastos(gastos, n, "alimentos", insercion, 1); // Gastos de "alimentos" sorted por inserción

                break;

            case 3:

                mostrarGastos(gastos, n, "diversion", seleccion, 0); // Gastos de "diversion" sorted por selección

                break;

            case 4:

                mostrarGastos(gastos, n, "pagos_fijos", burbuja, 1); // Gastos de "pagos_fijos" sorted por burbuja

                break;

            case 5:

                printf("Bye bye...\n"); // Sales del programa

                break;

            default:

                printf("Opcion no valida. Intente de nuevo.\n"); // Si eliges algo que no existe

        }

    } while(opcion != 5); // El programa sigue hasta que eliges salir

// Limpiamos la memoria dinámica antes de salir

    free(gastos);

    return 0;
}
// Función para capturar un gasto nuevo
void capturarGasto(Gasto **gastos, int *n) {

// Pedimos más memoria para guardar un gasto más

    *gastos = realloc(*gastos, (*n + 1) * sizeof(Gasto));

    if (*gastos == NULL) {

// Si falla la memoria, decimos que hubo un error y cerramos

        printf("Error al asignar memoria.\n");

        exit(EXIT_FAILURE); // Cerramos el programa

    }

// Pedimos al user que ingrese la categoría

    printf("Ingrese la categoria (alimentos, diversion, pagos_fijos): ");

    scanf("%s", (*gastos)[*n].categoria);

// Pedimos el concepto del gasto (qué compraste)

    printf("Ingrese el concepto: ");

    scanf("%s", (*gastos)[*n].concepto);

// Pedimos el costo del gasto (cuánto te costó)

    printf("Ingrese el costo: ");


    scanf("%f", &(*gastos)[*n].costo);

// Sumamos 1 al contador de gastos

    (*n)++;
}
// Función para mostrar los gastos filtrados por categoría
void mostrarGastos(Gasto *gastos, int n, const char *categoria, void (*ordenar)(Gasto*, int), int ascendente) {

    int i, count = 0;

    float total = 0.0;

    Gasto *filtrados = malloc(n * sizeof(Gasto)); // Creamos espacio para los gastos filtrados

// Filtramos por categoría

    for (i = 0; i < n; i++) {

        if (strcmp(gastos[i].categoria, categoria) == 0) {

            filtrados[count++] = gastos[i]; // Guardamos los gastos filtrados

            total += gastos[i].costo; // Sumamos el costo al total

        }

    }

// Si hay gastos, los mostramos

    if (count > 0) {

        ordenar(filtrados, count); // Ordenamos los gastos

        printf("\nGastos en %s ordenados por concepto:\n", categoria);

        for (i = 0; i < count; i++) {

// Mostramos cada gasto filtrado

            printf("Concepto: %s, Costo: %.2f\n", filtrados[i].concepto, filtrados[i].costo);

        }

        printf("Total en %s: %.2f\n", categoria, total); // Mostramos el total de los gastos

    } else {

        printf("No hay gastos en la categoria %s.\n", categoria); // Si no hay gastos, lo decimos

    }

    free(filtrados); // Liberamos la memoria de los gastos filtrados
}
// Algoritmo de inserción (sort)
void insercion(Gasto *gastos, int n) {

    int i, j;

    Gasto temp;

// Vamos desde el segundo elemento hasta el final

    for (i = 1; i < n; i++) {

        temp = gastos[i]; // Guardamos el gasto actual

        j = i - 1;

// Movemos los elementos mayores

        while (j >= 0 && strcmp(gastos[j].concepto, temp.concepto) > 0) {

            gastos[j + 1] = gastos[j];

            j--;

        }

        gastos[j + 1] = temp; // Insertamos el gasto en la posición correcta

    }
}
// Algoritmo de selección (sort)
void seleccion(Gasto *gastos, int n) {

    int i, j, min_idx;

    Gasto temp;

// Recorremos desde el primer elemento hasta el penúltimo

    for (i = 0; i < n-1; i++) {

        min_idx = i; // Suponemos que el primero es el más chico

        for (j = i+1; j < n; j++) {

// Buscamos el gasto con el concepto menor (orden descendente)

            if (strcmp(gastos[j].concepto, gastos[min_idx].concepto) > 0) {

                min_idx = j; // Actualizamos el índice del menor

            }

        }

// Intercambiamos los elementos

        temp = gastos[min_idx];

        gastos[min_idx] = gastos[i];

        gastos[i] = temp;

    }
}
// Algoritmo burbuja (sort)
void burbuja(Gasto *gastos, int n) {

    int i, j;

    Gasto temp;

// Vamos desde el primer elemento hasta el penúltimo

    for (i = 0; i < n-1; i++) {

        for (j = 0; j < n-i-1; j++) {

// Comparamos conceptos de gastos adyacentes

            if (strcmp(gastos[j].concepto, gastos[j+1].concepto) > 0) {

// Intercambiamos si no están en el orden correcto

                temp = gastos[j];

                gastos[j] = gastos[j+1];

                gastos[j+1] = temp;


            }

        }

    }
}