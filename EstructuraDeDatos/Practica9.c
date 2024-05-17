#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct nodo {
    int paginas;
    char nombre[50];
    struct nodo *izq;
    struct nodo *dch;
} Nodo;

typedef struct {
    Nodo *raiz;
    Nodo **arreglo_nodos;
    int num_nodos;
    int capacidad;
    int esMinHeap;
} Monton;

Monton* crearMonton(int capacidad, int esMinHeap);
void destruirMonton(Monton* monton);
void cambiarPrioridad(Monton* monton);
void mostrarColaDeImpresion(Monton* monton);
void agregarArchivo(Monton* monton, int paginas, const char* nombre);
void eliminarArchivo(Monton* monton, int indice);
void eliminarTodosLosArchivos(Monton* monton);
void procesarArchivo(Monton* monton);
void heapifyUp(Monton* monton, int idx);
void heapifyDown(Monton* monton, int idx);
int comparar(Nodo* a, Nodo* b, int esMinHeap);
void sincronizarArbol(Nodo* nodo, Nodo** arreglo, int idx, int num_nodos);
void ordenarArregloNodos(Nodo** arreglo, int num_nodos, int esMinHeap);

void insertarDocumentosIniciales(Monton* monton) {
    agregarArchivo(monton, 10, "doc1");
    agregarArchivo(monton, 5, "doc2");
    agregarArchivo(monton, 20, "doc3");
    agregarArchivo(monton, 5, "doc4");   // Misma cantidad de páginas que doc2
    agregarArchivo(monton, 15, "doc5");
    agregarArchivo(monton, 25, "doc6");
    agregarArchivo(monton, 10, "doc7");  // Misma cantidad de páginas que doc1
    agregarArchivo(monton, 30, "doc8");
    printf("Documentos iniciales insertados.\n");
}

int main(void) {
    int opcion, paginas;
    char nombre[50];
    Monton* colaDeImpresion = crearMonton(10, 1); // heap min por defecto

    // Insertar documentos iniciales
    insertarDocumentosIniciales(colaDeImpresion);

    while (1) {
        printf("\nMENU\n");
        printf("[0] CAMBIAR PRIORIDAD\n");
        printf("[1] MOSTRAR COLA DE IMPRESION\n");
        printf("[2] AGREGAR ARCHIVO\n");
        printf("[3] ELIMINAR ARCHIVO\n");
        printf("[4] ELIMINAR TODOS LOS ARCHIVOS\n");
        printf("[5] PROCESAR/IMPRIMIR ARCHIVO\n");
        printf("[6] TERMINAR PROGRAMA\n");
        printf("Seleccione una opción: ");
        scanf("%d", &opcion);

        switch (opcion) {
            case 0:
                cambiarPrioridad(colaDeImpresion);
                break;
            case 1:
                mostrarColaDeImpresion(colaDeImpresion);
                break;
            case 2:
                printf("Ingrese el nombre del archivo: ");
                scanf("%s", nombre);
                printf("Ingrese el número de páginas: ");
                scanf("%d", &paginas);
                agregarArchivo(colaDeImpresion, paginas, nombre);
                break;
            case 3:
                mostrarColaDeImpresion(colaDeImpresion);
                printf("Seleccione el índice del archivo a eliminar: ");
                scanf("%d", &opcion);
                eliminarArchivo(colaDeImpresion, opcion);
                break;
            case 4:
                eliminarTodosLosArchivos(colaDeImpresion);
                break;
            case 5:
                procesarArchivo(colaDeImpresion);
                break;
            case 6:
                destruirMonton(colaDeImpresion);
                exit(0);
                break;
            default:
                printf("Opción no válida\n");
        }
    }

    return 0;
}

Monton* crearMonton(int capacidad, int esMinHeap) {
    Monton* monton = (Monton*)malloc(sizeof(Monton));
    monton->raiz = NULL;
    monton->arreglo_nodos = (Nodo**)malloc(capacidad * sizeof(Nodo*));
    monton->num_nodos = 0;
    monton->capacidad = capacidad;
    monton->esMinHeap = esMinHeap;
    return monton;
}

void destruirMonton(Monton* monton) {
    eliminarTodosLosArchivos(monton);
    free(monton->arreglo_nodos);
    free(monton);
}

void cambiarPrioridad(Monton* monton) {
    monton->esMinHeap = !monton->esMinHeap;
    for (int i = (monton->num_nodos - 2) / 2; i >= 0; i--) {
        heapifyDown(monton, i);
    }
    printf("Prioridad cambiada.\n");
}

void mostrarColaDeImpresion(Monton* monton) {
    if (monton->num_nodos == 0) {
        printf("La cola de impresión está vacía.\n");
        return;
    }

    Nodo** copia_nodos = (Nodo**)malloc(monton->num_nodos * sizeof(Nodo*));
    memcpy(copia_nodos, monton->arreglo_nodos, monton->num_nodos * sizeof(Nodo*));
    ordenarArregloNodos(copia_nodos, monton->num_nodos, monton->esMinHeap);

    for (int i = 0; i < monton->num_nodos; i++) {
        printf("[%d] Nombre: %s, Páginas: %d\n", i, copia_nodos[i]->nombre, copia_nodos[i]->paginas);
    }

    free(copia_nodos);
}

