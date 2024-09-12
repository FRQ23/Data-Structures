//
// Created by Fernando Rosales on 9/12/24.
//


#include <stdio.h>
#include <string.h>

#define LONGITUD 100

int main(void)
{
    char frase[LONGITUD];
    int cantidadPalabras = 1;

    printf("Ingresa una frase: ");
    fgets(frase, LONGITUD, stdin);

    frase[strcspn(frase, "\n")] = '\0';

    for(int i = 0; i < strlen(frase); i++)
    {
        if(frase[i] == ' ' && frase[i+1] != ' ' && frase[i+1] != '\0')
        {
            cantidadPalabras++;
        }
    }


    if (strlen(frase) == 0)
    {
        cantidadPalabras = 0;
    }

    printf("La longitud de tu frase (en cantidad de Palabras) es: %d", cantidadPalabras);


    return 0;
}