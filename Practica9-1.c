//
// Created by Fernando Rosales on 3/25/25.
//


#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Prototipos de funciones
void quickSort(int arreglo[], int bajo, int alto, int tamano);
void mergeSort(int arr[], int temp[], int low, int high);
void heapSort(int arr[], int n);
void quickHeap(int arreglo[], int bajo, int alto, int tamano);
void generarArregloAleatorio(int arreglo[], int tamano);
void generarArregloOrdenado(int arreglo[], int tamano);
void generarArregloOrdenadoAlReves(int arreglo[], int tamano);
void imprimirArreglo(int arreglo[], int tamano);
void copiarArreglo(int origen[], int destino[], int tamano);


/*------------------------------------*/

// MergeSort

/*------------------------------------*/

// Funciones para MergeSort
void merge(int arr[], int temp[], int low, int mid, int high) {
    int l1 = low;
    int l2 = mid + 1;
    int i = low;

    while (l1 <= mid && l2 <= high) {
        if (arr[l1] <= arr[l2])
            temp[i++] = arr[l1++];
        else
            temp[i++] = arr[l2++];
    }

    while (l1 <= mid)
        temp[i++] = arr[l1++];

    while (l2 <= high)
        temp[i++] = arr[l2++];

    for (i = low; i <= high; i++)
        arr[i] = temp[i];
}

void mergeSort(int arr[], int temp[], int low, int high) {
    if (low < high) {
        int mid = (low + high) / 2;
        mergeSort(arr, temp, low, mid);
        mergeSort(arr, temp, mid + 1, high);
        merge(arr, temp, low, mid, high);
    }
}

/*------------------------------------*/

// MergeSort

/*------------------------------------*/


/*------------------------------------*/

// QuickSort

/*------------------------------------*/

// Funciones para QuickSort
void intercambiar(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

int particionar(int arreglo[], int bajo, int alto, int tamano) {
    int pivote = arreglo[alto];
    int indiceMenor = bajo - 1;

    for (int j = bajo; j <= alto - 1; j++) {
        if (arreglo[j] < pivote) {
            indiceMenor++;
            intercambiar(&arreglo[indiceMenor], &arreglo[j]);
        }
    }

    intercambiar(&arreglo[indiceMenor + 1], &arreglo[alto]);
    return indiceMenor + 1;
}

void quickSort(int arreglo[], int bajo, int alto, int tamano) {
    if (bajo < alto) {
        int indicePivote = particionar(arreglo, bajo, alto, tamano);
        quickSort(arreglo, bajo, indicePivote - 1, tamano);
        quickSort(arreglo, indicePivote + 1, alto, tamano);
    }
}

/*------------------------------------*/

// QuickSort

/*------------------------------------*/

/*------------------------------------*/

// HeapSort

/*------------------------------------*/

// Función para HeapSort
void heapify(int arr[], int n, int i) {
    int greatest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && arr[left] > arr[greatest])
        greatest = left;

    if (right < n && arr[right] > arr[greatest])
        greatest = right;

    if (greatest != i) {
        intercambiar(&arr[i], &arr[greatest]);
        heapify(arr, n, greatest);
    }
}

void heapSort(int arr[], int n) {
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);

    for (int i = n - 1; i >= 0; i--) {
        intercambiar(&arr[0], &arr[i]);
        heapify(arr, i, 0);
    }
}

/*------------------------------------*/

// HeapSort

/*------------------------------------*/


/*------------------------------------*/

// quickHeap

/*------------------------------------*/

// Algoritmo híbrido QuickHeap
void quickHeap(int arreglo[], int bajo, int alto, int tamano) {
    if (bajo < alto) {
        int indicePivote = particionar(arreglo, bajo, alto, tamano);
        quickHeap(arreglo, bajo, indicePivote - 1, tamano);
        quickHeap(arreglo, indicePivote + 1, alto, tamano);
    }
    heapSort(arreglo, tamano);
}

/*------------------------------------*/

// quickHeap

/*------------------------------------*/



