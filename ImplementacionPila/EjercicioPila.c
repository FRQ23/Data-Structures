//
// Created by Fertronic on 2/29/2024.
//

#include "Pila.h"

int main(){

    //creamos tres pilas con funcion crear pila

    Pila PilaUsuario = crearPila();
    Pila PilaMenor = crearPila();
    Pila PilaAuxiliar = crearPila();

    //crear bucle para agregar los valores al apila Usuario

    for(int i = 0; i < 8; ++i){

        int valor;
        printf("Escribe el valor [%d] de la pila: \n", i);
        scanf("%d", &valor);
        fflush(stdin);
        push(&PilaUsuario, valor);

    }

    //Determinar el menor de los datos ingresados por el usuario

    while(isEmpty(PilaUsuario)==0){

        push(&PilaMenor, pop(&PilaUsuario));
        while(isEmpty(PilaUsuario)==0){

            if(top(PilaUsuario)>top(PilaMenor)){
                push(&PilaAuxiliar, pop(&PilaUsuario));

            }else{

                push(&PilaAuxiliar, pop(&PilaMenor));
                push(&PilaMenor, pop(&PilaUsuario));
            }
        }

    }

    printf("El valor menor de los ingresados es el %d\n", pop(&PilaMenor));

    return 0;
}