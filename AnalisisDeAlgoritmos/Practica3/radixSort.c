#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NUM_REGISTROS 8

typedef struct {
    char placa[20];
    char marca[20];
    char modelo[20];
    int anio;
    int multa;
    char infraccion[100];
    char fecha[15];
} Vehiculo;

// Función de comparación para qsort basada en el valor ASCII de la placa
int compararPlacas(const void *a, const void *b) {
    Vehiculo *vehiculoA = (Vehiculo *)a;
    Vehiculo *vehiculoB = (Vehiculo *)b;
    return strcmp(vehiculoA->placa, vehiculoB->placa);
}

// Función para calcular el valor total basado en el valor ASCII de cada carácter de una cadena
int calcularValorASCII(const char *str) {
    int suma = 0;
    while (*str) {
        suma += (unsigned char)*str;
        str++;
    }
    return suma;
}

int main() {
    Vehiculo vehiculos[NUM_REGISTROS] = {
        {"A59-NZC-6", "Honda", "Civic", 2020, 500, "Exceso de velocidad.", "08/03/2023"},
        {"EJM-47-40", "Nissan", "Pathfinder", 2018, 600, "Conducir en estado de ebriedad.", "07/03/2019"},
        {"3-MM-778", "Suzuki", "Scross", 2021, 400, "Voltear en U.", "02/09/2024"},
        {"257-NWD-8", "Honda", "Accord", 2022, 700, "Conducir con dispositivo.", "02/01/2024"},
        {"AHA-50-15", "Mazda", "Sedán", 2019, 300, "Verificación expirada.", "03/07/2020"},
        {"YBU-80-66", "Suzuki", "Ignis", 2021, 450, "Estacionarse en doble fila.", "05/05/2021"},
        {"EMN-71-71", "Nissan", "Versa", 2020, 300, "Conducir sin licencia.", "24/12/2018"},
        {"C87-NRL-7", "Kia", "Optima", 2050, 1000000, "prueba.", "15/12/2004"}


    };

    // Ordenar el arreglo por la placa
    qsort(vehiculos, NUM_REGISTROS, sizeof(Vehiculo), compararPlacas);

    // Imprimir los resultados ordenados
    for (int i = 0; i < NUM_REGISTROS; i++) {
        int valorASCII = calcularValorASCII(vehiculos[i].placa);
        printf("Placa: %s (Valor ASCII Total: %d), Marca: %s, Modelo: %s, Año: %d, Multa: %d, Infracción: %s, Fecha: %s\n",
               vehiculos[i].placa, valorASCII, vehiculos[i].marca, vehiculos[i].modelo, vehiculos[i].anio,
               vehiculos[i].multa, vehiculos[i].infraccion, vehiculos[i].fecha);
    }

    return 0;
}
