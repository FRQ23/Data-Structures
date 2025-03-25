//
// Created by Fernando Rosales on 3/4/25.
//


/*
 * Implementar un algoritmo de fuerza bruta en C que pruebe todas las combinaciones posibles
 * de una contraseña de 4 caracteres, donde los caracteres pueden ser cualquier vocal (a, e, i, o,
 * u) o cualquier dígito (0-9). El programa deberá encontrar una contraseña secreta predefinida.
 *
 */



/*
 * Longitud de la contraseña: 4 caracteres
*/

/*
 * Caracteres posibles: 0-9, a, e, i, o, u
 */

/*
 * Definir la contraseña secreta
 */

#include <stdio.h>
#include <string.h>
#include <stdbool.h>

// Prototipos de funciones
void buscarContrasena(char *str, char *contrasena, char *intento, int pos, int longitud, bool *encontrada);

// Definicion de la contraseña
char contrasena[5] = "9999";
int contador = 0;

void buscarContrasena(char *str, char *contrasena, char *intento, int pos, int longitud, bool *encontrada) {
    if (*encontrada) return; // Detener la recursion si la contraseña ya fue encontrada

    if (pos == longitud) {
        intento[pos] = '\0';
        contador++;
        printf("Intento: %s\n", intento);
        if (strcmp(intento, contrasena) == 0) {
            printf("La contraseña es: %s\n", intento);
            printf("Numero de intentos: %d\n", contador);
            *encontrada = true;
        }
        return;
    } else {
        for (int i = 0; i < strlen(str); i++) {
            if (*encontrada) return;
            intento[pos] = str[i];
            buscarContrasena(str, contrasena, intento, pos + 1, longitud, encontrada);
        }
    }
}

int main(void) {
    char str[] = "aeiou0123456789";
    char intento[5];
    bool encontrada = false;
    buscarContrasena(str, contrasena, intento, 0, 4, &encontrada);
    return 0;
}