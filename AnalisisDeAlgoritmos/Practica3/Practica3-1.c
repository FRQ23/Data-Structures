// Autor: Fernando Rosales Quiñones 1299440

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// Definición de la estructura de Infracción
typedef struct {
    char placas[10];
    char marca[20];
    char modelo[20];
    int anio;
    float multa;
    char motivo[100];
    char fecha[11];  // dd/mm/yyyy
} Infraccion;

// Prototipos de las funciones
void agregarInfraccion(Infraccion **infracciones, int *n, int *capacidad);
void saldarMulta(Infraccion infracciones[], int *n);
void radixSort(Infraccion infracciones[], int n);
void shellSort(Infraccion infracciones[], int n);
void quickSort(Infraccion infracciones[], int low, int high);
int compararFechas(char fecha1[], char fecha2[]);
int partition(Infraccion infracciones[], int low, int high);
void imprimirInfracciones(Infraccion infracciones[], int n);
void visualizarPasoAPaso(Infraccion infracciones[], int n);

int main() {
    int opcion, n = 8, capacidad = 10;

    // Asignamos espacio para 10 infracciones inicialmente
    Infraccion *infracciones = (Infraccion *)malloc(capacidad * sizeof(Infraccion));

    // Datos iniciales
    Infraccion datos_iniciales[] = {
            {"A59-NZC-6", "Honda", "Civic", 2020, 500, "Exceso de velocidad.", "08/03/2023"},
            {"EJM-47-40", "Nissan", "Pathfinder", 2018, 600, "Conducir en estado de ebriedad.", "07/03/2019"},
            {"3-MM-778", "Suzuki", "Scross", 2021, 400, "Voltear en U.", "02/09/2024"},
            {"257-NWD-8", "Honda", "Accord", 2022, 700, "Conducir con dispositivo.", "02/01/2024"},
            {"AHA-50-15", "Mazda", "Sedán", 2019, 300, "Verificación expirada.", "03/07/2020"},
            {"YBU-80-66", "Suzuki", "Ignis", 2021, 450, "Estacionarse en doble fila.", "05/05/2021"},
            {"EMN-71-71", "Nissan", "Versa", 2020, 300, "Conducir sin licencia.", "24/12/2018"},
            {"C87-NRL-7", "Kia", "Optima", 2050, 1000000, "prueba.", "15/12/2004"}

    };

    // Copiamos los datos iniciales al arreglo dinámico
    memcpy(infracciones, datos_iniciales, n * sizeof(Infraccion));

    do {
        printf("\n--- Menú ---\n");
        printf("1. Agregar infracción\n");
        printf("2. Saldar multa\n");
        printf("3. Mostrar infracciones ordenadas por número de placas (Radix Sort)\n");
        printf("4. Mostrar infracciones ordenadas por Marca y Modelo (Shell Sort)\n");
        printf("5. Mostrar infracciones ordenadas por fecha de la multa (Quick Sort)\n");
        printf("6. Salir\n");
        printf("Seleccione una opción: ");
        scanf("%d", &opcion);

        switch (opcion) {
            case 1:
                agregarInfraccion(&infracciones, &n, &capacidad);  // Llamamos con puntero doble
                break;
            case 2:
                saldarMulta(infracciones, &n);
                break;
            case 3:
                radixSort(infracciones, n);
                visualizarPasoAPaso(infracciones, n);
                imprimirInfracciones(infracciones, n);
                break;
            case 4:
                shellSort(infracciones, n);
                visualizarPasoAPaso(infracciones, n);
                imprimirInfracciones(infracciones, n);
                break;
            case 5:
                quickSort(infracciones, 0, n - 1);
                visualizarPasoAPaso(infracciones, n);
                imprimirInfracciones(infracciones, n);
                break;
            case 6:
                printf("Saliendo...\n");
                break;
            default:
                printf("Opción inválida.\n");
        }
    } while (opcion != 6);

    // Liberar la memoria
    free(infracciones);

    return 0;
}

