/*
* ------------------------------------------------------------
* Lab5_3.c
* -------------------------------------------------------------
* UNIVERSIDAD DEL VALLE DE GUATEMALA
* Programación de Microprocesadores
*
* Laboratorio 5
* Descripción: Este programa en C ejecuta tres funciones diferentes en 
*              paralelo utilizando la directiva #pragma omp sections.
*              Cada sección ejecuta una función independiente: calcular 
*              el factorial de un número, generar la serie de Fibonacci 
*              hasta un número dado, y encontrar el máximo en un arreglo.
*
* Autor:	   Javier Linares
* Fecha:	   Agosto 24, 2024.
* -------------------------------------------------------------
*/

#include <stdio.h>
#include <omp.h>

// Función para calcular el factorial de un número
void calcularFactorial(int num) {
    long long factorial = 1;
    for (int i = 1; i <= num; i++) {
        factorial *= i;
    }
    printf("El factorial de %d es: %lld\n", num, factorial);
}

// Función para generar la serie de Fibonacci hasta un número dado
void generarFibonacci(int num) {
    int fib[num];  // Array para almacenar los números de Fibonacci
    fib[0] = 0;
    fib[1] = 1;
    printf("Serie de Fibonacci hasta %d: %d %d", num, fib[0], fib[1]);
    
    for (int i = 2; i < num; i++) {
        fib[i] = fib[i - 1] + fib[i - 2];
        printf(" %d", fib[i]);
    }
    printf("\n");
}

// Función para encontrar el máximo en un arreglo
void encontrarMaximo(int arr[], int size) {
    int max = arr[0];
    for (int i = 1; i < size; i++) {
        if (arr[i] > max) {
            max = arr[i];
        }
    }
    printf("El maximo en el arreglo es: %d\n", max);
}

int main() {
    // Parámetros de las funciones
    int numFactorial = 10;  // Número para calcular el factorial
    int numFibonacci = 10;  // Número de términos para la serie de Fibonacci
    int arr[] = {1, 5, 3, 9, 2, 8, 4};  // Arreglo para encontrar el máximo
    int size = sizeof(arr) / sizeof(arr[0]);  // Tamaño del arreglo

    // Ejecutamos las tres funciones en paralelo usando secciones
    #pragma omp parallel sections
    {
        // Sección 1: Calcular el factorial
        #pragma omp section
        {
            calcularFactorial(numFactorial);
        }

        // Sección 2: Generar la serie de Fibonacci
        #pragma omp section
        {
            generarFibonacci(numFibonacci);
        }

        // Sección 3: Encontrar el máximo en un arreglo
        #pragma omp section
        {
            encontrarMaximo(arr, size);
        }
    }

    return 0;
}
