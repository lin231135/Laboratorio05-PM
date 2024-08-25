/*
 * Archivo: Ejercicio_5A.c
 * Descripción: Este programa cuenta cuántas veces aparece un valor específico 
 * ('key') en un arreglo de números aleatorios.
 * 
 * Funcionalidad:
 * - Genera un arreglo de tamaño N con valores aleatorios.
 * - Inserta manualmente el valor 'key' en tres posiciones específicas del arreglo.
 * - Cuenta cuántas veces aparece 'key' en el arreglo usando una función llamada count_key().
 * - Imprime el número de apariciones de 'key' en el arreglo.
 * 
 * Referencia:
 * Chandra, . R. et al. Parallel Programming in OpenMP
 *
 * Fecha modificación: 08-16-2024
 */

#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define N 131072  
#define THRESHOLD 1024 

// Función para contar las apariciones de 'key' en un subarreglo
long count_key(long *a, long key, long start, long end) {
    long count = 0; // Inicializa el contador de 'key' a 0
    
    // Si el tamaño del subarreglo es menor o igual a THRESHOLD se procesa secuencialmente
    if (end - start <= THRESHOLD) {
        for (long i = start; i < end; i++) { // Recorre el subarreglo desde 'start' hasta 'end'
            if (a[i] == key) count++; // Incrementa el contador si encuentra 'key'
        }
    } else {
        // Si el subarreglo es más grande que el THRESHOLD se divide el trabajo en dos tareas recursivas
        long mid = (start + end) / 2; // Encuentra el punto medio del subarreglo
        long count1 = 0, count2 = 0;  // Variables para almacenar los resultados de las dos mitades
        // Crea una tarea para contar las apariciones de 'key' en la primera mitad del subarreglo
        #pragma omp task shared(count1)
        count1 = count_key(a, key, start, mid);
        // Crea una tarea para contar las apariciones de 'key' en la segunda mitad del subarreglo
        #pragma omp task shared(count2)
        count2 = count_key(a, key, mid, end);
        // Espera a que ambas tareas terminen antes de continuar
        #pragma omp taskwait
        // Suma los resultados de las dos mitades
        count = count1 + count2;
    }
    return count; // Devuelve el número total de apariciones de 'key' en el subarreglo
}

int main() {
    long a[N], key = 42, nkey = 0; // Declara un arreglo 'a' de tamaño N y las variables 'key' y 'nkey'
    // Inicializar el arreglo con valores aleatorios
    for (long i = 0; i < N; i++) a[i] = rand() % N; // Llena el arreglo con valores aleatorios entre 0 y N-1
    // Inserta el valor 'key' en tres posiciones específicas del arreglo
    a[N % 43] = key; // Inserta 'key' en la posición N % 43
    a[N % 73] = key; // Inserta 'key' en la posición N % 73
    a[N % 3] = key;  // Inserta 'key' en la posición N % 3
    // Configura el número de hilos disponibles para OpenMP
    omp_set_num_threads(omp_get_max_threads());
    
    // Inicia la región paralela
    #pragma omp parallel
    {
        // Solo un hilo ejecuta la llamada inicial a la función recursiva
        #pragma omp single
        {
            nkey = count_key(a, key, 0, N); // Llamada inicial a la función recursiva para todo el arreglo
        }
    }
    // Imprimir el resultado
    printf("Numero de veces que 'key' aparece en paralelo: %ld\n", nkey); // Imprime el número de apariciones de 'key'
    return 0; // Termina el programa
}