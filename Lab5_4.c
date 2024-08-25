/*
* ------------------------------------------------------------
* Lab5_4.c
* -------------------------------------------------------------
* UNIVERSIDAD DEL VALLE DE GUATEMALA
* Programación de Microprocesadores
*
* Laboratorio 5
* Descripción: Este programa en C ejecuta un ciclo for en paralelo donde se 
*              modifican dos variables utilizando OpenMP. La primera variable 
*              es gestionada con la cláusula shared y la segunda con la cláusula 
*              private. Se observan las diferencias en los resultados.
*
* Autor:	   Javier Linares
* Fecha:	   Agosto 24, 2024.
* -------------------------------------------------------------
*/

#include <stdio.h>
#include <omp.h>

int main() {
    int N = 10;  // Definimos el tamaño del ciclo
    int variable1 = 0;  // Variable compartida entre los hilos (shared)
    int variable2 = 0;  // Variable privada para cada hilo (private)
    
    // Ciclo for paralelo con cláusulas shared y private
    #pragma omp parallel for shared(variable1) private(variable2)
    for (int i = 0; i < N; i++) {
        // Incremento de variable1 (compartida)
        variable1 += i;

        // Inicializamos variable2 en cada hilo de forma independiente
        variable2 = i * 2;

        // Imprimimos dentro del ciclo para ver los resultados
        printf("Numero de Hilo %d - Iteracion %d: variable1 = %d, variable2 = %d\n", omp_get_thread_num(), i, variable1, variable2);
    }

    // Resultados finales
    printf("\nResultado final:\n");
    printf("variable1 (shared) = %d\n", variable1);

    return 0;
}
