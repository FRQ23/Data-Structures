//
// Created by Fertronic on 5/7/2024.
//

#ifndef SIU_QUEUES_H
#define SIU_QUEUES_H



#include <stdio.h>
#include <stdlib.h>

typedef struct dato
{
    char *nombre;
    short int paginas;
}Dato;

typedef struct nodo
{
    Dato archivo;
    struct nodo *sig;
}Nodo;

typedef struct cola
{
    Nodo *inicio;
    Nodo *fin;
    short int cantidad_nodos;
    struct cola *sig;
}Cola;

typedef struct cola_2
{
    Cola *inicio;
    Cola *fin;
    short int cantidad_colas;
    short int prioridad;
}Cola_2;

Cola_2* inicializarColaPrincipal();
void agregarArchivo(Cola_2 *colaPrincipal);
void mostrarColaImpresion(Cola_2 *colaPrincipal);
void cambiarPrioridad(Cola_2 *colaPrincipal);
void eliminarArchivo(Cola_2 *colaPrincipal);
void eliminarTodosLosArchivos(Cola_2 *colaPrincipal);
void procesarImprimirArchivo(Cola_2 *colaPrincipal);
void liberarRecursos(Cola_2 *colaPrincipal);
Nodo* crearNodo(Dato dato);
Cola* buscarOCrearCola(Cola_2 *colaPrincipal, int paginas);
void insertarEnCola(Cola *cola, Nodo *nuevoNodo);
void mostrarArchivos(Cola *cola);
void eliminarNodo(Cola *cola);

#endif //SIU_QUEUES_H