// Agregar infracción de forma dinámica
void agregarInfraccion(Infraccion **infracciones, int *n, int *capacidad) {
    if (*n >= *capacidad) {
        *capacidad *= 2;  // Duplicamos la capacidad si es necesario
        *infracciones = (Infraccion *)realloc(*infracciones, *capacidad * sizeof(Infraccion));
        if (*infracciones == NULL) {
            printf("Error al asignar memoria.\n");
            exit(1);
        }
    }

    printf("Ingrese los datos de la infracción:\n");
    printf("Placas: ");
    scanf("%s", (*infracciones)[*n].placas);
    printf("Marca: ");
    scanf("%s", (*infracciones)[*n].marca);
    printf("Modelo: ");
    scanf("%s", (*infracciones)[*n].modelo);
    printf("anio: ");
    scanf("%d", &(*infracciones)[*n].anio);
    printf("Multa: ");
    scanf("%f", &(*infracciones)[*n].multa);
    printf("Motivo: ");
    scanf(" %[^\n]", (*infracciones)[*n].motivo);
    printf("Fecha (dd/mm/yyyy): ");
    scanf("%s", (*infracciones)[*n].fecha);
    (*n)++;
}

// Saldar multa (eliminar infracción)
void saldarMulta(Infraccion infracciones[], int *n) {
    char placas[10];
    printf("Ingrese las placas de la infracción a saldar: ");
    scanf("%s", placas);

    for (int i = 0; i < *n; i++) {
        if (strcmp(infracciones[i].placas, placas) == 0) {
            for (int j = i; j < *n - 1; j++) {
                infracciones[j] = infracciones[j + 1];
            }
            (*n)--;
            printf("Multa saldada.\n");
            return;
        }
    }
    printf("Infracción no encontrada.\n");
}

// Función auxiliar para obtener el dígito en una posición dada de un número de placa
int getdigito(char *placa, int pos) {
    return placa[pos] - '0'; // Convertir carácter a dígito
}

// Función para obtener el valor del carácter de la placa, ya sea un número o una letra
int obtenerPlaca(char c, bool esPrimeraPosicion) {
    if (c >= '0' && c <= '9') {
        if (esPrimeraPosicion && c == '3') {
            return 3;  // Tratar '3' en la primera posición como '003'
        }
        return c - '0';  // Convertir caracteres numéricos a su valor correspondiente
    } else if (c >= 'A' && c <= 'Z') {
        return c - 'A' + 10;  // Convertir letras mayúsculas a valores desde 10 en adelante
    } else if (c >= 'a' && c <= 'z') {
        return c - 'a' + 10;  // Convertir letras minúsculas a valores desde 10 en adelante
    } else {
        return -1;  // Retornar -1 si el carácter no es un número o una letra
    }
}



// Función para encontrar el número de caracteres en la placa más larga
int maxLen(Infraccion infracciones[], int n) {
    int max = strlen(infracciones[0].placas);
    for (int i = 1; i < n; i++) {
        if (strlen(infracciones[i].placas) > max) {
            max = strlen(infracciones[i].placas);
        }
    }
    return max;
}

// Radix Sort modificado para manejar placas alfanuméricas y mostrar el proceso paso a paso
void radixSort(Infraccion infracciones[], int n) {
    int max_longitud = maxLen(infracciones, n);  // Máxima longitud de las placas
    Infraccion output[n];
    int count[36];  // Para manejar dígitos (0-9) y letras (A-Z)

    for (int pos = max_longitud - 1; pos >= 0; pos--) {
        memset(count, 0, sizeof(count));  // Inicializar el contador

        // Contar las ocurrencias de cada carácter (números y letras)
        for (int i = 0; i < n; i++) {
            int longitud = strlen(infracciones[i].placas);
            int digito = (pos < longitud) ? obtenerPlaca(infracciones[i].placas[pos]) : 0;
            count[digito]++;
        }

        // Cambiar count[i] para contener las posiciones reales de los caracteres
        for (int i = 1; i < 36; i++) {
            count[i] += count[i - 1];
        }

        // Construir el arreglo ordenado
        for (int i = n - 1; i >= 0; i--) {
            int longitud = strlen(infracciones[i].placas);
            int digito = (pos < longitud) ? obtenerPlaca(infracciones[i].placas[pos]) : 0;
            output[count[digito] - 1] = infracciones[i];
            count[digito]--;
        }

        // Copiar el arreglo ordenado a las infracciones originales
        for (int i = 0; i < n; i++) {
            infracciones[i] = output[i];
        }

        // Mostrar el estado actual del arreglo
        printf("Paso en la posición %d:\n", pos);
        visualizarPasoAPaso(infracciones, n);
    }
}

