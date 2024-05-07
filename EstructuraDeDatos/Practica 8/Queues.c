//
// Created by Fertronic on 5/7/2024.
//

#include "Queues.h"


//funciones incializadoras

// Inicializar la cola principal
Cola_2* inicializarColaPrincipal() {
    Cola_2 *colaPrincipal = (Cola_2*) malloc(sizeof(Cola_2));
    if (colaPrincipal == NULL) {
        perror("Error al crear la cola principal");
        exit(EXIT_FAILURE);
    }
    colaPrincipal->inicio = colaPrincipal->fin = NULL;
    colaPrincipal->cantidad_colas = 0;
    colaPrincipal->prioridad = 0; // Menor cantidad de paginas primero
    return colaPrincipal;
}

// Liberar todos los recursos
void liberarRecursos(Cola_2 *colaPrincipal) {
    Cola *actual = colaPrincipal->inicio;
    while (actual != NULL) {
        Cola *temp = actual;
        actual = actual->sig;
        Nodo *nodoActual = temp->inicio;
        while (nodoActual != NULL) {
            Nodo *tempNodo = nodoActual;
            nodoActual = nodoActual->sig;
            free(tempNodo);
        }
        free(temp);
    }
    free(colaPrincipal);
    printf("Todos los recursos han sido liberados.\n");
}




// Funcion para crear un nodo nuevo
Nodo* crearNodo(Dato dato) {
    Nodo *nuevoNodo = (Nodo*) malloc(sizeof(Nodo));
    if (nuevoNodo == NULL) {
        perror("Error al crear nodo");
        exit(EXIT_FAILURE);
    }
    nuevoNodo->archivo = dato;
    nuevoNodo->sig = NULL;
    return nuevoNodo;
}

// Función para buscar o crear una cola basada en el número de páginas del archivo
Cola* buscarOCrearCola(Cola_2 *colaPrincipal, int paginas) {
    Cola *actual = colaPrincipal->inicio;
    Cola *anterior = NULL;

    // Este bucle busca una cola con el mismo número de páginas
    while (actual != NULL && actual->cantidad_nodos != paginas) {
        anterior = actual;
        actual = actual->sig;
    }

    // Si no se encuentra una cola, crea una nueva
    if (actual == NULL) {
        Cola *nuevaCola = (Cola*) malloc(sizeof(Cola));
        if (nuevaCola == NULL) {
            perror("Error al crear cola");
            exit(EXIT_FAILURE);
        }
        nuevaCola->inicio = nuevaCola->fin = NULL;
        nuevaCola->cantidad_nodos = paginas;  // Asigna el número de páginas correctamente
        nuevaCola->sig = NULL;

        // Conectar la nueva cola a la lista de colas
        if (anterior == NULL) {
            colaPrincipal->inicio = nuevaCola;
        } else {
            anterior->sig = nuevaCola;
        }
        if (colaPrincipal->fin == NULL || anterior == colaPrincipal->fin) {
            colaPrincipal->fin = nuevaCola;
        }
        colaPrincipal->cantidad_colas++;
        return nuevaCola;
    }
    return actual;
}



// Insertar un nuevo nodo en la cola

void insertarEnCola(Cola *cola, Nodo *nuevoNodo) {
    if (cola->inicio == NULL) {
        cola->inicio = cola->fin = nuevoNodo; // Si la cola está vacía
    } else {
        cola->fin->sig = nuevoNodo;  // Añade el nodo al final de la cola
        cola->fin = nuevoNodo;       // Actualiza el fin de la cola
    }
}


// Mostrar los archivos en una cola

void mostrarArchivos(Cola *cola) {
    Nodo *actual = cola->inicio;
    while (actual != NULL) {
        printf("Archivo: %s, Paginas: %d\n", actual->archivo.nombre, actual->archivo.paginas);
        actual = actual->sig;
    }
}

void eliminarNodo(Cola *cola) {
    Nodo *temp = cola->inicio;
    cola->inicio = cola->inicio->sig;
    if (cola->inicio == NULL) {
        cola->fin = NULL;
    }
    free(temp);
    cola->cantidad_nodos--;
}



//funciones del menú

// Mostrar todos los archivos en todas las colass
void mostrarColaImpresion(Cola_2 *colaPrincipal) {
    Cola *actual = colaPrincipal->inicio;
    while (actual != NULL) {
        printf("Cola para archivos con %d página(s):\n", actual->cantidad_nodos);
        Nodo *nodoActual = actual->inicio;
        while (nodoActual != NULL) {
            printf(" - %s (%d páginas)\n", nodoActual->archivo.nombre, nodoActual->archivo.paginas);
            nodoActual = nodoActual->sig;
        }
        actual = actual->sig;
    }
}


// Cambiar la prioridad de impresion
void cambiarPrioridad(Cola_2 *colaPrincipal) {
    colaPrincipal->prioridad = !colaPrincipal->prioridad;
    printf("Prioridad de impresion cambiada a %s.\n", colaPrincipal->prioridad ? "mayor primero" : "menor primero");
}


