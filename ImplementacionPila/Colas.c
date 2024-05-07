//
// Created by Fertronic on 4/12/2024.
//


#include <stdio.h>
#include <stdlib.h>

typedef struct tNodo{
    int valor;
    struct tNodo *sig;
}Nodo;

typedef struct tCola{
    int tamanio;
    Nodo *frontal;
    Nodo *final;
}Cola;

Nodo* crearNodo(int valor){
    Nodo *nodo = (Nodo*)malloc(sizeof(Nodo));
    nodo->valor = valor;
    nodo->sig = NULL;
    return nodo;
}

Cola *crearColas()
{
    Cola* n = (Cola*)malloc(sizeof(Cola));
    n->tamanio = 0;
    n->frontal = NULL;
    n->final = NULL;
    return n;
}


void encolar(Cola* n, Nodo* nodo){
    if(n->frontal == NULL) n->frontal = nodo;
    else n->final->sig = nodo;
    n->final = nodo;
    n->tamanio++;




}

int desencolar(Cola* n){
    if (n->tamanio){
        int returnValue;
        Nodo* aux = aux->valor;
        returnValue = aux->valor;
        n->frontal = n->frontal->sig;
        free(aux);
        n->tamanio--;
        return returnValue;
    }
    return -1; //indicado de que no hay elementos

}

int main(){

    Cola* COLA = crearColas();
    Nodo* a = crearNodo(1);
    Nodo* b = crearNodo(2);
    Nodo* c = crearNodo(3);
    Nodo* d = crearNodo(4);

    encolar(COLA, a);
    encolar(COLA, b);
    encolar(COLA, c);

    printf("\n %d", desencolar(COLA));
    printf("\n %d", desencolar(COLA));
    printf("\n %d", desencolar(COLA));

    free(COLA);
}