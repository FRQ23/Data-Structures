//
// Created by Fernando Rosales on 3/25/25.
//

#include <stdio.h>
#include <stdlib.h>
#include <time.h>





/*------------------------------------*/

// quicksort.c

/*------------------------------------*/


void intercambiar(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void imprimirArreglo(int arreglo[], int tamano) {
    for (int i = 0; i < tamano; i++) {
        printf("%d ", arreglo[i]);
    }
    printf("\n");
}

int particionar(int arreglo[], int bajo, int alto, int tamano) {
    int pivote = arreglo[alto];
    printf("\nSubarreglo actual: ");
    for (int i = bajo; i <= alto; i++) printf("%d ", arreglo[i]);
    printf("\nPivote seleccionado: %d\n", pivote);

    int indiceMenor = bajo - 1;

    for (int j = bajo; j <= alto - 1; j++) {
        if (arreglo[j] < pivote) {
            indiceMenor++;
            intercambiar(&arreglo[indiceMenor], &arreglo[j]);
            printf("Intercambio: ");
            imprimirArreglo(arreglo, tamano);
        }
    }

    intercambiar(&arreglo[indiceMenor + 1], &arreglo[alto]);
    printf("Pivote colocado: ");
    imprimirArreglo(arreglo, tamano);
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


//mergesort


void merging(int low, int mid, int high) {
    int l1, l2, i;

    for(l1 = low, l2 = mid + 1, i = low; l1 <= mid && l2 <= high; i++) {
        if(a[l1] <= a[l2])
            b[i] = a[l1++];
        else
            b[i] = a[l2++];
    }

    while(l1 <= mid)
        b[i++] = a[l1++];

    while(l2 <= high)
        b[i++] = a[l2++];

    for(i = low; i <= high; i++)
        a[i] = b[i];
}

void sort(int low, int high) {
    int mid;

    if(low < high) {
        mid = (low + high) / 2;
        sort(low, mid);
        sort(mid+1, high);
        merging(low, mid, high);
    } else {
        return;
    }
}


/*------------------------------------*/

//heapsort


// Implementation of Heap Sort in C

#include <stdio.h>

// Function to swap the position of two elements in an array
void swap(int *a, int *b) {
    int tempvar = *a;
    *a = *b;
    *b = tempvar;
}

void heapify(int arr[], int n, int i) {
    // Finding the greatest among root, leftSide child, and rightSide child of the tree
    int greatest = i;
    int leftSide = 2 * i + 1;
    int rightSide = 2 * i + 2;

    if (leftSide < n && arr[leftSide] > arr[greatest])
        greatest = leftSide;

    if (rightSide < n && arr[rightSide] > arr[greatest])
        greatest = rightSide;

    // Swap and continue heapifying if the root is not the greatest
    if (greatest != i) {
        swap(&arr[i], &arr[greatest]);
        heapify(arr, n, greatest);
    }
}

// Main function
void heapSort(int arr[], int n) {
    // Build max heap
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);


    for (int i = n - 1; i >= 0; i--) {
        swap(&arr[0], &arr[i]);

        heapify(arr, i, 0);
    }
}

// Printing the array
void printArray(int arr[], int n) {
    for (int i = 0; i < n; ++i)
        printf("%d ", arr[i]);
    printf("\n");
}

/*------------------------------------*/

//algortimo hibrido, QuickHeap


void quickHeap(int arreglo[], int bajo, int alto, int tamano) {
    if (bajo < alto) {
        int indicePivote = particionar(arreglo, bajo, alto, tamano);
        quickHeap(arreglo, bajo, indicePivote - 1, tamano);
        quickHeap(arreglo, indicePivote + 1, alto, tamano);
    }
    heapSort(arreglo, tamano);
}

/*------------------------------------*/



/*------------------------------------*/

//Generar arreglos aleatorios

int generarArregloAleatorio(int arreglo[], int tamano) {
    for (int i = 0; i < tamano; i++) {
        arreglo[i] = rand() % 100;
    }
}

//Generar arreglos ordenados

int generarArregloOrdenado(int arreglo[], int tamano) {
    for (int i = 0; i < tamano; i++) {
        arreglo[i] = i;
    }
}

//Generar arreglos ordenados al reves

int generarArregloOrdenadoAlReves(int arreglo[], int tamano) {
    for (int i = 0; i < tamano; i++) {
        arreglo[i] = tamano - i;
    }
}

int imprimirArreglo(int arreglo[], int tamano) {
    for (int i = 0; i < tamano; i++) {
        printf("%d ", arreglo[i]);
    }
    printf("\n");
}

int imprimirArregloInverso(int arreglo[], int tamano) {
    for (int i = tamano - 1; i >= 0; i--) {
        printf("%d ", arreglo[i]);
    }
    printf("\n");
}

int calculoTiempoEjecucion(int arreglo[], int tamano) {
    clock_t inicio, fin;
    double tiempo;
    inicio = clock();
    quickSort(arreglo, 0, tamano - 1, tamano);
    fin = clock();
    tiempo = (double)(fin - inicio) / CLOCKS_PER_SEC;
    return tiempo;
}


int main() {

    //generar arreglos de los 3 tipos, de 10, 100, 1000, 10000, 100000, 1000000 elementos

    int arregloAleatorio10[10];
    int arregloAleatorio100[100];
    int arregloAleatorio1000[1000];
    int arregloAleatorio10000[10000];
    int arregloAleatorio100000[100000];

    int arregloOrdenado10[10];
    int arregloOrdenado100[100];
    int arregloOrdenado1000[1000];
    int arregloOrdenado10000[10000];
    int arregloOrdenado100000[100000];

    int arregloOrdenadoAlReves10[10];
    int arregloOrdenadoAlReves100[100];
    int arregloOrdenadoAlReves1000[1000];
    int arregloOrdenadoAlReves10000[10000];
    int arregloOrdenadoAlReves100000[100000];

    generarArregloAleatorio(arregloAleatorio10, 10);
    generarArregloAleatorio(arregloAleatorio100, 100);
    generarArregloAleatorio(arregloAleatorio1000, 1000);
    generarArregloAleatorio(arregloAleatorio10000, 10000);
    generarArregloAleatorio(arregloAleatorio100000, 100000);

    generarArregloOrdenado(arregloOrdenado10, 10);
    generarArregloOrdenado(arregloOrdenado100, 100);
    generarArregloOrdenado(arregloOrdenado1000, 1000);
    generarArregloOrdenado(arregloOrdenado10000, 10000);
    generarArregloOrdenado(arregloOrdenado100000, 100000);

    generarArregloOrdenadoAlReves(arregloOrdenadoAlReves10, 10);
    generarArregloOrdenadoAlReves(arregloOrdenadoAlReves100, 100);
    generarArregloOrdenadoAlReves(arregloOrdenadoAlReves1000, 1000);
    generarArregloOrdenadoAlReves(arregloOrdenadoAlReves10000, 10000);
    generarArregloOrdenadoAlReves(arregloOrdenadoAlReves100000, 100000);

    //ordenar los arreglos con los 4 algoritmos

    quickSort(arregloAleatorio10, 0, 9, 10);
    quickSort(arregloAleatorio100, 0, 99, 100);
    quickSort(arregloAleatorio1000, 0, 999, 1000);
    quickSort(arregloAleatorio10000, 0, 9999, 10000);
    quickSort(arregloAleatorio100000, 0, 99999, 100000);

    quickSort(arregloOrdenado10, 0, 9, 10);
    quickSort(arregloOrdenado100, 0, 99, 100);
    quickSort(arregloOrdenado1000, 0, 999, 1000);
    quickSort(arregloOrdenado10000, 0, 9999, 10000);
    quickSort(arregloOrdenado100000, 0, 99999, 100000);

    quickSort(arregloOrdenadoAlReves10, 0, 9, 10);
    quickSort(arregloOrdenadoAlReves100, 0, 99, 100);
    quickSort(arregloOrdenadoAlReves1000, 0, 999, 1000);
    quickSort(arregloOrdenadoAlReves10000, 0, 9999, 10000);
    quickSort(arregloOrdenadoAlReves100000, 0, 99999, 100000);

    heapSort(arregloAleatorio10, 10);
    heapSort(arregloAleatorio100, 100);
    heapSort(arregloAleatorio1000, 1000);
    heapSort(arregloAleatorio10000, 10000);
    heapSort(arregloAleatorio100000, 100000);

    heapSort(arregloOrdenado10, 10);
    heapSort(arregloOrdenado100, 100);
    heapSort(arregloOrdenado1000, 1000);
    heapSort(arregloOrdenado10000, 10000);
    heapSort(arregloOrdenado100000, 100000);

    heapSort(arregloOrdenadoAlReves10, 10);
    heapSort(arregloOrdenadoAlReves100, 100);
    heapSort(arregloOrdenadoAlReves1000, 1000);
    heapSort(arregloOrdenadoAlReves10000, 10000);
    heapSort(arregloOrdenadoAlReves100000, 100000);

    quickHeap(arregloAleatorio10, 0, 9, 10);
    quickHeap(arregloAleatorio100, 0, 99, 100);
    quickHeap(arregloAleatorio1000, 0, 999, 1000);
    quickHeap(arregloAleatorio10000, 0, 9999, 10000);
    quickHeap(arregloAleatorio100000, 0, 99999, 100000);

    quickHeap(arregloOrdenado10, 0, 9, 10);
    quickHeap(arregloOrdenado100, 0, 99, 100);
    quickHeap(arregloOrdenado1000, 0, 999, 1000);
    quickHeap(arregloOrdenado10000, 0, 9999, 10000);
    quickHeap(arregloOrdenado100000, 0, 99999, 100000);

    quickHeap(arregloOrdenadoAlReves10, 0, 9, 10);
    quickHeap(arregloOrdenadoAlReves100, 0, 99, 100);
    quickHeap(arregloOrdenadoAlReves1000, 0, 999, 1000);
    quickHeap(arregloOrdenadoAlReves10000, 0, 9999, 10000);
    quickHeap(arregloOrdenadoAlReves100000, 0, 99999, 100000);


    //imprimir los tiempos de ejecucion de los 4 algoritmos para cada arreglo

    //arreglos aleatorios




    return 0;
}