void agregarArchivo(Monton* monton, int paginas, const char* nombre) {
    if (monton->num_nodos == monton->capacidad) {
        monton->capacidad *= 2;
        monton->arreglo_nodos = (Nodo**)realloc(monton->arreglo_nodos, monton->capacidad * sizeof(Nodo*));
    }
    Nodo* nuevo = (Nodo*)malloc(sizeof(Nodo));
    nuevo->paginas = paginas;
    strcpy(nuevo->nombre, nombre);
    nuevo->izq = nuevo->dch = NULL;
    monton->arreglo_nodos[monton->num_nodos] = nuevo;
    heapifyUp(monton, monton->num_nodos);
    monton->num_nodos++;
    sincronizarArbol(monton->raiz, monton->arreglo_nodos, 0, monton->num_nodos);
}

void eliminarArchivo(Monton* monton, int indice) {
    if (indice < 0 || indice >= monton->num_nodos) {
        printf("Índice no válido.\n");
        return;
    }

    Nodo* a_eliminar = monton->arreglo_nodos[indice];
    Nodo* ultimo = monton->arreglo_nodos[monton->num_nodos - 1];

    // Mostrar la información del archivo que se va a eliminar
    printf("Eliminando archivo: %s, Páginas: %d\n", a_eliminar->nombre, a_eliminar->paginas);

    if (indice != monton->num_nodos - 1) {
        monton->arreglo_nodos[indice] = ultimo;
        // Reorganizar el heap
        heapifyDown(monton, indice);
        heapifyUp(monton, indice);
    }

    monton->num_nodos--;
    sincronizarArbol(monton->raiz, monton->arreglo_nodos, 0, monton->num_nodos);

    // Liberar el nodo eliminado
    free(a_eliminar);
}


void eliminarTodosLosArchivos(Monton* monton) {
    for (int i = 0; i < monton->num_nodos; i++) {
        free(monton->arreglo_nodos[i]);
    }
    monton->num_nodos = 0;
    printf("Todos los archivos han sido eliminados.\n");
}

void procesarArchivo(Monton* monton) {
    if (monton->num_nodos == 0) {
        printf("La cola de impresión está vacía.\n");
        return;
    }
    printf("Procesando archivo: %s, Páginas: %d\n", monton->arreglo_nodos[0]->nombre, monton->arreglo_nodos[0]->paginas);
    eliminarArchivo(monton, 0);
}

void heapifyUp(Monton* monton, int idx) {
    int padre = (idx - 1) / 2;
    while (idx > 0 && comparar(monton->arreglo_nodos[idx], monton->arreglo_nodos[padre], monton->esMinHeap)) {
        Nodo* temp = monton->arreglo_nodos[idx];
        monton->arreglo_nodos[idx] = monton->arreglo_nodos[padre];
        monton->arreglo_nodos[padre] = temp;
        idx = padre;
        padre = (idx - 1) / 2;
    }
}

void heapifyDown(Monton* monton, int idx) {
    int hijo_izq = 2 * idx + 1;
    int hijo_dch = 2 * idx + 2;
    int menor_mayor = idx;

    if (hijo_izq < monton->num_nodos && comparar(monton->arreglo_nodos[hijo_izq], monton->arreglo_nodos[menor_mayor], monton->esMinHeap)) {
        menor_mayor = hijo_izq;
    }
    if (hijo_dch < monton->num_nodos && comparar(monton->arreglo_nodos[hijo_dch], monton->arreglo_nodos[menor_mayor], monton->esMinHeap)) {
        menor_mayor = hijo_dch;
    }
    if (menor_mayor != idx) {
        Nodo* temp = monton->arreglo_nodos[idx];
        monton->arreglo_nodos[idx] = monton->arreglo_nodos[menor_mayor];
        monton->arreglo_nodos[menor_mayor] = temp;
        heapifyDown(monton, menor_mayor);
    }
}

int comparar(Nodo* a, Nodo* b, int esMinHeap) {
    if (esMinHeap) {
        return a->paginas < b->paginas;
    } else {
        return a->paginas > b->paginas;
    }
}

void sincronizarArbol(Nodo* nodo, Nodo** arreglo, int idx, int num_nodos) {
    if (idx >= num_nodos) return;
    nodo = arreglo[idx];
    nodo->izq = (2 * idx + 1 < num_nodos) ? arreglo[2 * idx + 1] : NULL;
    nodo->dch = (2 * idx + 2 < num_nodos) ? arreglo[2 * idx + 2] : NULL;
    if (nodo->izq) sincronizarArbol(nodo->izq, arreglo, 2 * idx + 1, num_nodos);
    if (nodo->dch) sincronizarArbol(nodo->dch, arreglo, 2 * idx + 2, num_nodos);
}

void ordenarArregloNodos(Nodo** arreglo, int num_nodos, int esMinHeap) {
    for (int i = 0; i < num_nodos - 1; i++) {
        for (int j = 0; j < num_nodos - i - 1; j++) {
            if ((esMinHeap && arreglo[j]->paginas > arreglo[j + 1]->paginas) ||
                (!esMinHeap && arreglo[j]->paginas < arreglo[j + 1]->paginas)) {
                Nodo* temp = arreglo[j];
                arreglo[j] = arreglo[j + 1];
                arreglo[j + 1] = temp;
            }
        }
    }
}
