#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "chambuchito.h"
#include "cocineritos.h"


int main() {
    srand((unsigned)time(NULL));

    int precio = 0;
    juego_t juego;
    char movimiento = ' ';
    
    // Pre: el usuario debía haber elegido ingredientes válidos.
    // Pos: devuelve el precio del sandwich.
    calcular_precio_chambuchito(&precio);

    inicializar_juego(&juego, precio);
    printf("EN ESTE JUEGO VOS PODER MOVERTE CON A,W,S,D. PARA CORTAR(C), ESTANDO ARRIBA DEL CUCHIILO(C).PARA COCINAR(H). DEBES ENTREGAR LA COMIDA CORTADA O COCINADA EN LA PUERTA(P).\n");
    printf("AHORA DEBES CORTAR LOS INGREDIENTES DE LA PIZZA: LECHUGA(L) Y TOMATE(T).\n");
    imprimir_terreno(juego);

    while (estado_juego(juego) == 0) {
        scanf(" %c", &movimiento);
        realizar_jugada(&juego, movimiento);
        imprimir_terreno(juego);
        estado_juego(juego);
        if (estado_juego(juego) == -1) {
            printf("CAISTE EN UN AGUJERO\n");
        } else if (estado_juego(juego) == 1) {
            printf("Sos el ganador");
        }
    }

    return 0;
}