void agregarArchivo(Cola_2 *colaPrincipal) {
    Dato nuevoDato;
    printf("Ingrese el nombre del archivo: ");
    scanf("%s", nuevoDato.nombre);
    printf("Ingrese el número de paginas del archivo: ");
    scanf("%hd", &nuevoDato.paginas);

    Nodo *nuevoNodo = crearNodo(nuevoDato); // Utiliza la funcion crearNodo para preparar el nuevo archivo
    if (nuevoNodo == NULL) {
        printf("Error al crear un nuevo nodo.\n");
        return;
    }

    Cola *colaCorrespondiente = buscarOCrearCola(colaPrincipal, nuevoDato.paginas); // Encuentra la cola adecuada para este archivo
    if (colaCorrespondiente == NULL) {
        printf("Error al buscar o crear la cola correspondiente.\n");
        free(nuevoNodo); // No olvides liberar memoria si no vas a usar el nodo
        return;
    }

    insertarEnCola(colaCorrespondiente, nuevoNodo); // Inserta el nodo en la cola correcta
    printf("Archivo '%s' agregado correctamente.\n", nuevoDato.nombre);
}


// Eliminar un archivo específico
void eliminarArchivo(Cola_2 *colaPrincipal) {
    int paginas;
    printf("Ingrese el número de paginas del archivo a eliminar: ");
    scanf("%d", &paginas);
    Cola *cola = buscarOCrearCola(colaPrincipal, paginas);
    if (cola != NULL && cola->inicio != NULL) {
        Nodo *temp = cola->inicio;
        cola->inicio = cola->inicio->sig;
        if (cola->inicio == NULL) {
            cola->fin = NULL;
        }
        free(temp);
        printf("Archivo eliminado.\n");
    } else {
        printf("No se encontro el archivo con ese número de paginas.\n");
    }
}

// Eliminar todos los archivos
void eliminarTodosLosArchivos(Cola_2 *colaPrincipal) {
    Cola *actual = colaPrincipal->inicio;
    while (actual != NULL) {
        Cola *temp = actual;
        actual = actual->sig;
        Nodo *nodoActual = temp->inicio;
        while (nodoActual != NULL) {
            Nodo *tempNodo = nodoActual;
            nodoActual = nodoActual->sig;
            free(tempNodo);
        }
        free(temp);
    }
    colaPrincipal->inicio = colaPrincipal->fin = NULL;
    colaPrincipal->cantidad_colas = 0;
    printf("Todos los archivos han sido eliminados.\n");
}


// Procesar/Imprimir el archivo de mayor o menor prioridad
void procesarImprimirArchivo(Cola_2 *colaPrincipal) {
    if (colaPrincipal->inicio == NULL) {
        printf("No hay archivos para procesar.\n");
        return;
    }
    Cola *actual = colaPrincipal->inicio, *seleccionada = actual;
    if (colaPrincipal->prioridad) { // Mayor cantidad de paginas primero
        while (actual != NULL) {
            if (actual->cantidad_nodos > seleccionada->cantidad_nodos) {
                seleccionada = actual;
            }
            actual = actual->sig;
        }
    } else { // Menor cantidad de paginas primero
        while (actual != NULL) {
            if (actual->cantidad_nodos < seleccionada->cantidad_nodos) {
                seleccionada = actual;
            }
            actual = actual->sig;
        }
    }
    if (seleccionada != NULL && seleccionada->inicio != NULL) {
        Nodo *temp = seleccionada->inicio;
        printf("Procesando archivo: %s, Paginas: %d\n", temp->archivo.nombre, temp->archivo.paginas);
        seleccionada->inicio = seleccionada->inicio->sig;
        if (seleccionada->inicio == NULL) {
            seleccionada->fin = NULL;
        }
        free(temp);
    }
}






int main() {
    Cola_2 *colaPrincipal = inicializarColaPrincipal();
    int opcion;
    do {
        printf("[0] CAMBIAR PRIORIDAD\n[1] MOSTRAR COLA DE IMPRESIoN\n[2] AGREGAR ARCHIVO\n[3] ELIMINAR ARCHIVO\n[4] ELIMINAR TODOS LOS ARCHIVOS\n[5] PROCESAR/IMPRIMIR ARCHIVO\n[6] TERMINAR PROGRAMA\nSeleccione una opcion: ");
        scanf("%d", &opcion);
        switch(opcion) {
            case 0:
                cambiarPrioridad(colaPrincipal);
                break;
            case 1:
                mostrarColaImpresion(colaPrincipal);
                break;
            case 2:
                agregarArchivo(colaPrincipal);
                break;
            case 3:
                eliminarArchivo(colaPrincipal);
                break;
            case 4:
                eliminarTodosLosArchivos(colaPrincipal);
                break;
            case 5:
                procesarImprimirArchivo(colaPrincipal);
                break;
            case 6:
                liberarRecursos(colaPrincipal);
                printf("Programa terminado.\n");
                break;
            default:
                printf("Opcion no valida.\n");
        }
    } while(opcion != 6);
    return 0;
}