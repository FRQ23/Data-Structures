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
    char fecha[11];
} Vehiculo;

// Función para intercambiar dos vehículos
void intercambiar(Vehiculo *a, Vehiculo *b) {
    Vehiculo temp = *a;
    *a = *b;
    *b = temp;
}

// Función para ordenar los vehículos por marca y modelo en orden descendente usando Shell Sort
void shellSort(Vehiculo vehiculos[], int n) {
    int gap, i, j;
    Vehiculo temp;

    // Inicializa el intervalo
    for (gap = n / 2; gap > 0; gap /= 2) {
        // Realiza un sort de inserción con el intervalo dado
        for (i = gap; i < n; i++) {
            temp = vehiculos[i];
            j = i;
            
            // Compara primero por marca, luego por modelo, ambos en orden descendente
            while (j >= gap && (strcmp(vehiculos[j - gap].marca, temp.marca) < 0 ||
                (strcmp(vehiculos[j - gap].marca, temp.marca) == 0 &&
                 strcmp(vehiculos[j - gap].modelo, temp.modelo) < 0))) {
                vehiculos[j] = vehiculos[j - gap];
                j -= gap;
            }
            vehiculos[j] = temp;
        }
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

    // Ordenar las infracciones por marca y modelo en orden descendente usando Shell Sort
    shellSort(vehiculos, NUM_REGISTROS);

    // Imprimir el resultado ordenado
    printf("Infracciones ordenadas por marca y modelo (descendente):\n");
    for (int i = 0; i < NUM_REGISTROS; i++) {
        printf("Placa: %s, Marca: %s, Modelo: %s, Año: %d, Multa: %d, Motivo: %s, Fecha: %s\n",
               vehiculos[i].placa, vehiculos[i].marca, vehiculos[i].modelo, 
               vehiculos[i].anio, vehiculos[i].multa, vehiculos[i].motivo, vehiculos[i].fecha);
    }

    return 0;
}
