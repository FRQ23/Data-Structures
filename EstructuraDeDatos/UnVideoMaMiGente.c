//
// Created by Fertronic on 8/21/2024.
//
/*
Realiza un programa que contenga un menú de 3 opciones. Estas opciones serán 1, 2 y 3. Si el usuario introduce el número 0, el programa acabará, pero mientras elija una opción válida que no sea el 0 el programa debe seguir.

Estaría bien que si introduce una opción que no sea del menú, o sea, ni 1, ni 2, ni 3, el programa te avisara.

Es decir, que el resultado del programa tiene que ser como se aprecia en el vídeo en la parte inferior de la lección.
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int main() {
    int opcion;
    while(true)
    {
        switch (opcion)
        {
            case 0:
                printf("Saliendo del programa...\n");
                return 0;

            case 1:
                printf("Opción 1 seleccionada\n");
                break;
            case 2:
                printf("Opción 2 seleccionada\n")

        }
    }

}