// Shell Sort modificado para mostrar el proceso paso a paso
void shellSort(Infraccion infracciones[], int n) {
    int gap, i, j;
    Infraccion temp;

    for (gap = n / 2; gap > 0; gap /= 2) {
        for (i = gap; i < n; i++) {
            temp = infracciones[i];

            for (j = i; j >= gap && (strcmp(infracciones[j - gap].marca, temp.marca) < 0 ||
                                     (strcmp(infracciones[j - gap].marca, temp.marca) == 0 &&
                                      strcmp(infracciones[j - gap].modelo, temp.modelo) < 0)); j -= gap) {
                infracciones[j] = infracciones[j - gap];
            }
            infracciones[j] = temp;
        }
        // Mostrar el estado actual del arreglo
        printf("Gap %d:\n", gap);
        visualizarPasoAPaso(infracciones, n);
    }
}

// Función para intercambiar dos infracciones
void intercambiar(Infraccion *a, Infraccion *b) {
    Infraccion temp = *a;
    *a = *b;
    *b = temp;
}

// Función de Quick Sort modificado para mostrar el proceso paso a paso
void quickSort(Infraccion infracciones[], int low, int high) {
    if (low < high) {
        int pi = partition(infracciones, low, high);

        // Mostrar el estado actual del arreglo
        printf("Partición en índice %d:\n", pi);
        visualizarPasoAPaso(infracciones, high - low + 1);

        quickSort(infracciones, low, pi - 1);
        quickSort(infracciones, pi + 1, high);
    }
}

int compararFechas(char fecha1[], char fecha2[]) {
    // Formato esperado: DD/MM/AAAA
    int dia1, mes1, anio1;
    int dia2, mes2, anio2;

    // Parsear las fechas
    sscanf(fecha1, "%d/%d/%d", &dia1, &mes1, &anio1);
    sscanf(fecha2, "%d/%d/%d", &dia2, &mes2, &anio2);

    // Comparar los anios
    if (anio1 < anio2) return -1;
    if (anio1 > anio2) return 1;

    // Si los anios son iguales, comparar los meses
    if (mes1 < mes2) return -1;
    if (mes1 > mes2) return 1;

    // Si los meses son iguales, comparar los días
    if (dia1 < dia2) return -1;
    if (dia1 > dia2) return 1;

    // Las fechas son iguales
    return 0;
}

int partition(Infraccion infracciones[], int low, int high) {
    char pivot[11];
    strcpy(pivot, infracciones[high].fecha);
    int i = (low - 1);

    for (int j = low; j <= high - 1; j++) {
        if (compararFechas(infracciones[j].fecha, pivot) < 0) {
            i++;
            intercambiar(&infracciones[i], &infracciones[j]);
        }
    }
    intercambiar(&infracciones[i + 1], &infracciones[high]);
    return (i + 1);
}

// Visualización gráfica paso a paso
void visualizarPasoAPaso(Infraccion infracciones[], int n) {
    printf("\n--- Visualización paso a paso ---\n");
    for (int i = 0; i < n; i++) {
        printf("Placas: %s | Marca: %s | Modelo: %s | anio: %d | Multa: %.2f | Motivo: %s | Fecha: %s\n",
               infracciones[i].placas, infracciones[i].marca, infracciones[i].modelo, infracciones[i].anio,
               infracciones[i].multa, infracciones[i].motivo, infracciones[i].fecha);
    }
    printf("-----------------------------\n");
}

// Imprimir todas las infracciones
void imprimirInfracciones(Infraccion infracciones[], int n) {
    printf("\n--- Infracciones ---\n");
    for (int i = 0; i < n; i++) {
        printf("Placas: %s | Marca: %s | Modelo: %s | anio: %d | Multa: %.2f | Motivo: %s | Fecha: %s\n",
               infracciones[i].placas, infracciones[i].marca, infracciones[i].modelo, infracciones[i].anio,
               infracciones[i].multa, infracciones[i].motivo, infracciones[i].fecha);
    }
}
