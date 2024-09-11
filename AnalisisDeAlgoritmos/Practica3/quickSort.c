#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NUM_REGISTROS 8

typedef struct {
    char placa[15];
    char marca[20];
    char modelo[20];
    int anio;
    int multa;
    char motivo[50];
    char fecha[11];  // Fecha en formato DD/MM/YYYY
} Vehiculo;

// Función para intercambiar dos vehículos
void intercambiar(Vehiculo *a, Vehiculo *b) {
    Vehiculo temp = *a;
    *a = *b;
    *b = temp;
}

// Función para convertir una fecha en formato DD/MM/YYYY a un valor entero para comparación
int convertirFechaAEntero(const char *fecha) {
    int dia, mes, anio;
    sscanf(fecha, "%d/%d/%d", &dia, &mes, &anio);
    return (anio * 10000) + (mes * 100) + dia;
}

// Función de partición para Quick Sort
int particionar(Vehiculo vehiculos[], int bajo, int alto) {
    int pivote = convertirFechaAEntero(vehiculos[alto].fecha);
    int i = bajo - 1;

    for (int j = bajo; j < alto; j++) {
        if (convertirFechaAEntero(vehiculos[j].fecha) < pivote) {
            i++;
            intercambiar(&vehiculos[i], &vehiculos[j]);
        }
    }
    intercambiar(&vehiculos[i + 1], &vehiculos[alto]);
    return i + 1;
}

// Función de Quick Sort
void quickSort(Vehiculo vehiculos[], int bajo, int alto) {
    if (bajo < alto) {
        int indiceParticion = particionar(vehiculos, bajo, alto);
        quickSort(vehiculos, bajo, indiceParticion - 1);
        quickSort(vehiculos, indiceParticion + 1, alto);
    }
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

    // Ordenar las infracciones por fecha en orden ascendente usando Quick Sort
    quickSort(vehiculos, 0, NUM_REGISTROS - 1);

    // Imprimir el resultado ordenado
    printf("Infracciones ordenadas por fecha (ascendente):\n");
    for (int i = 0; i < NUM_REGISTROS; i++) {
        printf("Placa: %s, Marca: %s, Modelo: %s, Año: %d, Multa: %d, Motivo: %s, Fecha: %s\n",
               vehiculos[i].placa, vehiculos[i].marca, vehiculos[i].modelo, 
               vehiculos[i].anio, vehiculos[i].multa, vehiculos[i].motivo, vehiculos[i].fecha);
    }

    return 0;
}
