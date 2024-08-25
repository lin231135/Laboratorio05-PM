/*
* ------------------------------------------------------------
* Lab5_2.c
* -------------------------------------------------------------
* UNIVERSIDAD DEL VALLE DE GUATEMALA
* Programación de Microprocesadores
*
* Laboratorio 5
* Descripción: Este programa en C calcula la suma de los primeros 
*              N números naturales utilizando un ciclo for paralelo 
*              con la cláusula reduction para acumular la suma en una 
*              variable compartida. El tiempo de ejecución se mide 
*              utilizando omp_get_wtime().
*
* Autor:	   Javier Linares
* Fecha:	   Agosto 24, 2024.
* -------------------------------------------------------------
*/

#include <stdio.h>
#include <omp.h>  // Incluimos la librería de OpenMP para programación paralela

#define N 1000000  // Definimos N como una constante grande, el número de primeros números naturales que vamos a sumar

int main() {
    long long sum = 0;  // Variable para almacenar la suma de los números naturales
    double start_time, end_time;  // Variables para medir el tiempo de ejecución

    // Medimos el tiempo de inicio de la operación
    start_time = omp_get_wtime();

    // Paralelizamos el bucle con reducción para sumar los números
    // La cláusula reduction(+:sum) asegura que la variable 'sum' se acumule de manera segura entre todos los hilos
    #pragma omp parallel for reduction(+:sum)
    for (int i = 1; i <= N; i++) {
        sum += i;  // Acumulamos el valor de 'i' en 'sum'
    }

    // Medimos el tiempo de finalización de la operación
    end_time = omp_get_wtime();

    // Mostramos el resultado de la suma y el tiempo de ejecución
    printf("La suma de los primeros %d numeros naturales es: %lld\n", N, sum);
    printf("Tiempo de ejecucion: %f segundos\n", end_time - start_time);

    return 0;  // Finalizamos el programa
}