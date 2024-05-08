#include "Queues.h"

// Variables globales para controlar la prioridad
int prioridadMenorPrimero = 1;  // 1 = menor primero, 0 = mayor primero

// Función para crear un nodo
Nodo* crearNodo(Dato archivo) {
    Nodo* nuevo = (Nodo*)malloc(sizeof(Nodo));
    if (!nuevo) return NULL;
    nuevo->archivo = archivo;
    nuevo->sig = NULL;
    return nuevo;
}

// Función para agregar nodo a cola
void agregarNodoACola(Cola* cola, Nodo* nodo) {
    if (cola->fin) {
        cola->fin->sig = nodo;
    } else {
        cola->inicio = nodo;
    }
    cola->fin = nodo;
    cola->cantidad_nodos++;
}

// Función para crear una cola
Cola* crearCola() {
    Cola* nueva = (Cola*)malloc(sizeof(Cola));
    if (!nueva) return NULL;
    nueva->inicio = nueva->fin = NULL;
    nueva->cantidad_nodos = 0;
    nueva->sig = NULL;
    return nueva;
}

// Función para insertar cola en Cola_2
void insertarEnCola_2(Cola_2* cola2, Cola* cola) {
    if (cola2->fin) {
        cola2->fin->sig = cola;
    } else {
        cola2->inicio = cola;
    }
    cola2->fin = cola;
    cola2->cantidad_colas++;
}

// Función para encontrar cola por número de páginas
Cola* encontrarCola(Cola_2* cola2, int paginas) {
    Cola* actual = cola2->inicio;
    while (actual) {
        if (actual->inicio && actual->inicio->archivo.paginas == paginas) {
            return actual;
        }
        actual = actual->sig;
    }
    return NULL;
}

// Función para agregar un archivo
void agregarArchivo(Cola_2* cola2, char* nombre, int paginas) {
    Dato nuevoArchivo;
    nuevoArchivo.nombre = strdup(nombre);
    nuevoArchivo.paginas = paginas;

    Nodo* nuevoNodo = crearNodo(nuevoArchivo);
    if (!nuevoNodo) {
        printf("Error al crear nodo para el archivo\n");
        return;
    }

    Cola* cola = encontrarCola(cola2, paginas);
    if (!cola) {
        cola = crearCola();
        if (!cola) {
            printf("Error al crear cola para nuevas páginas\n");
            free(nuevoNodo);
            return;
        }
        insertarEnCola_2(cola2, cola);
    }
    agregarNodoACola(cola, nuevoNodo);
}


// Función de comparación para qsort
int compararArchivos(const void *a, const void *b) {
    ArchivoInfo *archivoA = (ArchivoInfo *)a;
    ArchivoInfo *archivoB = (ArchivoInfo *)b;

    // Orden ascendente o descendente basado en la prioridad
    if (prioridadMenorPrimero) {
        return archivoA->paginas - archivoB->paginas;
    } else {
        return archivoB->paginas - archivoA->paginas;
    }
}

// Función para mostrar las colas ordenadas por prioridad
void mostrarColas(Cola_2* cola2) {
    if (cola2->inicio == NULL) {
        printf("No hay archivos en la cola de impresión.\n");
        return;
    }

    // Calcular la cantidad total de archivos
    int totalArchivos = 0;
    Cola* colaActual = cola2->inicio;
    while (colaActual) {
        totalArchivos += colaActual->cantidad_nodos;
        colaActual = colaActual->sig;
    }

    // Crear un array para almacenar todos los archivos
    ArchivoInfo *archivos = malloc(totalArchivos * sizeof(ArchivoInfo));
    if (archivos == NULL) {
        printf("Error al asignar memoria para mostrar archivos.\n");
        return;
    }

    // Llenar el array con información de archivos
    int idx = 0;
    colaActual = cola2->inicio;
    while (colaActual) {
        Nodo* nodoActual = colaActual->inicio;
        while (nodoActual) {
            archivos[idx].nombre = nodoActual->archivo.nombre;
            archivos[idx].paginas = nodoActual->archivo.paginas;
            idx++;
            nodoActual = nodoActual->sig;
        }
        colaActual = colaActual->sig;
    }

    // Ordenar el array de archivos
    qsort(archivos, totalArchivos, sizeof(ArchivoInfo), compararArchivos);

    // Mostrar archivos ordenados
    printf("Archivos ordenados por %s páginas:\n", prioridadMenorPrimero ? "menor número de" : "mayor número de");
    for (int i = 0; i < totalArchivos; i++) {
        printf("  Archivo: %s, Páginas: %d\n", archivos[i].nombre, archivos[i].paginas);
    }

    // Liberar memoria
    free(archivos);
}

void eliminarCola(Cola_2 *cola2, Cola *cola) {
    if (cola2->inicio == NULL || cola == NULL) return;

    Cola *actual = cola2->inicio;
    Cola *anterior = NULL;

    // Buscando la cola en la lista de colas
    while (actual != NULL && actual != cola) {
        anterior = actual;
        actual = actual->sig;
    }

    if (actual == NULL) return; // La cola no se encontró

    // Desconectando la cola de la lista
    if (anterior) {
        anterior->sig = actual->sig;
    } else {
        cola2->inicio = actual->sig;
    }

    if (actual == cola2->fin) {
        cola2->fin = anterior;
    }

    // Vaciar la cola y liberar la estructura
    vaciarCola(actual);
    free(actual);
}