// Funciones auxiliares
void generarArregloAleatorio(int arreglo[], int tamano) {
    for (int i = 0; i < tamano; i++)
        arreglo[i] = rand() % 100;
}

void generarArregloOrdenado(int arreglo[], int tamano) {
    for (int i = 0; i < tamano; i++)
        arreglo[i] = i;
}

void generarArregloOrdenadoAlReves(int arreglo[], int tamano) {
    for (int i = 0; i < tamano; i++)
        arreglo[i] = tamano - i;
}

void imprimirArreglo(int arreglo[], int tamano) {
    for (int i = 0; i < tamano; i++)
        printf("%d ", arreglo[i]);
    printf("\n");
}

void copiarArreglo(int origen[], int destino[], int tamano) {
    for (int i = 0; i < tamano; i++)
        destino[i] = origen[i];
}

// Menú principal
void mostrarMenu() {
    printf("\nMENU PRINCIPAL\n");
    printf("1. QuickSort\n");
    printf("2. MergeSort\n");
    printf("3. HeapSort\n");
    printf("4. QuickHeap\n");
    printf("5. Salir\n");
    printf("Seleccione una opcion: ");
}

int main() {
    srand(time(NULL));

    // Inicializar todos los arreglos
    int tamanos[] = {10, 100, 1000, 10000, 100000};
    int* arreglos[3][5]; // [tipo][tamano]

    // Asignar memoria
    for (int tipo = 0; tipo < 3; tipo++) {
        for (int tam = 0; tam < 5; tam++) {
            arreglos[tipo][tam] = malloc(tamanos[tam] * sizeof(int));

            if (tipo == 0)
                generarArregloAleatorio(arreglos[tipo][tam], tamanos[tam]);
            else if (tipo == 1)
                generarArregloOrdenado(arreglos[tipo][tam], tamanos[tam]);
            else
                generarArregloOrdenadoAlReves(arreglos[tipo][tam], tamanos[tam]);
        }
    }

    int opcion;
    do {
        mostrarMenu();
        scanf("%d", &opcion);

        if (opcion == 5) break;
        if (opcion < 1 || opcion > 4) {
            printf("Opcion invalida!\n");
            continue;
        }

        // Selección de tipo de arreglo
        printf("\nTIPO DE ARREGLO:\n");
        printf("1. Aleatorio\n");
        printf("2. Ordenado\n");
        printf("3. Ordenado inverso\n");
        printf("Seleccione: ");
        int tipo;
        scanf("%d", &tipo);
        tipo--;

        // Selección de tamaño
        printf("\nTAMANO:\n");
        printf("1. 10\n2. 100\n3. 1000\n4. 10000\n5. 100000\n");
        printf("Seleccione: ");
        int tam;
        scanf("%d", &tam);
        tam--;

        // Crear copia del arreglo
        int* original = arreglos[tipo][tam];
        int* copia = malloc(tamanos[tam] * sizeof(int));
        copiarArreglo(original, copia, tamanos[tam]);

        // Medir tiempo
        clock_t inicio = clock();

        switch(opcion) {
            case 1:
                quickSort(copia, 0, tamanos[tam]-1, tamanos[tam]);
                break;
            case 2: {
                int* temp = malloc(tamanos[tam] * sizeof(int));
                mergeSort(copia, temp, 0, tamanos[tam]-1);
                free(temp);
                break;
            }
            case 3:
                heapSort(copia, tamanos[tam]);
                break;
            case 4:
                quickHeap(copia, 0, tamanos[tam]-1, tamanos[tam]);
                break;
        }

        double tiempo = (double)(clock() - inicio) / CLOCKS_PER_SEC;

        // Mostrar resultados
        printf("\nTiempo de ejecucion: %.6f segundos\n", tiempo);
        if (tamanos[tam] <= 100) {
            printf("Arreglo ordenado: ");
            imprimirArreglo(copia, tamanos[tam]);
        }

        free(copia);

    } while (1);

    // Liberar memoria
    for (int tipo = 0; tipo < 3; tipo++)
        for (int tam = 0; tam < 5; tam++)
            free(arreglos[tipo][tam]);

    return 0;
}