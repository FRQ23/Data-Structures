// Created by Fernando Rosales on 4/29/25.
// 1299440

/*
 * Equivalente Prolog (tu módulo dijkstra.pl):
 *
 * :- module(dijkstra, [dijkstra/5]).
 *
 * :- use_module(library(rbtrees)).
 * :- use_module(library(heaps)).
 *
 * add(A, B, C) :- C is A+B.
 *
 * update_distances(Start, End, NewDistance, TreeIn-HeapIn, TreeOut-HeapOut) :-
 *    ... % igual que tu definición: rb_lookup, rb_update, add_to_heap
 *
 * get_unvisited_min_node(Tree, HeapIn, P, K, HeapOut) :-
 *    ... % extrae del heap hasta encontrar unvisited
 *
 * dijkstra(Graph, Edge, Start, End, Path) :-
 *    ord_list_to_rbtree(Graph, GraphTree),
 *    empty_heap(Heap),
 *    list_to_rbtree([Start-unvisited(0, no)], TreeIn),
 *    dijkstra_(GraphTree, Edge, Start, End, 0, TreeIn, TreeOut, Heap),
 *    once(foldl(build_path(TreeOut), ReversePath, End, Start)),
 *    reverse([End | ReversePath], Path).
 *
 * dijkstra_(Graph, Edge, Start, End, CurrentDistance, TreeIn, TreeOut, Heap) :-
 *    rb_lookup(Start, Neighbours, Graph),
 *    maplist(call(Edge, Start), Neighbours, NeighboursWeights),
 *    maplist(add(CurrentDistance), NeighboursWeights, NeighboursDistances),
 *    foldl(update_distances(Start), Neighbours, NeighboursDistances, TreeIn-Heap, Tree2-Heap2),
 *    rb_update(Tree2, Start, unvisited(_, StartPrev), visited(StartPrev), Tree3),
 *    get_unvisited_min_node(Tree3, Heap2, NextDistance, NextNode, Heap3),
 *    ( NextNode == End
 *    -> rb_update(Tree3, End, unvisited(_, EndPrev), visited(EndPrev), TreeOut)
 *    ;  dijkstra_(Graph, Edge, NextNode, End, NextDistance, Tree3, TreeOut, Heap3)
 *    ).
 *
 * build_path(Tree, From, To, From) :- rb_lookup(To, visited(From), Tree).
 *
 * % Tests omitted...
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 * :- module(dijkstra, [dijkstra/5]).
 *
 * Prolog implementation overview (para referencia):
 *
 * update_distances(Start, End, NewDistance, TreeIn-HeapIn, TreeOut-HeapOut) :-
 *    \+ visita nodos ya procesados, actualiza distancia si NewDistance < Current
 *
 * get_unvisited_min_node(Tree, HeapIn, P, K, HeapOut) :-
 *    retira del heap el nodo no visitado de menor prioridad
 *
 * dijkstra(Graph, Edge, Start, End, Path) :-
 *    inicializa estructuras y llama a dijkstra_ recursivo
 *
 * dijkstra_(Graph, Edge, Start, End, CurrDist, TreeIn, TreeOut, Heap) :-
 *    procesa vecinos de Start, actualiza distancias, marca Start como visitado,
 *    extrae NextNode mínimo y recursa hasta End
 */

// === Estructuras y funciones de cola de prioridad (equivalente a heap y árboles en Prolog) ===

typedef struct{
    int id;
    int distancia;
    int padre;
} Nodo;

typedef struct{
    Nodo **nodos;
    int tamano;
    int capacidad;
} ColaPrioridad;

// inicializarCola <-> empty_heap/1 en Prolog
void inicializarCola(ColaPrioridad *cola, int capacidad) {
    cola->nodos = malloc(sizeof(Nodo*) * capacidad);
    cola->tamano = 0;
    cola->capacidad = capacidad;
}

// heapifyUp e heapifyDown <-> lógica interna del heap de Prolog
void swapNodo(Nodo **a, Nodo **b) {
    Nodo *tmp = *a; *a = *b; *b = tmp;
}

void heapifyUp(ColaPrioridad *cola, int idx) {
    if(idx <= 0) return;
    int parent = (idx - 1) / 2;
    if(cola->nodos[idx]->distancia < cola->nodos[parent]->distancia) {
        swapNodo(&cola->nodos[idx], &cola->nodos[parent]);
        heapifyUp(cola, parent);
    }
}

void heapifyDown(ColaPrioridad *cola, int idx) {
    int left = 2*idx + 1, right = 2*idx + 2, smallest = idx;
    if(left < cola->tamano && cola->nodos[left]->distancia < cola->nodos[smallest]->distancia)
        smallest = left;
    if(right < cola->tamano && cola->nodos[right]->distancia < cola->nodos[smallest]->distancia)
        smallest = right;
    if(smallest != idx) {
        swapNodo(&cola->nodos[idx], &cola->nodos[smallest]);
        heapifyDown(cola, smallest);
    }
}

// eliminarMinimo <-> get_unvisited_min_node/5 + get_from_heap/3 en Prolog
Nodo *eliminarMinimo(ColaPrioridad *cola) {
    if(cola->tamano == 0) return NULL;
    Nodo *min = cola->nodos[0];
    cola->nodos[0] = cola->nodos[--cola->tamano];
    heapifyDown(cola, 0);
    return min;
}