// Función para eliminar un archivo específico
void eliminarArchivo(Cola_2* cola2) {
    int pagina, index, i;
    printf("Ingrese el número de páginas del archivo que desea eliminar: ");
    scanf("%d", &pagina);
    Cola* cola = encontrarCola(cola2, pagina);
    if (!cola || !cola->inicio) {
        printf("No se encontraron archivos con %d páginas.\n", pagina);
        return;
    }

    // Mostrar archivos y seleccionar uno para eliminar
    Nodo* actual = cola->inicio;
    Nodo* previo = NULL;
    i = 0;
    printf("Seleccione el archivo a eliminar:\n");
    while (actual) {
        printf("[%d] %s, %d páginas\n", i, actual->archivo.nombre, actual->archivo.paginas);
        actual = actual->sig;
        i++;
    }
    scanf("%d", &index);

    actual = cola->inicio;
    for (i = 0; actual && i < index; i++) {
        previo = actual;
        actual = actual->sig;
    }

    if (!actual) {
        printf("Opción inválida.\n");
        return;
    }

    if (previo) {
        previo->sig = actual->sig;
    } else {
        cola->inicio = actual->sig;
    }
    if (!actual->sig) {
        cola->fin = previo;
    }

    free(actual->archivo.nombre);
    free(actual);

    cola->cantidad_nodos--;
    if (cola->cantidad_nodos == 0) {
        eliminarCola(cola2, cola);
    }
}

void vaciarCola(Cola *cola) {
    Nodo *actual = cola->inicio;
    Nodo *siguiente;

    while (actual != NULL) {
        siguiente = actual->sig;
        free(actual->archivo.nombre);  // Asegúrate de que el nombre se haya asignado dinámicamente
        free(actual);
        actual = siguiente;
    }

    cola->inicio = NULL;
    cola->fin = NULL;
    cola->cantidad_nodos = 0;
}


// Función para eliminar todas las colas y sus archivos
void eliminarTodosLosArchivos(Cola_2* cola2) {
    Cola* actual = cola2->inicio;
    Cola* temp;
    while (actual) {
        vaciarCola(actual);
        temp = actual;
        actual = actual->sig;
        free(temp);
    }
    cola2->inicio = cola2->fin = NULL;
    cola2->cantidad_colas = 0;
}

// Función para procesar el archivo con mayor prioridad
void procesarImprimirArchivo(Cola_2* cola2) {
    if (!cola2->inicio) {
        printf("No hay archivos para procesar.\n");
        return;
    }

    Cola* target = NULL;
    Cola* prev = NULL;
    Cola* actual = cola2->inicio;
    Cola* prev_actual = NULL;

    while (actual) {
        if (!target || (prioridadMenorPrimero && actual->inicio->archivo.paginas < target->inicio->archivo.paginas) ||
            (!prioridadMenorPrimero && actual->inicio->archivo.paginas > target->inicio->archivo.paginas)) {
            target = actual;
            prev = prev_actual;
        }
        prev_actual = actual;
        actual = actual->sig;
    }

    if (target && target->inicio) {
        Nodo* nodo = target->inicio;
        printf("Procesando archivo: %s, %d páginas\n", nodo->archivo.nombre, nodo->archivo.paginas);
        target->inicio = nodo->sig;
        if (!target->inicio) {
            target->fin = NULL;
        }
        free(nodo->archivo.nombre);
        free(nodo);
        target->cantidad_nodos--;

        if (target->cantidad_nodos == 0) {
            if (prev) {
                prev->sig = target->sig;
            } else {
                cola2->inicio = target->sig;
            }
            if (target == cola2->fin) {
                cola2->fin = prev;
            }
            free(target);
        }
    }
}

Cola_2* crearCola_2() {
    Cola_2* nueva = (Cola_2*)malloc(sizeof(Cola_2));
    if (nueva == NULL) return NULL;
    nueva->inicio = nueva->fin = NULL;
    nueva->cantidad_colas = 0;
    return nueva;
}




// Función principal que muestra el menú y maneja la entrada del usuario
int main() {
    Cola_2* colaImpresion = crearCola_2();
    if (!colaImpresion) {
        printf("No se pudo crear la cola de impresión.\n");
        return 1;
    }

    int opcion;
    char nombreArchivo[100];
    int paginas;

    do {
        printf("[0] Cambiar Prioridad\n");
        printf("[1] Mostrar Cola de Impresión\n");
        printf("[2] Agregar Archivo\n");
        printf("[3] Eliminar Archivo\n");
        printf("[4] Eliminar Todos los Archivos\n");
        printf("[5] Procesar/Imprimir Archivo\n");
        printf("[6] Terminar Programa\n");
        printf("Seleccione una opción: ");
        scanf("%d", &opcion);

        switch (opcion) {
            case 0:
                prioridadMenorPrimero = 1 - prioridadMenorPrimero;
                printf("Prioridad cambiada a %s primero.\n", prioridadMenorPrimero ? "menor" : "mayor");
                break;
            case 1:
                mostrarColas(colaImpresion);
                break;
            case 2:
                printf("Ingrese el nombre del archivo: ");
                scanf("%s", nombreArchivo);  // Considerar el uso de fgets para evitar problemas con espacios
                printf("Ingrese el número de páginas: ");
                scanf("%d", &paginas);
                agregarArchivo(colaImpresion, nombreArchivo, paginas);
                break;
            case 3:
                eliminarArchivo(colaImpresion);
                break;
            case 4:
                eliminarTodosLosArchivos(colaImpresion);
                printf("Todos los archivos han sido eliminados.\n");
                break;
            case 5:
                procesarImprimirArchivo(colaImpresion);
                break;
            case 6:
                printf("Terminando el programa...\n");
                eliminarTodosLosArchivos(colaImpresion);
                free(colaImpresion);
                break;
            default:
                printf("Opción inválida.\n");
        }
    } while (opcion != 6);

    return 0;
}