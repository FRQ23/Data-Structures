//
// Created by Fernando Rosales on 4/29/25.
// 1299440

#include <stdio.h>
#include <stdlib.h>


/*
 * :- module(dijkstra, [dijkstra/5]).

:- use_module(library(rbtrees)).
:- use_module(library(heaps)).

add(A, B, C) :- C is A+B.

%! update_distances(+Start, +End, +NewDistance, +StateIn, -StateOut) is det.
%
%  Update the tree and heap with the new distance from Start to End if the new
%  distance is smaller than the current distance.
%
%  Non existing node in the tree means that the node has currently an infinite
%  distance to the start node.
%
%  We only consider unvisited nodes since visited nodes have already found their
%  smallest distance to the start node.
%
%  Since the minimum priority heap implementation does not implement a decrease
%  priority method, we just unconditionally add the new priority to the heap.
%  This quirk is handled in `get_unvisited_min_node/5` by only retrieving unvisited
%  nodes.
%
update_distances(Start, End, NewDistance, TreeIn-HeapIn, TreeOut-HeapOut) :-
   (  rb_lookup(End, Val, TreeIn)
   -> (  Val = unvisited(CurrentDistance, _),
         NewDistance < CurrentDistance
      -> rb_update(TreeIn, End, unvisited(NewDistance, Start), TreeOut),
         add_to_heap(HeapIn, NewDistance, End, HeapOut)
      ;  TreeIn = TreeOut,
         HeapIn = HeapOut
      )
   ;  rb_insert(TreeIn, End, unvisited(NewDistance, Start), TreeOut),
      add_to_heap(HeapIn, NewDistance, End, HeapOut)
   ).

%! get_unvisited_min_node(+Tree, +HeapIn, +Priority, +Key, -HeapOut) is det.
%
%  Retrieve the unvisited node with the minimum distance to the start node.
%
%  Since nodes can be present multiple times with different priorities, we need to
%  check that the minimum node we obtain is unvisited.
%  An unvisited node is either node in the tree or present with a value
%  `unvisited(_, _)`.
%  If it was visited, we unconditionally remove it from the heap and get the next
%  minimum node.
%
get_unvisited_min_node(Tree, HeapIn, P, K, HeapOut) :-
   get_from_heap(HeapIn, PTmp, KTmp, HeapTmp),
   (  rb_lookup(KTmp, Val, Tree)
   -> (  Val = unvisited(_, _)
      -> HeapTmp = HeapOut,
         P = PTmp, K = KTmp
      ;  get_unvisited_min_node(Tree, HeapTmp, P, K, HeapOut)
      )
   ;  HeapTmp = HeapOut,
      P = PTmp, K = KTmp
   ).

build_path(Tree, From, To, From) :-
   rb_lookup(To, visited(From), Tree).

add_to_heap_(Default, Key, HeapIn, HeapOut) :-
   add_to_heap(HeapIn, Default, Key, HeapOut).

:- meta_predicate dijkstra(+, 3, +, +, -).

%! dijkstra(+Graph, +Edge, +Start, +End, -Path) is det.
%
%  Compute the shortest Path from Start to End using the dijkstra algorithm.
%  Graph should be the S-representation of a graph as given by the `library(ugraph)`.
%
%  Implementation details:
%
%  This implementation uses a red black tree for accessing and updating distances
%  to the start node, the previous node and the fact that the node was already
%  visited or not by using the following ideas:
%
%  * non-existing nodes are unvisited nodes with infinite distances to the start node
%  * existing nodes with the `unvisited(Distance, Previous)` values are unvisited nodes
%  * existing nodes with the `visited(Previous)` values are visited nodes
%
%  A minimum heap from `library(heaps)` is used to efficiently retrieve the node with
%  the current minimum distance to the start node.
%
%  The S-representation of the graph is converted to a red black tree to efficiently get
%  the neighbours of a node.
%
dijkstra(Graph, Edge, Start, End, Path) :-
   ord_list_to_rbtree(Graph, GraphTree),
   empty_heap(Heap),
   list_to_rbtree([Start-unvisited(0, no)], TreeIn),
   dijkstra_(GraphTree, Edge, Start, End, 0, TreeIn, TreeOut, Heap),
   once(foldl(build_path(TreeOut), ReversePath, End, Start)),
   reverse([End | ReversePath], Path).

dijkstra_(Graph, Edge, Start, End, CurrentDistance, TreeIn, TreeOut, Heap) :-
   rb_lookup(Start, Neighbours, Graph),
   maplist(call(Edge, Start), Neighbours, NeighboursWeights),
   maplist(add(CurrentDistance), NeighboursWeights, NeighboursDistances),
   foldl(update_distances(Start),
         Neighbours, NeighboursDistances,
         TreeIn-Heap, Tree2-Heap2),
   rb_update(Tree2, Start, unvisited(_, StartPrev), visited(StartPrev), Tree3),
   get_unvisited_min_node(Tree3, Heap2, NextDistance, NextNode, Heap3),
   (  NextNode == End
   -> rb_update(Tree3, End, unvisited(_, EndPrev), visited(EndPrev), TreeOut)
   ;  dijkstra_(Graph, Edge, NextNode, End, NextDistance, Tree3, TreeOut, Heap3)
   ).

:- begin_tests(dijkstra).

random_directed_edge(Low, High, Start-End, Weight) :-
   random_between(Low, High, Start),
   random_between(Low, High, End),
   random_between(Low, High, Weight).

random_graph(NumNodes, NumEdges, Nodes, Edges, Weights) :-
   numlist(1, NumNodes, Nodes),
   length(Edges, NumEdges),
   maplist(random_directed_edge(1, NumNodes), Edges, Weights).

weight(Weights, From, To, Distance) :-
   rb_lookup(From-To, Distance, Weights).

random_task(Seed, N, M, Graph, plunit_dijkstra:weight(EdgesWeights), Start, End) :-
   set_random(seed(Seed)),
   random_graph(N, M, Nodes, Edges, Weights),
   vertices_edges_to_ugraph(Nodes, Edges, Graph),
   random_between(1, N, Start),
   random_between(1, N, End),
   pairs_keys_values(EdgesWeightsPairs, Edges, Weights),
   list_to_rbtree(EdgesWeightsPairs, EdgesWeights).

test("4", [true(Path =@= [1, 3, 4])]) :-
   Edges = [1-2, 2-1, 1-4, 4-1, 3-1, 1-3, 4-3, 3-4],
   Weights = [24, 24, 20, 20, 3, 3, 12, 12],
   vertices_edges_to_ugraph([], Edges, Graph),
   pairs_keys_values(EdgesWeightsPairs, Edges, Weights),
   list_to_rbtree(EdgesWeightsPairs, EdgesWeights),
   dijkstra(Graph, plunit_dijkstra:weight(EdgesWeights), 1, 4, Path).

test("random_10", [setup(random_task(0, 10, 20, Graph, Edge, Start, End))]) :-
   dijkstra(Graph, Edge, Start, End, _Path).

test("random_100000",
     [setup(random_task(2, 100000, 200000, Graph, Edge, Start, End))]) :-
   dijkstra(Graph, Edge, Start, End, _Path).

:- end_tests(dijkstra).

 */

