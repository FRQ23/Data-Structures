// Autor: Fernando Rosales Quiñones 1299440

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Definición de la estructura de Infracción
typedef struct {
    char placas[10];
    char marca[20];
    char modelo[20];
    int año;
    float multa;
    char motivo[100];
    char fecha[11];  // dd/mm/yyyy
} Infraccion;

// Prototipos de las funciones
void agregarInfraccion(Infraccion infracciones[], int *n);
void saldarMulta(Infraccion infracciones[], int *n);
void radixSort(Infraccion infracciones[], int n);
void shellSort(Infraccion infracciones[], int n);
void quickSort(Infraccion infracciones[], int low, int high);
int partition(Infraccion infracciones[], int low, int high);
void imprimirInfracciones(Infraccion infracciones[], int n);
void visualizarPasoAPaso(Infraccion infracciones[], int n);

int main() {
    int opcion, n = 7;
    Infraccion infracciones[100] = {
            {"A59-NZC-6", "Honda", "Civic", 2020, 500, "Exceso de velocidad.", "08/03/2023"},
            {"EJM-47-40", "Nissan", "Pathfinder", 2018, 600, "Conducir en estado de ebriedad.", "07/03/2019"},
            {"3-MM-778", "Suzuki", "Scross", 2021, 400, "Voltear en U.", "02/09/2024"},
            {"257-NWD-8", "Honda", "Accord", 2022, 700, "Conducir con dispositivo.", "02/01/2024"},
            {"AHA-50-15", "Mazda", "Sedán", 2019, 300, "Verificación expirada.", "03/07/2020"},
            {"YBU-80-66", "Suzuki", "Ignis", 2021, 450, "Estacionarse en doble fila.", "05/05/2021"},
            {"EMN-71-71", "Nissan", "Versa", 2020, 300, "Conducir sin licencia.", "24/12/2018"}
    };

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
                agregarInfraccion(infracciones, &n);
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

    return 0;
}

// Agregar infracción
void agregarInfraccion(Infraccion infracciones[], int *n) {
    printf("Ingrese los datos de la infracción:\n");
    printf("Placas: ");
    scanf("%s", infracciones[*n].placas);
    printf("Marca: ");
    scanf("%s", infracciones[*n].marca);
    printf("Modelo: ");
    scanf("%s", infracciones[*n].modelo);
    printf("Año: ");
    scanf("%d", &infracciones[*n].año);
    printf("Multa: ");
    scanf("%f", &infracciones[*n].multa);
    printf("Motivo: ");
    scanf(" %[^\n]", infracciones[*n].motivo);
    printf("Fecha (dd/mm/yyyy): ");
    scanf("%s", infracciones[*n].fecha);
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
int getDigit(char *placa, int pos) {
    return placa[pos] - '0'; // Convertir carácter a dígito
}

// Función para obtener el valor del carácter de la placa, ya sea un número o una letra
int getPlacaValue(char c) {
    if (isdigit(c)) {
        return c - '0';  // Convertir caracteres numéricos a su valor correspondiente
    } else if (isalpha(c)) {
        return toupper(c) - 'A' + 10;  // Convertir letras a valores desde 10 en adelante
    } else {
        return 0;  // Asignar un valor predeterminado para cualquier otro carácter no esperado
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

// Radix Sort modificado para manejar placas alfanuméricas
void radixSort(Infraccion infracciones[], int n) {
    int max_length = maxLen(infracciones, n);  // Máxima longitud de las placas
    Infraccion output[n];
    int count[36];  // Para manejar dígitos (0-9) y letras (A-Z)

    for (int pos = max_length - 1; pos >= 0; pos--) {
        memset(count, 0, sizeof(count));  // Inicializar el contador

        // Contar las ocurrencias de cada carácter (números y letras)
        for (int i = 0; i < n; i++) {
            int length = strlen(infracciones[i].placas);
            int digit = (pos < length) ? getPlacaValue(infracciones[i].placas[pos]) : 0;
            count[digit]++;
        }

        // Cambiar count[i] para contener las posiciones reales de los caracteres
        for (int i = 1; i < 36; i++) {
            count[i] += count[i - 1];
        }

        // Construir el arreglo ordenado
        for (int i = n - 1; i >= 0; i--) {
            int length = strlen(infracciones[i].placas);
            int digit = (pos < length) ? getPlacaValue(infracciones[i].placas[pos]) : 0;
            output[count[digit] - 1] = infracciones[i];
            count[digit]--;
        }

        // Copiar el arreglo ordenado a las infracciones originales
        for (int i = 0; i < n; i++) {
            infracciones[i] = output[i];
        }
    }
}

// Shell Sort para ordenar por Marca y Modelo
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
    }
}

// Quick Sort para ordenar por fecha
void quickSort(Infraccion infracciones[], int low, int high) {
    if (low < high) {
        int pi = partition(infracciones, low, high);
        quickSort(infracciones, low, pi - 1);
        quickSort(infracciones, pi + 1, high);
    }
}

int partition(Infraccion infracciones[], int low, int high) {
    char pivot[11];
    strcpy(pivot, infracciones[high].fecha);
    int i = (low - 1);
    for (int j = low; j <= high - 1; j++) {
        if (strcmp(infracciones[j].fecha, pivot) < 0) {
            i++;
            Infraccion temp = infracciones[i];
            infracciones[i] = infracciones[j];
            infracciones[j] = temp;
        }
    }
    Infraccion temp = infracciones[i + 1];
    infracciones[i + 1] = infracciones[high];
    infracciones[high] = temp;
    return (i + 1);
}

// Visualización gráfica paso a paso
void visualizarPasoAPaso(Infraccion infracciones[], int n) {
    printf("\n--- Visualización paso a paso ---\n");
    for (int i = 0; i < n; i++) {
        printf("Placas: %s | Marca: %s | Modelo: %s | Año: %d | Multa: %.2f | Motivo: %s | Fecha: %s\n",
               infracciones[i].placas, infracciones[i].marca, infracciones[i].modelo, infracciones[i].año,
               infracciones[i].multa, infracciones[i].motivo, infracciones[i].fecha);
    }
    printf("-----------------------------\n");
}

// Imprimir todas las infracciones
void imprimirInfracciones(Infraccion infracciones[], int n) {
    printf("\n--- Infracciones ---\n");
    for (int i = 0; i < n; i++) {
        printf("Placas: %s | Marca: %s | Modelo: %s | Año: %d | Multa: %.2f | Motivo: %s | Fecha: %s\n",
               infracciones[i].placas, infracciones[i].marca, infracciones[i].modelo, infracciones[i].año,
               infracciones[i].multa, infracciones[i].motivo, infracciones[i].fecha);
    }
}
