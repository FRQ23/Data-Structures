//
// Created by Fertronic on 2/29/2024.
//

#include <stdio.h>
#include <stdlib.h>

typedef struct Pila{
    int tope;
    int lista[100];
}Pila;


Pila crearPila();

int isEmpty(Pila);

void push(Pila*, int);

int pop(Pila*);

int top(Pila);

Pila crearPila(){

    Pila p;
    p.tope = 0;
    return p;

}

int isEmpty(Pila p){

    if(p.tope == 0)
        return 1;
    return 0;
}

void push(Pila*p, int x){

    p->lista[p->tope] = x;
    p->tope++;

}

int pop(Pila* p){

    if (isEmpty(*p) ==1){
        printf("\nLa pila ya esta vacia");
        return -1;
    }else{
        int aux = p->lista[p->tope-1];
        p->tope--;
        return aux;
    }
}

int top(Pila p){

    if(isEmpty(p)==1){
        printf("\n La pila ya esta vacia");
        return -1;

    }else{

        return p.lista[p.tope-1];
    }
}