//estructura

typedef struct{
    int id;
    int distancia;
    int padre;
} Nodo;

typedef struct{
    Nodo *nodos[1000];
    int tamano;
} ColaPrioridad;

typedef struct{
    int id;
    int peso;
} Arista;

typedef struct{
    int id;
    int distancia;
} Vertice;

typedef struct{
    Vertice *vertices[5];
    int tamano;
} Grafo;



// funcion

int **crearGrafo(int nodos, int aristas) {
    int **grafo = (int **)malloc(nodos * sizeof(int *));
    for (int i = 0; i < nodos; i++) {
        grafo[i] = (int *)malloc(nodos * sizeof(int));
        for (int j = 0; j < nodos; j++) {
            grafo[i][j] = 0;
        }
    }

    for (int i = 0; i < aristas; i++) {
        int origen, destino, peso;
        printf("Ingrese el origen, destino y peso de la arista %d: ", i + 1);
        while (scanf("%d %d %d", &origen, &destino, &peso) != 3) {
            printf("Entrada inválida. Por favor, ingrese tres números enteros.\n");
            while (getchar() != '\n'); // Limpiar el buffer de entrada
        }
        grafo[origen][destino] = peso;
        grafo[destino][origen] = peso; // Grafo no dirigido
    }

    return grafo;
}





// cola de prioridad

void inicializarCola(ColaPrioridad *cola)
{
    cola->tamano = 0;
}

void agregarCola(ColaPrioridad *cola, Nodo *nodo)
{
    cola->nodos[cola->tamano] = nodo;
    cola->tamano++;
}


void eliminarCola(ColaPrioridad *cola)
{
    if(cola->tamano == 0)
        return;
    Nodo *nodo = cola->nodos[0];
    for(int i = 0; i < cola->tamano - 1; i++)
    {
        cola->nodos[i] = cola->nodos[i + 1];
    }
    cola->tamano--;

    free(nodo);
}

