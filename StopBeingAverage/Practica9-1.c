#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Prototipos
void quickSort(int arr[], int low, int high);
void mergeSort(int arr[], int temp[], int low, int high);
void heapSort(int arr[], int n);
void quickHeap(int arr[], int low, int high);
void generarArregloAleatorio(int arr[], int size);
void generarArregloOrdenado(int arr[], int size);
void generarArregloOrdenadoInverso(int arr[], int size);
void imprimirArreglo(int arr[], int size);
void copiarArreglo(int origen[], int destino[], int size);

// Intercambio de valores
void intercambiar(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

/* ====== QuickSort Optimizado ====== */

int particionar(int arr[], int low, int high) {
    int randomIndex = low + rand() % (high - low + 1);
    intercambiar(&arr[randomIndex], &arr[high]);

    int pivot = arr[high];
    int i = low - 1;

    for (int j = low; j < high; j++) {
        if (arr[j] < pivot) {
            intercambiar(&arr[++i], &arr[j]);
        }
    }
    intercambiar(&arr[i + 1], &arr[high]);
    return i + 1;
}

void quickSort(int arr[], int low, int high) {
    if (low < high) {
        if (high - low < 10) {
            for (int i = low + 1; i <= high; i++) {
                int key = arr[i], j = i - 1;
                while (j >= low && arr[j] > key) {
                    arr[j + 1] = arr[j];
                    j--;
                }
                arr[j + 1] = key;
            }
            return;
        }

        int pivotIndex = particionar(arr, low, high);
        quickSort(arr, low, pivotIndex - 1);
        quickSort(arr, pivotIndex + 1, high);
    }
}

/* ====== MergeSort ====== */

void merge(int arr[], int temp[], int low, int mid, int high) {
    int i = low, j = mid + 1, k = low;

    while (i <= mid && j <= high) {
        temp[k++] = (arr[i] <= arr[j]) ? arr[i++] : arr[j++];
    }

    while (i <= mid) temp[k++] = arr[i++];
    while (j <= high) temp[k++] = arr[j++];

    for (i = low; i <= high; i++) arr[i] = temp[i];
}

void mergeSort(int arr[], int temp[], int low, int high) {
    if (low < high) {
        int mid = (low + high) / 2;
        mergeSort(arr, temp, low, mid);
        mergeSort(arr, temp, mid + 1, high);
        merge(arr, temp, low, mid, high);
    }
}

/* ====== HeapSort ====== */

void heapify(int arr[], int n, int i) {
    while (1) {
        int largest = i, left = 2 * i + 1, right = 2 * i + 2;

        if (left < n && arr[left] > arr[largest]) largest = left;
        if (right < n && arr[right] > arr[largest]) largest = right;

        if (largest == i) break;

        intercambiar(&arr[i], &arr[largest]);
        i = largest;
    }
}

void heapSort(int arr[], int n) {
    for (int i = n / 2 - 1; i >= 0; i--) heapify(arr, n, i);
    for (int i = n - 1; i > 0; i--) {
        intercambiar(&arr[0], &arr[i]);
        heapify(arr, i, 0);
    }
}

/* ====== QuickHeap (Híbrido de QuickSort y HeapSort) ====== */

void quickHeap(int arr[], int low, int high) {
    while (low < high) {
        if (high - low < 10) {
            for (int i = low + 1; i <= high; i++) {
                int key = arr[i], j = i - 1;
                while (j >= low && arr[j] > key) {
                    arr[j + 1] = arr[j];
                    j--;
                }
                arr[j + 1] = key;
            }
            return;
        }

        int pivotIndex = particionar(arr, low, high);

        if (pivotIndex - low > 5000) {
            heapSort(arr + low, pivotIndex - low + 1);
        } else {
            quickHeap(arr, low, pivotIndex - 1);
        }

        low = pivotIndex + 1;
    }
}

/* ====== Funciones Auxiliares ====== */

void generarArregloAleatorio(int arr[], int size) {
    for (int i = 0; i < size; i++) arr[i] = rand() % 100;
}

void imprimirArreglo(int arr[], int size) {
    for (int i = 0; i < size; i++) printf("%d ", arr[i]);
    printf("\n");
}

void copiarArreglo(int origen[], int destino[], int size) {
    for (int i = 0; i < size; i++) destino[i] = origen[i];
}

/* ====== Menú ====== */

void mostrarMenu() {
    printf("\nMENU PRINCIPAL\n");
    printf("1. QuickSort\n");
    printf("2. MergeSort\n");
    printf("3. HeapSort\n");
    printf("4. QuickHeap\n");
    printf("5. Salir\n");
    printf("Seleccione una opción: ");
}

void ejecutarAlgoritmo(int opcion, int size) {
    int* arr = malloc(size * sizeof(int));
    generarArregloAleatorio(arr, size);

    printf("\nEjecutando algoritmo con tamaño %d...\n", size);
    int* copia = malloc(size * sizeof(int));
    copiarArreglo(arr, copia, size);

    clock_t inicio = clock();

    switch (opcion) {
        case 1: quickSort(copia, 0, size - 1); break;
        case 2: {
            int* temp = malloc(size * sizeof(int));
            mergeSort(copia, temp, 0, size - 1);
            free(temp);
            break;
        }
        case 3: heapSort(copia, size); break;
        case 4: quickHeap(copia, 0, size - 1); break;
    }

    double tiempo = (double)(clock() - inicio) / CLOCKS_PER_SEC;
    printf("Tiempo: %.6f segundos\n", tiempo);

    if (size == 10) {
        printf("Antes: ");
        imprimirArreglo(arr, size);
        printf("Después: ");
        imprimirArreglo(copia, size);
    }

    free(arr);
    free(copia);
}

int main() {
    srand(time(NULL));
    int tamanos[] = {10, 100, 1000, 10000, 100000, 1000000, 10000000};
    int opcion;

    do {
        mostrarMenu();
        scanf("%d", &opcion);
        if (opcion == 5) break;
        for (int i = 0; i < 7; i++) ejecutarAlgoritmo(opcion, tamanos[i]);
    } while (1);

    return 0;
}
