/*
 *  Alumno: Fernando Rosales Quiñones
 *  Matricula: 1299440
 */



/*

Requisitos:
- Implementar el algoritmo de búsqueda binaria en lenguaje C
- Crear una lista ordenada de al menos 20 elementos con información simulada, por ejemplo:
-Lista de estudiantes con su número de matrícula y nombre.
-Inventario de productos con código y descripción.
-Permitir que el usuario ingrese un valor para buscar en la base de datos.
- Usar búsqueda binaria para localizar el elemento y mostrar la información completa del
        registro si se encuentra, o un mensaje de “No encontrado” si no existe.
-Implementar un menú con las siguientes opciones:
Buscar un registro (ingresando un número de matrícula/código).
Mostrar toda la base de datos ordenada.
Salir del programa.

*/

#include <stdio.h>
#include <stdlib.h>

// lista (structura de estudiantes).

typedef struct {
    int matricula;
    char nombre[50];
} Estudiante;

// Prototipos de funciones

void buscarRegistro(int matricula);
void mostrarDatosOrdenados();


// 20 elementos en la lista

Estudiante estudiantes[20] = {
    {220044, "Chalino Sanchez"},
    {443322, "Francisca Viveros"},
    {1199440, "Gonzalo Garcia"},
    {1234567, "Luis Perez"},
    {1299440, "Fernando Rosales"},
    {1299550, "Marcos Reyes"},
    {1313131, "Gusgri Vlogs "},
    {1834025, "Alejandro Lopez"},
    {1940123, "Vicente Fernandez"},
    {1960054, "Gerardo Legarreta"},
    {1990739, "David Canovas"},
    {2000456, "Marta Diaz"},
    {2024063, "Claudia Sheinbaum"},
    {2200304, "Emiliano Herrera"},
    {6748291, "Daniel Bisogno"},
    {6749204, "Patricia Perez"},
    {7654321, "Wismichu Martinez"},
    {7777777, "Jose Lagunas"},
    {9030503, "Raul Jimenez"},
    {9944001, "Dalas Jimenez"}
};



void buscarRegistro(int matricula){
    int inicio = 0;
    int medio;
    int fin = 19;

    while (inicio <= fin){
        medio = (inicio + fin) / 2;

        if (estudiantes[medio].matricula == matricula)
        {
            printf("La matricula es: %d y el nombre es %s \n", estudiantes[medio].matricula, estudiantes[medio].nombre);
            return;
        } else if (estudiantes[medio].matricula <matricula)
        {
            inicio = medio + 1;
        } else
        {
            fin = medio - 1;
        }

    }

    printf("no se ha encontrado un aulumno con esa matricula (%d) \n", matricula);
}

void mostrarDatosOrdenados() {
    for (int i = 0; i < 20; i++) {
        printf("la matricula es  %d y el nombre es %s\n", estudiantes[i].matricula, estudiantes[i].nombre);
    }
}



int main(void) {
    int opcion, matricula = 0;

    while (opcion != 3)
    {
        printf("1. Buscar un alumno por matricula. \n");
        printf("2. Mostrar la base de datos. \n");
        printf("3. Salir. \n");
        scanf("%d", &opcion);

        switch(opcion)
        {
            case 1:
                printf("Ingrese la matricula: ");
                scanf("%d", &matricula);
                buscarRegistro(matricula);
                break;
            case 2:
                mostrarDatosOrdenados();
                break;
            case 3:
                printf("bye bye");
                break;
            default:
                printf("Ingrese una opcion valida.");

        }

    }


}