Nodo *obtenerMinimo(ColaPrioridad *cola)
{
    if(cola->tamano == 0)
        return NULL;
    Nodo *minimo = cola->nodos[0];
    for(int i = 1; i < cola->tamano; i++)
    {
        if(cola->nodos[i]->distancia < minimo->distancia)
        {
            minimo = cola->nodos[i];
        }
    }
    return minimo;
}

void eliminarNodo(ColaPrioridad *cola, Nodo *nodo)
{
    for(int i = 0; i < cola->tamano; i++)
    {
        if(cola->nodos[i] == nodo)
        {
            for(int j = i; j < cola->tamano - 1; j++)
            {
                cola->nodos[j] = cola->nodos[j + 1];
            }
            cola->tamano--;
            free(nodo);
            return;
        }
    }
}


void liberarCola(ColaPrioridad *cola)
{
    for(int i = 0; i < cola->tamano; i++)
    {
        free(cola->nodos[i]);
    }
    free(cola);
}

void liberarGrafo(int **grafo, int nodos)
{
    for (int i = 0; i < nodos; i++)
    {
        free(grafo[i]);
    }
    free(grafo);
}

//djikstra


/*
 *
 *
 * dijkstra(Graph, Edge, Start, End, Path) :-
   ord_list_to_rbtree(Graph, GraphTree),
   empty_heap(Heap),
   list_to_rbtree([Start-unvisited(0, no)], TreeIn),
   dijkstra_(GraphTree, Edge, Start, End, 0, TreeIn, TreeOut, Heap),
   once(foldl(build_path(TreeOut), ReversePath, End, Start)),
   reverse([End | ReversePath], Path).

dijkstra_(Graph, Edge, Start, End, CurrentDistance, TreeIn, TreeOut, Heap) :-
   rb_lookup(Start, Neighbours, Graph),
   maplist(call(Edge, Start), Neighbours, NeighboursWeights),
   maplist(add(CurrentDistance), NeighboursWeights, NeighboursDistances),
   foldl(update_distances(Start),
         Neighbours, NeighboursDistances,
         TreeIn-Heap, Tree2-Heap2),
   rb_update(Tree2, Start, unvisited(_, StartPrev), visited(StartPrev), Tree3),
   get_unvisited_min_node(Tree3, Heap2, NextDistance, NextNode, Heap3),
   (  NextNode == End
   -> rb_update(Tree3, End, unvisited(_, EndPrev), visited(EndPrev), TreeOut)
   ;  dijkstra_(Graph, Edge, NextNode, End, NextDistance, Tree3, TreeOut, Heap3)
   ).

:- begin_tests(dijkstra).
 */


void dijkstra(int **grafo, int nodos, int origen, int destino)
{
    ColaPrioridad cola;
    inicializarCola(&cola);

    Nodo *nodo = (Nodo *)malloc(sizeof(Nodo));
    nodo->id = origen;
    nodo->distancia = 0;
    nodo->padre = -1;

    agregarCola(&cola, nodo);

    while(cola.tamano > 0)
    {
        Nodo *minimo = obtenerMinimo(&cola);
        eliminarNodo(&cola, minimo);

        if(minimo->id == destino)
        {
            printf("El camino mas corto es: %d\n", minimo->distancia);
            free(minimo);
            return;
        }

        for(int i = 0; i < nodos; i++)
        {
            if(grafo[minimo->id][i] != 0)
            {
                Nodo *nuevoNodo = (Nodo *)malloc(sizeof(Nodo));
                nuevoNodo->id = i;
                nuevoNodo->distancia = minimo->distancia + grafo[minimo->id][i];
                nuevoNodo->padre = minimo->id;

                agregarCola(&cola, nuevoNodo);
            }
        }
        free(minimo);
    }

    printf("No se encontro un camino entre %d y %d\n", origen, destino);
}

//imprimir de centro de distribucion a todos los demas puntos
int imprimirRuta(int **grafo, int nodos, int origen, int destino)
{
    printf("Ruta mas corta de %d a %d: ", origen, destino);
    for(int i = 0; i < nodos; i++)
    {
        printf("%d ", grafo[origen][i]);
    }
    printf("\n");
    return 0;
}


int main(void)
{
    int nodos, aristas;
    printf("Ingrese el numero de nodos: ");
    scanf("%d", &nodos);
    printf("Ingrese el numero de aristas: ");
    scanf("%d", &aristas);

    int **grafo = crearGrafo(nodos, aristas);

    int origen, destino;
    printf("Ingrese el nodo de origen: ");
    scanf("%d", &origen);
    printf("Ingrese el nodo de destino: ");
    scanf("%d", &destino);

    dijkstra(grafo, nodos, origen, destino);

    liberarGrafo(grafo, nodos);
    return 0;

}
