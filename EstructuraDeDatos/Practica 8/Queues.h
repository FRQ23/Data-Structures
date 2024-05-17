#ifndef QUEUES_H
#define QUEUES_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
}Cola_2;


typedef struct archivo_info {
    char *nombre;
    int paginas;
} ArchivoInfo;


void vaciarCola(Cola* cola);
void eliminarCola(Cola_2* cola2, Cola* cola);
Cola_2* crearCola_2();


#endif