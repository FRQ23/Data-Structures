//
// Created by Fernando Rosales on 2/11/25.
//




#include<stdio.h>
#define ENTER 13
#define BACKSPACE 8
#define NEGATIVO 45
#define PUNTO 46



// Implementar una función que capture y valide números flotantes con signo.


/*
 *
 *
    Validaciones requeridas:
    - No permitir más de un punto decimal.
    - No permitir que el primer carácter sea un punto.
    - No permitir más de un signo negativo y solo al inicio.
    - Solo permitir un carácter 'E' en la notación científica.
    - No permitir que 'E' sea el primer carácter o que vaya seguido de otro 'E'.

    Se debe utilizar `getch()` o ‘getchar’ para capturar cada carácter ingresado.
 *
 *
 */



//Prototipos de funciones

int primera_validacion(int numero);
int segunda_validacion(int numero);
int tercera_validacion(int numero);
int cuarta_validacion(int numero);
int quinta_validacion(int numero);
int sexta_validacion(float numero);



// - No permitir más de un punto decimal.

int primera_validacion(int numero){



    int contador = 0;

    while(numero != ENTER){
        if(numero == PUNTO){
            contador++;
        }
        numero = getchar();
    }

    if(contador > 1){
        return 0;

}


// - No permitir que el primer carácter sea un punto.
    int segunda_validacion(int numero) {
        if (numero == PUNTO) {
            return 0;
        }
        return 1;
    }


// - No permitir más de un signo negativo y solo al inicio.

int tercera_validacion(int numero){

    if(numero == NEGATIVO){
        return 0;
    }

    return 1;

}


// - Solo permitir un carácter 'E' en la notación científica.

int cuarta_validacion(int numero) {

    int contador = 0;

    while (numero != ENTER) {
        if (numero == 'E') {
            contador++;
        }
        numero = getch();
    }

    if (contador > 1) {
        return 0;

    }
}



// - No permitir que 'E' sea el primer carácter o que vaya seguido de otro 'E'.

    int quinta_validacion(int numero) {

        if (numero == 'E') {
            return 0;
        }

        return 1;

    }



// Implementar una función de validación que garantice que el número ingresado esté dentro del
// rango permitido (3.4E-38 a 3.4E+38).

int sexta_validacion(float numero) {

        if (numero < 3.4E-38 || numero > 3.4E+38) {
            return 0;
        }
    }

        return 1;
    }


// Imprimir un mensaje de error si la entrada no es válida y permitir al usuario volver a intentarlo.







int main(void)
{

    float numero;

    while(1)
    {
        printf("Ingrese el numero: ");
        numero = getchar();


        if(primera_validacion(numero) == 0){
            printf("Error: No se permiten más de un punto decimal.\n");
            continue;
        }

        if(segunda_validacion(numero) == 0){
            printf("Error: No se permite que el primer carácter sea un punto.\n");
            continue;
        }

        if(tercera_validacion(numero) == 0){
            printf("Error: No se permite más de un signo negativo y solo al inicio.\n");
            continue;
        }

        if(cuarta_validacion(numero) == 0){
            printf("Error: Solo se permite un carácter 'E' en la notación científica.\n");
            continue;
        }

        if(quinta_validacion(numero) == 0){
            printf("Error: No se permite que 'E' sea el primer carácter o que vaya seguido de otro 'E'.\n");
            continue;
        }

        if(sexta_validacion(numero) == 0){
            printf("Error: El número ingresado no está dentro del rango permitido (3.4E-38 a 3.4E+38).\n");
            continue;
        }

        printf("El número ingresado es válido.\n");
        break;
    }
    return 0;
}