// agregarCola <-> add_to_heap/4 en Prolog
void agregarCola(ColaPrioridad *cola, Nodo *nodo) {
    if(cola->tamano == cola->capacidad) return;
    cola->nodos[cola->tamano++] = nodo;
    heapifyUp(cola, cola->tamano - 1);
}

// liberarCola <-> cleanup de estructuras en Prolog
void liberarCola(ColaPrioridad *cola) {
    for(int i = 0; i < cola->tamano; i++) free(cola->nodos[i]);
    free(cola->nodos);
}

// === Implementación de Dijkstra en C (paralela a dijkstra_/6 en Prolog) ===
void dijkstra(int **grafo, int nodos, int origen, int *dist, int *padre) {
    int INF = 1000000000;
    for(int i = 0; i < nodos; i++) { dist[i] = INF; padre[i] = -1; }
    dist[origen] = 0;

    ColaPrioridad cola;
    inicializarCola(&cola, nodos * nodos);
    Nodo *start = malloc(sizeof(Nodo));
    start->id = origen; start->distancia = 0; start->padre = -1;
    agregarCola(&cola, start);

    while(cola.tamano > 0) {
        Nodo *u = eliminarMinimo(&cola);  // obtiene u de menor distancia
        if(!u) break;
        int uid = u->id, udist = u->distancia;
        free(u);
        if(udist > dist[uid]) continue;   // ignora entradas obsoletas

        // recorre vecinos de uid: equivalente al maplist y foldl en Prolog
        for(int v = 0; v < nodos; v++) {
            if(grafo[uid][v] > 0) {
                int alt = dist[uid] + grafo[uid][v];
                if(alt < dist[v]) {
                    dist[v] = alt;
                    padre[v] = uid;
                    Nodo *nv = malloc(sizeof(Nodo));
                    nv->id = v; nv->distancia = alt; nv->padre = uid;
                    agregarCola(&cola, nv);
                }
            }
        }
    }
    liberarCola(&cola);
}

// reconstruir ruta (simula foldl(build_path) + reverse en Prolog)
char *rutaCadena(int *padre, int destino, char **nombres) {
    char temp[1024] = "";
    int stack[1000], top = 0, u = destino;
    while(u != -1) { stack[top++] = u; u = padre[u]; }
    for(int i = top-1; i >= 0; i--) {
        strcat(temp, nombres[stack[i]]);
        if(i > 0) strcat(temp, " -> ");
    }
    return strdup(temp);
}

// === Construcción del grafo como matriz de adyacencia ===
int **crearGrafo(int nodos) {
    int **grafo = malloc(nodos * sizeof(int*));
    for(int i = 0; i < nodos; i++) grafo[i] = calloc(nodos, sizeof(int));
    return grafo;
}
void liberarGrafo(int **grafo, int nodos) {
    for(int i = 0; i < nodos; i++) free(grafo[i]); free(grafo);
}
int indiceNodo(char *nombre, char **nombres, int nodos) {
    for(int i = 0; i < nodos; i++) if(strcmp(nombre, nombres[i])==0) return i;
    return -1;
}

int main() {
    int nodos, aristas;
    printf("Ingrese el numero de ubicaciones: "); scanf("%d", &nodos);
    char **nombres = malloc(nodos * sizeof(char*));
    for(int i = 0; i < nodos; i++) {
        nombres[i] = malloc(50);
        printf("Nombre de ubicacion %d: ", i+1);
        scanf("%s", nombres[i]);
    }
    printf("Ingrese el numero de rutas: "); scanf("%d", &aristas);

    int **grafo = crearGrafo(nodos);
    printf("Ingrese las rutas (origen destino distancia):\n");
    for(int i = 0; i < aristas; i++) {
        char a[50], b[50]; int peso;
        scanf("%s %s %d", a, b, &peso);
        int u = indiceNodo(a,nombres,nodos), v = indiceNodo(b,nombres,nodos);
        if(u<0||v<0) { printf("Nodo no encontrado.\n"); i--; continue; }
        if(grafo[u][v]!=0) { printf("Ruta ya ingresada.\n"); i--; continue; }
        grafo[u][v]=peso; grafo[v][u]=peso;  // bidireccional
    }

    char origenName[50];
    printf("Centro de distribucion: "); scanf("%s", origenName);
    int origen = indiceNodo(origenName,nombres,nodos);
    if(origen<0){ printf("Centro invalido.\n"); return 1; }

    int *dist = malloc(nodos*sizeof(int));
    int *padre = malloc(nodos*sizeof(int));
    dijkstra(grafo,nodos,origen,dist,padre);

    printf("\nRutas mas cortas desde %s:\n",nombres[origen]);
    for(int i=0;i<nodos;i++){
        if(i==origen) continue;
        if(dist[i]>=1000000000) printf("%s inalcanzable\n",nombres[i]);
        else{
            char *ruta = rutaCadena(padre,i,nombres);
            printf("Ruta mas corta de %s a %s: %s (%d unidades)\n", 
                   nombres[origen],nombres[i],ruta,dist[i]);
            free(ruta);
        }
    }
    for(int i=0;i<nodos;i++) free(nombres[i]); free(nombres);
    free(dist); free(padre); liberarGrafo(grafo,nodos);
    return 0;
}
