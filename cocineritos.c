#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "cocineritos.h"

const char FUEGO = 'F';
const char AGUJEROS = 'A';
const char MATAFUEGOS = 'M';
const char CUCHILLOS = 'C';
const char HORNO = 'H';
const char PUERTA_DE_SALIDA = 'P';
const char PIZZA = 'P';
const char HAMBURGUESA = 'H'; 
const char ENSALADA = 'E';
const char SANDWICH = 'S'; 
const char LECHUGA = 'L';
const char TOMATE = 'T';
const char MILANESA = 'I';
const char PAN = 'N';
const char JAMON = 'J';
const char QUESO = 'Q';
const char MASA = 'O';
const char CARNE = 'B';
const char STITCH = 'S';
const char REUBEN = 'R'; 
const char MANOS_VACIAS = 'V';
#define ARRIBA  'W'
#define ABAJO  'S'
#define IZQUIERDA  'A'
#define DERECHA  'D'
#define ALTERNARNADOR_DE_PERSONAJE 'X'
#define ACTIVAR_MATAFUEGOS 'M'
#define CORTAR_INGREDIENTES 'C'
#define COCINAR_INGREDIENTES 'H'
#define AGARRAR_INGREDIENTE 'R'
#define SOLTAR_INGREDIENTE_MESA 'T'
#define AGARRAR_INGREDIENTE_MESA 'T'
const int  MOVIMIENTOS_FUEGO = 15;
const int NO_CONTAR_MOVIMIENTOS = 0;

//Pre: -
//Pos: darle una ubicacion a cada elemento
int generar_posicion_aleatoria() {
    return rand() % 19 + 1;
}

//Pre:-
//Pos: calcula la distancia entre dos elementos.
int calcular_distancia_manhatan(coordenada_t pos1, coordenada_t pos2) {
    return abs(pos1.fil - pos2.fil) + abs(pos1.col - pos2.col);
}

//Pre:-
//Pos: las filas y columnas seleccionadas estaran ocupadas por las paredes
void inicializar_paredes(juego_t* juego) {
    juego->tope_paredes = 0;

    for (int i = 0; i < 21; i++) {
        juego->paredes[juego->tope_paredes].fil = i;
        juego->paredes[juego->tope_paredes].col = 0;
        juego->tope_paredes++;

        juego->paredes[juego->tope_paredes].fil = i;
        juego->paredes[juego->tope_paredes].col = 20;
        juego->tope_paredes++;
    }

    for (int j = 1; j <= 19; j++) {
        juego->paredes[juego->tope_paredes].fil = 0;
        juego->paredes[juego->tope_paredes].col = j;
        juego->tope_paredes++;

        juego->paredes[juego->tope_paredes].fil = 20;
        juego->paredes[juego->tope_paredes].col = j;
        juego->tope_paredes++;      
    }

    for (int k = 1; k < 10; k++) {
        juego->paredes[juego->tope_paredes].fil = 10;
        juego->paredes[juego->tope_paredes].col = k;
        juego->tope_paredes++;
    }

    for (int k = 11; k < 20; k++) {
        juego->paredes[juego->tope_paredes].fil = 10;
        juego->paredes[juego->tope_paredes].col = k;
        juego->tope_paredes++;
    } 
}

//Pre: -
//Pos: en el casillero seleccionado ya queda ocupado por la mesa
void inicializar_mesa(juego_t* juego){
    juego->mesa.fil = 10;
    juego->mesa.col = 10;
}

//Pre: -
//Pos: devuelve si cada  obstaculo tiene su casillero libre
bool esta_obstaculo_ocupado(juego_t juego, int fil, int col) {
    for (int i = 0; i < juego.tope_paredes; i++) {
        if (juego.paredes[i].fil == fil && juego.paredes[i].col == col) {
            return false;
        }
    }
    for (int i = 0; i < juego.tope_obstaculos; i++) {
        if (juego.obstaculos[i].posicion.fil == fil && juego.obstaculos[i].posicion.col == col) {
            return false;
        }
    }
    return true;
}

//Pre: -
//Pos: devuelve si cada  herramienta tiene su casillero libre
bool esta_herramienta_ocupada(juego_t juego, int fil, int col) {
    for (int i = 0; i < juego.tope_paredes; i++) {
        if (juego.paredes[i].fil == fil && juego.paredes[i].col == col) {
            return false;
        }
    }
    for (int i = 0; i < juego.tope_obstaculos; i++) {
        if (juego.obstaculos[i].posicion.fil == fil && juego.obstaculos[i].posicion.col == col) {
            return false;
        }
    }
    for (int i = 0; i < juego.tope_herramientas; i++) {
        if (juego.herramientas[i].posicion.fil == fil && juego.herramientas[i].posicion.col == col) {
            return false;
        }
    }
    return true;
}

//Pre: -
//Pos: devuelve si cada  personaje tiene su casillero libre
bool esta_personaje_ocupado(juego_t juego, int fil, int col) {
    for (int i = 0; i < juego.tope_paredes; i++) {
        if (juego.paredes[i].fil == fil && juego.paredes[i].col == col) {
            return false;
        }
    }
    for (int i = 0; i < juego.tope_obstaculos; i++) {
        if (juego.obstaculos[i].posicion.fil == fil && juego.obstaculos[i].posicion.col == col) {
            return false;
        }
    }
    for (int i = 0; i < juego.tope_herramientas; i++) {
        if (juego.herramientas[i].posicion.fil == fil && juego.herramientas[i].posicion.col == col) {
            return false;
        }
    }
    for (int i = 0; i < juego.tope_comida; i++) {
        for (int j = 0; j < juego.comida[i].tope_ingredientes; j++) {
            if (juego.comida[i].ingrediente[j].posicion.fil == fil && juego.comida[i].ingrediente[j].posicion.col == col) {
                return false;
            }
        }
    }
    return true;
}

//Pre: -
//Pos: devuelve si cada obstaculo tiene su casillero libre
bool esta_posicion_ocupada(juego_t juego, int fil, int col) {
    for (int i = 0; i < juego.tope_paredes; i++) {
        if (juego.paredes[i].fil == fil && juego.paredes[i].col == col) {
            return false;
        }
    }
    for (int i = 0; i < juego.tope_obstaculos; i++) {
        if (juego.obstaculos[i].posicion.fil == fil && juego.obstaculos[i].posicion.col == col) {
            return false;
        }
    }
    for (int i = 0; i < juego.tope_herramientas; i++) {
        if (juego.herramientas[i].posicion.fil == fil && juego.herramientas[i].posicion.col == col) {
            return false;
        }
    }
    if (juego.stitch.posicion.fil == fil && juego.stitch.posicion.col == col) {
        return false;
    }
    if (juego.reuben.posicion.fil == fil && juego.reuben.posicion.col == col) {
        return false;
    }
    for (int i = 0; i < juego.tope_comida; i++) {
        for (int j = 0; j < juego.comida[i].tope_ingredientes; j++) {
            if (juego.comida[i].ingrediente[j].posicion.fil == fil && juego.comida[i].ingrediente[j].posicion.col == col) {
                return false;
            }
        }
    }

    if(juego.salida.fil == fil && juego.salida.col == col){
        return false;
    }

    return true;
}

//Pre: -
//Pos: deja que la puerta se genere en un lugar no ocupado.
bool esta_puerta_ocupada(juego_t juego, int fil, int col) {
    for (int i = 0; i < juego.tope_paredes; i++) {
        if (juego.paredes[i].fil == fil && juego.paredes[i].col == col) {
            return false;
        }
    }
    for (int i = 0; i < juego.tope_obstaculos; i++) {
        if (juego.obstaculos[i].posicion.fil == fil && juego.obstaculos[i].posicion.col == col) {
            return false;
        }
    }
    for (int i = 0; i < juego.tope_herramientas; i++) {
        if (juego.herramientas[i].posicion.fil == fil && juego.herramientas[i].posicion.col == col) {
            return false;
        }
    }
    for (int i = 0; i < juego.tope_comida; i++) {
        for (int j = 0; j < juego.comida[i].tope_ingredientes; j++) {
            if (juego.comida[i].ingrediente[j].posicion.fil == fil && juego.comida[i].ingrediente[j].posicion.col == col) {
                return false;
            }
        }
    }
    if (juego.stitch.posicion.fil == fil && juego.stitch.posicion.col == col) {
        return false;
    }
    if (juego.reuben.posicion.fil == fil && juego.reuben.posicion.col == col) {
        return false;
    }
    return true;
}

//Pre: -
//Pos: devuelve si el fuego tiene su casillero libre
bool esta_fuego_ocupado(juego_t juego, int fil, int col) {
    for (int i = 0; i < juego.tope_paredes; i++) {
        if (juego.paredes[i].fil == fil && juego.paredes[i].col == col) {
            return false;
        }
    }
    for (int i = 0; i < juego.tope_obstaculos; i++) {
        if (juego.obstaculos[i].posicion.fil == fil && juego.obstaculos[i].posicion.col == col) {
            return false;
        }
    }
    for (int i = 0; i < juego.tope_herramientas; i++) {
        if (juego.herramientas[i].posicion.fil == fil && juego.herramientas[i].posicion.col == col) {
            return false;
        }
    }
    if (juego.stitch.posicion.fil == fil && juego.stitch.posicion.col == col) {
        return false;
    }
    if (juego.reuben.posicion.fil == fil && juego.reuben.posicion.col == col) {
        return false;
    }
    for (int i = 0; i < juego.tope_comida; i++) {
        for (int j = 0; j < juego.comida[i].tope_ingredientes; j++) {
            if (juego.comida[i].ingrediente[j].posicion.fil == fil && juego.comida[i].ingrediente[j].posicion.col == col) {
                return false;
            }
        }
    }

    if(juego.mesa.fil == fil && juego.mesa.col == col){
        return false;
    }

    if(juego.salida.fil == fil && juego.salida.col == col){
        return false;
    }

    return true;
}

//Pre: -
//Pos: la puerta aparece en un casillero no ocupado en el cudrante inferior
void inicializar_puerta_salida(juego_t* juego){
    for(int i = 0; i < 1; i++){
        juego->salida.fil = generar_posicion_aleatoria() % 7 + 12; 
        juego->salida.col = generar_posicion_aleatoria() % 7 + 12; 
        while(!esta_puerta_ocupada(*juego, juego->salida.fil, juego->salida.col) && juego->salida.col != 0 && juego->salida.col != 20){
            juego->salida.fil = generar_posicion_aleatoria() % 7 + 12; 
            juego->salida.col = generar_posicion_aleatoria() % 7 + 12; 
        }
    }
}

//Pre: -
//Pos: el fuego aparece en cualquier parte del mapa
void inicializar_fuego(juego_t* juego){
    for(int i = 0; i < 1; i++){
        juego->obstaculos[juego->tope_obstaculos].posicion.fil = generar_posicion_aleatoria();
        juego->obstaculos[juego->tope_obstaculos].posicion.col = generar_posicion_aleatoria();

    while (!esta_fuego_ocupado(*juego, juego->obstaculos[juego->tope_obstaculos].posicion.fil, juego->obstaculos[juego->tope_obstaculos].posicion.col)
         && (juego->obstaculos[juego->tope_obstaculos].posicion.col != 0 && juego->obstaculos[juego->tope_obstaculos].posicion.col != 20)) {
                juego->obstaculos[juego->tope_obstaculos].posicion.fil = generar_posicion_aleatoria();
                juego->obstaculos[juego->tope_obstaculos].posicion.col = generar_posicion_aleatoria();
    }
    juego->obstaculos[juego->tope_obstaculos].tipo = FUEGO;
    juego->tope_obstaculos++;
    }
}

//Pre: -
//Pos: carga la informacion de los obstaculos.
void inicializar_obstaculos(juego_t* juego) {
    juego->tope_obstaculos = 0;
    juego->movimientos = 0;

    for (int i = 0; i < 10; i++) {
        juego->obstaculos[juego->tope_obstaculos].posicion.fil = generar_posicion_aleatoria() % 7 + 2;
        juego->obstaculos[juego->tope_obstaculos].posicion.col = generar_posicion_aleatoria() % 19 + 1;

        while (!esta_obstaculo_ocupado(*juego, juego->obstaculos[juego->tope_obstaculos].posicion.fil, juego->obstaculos[juego->tope_obstaculos].posicion.col)
               && (juego->obstaculos[juego->tope_obstaculos].posicion.col != 0 && juego->obstaculos[juego->tope_obstaculos].posicion.col != 20)) {
            juego->obstaculos[juego->tope_obstaculos].posicion.fil = generar_posicion_aleatoria() % 7 + 2;
            juego->obstaculos[juego->tope_obstaculos].posicion.col = generar_posicion_aleatoria() % 19 + 1;
        }
        juego->obstaculos[juego->tope_obstaculos].tipo = AGUJEROS;
        juego->tope_obstaculos++;
    }
    for (int i = 0; i < 10; i++) {
        juego->obstaculos[juego->tope_obstaculos].posicion.fil = generar_posicion_aleatoria() % 7 + 12;
        juego->obstaculos[juego->tope_obstaculos].posicion.col = generar_posicion_aleatoria() % 19 + 1;

        while (!esta_obstaculo_ocupado(*juego, juego->obstaculos[juego->tope_obstaculos].posicion.fil, juego->obstaculos[juego->tope_obstaculos].posicion.col)
               && (juego->obstaculos[juego->tope_obstaculos].posicion.col != 0 && juego->obstaculos[juego->tope_obstaculos].posicion.col != 20)) {
            juego->obstaculos[juego->tope_obstaculos].posicion.fil = generar_posicion_aleatoria() % 7 + 12;
            juego->obstaculos[juego->tope_obstaculos].posicion.col = generar_posicion_aleatoria() % 19 + 1;
        }
        juego->obstaculos[juego->tope_obstaculos].tipo = AGUJEROS;
        juego->tope_obstaculos++;
    }
}

//Pre: -
//Pos: se genera el matafuegos en el mismo cudrante que el fuego
void inicializar_matafuegos_arriba(juego_t* juego){
    juego->herramientas[juego->tope_herramientas].posicion.fil = generar_posicion_aleatoria(); 
    juego->herramientas[juego->tope_herramientas].posicion.col = generar_posicion_aleatoria(); 
    for (int i = 0; i < 1; i++) {
        juego->herramientas[juego->tope_herramientas].posicion.fil = generar_posicion_aleatoria() % 7 + 2; 
        juego->herramientas[juego->tope_herramientas].posicion.col = generar_posicion_aleatoria() % 19 + 1;

        while(!esta_posicion_ocupada(*juego, juego->herramientas[juego->tope_herramientas].posicion.fil, juego->herramientas[juego->tope_herramientas].posicion.col) ){
            juego->herramientas[juego->tope_herramientas].posicion.fil = generar_posicion_aleatoria() % 7 + 2;  
            juego->herramientas[juego->tope_herramientas].posicion.col = generar_posicion_aleatoria()% 19 + 1; 
        } 
        juego->herramientas[juego->tope_herramientas].tipo = MATAFUEGOS ;
        juego->tope_herramientas++;
    }
}

//Pre: -
//Pos: se genera el matafuegos en el mismo cuadrante que el fuego
void inicializar_matafuegos_abajo(juego_t* juego){
    juego->herramientas[juego->tope_herramientas].posicion.fil = generar_posicion_aleatoria(); 
    juego->herramientas[juego->tope_herramientas].posicion.col = generar_posicion_aleatoria(); 
    for (int i = 0; i < 1; i++) {
        juego->herramientas[juego->tope_herramientas].posicion.fil = generar_posicion_aleatoria() % 7 + 12; 
        juego->herramientas[juego->tope_herramientas].posicion.col = generar_posicion_aleatoria() % 19 + 1;

        while(!esta_posicion_ocupada(*juego, juego->herramientas[juego->tope_herramientas].posicion.fil, juego->herramientas[juego->tope_herramientas].posicion.col) ){
            juego->herramientas[juego->tope_herramientas].posicion.fil = generar_posicion_aleatoria() % 7 + 12;  
            juego->herramientas[juego->tope_herramientas].posicion.col = generar_posicion_aleatoria()% 19 + 1; 
        } 
        juego->herramientas[juego->tope_herramientas].tipo = MATAFUEGOS ;
        juego->tope_herramientas++;
    }
}

//Pre: -
//Pos: se carga la informacion las herramientas
void inicializar_herramientas(juego_t* juego) {
    juego->tope_herramientas = 0;
    
    juego->herramientas[juego->tope_herramientas].posicion.fil = generar_posicion_aleatoria(); 
    juego->herramientas[juego->tope_herramientas].posicion.col = generar_posicion_aleatoria(); 

    for (int i = 1; i < 3; i++) {
        juego->herramientas[juego->tope_herramientas].posicion.fil = generar_posicion_aleatoria() % 7 + 2; 
        juego->herramientas[juego->tope_herramientas].posicion.col = generar_posicion_aleatoria() % 19 + 1;
        
        while(!esta_herramienta_ocupada(*juego, juego->herramientas[juego->tope_herramientas].posicion.fil, juego->herramientas[juego->tope_herramientas].posicion.col) ){
            juego->herramientas[juego->tope_herramientas].posicion.fil = generar_posicion_aleatoria() % 7 + 2;  
            juego->herramientas[juego->tope_herramientas].posicion.col = generar_posicion_aleatoria() % 19 + 1; 
        } 
        
        juego->herramientas[juego->tope_herramientas].tipo = CUCHILLOS ;
        juego->tope_herramientas++;
    }

        for (int i = 1; i < 3; i++){
          juego->herramientas[juego->tope_herramientas].posicion.fil = generar_posicion_aleatoria() % 7 + 12; 
        juego->herramientas[juego->tope_herramientas].posicion.col = generar_posicion_aleatoria() % 19 + 1;
        
        while(!esta_herramienta_ocupada(*juego, juego->herramientas[juego->tope_herramientas].posicion.fil, juego->herramientas[juego->tope_herramientas].posicion.col) ){
            juego->herramientas[juego->tope_herramientas].posicion.fil = generar_posicion_aleatoria() % 7 + 12;  
            juego->herramientas[juego->tope_herramientas].posicion.col = generar_posicion_aleatoria() % 19 + 1; 
        } 
        
        juego->herramientas[juego->tope_herramientas].tipo = HORNO ;
        juego->tope_herramientas++;
    }
}

// Pre: -
// Pos: se generan los ingredientes de la ensalada.
void inicializar_ensalada(juego_t* juego) {

    for (int i = 0; i < 1; i++) { 
        juego->comida[juego->tope_comida].tope_ingredientes = 0;
        juego->comida[juego->tope_comida].tipo = ENSALADA;
        
        for (int i = 0; i < 1; i++) {
            juego->comida[juego->tope_comida].ingrediente[i].posicion.fil = generar_posicion_aleatoria() % 7 + 2;
            juego->comida[juego->tope_comida].ingrediente[i].posicion.col = generar_posicion_aleatoria() % 19 + 1;
            
            while (!esta_posicion_ocupada(*juego, juego->comida[juego->tope_comida].ingrediente[i].posicion.fil, juego->comida[juego->tope_comida].ingrediente[i].posicion.col)) {
                juego->comida[juego->tope_comida].ingrediente[i].posicion.fil = generar_posicion_aleatoria() % 7 + 2;
                juego->comida[juego->tope_comida].ingrediente[i].posicion.col = generar_posicion_aleatoria() % 19 + 1;
            }
            
            juego->comida[juego->tope_comida].ingrediente[i].tipo = LECHUGA;
            juego->comida[juego->tope_comida].ingrediente[i].esta_cortado = false;
            juego->comida[juego->tope_comida].ingrediente[i].esta_cocinado = false;
            juego->comida[juego->tope_comida].tope_ingredientes++;
        }

        for (int i = 1; i < 2; i++) {
            juego->comida[juego->tope_comida].ingrediente[i].posicion.fil = generar_posicion_aleatoria() % 7 + 2;
            juego->comida[juego->tope_comida].ingrediente[i].posicion.col = generar_posicion_aleatoria() % 19 + 1;
            
            while (!esta_posicion_ocupada(*juego, juego->comida[juego->tope_comida].ingrediente[i].posicion.fil, juego->comida[juego->tope_comida].ingrediente[i].posicion.col)) {
                juego->comida[juego->tope_comida].ingrediente[i].posicion.fil = generar_posicion_aleatoria() % 7 + 2;
                juego->comida[juego->tope_comida].ingrediente[i].posicion.col = generar_posicion_aleatoria() % 19 + 1;
            }
            
            juego->comida[juego->tope_comida].ingrediente[i].tipo = TOMATE;
            juego->comida[juego->tope_comida].ingrediente[i].esta_cortado = false;
            juego->comida[juego->tope_comida].ingrediente[i].esta_cocinado = false;
            juego->comida[juego->tope_comida].tope_ingredientes++;
        } 

        juego->tope_comida++;
    }
}

// Pre: -
// Pos: se generan los ingredientes de la pizza
void inicializar_pizza(juego_t* juego) {
   printf("AHORA DEBES CORTAR LOS INGREDIENTES DE LA PIZZA: JAMON(J) Y QUESO(Q). Y COCINAR: MASA(O).\n");
    for (int i = 0; i < 1; i++) {
        juego->comida[juego->tope_comida].tipo = PIZZA;
        juego->comida[juego->tope_comida].tope_ingredientes = 0;
        
        for (int i = 0; i < 1; i++) {
            juego->comida[juego->tope_comida].ingrediente[i].posicion.fil = generar_posicion_aleatoria() % 7 + 12;
            juego->comida[juego->tope_comida].ingrediente[i].posicion.col = generar_posicion_aleatoria() % 19 + 1;
            
            while (!esta_posicion_ocupada(*juego, juego->comida[juego->tope_comida].ingrediente[i].posicion.fil, juego->comida[juego->tope_comida].ingrediente[i].posicion.col)) {
                juego->comida[juego->tope_comida].ingrediente[i].posicion.fil = generar_posicion_aleatoria() % 7 + 12;
                juego->comida[juego->tope_comida].ingrediente[i].posicion.col = generar_posicion_aleatoria() % 19 + 1;
            }
            
            juego->comida[juego->tope_comida].ingrediente[i].tipo = MASA;
            juego->comida[juego->tope_comida].ingrediente[i].esta_cortado = false;
            juego->comida[juego->tope_comida].ingrediente[i].esta_cocinado = false;
            juego->comida[juego->tope_comida].tope_ingredientes++;
        }

        for (int i = 1; i < 2; i++) {
            juego->comida[juego->tope_comida].ingrediente[i].posicion.fil = generar_posicion_aleatoria() % 7 + 2;
            juego->comida[juego->tope_comida].ingrediente[i].posicion.col = generar_posicion_aleatoria() % 19 + 1;
            
            while (!esta_posicion_ocupada(*juego, juego->comida[juego->tope_comida].ingrediente[i].posicion.fil, juego->comida[juego->tope_comida].ingrediente[i].posicion.col)) {
                juego->comida[juego->tope_comida].ingrediente[i].posicion.fil = generar_posicion_aleatoria() % 7 + 2;
                juego->comida[juego->tope_comida].ingrediente[i].posicion.col = generar_posicion_aleatoria() % 19 + 1;
            }
            
            juego->comida[juego->tope_comida].ingrediente[i].tipo = JAMON;
            juego->comida[juego->tope_comida].ingrediente[i].esta_cortado = false;
            juego->comida[juego->tope_comida].ingrediente[i].esta_cocinado = false;
            juego->comida[juego->tope_comida].tope_ingredientes++;
        }

        for (int i = 2; i < 3; i++) {
            juego->comida[juego->tope_comida].ingrediente[i].posicion.fil = generar_posicion_aleatoria() % 7 + 2;
            juego->comida[juego->tope_comida].ingrediente[i].posicion.col = generar_posicion_aleatoria() % 19 + 1;
            
            while (!esta_posicion_ocupada(*juego, juego->comida[juego->tope_comida].ingrediente[i].posicion.fil, juego->comida[juego->tope_comida].ingrediente[i].posicion.col)) {
                juego->comida[juego->tope_comida].ingrediente[i].posicion.fil = generar_posicion_aleatoria() % 7 + 2;
                juego->comida[juego->tope_comida].ingrediente[i].posicion.col = generar_posicion_aleatoria() % 19 + 1;
            }
            
            juego->comida[juego->tope_comida].ingrediente[i].tipo = QUESO;
            juego->comida[juego->tope_comida].ingrediente[i].esta_cortado = false;
            juego->comida[juego->tope_comida].ingrediente[i].esta_cocinado = false;
            juego->comida[juego->tope_comida].tope_ingredientes++;
        }
        
        juego->tope_comida++;
    }
}


// Pre: -
// Pos: se generan los ingredientes de la hamburguesa
void inicializar_hamburguesa(juego_t* juego) {
   printf("AHORA DEBES CORTAR LOS INGREDIENTES DE LA HAMBURGUESA: LECHUGA(L) , TOMATE(T) Y PAN(N). Y COCINAR: CARNE(B).\n");
    for (int i = 0; i < 1; i++) {
        juego->comida[juego->tope_comida].tipo = HAMBURGUESA;
        juego->comida[juego->tope_comida].tope_ingredientes = 0;

        for (int i = 0; i < 1; i++) {
            juego->comida[juego->tope_comida].ingrediente[i].posicion.fil = generar_posicion_aleatoria() % 7 + 2;
            juego->comida[juego->tope_comida].ingrediente[i].posicion.col = generar_posicion_aleatoria() % 19 + 1;
            while (!esta_posicion_ocupada(*juego, juego->comida[juego->tope_comida].ingrediente[i].posicion.fil, juego->comida[juego->tope_comida].ingrediente[i].posicion.col)) {
                juego->comida[juego->tope_comida].ingrediente[i].posicion.fil = generar_posicion_aleatoria() % 7 + 2;
                juego->comida[juego->tope_comida].ingrediente[i].posicion.col = generar_posicion_aleatoria() % 19 + 1;
            }
            juego->comida[juego->tope_comida].ingrediente[i].tipo = PAN;
            juego->comida[juego->tope_comida].ingrediente[i].esta_cortado = false;
            juego->comida[juego->tope_comida].ingrediente[i].esta_cocinado = false;
            juego->comida[juego->tope_comida].tope_ingredientes++;
        }

        for (int i = 1; i < 2; i++) {
            juego->comida[juego->tope_comida].ingrediente[i].posicion.fil = generar_posicion_aleatoria() % 7 + 12;
            juego->comida[juego->tope_comida].ingrediente[i].posicion.col = generar_posicion_aleatoria() % 19 + 1;
            while (!esta_posicion_ocupada(*juego, juego->comida[juego->tope_comida].ingrediente[i].posicion.fil, juego->comida[juego->tope_comida].ingrediente[i].posicion.col)) {
                juego->comida[juego->tope_comida].ingrediente[i].posicion.fil = generar_posicion_aleatoria() % 7 + 12;
                juego->comida[juego->tope_comida].ingrediente[i].posicion.col = generar_posicion_aleatoria() % 19 + 1;
            }
            juego->comida[juego->tope_comida].ingrediente[i].tipo = CARNE;
            juego->comida[juego->tope_comida].ingrediente[i].esta_cortado = false;
            juego->comida[juego->tope_comida].ingrediente[i].esta_cocinado = false;
            juego->comida[juego->tope_comida].tope_ingredientes++;
        }

        for (int i = 2; i < 3; i++) {
            juego->comida[juego->tope_comida].ingrediente[i].posicion.fil = generar_posicion_aleatoria() % 7 + 2;
            juego->comida[juego->tope_comida].ingrediente[i].posicion.col = generar_posicion_aleatoria() % 19 + 1;
            while (!esta_posicion_ocupada(*juego, juego->comida[juego->tope_comida].ingrediente[i].posicion.fil, juego->comida[juego->tope_comida].ingrediente[i].posicion.col)) {
                juego->comida[juego->tope_comida].ingrediente[i].posicion.fil = generar_posicion_aleatoria() % 7 + 2;
                juego->comida[juego->tope_comida].ingrediente[i].posicion.col = generar_posicion_aleatoria() % 19 + 1;
            }
            juego->comida[juego->tope_comida].ingrediente[i].tipo = LECHUGA;
            juego->comida[juego->tope_comida].ingrediente[i].esta_cortado = false;
            juego->comida[juego->tope_comida].ingrediente[i].esta_cocinado = false;
            juego->comida[juego->tope_comida].tope_ingredientes++;
        }

        for (int i = 3; i < 4; i++) {
            juego->comida[juego->tope_comida].ingrediente[i].posicion.fil = generar_posicion_aleatoria() % 7 + 2;
            juego->comida[juego->tope_comida].ingrediente[i].posicion.col = generar_posicion_aleatoria() % 19 + 1;
            while (!esta_posicion_ocupada(*juego, juego->comida[juego->tope_comida].ingrediente[i].posicion.fil, juego->comida[juego->tope_comida].ingrediente[i].posicion.col)) {
                juego->comida[juego->tope_comida].ingrediente[i].posicion.fil = generar_posicion_aleatoria() % 7 + 2;
                juego->comida[juego->tope_comida].ingrediente[i].posicion.col = generar_posicion_aleatoria() % 19 + 1;
            }
            juego->comida[juego->tope_comida].ingrediente[i].tipo = TOMATE;
            juego->comida[juego->tope_comida].ingrediente[i].esta_cortado = false;
            juego->comida[juego->tope_comida].ingrediente[i].esta_cocinado = false;
            juego->comida[juego->tope_comida].tope_ingredientes++;
        }
        
        juego->tope_comida++;
    }
}

// Pre: -
// Pos: se generan los ingredientes de la milanesa
void inicializar_sandwich(juego_t* juego) {
    printf("Ahora debes hacer el sandwich, tenes que cortar: LECHUGA(L), TOMATE(T), JAMON(J), QUESO(Q), PAN(N). y tenes que cocinar: MILANESA(I).\n");
   
    for (int i = 0; i < 1; i++) {
        juego->comida[juego->tope_comida].tipo = SANDWICH;
        juego->comida[juego->tope_comida].tope_ingredientes = 0;

        for (int i = 0; i < 1; i++) {
            juego->comida[juego->tope_comida].ingrediente[i].posicion.fil = generar_posicion_aleatoria() % 7 + 2;
            juego->comida[juego->tope_comida].ingrediente[i].posicion.col = generar_posicion_aleatoria() % 19 + 1;
            while (!esta_posicion_ocupada(*juego, juego->comida[juego->tope_comida].ingrediente[i].posicion.fil, juego->comida[juego->tope_comida].ingrediente[i].posicion.col)) {
                juego->comida[juego->tope_comida].ingrediente[i].posicion.fil = generar_posicion_aleatoria() % 7 + 2;
                juego->comida[juego->tope_comida].ingrediente[i].posicion.col = generar_posicion_aleatoria() % 19 + 1;
            }
            juego->comida[juego->tope_comida].ingrediente[i].tipo = TOMATE;
            juego->comida[juego->tope_comida].ingrediente[i].esta_cortado = false;
            juego->comida[juego->tope_comida].ingrediente[i].esta_cocinado = false;
            juego->comida[juego->tope_comida].tope_ingredientes++;
        }

        for (int i = 1; i < 2; i++) {
            juego->comida[juego->tope_comida].ingrediente[i].posicion.fil = generar_posicion_aleatoria() % 7 + 2;
            juego->comida[juego->tope_comida].ingrediente[i].posicion.col = generar_posicion_aleatoria() % 19 + 1;
            while (!esta_posicion_ocupada(*juego, juego->comida[juego->tope_comida].ingrediente[i].posicion.fil, juego->comida[juego->tope_comida].ingrediente[i].posicion.col)) {
                juego->comida[juego->tope_comida].ingrediente[i].posicion.fil = generar_posicion_aleatoria() % 7 + 2;
                juego->comida[juego->tope_comida].ingrediente[i].posicion.col = generar_posicion_aleatoria() % 19 + 1;
            }
            juego->comida[juego->tope_comida].ingrediente[i].tipo = LECHUGA;
            juego->comida[juego->tope_comida].ingrediente[i].esta_cortado = false;
            juego->comida[juego->tope_comida].ingrediente[i].esta_cocinado = false;
            juego->comida[juego->tope_comida].tope_ingredientes++;
        }

        for (int i = 2; i < 3; i++) {
            juego->comida[juego->tope_comida].ingrediente[i].posicion.fil = generar_posicion_aleatoria() % 7 + 2;
            juego->comida[juego->tope_comida].ingrediente[i].posicion.col = generar_posicion_aleatoria() % 19 + 1;
            while (!esta_posicion_ocupada(*juego, juego->comida[juego->tope_comida].ingrediente[i].posicion.fil, juego->comida[juego->tope_comida].ingrediente[i].posicion.col)) {
                juego->comida[juego->tope_comida].ingrediente[i].posicion.fil = generar_posicion_aleatoria() % 7 + 2;
                juego->comida[juego->tope_comida].ingrediente[i].posicion.col = generar_posicion_aleatoria() % 19 + 1;
            }
            juego->comida[juego->tope_comida].ingrediente[i].tipo = JAMON;
            juego->comida[juego->tope_comida].ingrediente[i].esta_cortado = false;
            juego->comida[juego->tope_comida].ingrediente[i].esta_cocinado = false;
            juego->comida[juego->tope_comida].tope_ingredientes++;
        }

        for (int i = 3; i < 4; i++) {
            juego->comida[juego->tope_comida].ingrediente[i].posicion.fil = generar_posicion_aleatoria() % 7 + 2;
            juego->comida[juego->tope_comida].ingrediente[i].posicion.col = generar_posicion_aleatoria() % 19 + 1;
            while (!esta_posicion_ocupada(*juego, juego->comida[juego->tope_comida].ingrediente[i].posicion.fil, juego->comida[juego->tope_comida].ingrediente[i].posicion.col)) {
                juego->comida[juego->tope_comida].ingrediente[i].posicion.fil = generar_posicion_aleatoria() % 7 + 2;
                juego->comida[juego->tope_comida].ingrediente[i].posicion.col = generar_posicion_aleatoria() % 19 + 1;
            }
            juego->comida[juego->tope_comida].ingrediente[i].tipo = QUESO;
            juego->comida[juego->tope_comida].ingrediente[i].esta_cortado = false;
            juego->comida[juego->tope_comida].ingrediente[i].esta_cocinado = false;
            juego->comida[juego->tope_comida].tope_ingredientes++;
        }

        for (int i = 4; i < 5; i++) {
            juego->comida[juego->tope_comida].ingrediente[i].posicion.fil = generar_posicion_aleatoria() % 7 + 12;
            juego->comida[juego->tope_comida].ingrediente[i].posicion.col = generar_posicion_aleatoria() % 19 + 1;
            while (!esta_posicion_ocupada(*juego, juego->comida[juego->tope_comida].ingrediente[i].posicion.fil, juego->comida[juego->tope_comida].ingrediente[i].posicion.col)) {
                juego->comida[juego->tope_comida].ingrediente[i].posicion.fil = generar_posicion_aleatoria() % 7 + 12;
                juego->comida[juego->tope_comida].ingrediente[i].posicion.col = generar_posicion_aleatoria() % 19 + 1;
            }
            juego->comida[juego->tope_comida].ingrediente[i].tipo = MILANESA;
            juego->comida[juego->tope_comida].ingrediente[i].esta_cortado = false;
            juego->comida[juego->tope_comida].ingrediente[i].esta_cocinado = false;
            juego->comida[juego->tope_comida].tope_ingredientes++;
        }

        for (int i = 5; i < 6; i++) {
            juego->comida[juego->tope_comida].ingrediente[i].posicion.fil = generar_posicion_aleatoria() % 7 + 2;
            juego->comida[juego->tope_comida].ingrediente[i].posicion.col = generar_posicion_aleatoria() % 19 + 1;
            while (!esta_posicion_ocupada(*juego, juego->comida[juego->tope_comida].ingrediente[i].posicion.fil, juego->comida[juego->tope_comida].ingrediente[i].posicion.col)) {
                juego->comida[juego->tope_comida].ingrediente[i].posicion.fil = generar_posicion_aleatoria() % 7 + 2;
                juego->comida[juego->tope_comida].ingrediente[i].posicion.col = generar_posicion_aleatoria() % 19 + 1;
            }
            juego->comida[juego->tope_comida].ingrediente[i].tipo = PAN;
            juego->comida[juego->tope_comida].ingrediente[i].esta_cortado = false;
            juego->comida[juego->tope_comida].ingrediente[i].esta_cocinado = false;
            juego->comida[juego->tope_comida].tope_ingredientes++;
        }
        juego->tope_comida++;
    }
}

//Pre:-
//Pos: carga la informacion de la primera comida
void inicializar_comida(juego_t* juego){
    juego->comida_actual = ENSALADA;
    inicializar_ensalada(juego);
}

//Pre:-
//Pos: carga las ubicaciones de los personajes en el terreno
void inicializar_personajes(juego_t* juego) {

    for (int i = 0; i < 1; i++) {
        juego->stitch.posicion.fil = generar_posicion_aleatoria() % 7 + 2;
        juego->stitch.posicion.col = generar_posicion_aleatoria() % 19 + 1;
        while (!esta_personaje_ocupado(*juego, juego->stitch.posicion.fil, juego->stitch.posicion.col)) {
            juego->stitch.posicion.fil = generar_posicion_aleatoria() % 7 + 2;
            juego->stitch.posicion.col = generar_posicion_aleatoria() % 19 + 1;
        }
        juego->stitch.tipo = STITCH;
    }

    for (int i = 0; i < 1; i++) {
        juego->reuben.posicion.fil = generar_posicion_aleatoria() % 7 + 12;
        juego->reuben.posicion.col = generar_posicion_aleatoria() % 19 + 1;
        while (!esta_personaje_ocupado(*juego, juego->reuben.posicion.fil, juego->reuben.posicion.col)) {
            juego->reuben.posicion.fil = generar_posicion_aleatoria() % 7 + 12;
            juego->reuben.posicion.col = generar_posicion_aleatoria() % 19 + 1;
        }
        juego->reuben.tipo = REUBEN;
    }

    juego->personaje_activo = STITCH;
    juego->reuben.objeto_en_mano = MANOS_VACIAS;
    juego->stitch.objeto_en_mano = MANOS_VACIAS;
}

//Pre: que esten todos los elementos inicializados corrrectamente
//Pos: Muestra el juego en la pantalla
void imprimir_terreno(juego_t juego) {
    char matriz[MAX_PAREDES][MAX_PAREDES];
    int fila = 0;
    int columna = 0;
    char tipo = ' ';

    int tope = 21;
    for (int i = 0; i < tope; i++) {
        for (int j = 0; j < tope; j++) {
            matriz[i][j] = '-';
        }
    }

    
    for (int i = 0; i < juego.tope_paredes; i++) {
        fila = juego.paredes[i].fil;
        columna = juego.paredes[i].col;
        matriz[fila][columna] = '#';   
    }

    matriz[juego.mesa.fil][juego.mesa.col] = '_';

    
    int tope_obstaculos = juego.tope_obstaculos;
    for (int i = 0; i < tope_obstaculos; i++) {
        fila = juego.obstaculos[i].posicion.fil;
        columna = juego.obstaculos[i].posicion.col;
        tipo = juego.obstaculos[i].tipo;

        matriz[fila][columna] = tipo;
    }

    
    int tope_herramientas = juego.tope_herramientas;
    for (int i = 0; i < tope_herramientas; i++) {
        fila = juego.herramientas[i].posicion.fil;
        columna = juego.herramientas[i].posicion.col;
        tipo = juego.herramientas[i].tipo;

        matriz[fila][columna] = tipo;
    }

    for (int i = 0; i < juego.comida[juego.tope_comida - 1].tope_ingredientes; i++) {
        if (juego.stitch.objeto_en_mano != juego.comida[juego.tope_comida - 1].ingrediente[i].tipo &&
            juego.reuben.objeto_en_mano != juego.comida[juego.tope_comida - 1].ingrediente[i].tipo) {
            tipo = juego.comida[juego.tope_comida - 1].ingrediente[i].tipo;
            matriz[juego.comida[juego.tope_comida - 1].ingrediente[i].posicion.fil][juego.comida[juego.tope_comida - 1].ingrediente[i].posicion.col] = tipo;
        }
    }

    
    matriz[juego.stitch.posicion.fil][juego.stitch.posicion.col] = juego.stitch.tipo;
    matriz[juego.reuben.posicion.fil][juego.reuben.posicion.col] = juego.reuben.tipo;

    matriz[juego.salida.fil][juego.salida.col] = PUERTA_DE_SALIDA;

    
    for (int i = 0; i < tope; i++) {
        for (int j = 0; j < tope; j++) {
            printf("%c ", matriz[i][j]);
        }
        printf("\n");
    }
}

//Pre: -
//Pos: devuelve si te podes mover hacia ese lugar
bool hay_agujero(juego_t juego, personaje_t personaje) {
    for (int i = 0; i < juego.tope_obstaculos; i++) {
        if (juego.obstaculos[i].tipo == AGUJEROS) {
            if (juego.obstaculos[i].posicion.fil == personaje.posicion.fil && juego.obstaculos[i].posicion.col == personaje.posicion.col) {
                return true;
            }
        }
    }
    return false;
}

//Pre: -
//Pos: devuelve si te podes mover hacia ese lugar
bool hay_pared_arriba(juego_t juego, personaje_t personaje) {
    for (int i = 0; i < juego.tope_paredes; i++) {
        if (juego.paredes[i].fil == (personaje.posicion.fil - 1) && juego.paredes[i].col == (personaje.posicion.col)) {
            return false;
        }
    }
    return true;
}

//Pre: -
//Pos: devuelve si te podes mover hacia ese lugar
bool hay_pared_abajo(juego_t juego, personaje_t personaje) {
    for (int i = 0; i < juego.tope_paredes; i++) {
        if (juego.paredes[i].fil == (personaje.posicion.fil + 1) && juego.paredes[i].col == (personaje.posicion.col)) {
            return false;
        }
    }
    return true;
}

//Pre: -
//Pos: devuelve si te podes mover hacia ese lugar
bool hay_pared_izquierda(juego_t juego, personaje_t personaje) {
    for (int i = 0; i < juego.tope_paredes; i++) {
        if (juego.paredes[i].fil == personaje.posicion.fil && juego.paredes[i].col == (personaje.posicion.col - 1)) {
            return false;
        }
    }
    return true;
}

//Pre: -
//Pos: devuelve si te podes mover hacia ese lugar
bool hay_pared_derecha(juego_t juego, personaje_t personaje) {
    for (int i = 0; i < juego.tope_paredes; i++) {
        if (juego.paredes[i].fil == personaje.posicion.fil && juego.paredes[i].col == (personaje.posicion.col + 1)) {
            return false;
        }
    }
    return true;
}

//Pre: -
//Pos: devuelve si te podes mover hacia ese lugar
bool fuego_arriba(juego_t juego, personaje_t personaje) {
    for (int i = 0; i < juego.tope_obstaculos; i++) {
        if (juego.obstaculos[i].tipo == FUEGO &&
            juego.obstaculos[i].posicion.fil == (personaje.posicion.fil-1) &&
            juego.obstaculos[i].posicion.col == personaje.posicion.col) {
            return false;
        }
    }
    return true;
}

//Pre: -
//Pos: devuelve si te podes mover hacia ese lugar
bool fuego_abajo(juego_t juego, personaje_t personaje) {
    for (int i = 0; i < juego.tope_obstaculos; i++) {
        if (juego.obstaculos[i].tipo == FUEGO &&
            juego.obstaculos[i].posicion.fil == (personaje.posicion.fil+1) &&
            juego.obstaculos[i].posicion.col == personaje.posicion.col) {
            return false;
        }
    }
    return true;
}

//Pre: -
//Pos: devuelve si te podes mover hacia ese lugar
bool fuego_izquierda(juego_t juego, personaje_t personaje) {
    for (int i = 0; i < juego.tope_obstaculos; i++) {
        if (juego.obstaculos[i].tipo == FUEGO &&
            juego.obstaculos[i].posicion.fil == personaje.posicion.fil &&
            juego.obstaculos[i].posicion.col == (personaje.posicion.col-1)) {
            return false;
        }
    }
    return true;
}

//Pre: -
//Pos: devuelve si te podes mover hacia ese lugar
bool fuego_derecha(juego_t juego, personaje_t personaje) {
    for (int i = 0; i < juego.tope_obstaculos; i++) {
        if (juego.obstaculos[i].tipo == FUEGO &&
            juego.obstaculos[i].posicion.fil == personaje.posicion.fil &&
            juego.obstaculos[i].posicion.col == (personaje.posicion.col+1)) {
            return false;
        }
    }
    return true;
}

//Pre:-
//Pos: no permite que se genere mas de un fuego.
bool hay_fuego(juego_t juego) {
    for (int i = 0; i < juego.tope_obstaculos; i++) {
        if (juego.obstaculos[i].tipo == FUEGO) {
            return true;  
        }
    }
    return false;  
}


//Pre: -
//Pos: devuelve si te podes mover hacia ese lugar
bool horno_arriba(juego_t juego, personaje_t personaje) {
    for (int i = 0; i < juego.tope_herramientas; i++) {
        if (juego.herramientas[i].tipo == HORNO &&
            juego.herramientas[i].posicion.fil == (personaje.posicion.fil-1) &&
            juego.herramientas[i].posicion.col == personaje.posicion.col) {
            return false;
        }
    }
    return true;
}

//Pre: -
//Pos: devuelve si te podes mover hacia ese lugar
bool horno_abajo(juego_t juego, personaje_t personaje){
    for (int i = 0; i < juego.tope_herramientas; i++) {
        if (juego.herramientas[i].tipo == HORNO &&
            juego.herramientas[i].posicion.fil == (personaje.posicion.fil+1) &&
            juego.herramientas[i].posicion.col == personaje.posicion.col) {
            return false;
        }
    }
    return true;
}

//Pre: -
//Pos: devuelve si te podes mover hacia ese lugar
bool horno_izquierda(juego_t juego, personaje_t personaje){
    for (int i = 0; i < juego.tope_herramientas; i++) {
        if (juego.herramientas[i].tipo == HORNO &&
            juego.herramientas[i].posicion.fil == (personaje.posicion.fil) &&
            juego.herramientas[i].posicion.col == personaje.posicion.col-1) {
            return false;
        }
    }
    return true;
}

//Pre: -
//Pos: devuelve si te podes mover hacia ese lugar
bool horno_derecha(juego_t juego, personaje_t personaje){
    for (int i = 0; i < juego.tope_herramientas; i++) {
        if (juego.herramientas[i].tipo == HORNO &&
            juego.herramientas[i].posicion.fil == (personaje.posicion.fil) &&
            juego.herramientas[i].posicion.col == personaje.posicion.col+1) {
            return false;
        }
    }
    return true;
}

//Pre: -
//Pos: devuelve si te podes mover hacia ese lugar
bool mesa_arriba(juego_t juego, personaje_t personaje){
    if(juego.mesa.fil == (personaje.posicion.fil - 1) && juego.mesa.col == personaje.posicion.col){
        return false;
    }
    return true;
}

//Pre: -
//Pos: devuelve si te podes mover hacia ese lugar
bool mesa_abajo(juego_t juego, personaje_t personaje){
    if(juego.mesa.fil == (personaje.posicion.fil + 1) && juego.mesa.col == personaje.posicion.col){
        return false;
    }
    return true;
}

//Pre: No tener las manos ocupadas
//Pos: devuelve si podes agarrar el matafuegos
bool matafuegos(juego_t* juego, personaje_t* personaje) {
    if (personaje->objeto_en_mano != MANOS_VACIAS) {
        return false;
    }
    for (int i = 0; i < juego->tope_herramientas; i++) {
        if (juego->herramientas[i].tipo == MATAFUEGOS) {
            if (juego->herramientas[i].posicion.fil == personaje->posicion.fil && juego->herramientas[i].posicion.col == personaje->posicion.col) {
                juego->tope_herramientas--;
                personaje->objeto_en_mano = MATAFUEGOS;
                return true;
            }
        }
    }
    return false;
}

//Pre: Tener el matafuegos en la mano
//Pos: Elimina al fuego de la pantalla
void apagar_fuego(juego_t* juego, personaje_t* personaje) {
    for(int i = 0; i < juego->tope_obstaculos; i++) {
        if(juego->obstaculos[i].tipo == FUEGO) {
            if (personaje->objeto_en_mano == MATAFUEGOS) {
                if ((calcular_distancia_manhatan(personaje->posicion, juego->obstaculos[i].posicion) <= 2)) {
                    juego->tope_obstaculos--;  
                    personaje->objeto_en_mano = MANOS_VACIAS;  
                    juego->movimientos = 0;
                    printf("El fuego ha sido apagado!\n");
                } else {
                    printf("Estas muy lejos para apagarlo.\n");
                }
            }  else {
                printf("Debes tener el matafuegos en tu mano para apagar el fuego.\n");
            }
        }
    }
}

//Pre: Tener las manos libres
//Pos: devuelve si te podes mover hacia ese lugar
void agarrar_ingrediente(juego_t* juego, personaje_t* personaje){
        for(int j = 0; j < juego->comida[juego->tope_comida-1].tope_ingredientes; j++){
                if (juego->comida[juego->tope_comida-1].ingrediente[j].posicion.fil == personaje->posicion.fil && 
                juego->comida[juego->tope_comida-1].ingrediente[j].posicion.col == personaje->posicion.col) {
                personaje->objeto_en_mano = juego->comida[juego->tope_comida-1].ingrediente[j].tipo;
                return;
            }
     }
}

 //Pre: Estar arriba de un cuchillo
//Pos: el ingrediente figura como cortado 
void cortar_ingrediente(juego_t* juego, personaje_t* personaje) {
    for (int i = 0; i < juego->tope_herramientas; i++) {
        if (juego->herramientas[i].tipo == CUCHILLOS &&
            juego->herramientas[i].posicion.fil == personaje->posicion.fil &&
            juego->herramientas[i].posicion.col == personaje->posicion.col) {
            
            if (personaje->objeto_en_mano != MANOS_VACIAS) {
                for (int j = 0; j < juego->comida[juego->tope_comida - 1].tope_ingredientes; j++) {
                    if (personaje->objeto_en_mano == juego->comida[juego->tope_comida - 1].ingrediente[j].tipo) {
                        juego->comida[juego->tope_comida - 1].ingrediente[j].esta_cortado = true;
                        printf("Ingrediente cortado!\n");
                        return; 
                    }
                }
                
                printf("No se encontró el ingrediente en la mano del personaje.\n");
                return;
            } else {
                printf("El personaje no tiene un ingrediente en la mano.\n");
                return;
            }
        }
    }
    
    printf("No estás arriba de un cuchillo.\n");
}

//Pre: tener un ingredinete en la mano
//Pos: el ingrediente se queda en el casillero que esta ubicado el personaje
void soltar_ingrediente(juego_t* juego, personaje_t* personaje) {
    if (personaje->objeto_en_mano == MANOS_VACIAS) {
        printf("No tienes ningún ingrediente en la mano\n");
        return;
    }
    for (int i = 0; i < juego->tope_comida; i++) {
        for (int j = 0; j < juego->comida[i].tope_ingredientes; j++) {
            if (personaje->posicion.fil == juego->comida[i].ingrediente[j].posicion.fil &&
                personaje->posicion.col == juego->comida[i].ingrediente[j].posicion.col) {
                printf("No puedes soltar el ingrediente aquí, la posición está ocupada\n");
                return;
            }
        }
    }
    for (int i = 0; i < juego->tope_comida; i++) {
        for (int j = 0; j < juego->comida[i].tope_ingredientes; j++) {
            if (personaje->objeto_en_mano == juego->comida[i].ingrediente[j].tipo) {
                juego->comida[i].ingrediente[j].posicion.fil = personaje->posicion.fil;
                juego->comida[i].ingrediente[j].posicion.col = personaje->posicion.col;
                personaje->objeto_en_mano = MANOS_VACIAS;
                return;
            }
        }
    }
}



//Pre: tener un ingrediente en las manos
//Pos: el ingrediente se queda en el casillero de la mesa.
void soltar_ingrediente_mesa(juego_t* juego, personaje_t* personaje) {
    for (int j = 0; j < juego->comida[juego->tope_comida - 1].tope_ingredientes; j++) {
        if (personaje->objeto_en_mano == juego->comida[juego->tope_comida - 1].ingrediente[j].tipo) {
            juego->comida[juego->tope_comida - 1].ingrediente[j].posicion.fil = juego->mesa.fil;
            juego->comida[juego->tope_comida - 1].ingrediente[j].posicion.col = juego->mesa.col;
            personaje->objeto_en_mano = MANOS_VACIAS;
            return;
        }
    }
}

//Pre: tener las manos vacias
//Pos: la mesa queda vacia y el personaje se queda con el ingredinete.
void agarrar_ingrediente_mesa(juego_t* juego, personaje_t* personaje) {
    for (int j = 0; j < juego->comida[juego->tope_comida - 1].tope_ingredientes; j++) {
        if (personaje->objeto_en_mano == MANOS_VACIAS &&
            juego->comida[juego->tope_comida - 1].ingrediente[j].posicion.fil == juego->mesa.fil &&
            juego->comida[juego->tope_comida - 1].ingrediente[j].posicion.col == juego->mesa.col) {
            personaje->objeto_en_mano = juego->comida[juego->tope_comida - 1].ingrediente[j].tipo;
            juego->comida[juego->tope_comida - 1].ingrediente[j].posicion.fil = personaje->posicion.fil; 
            juego->comida[juego->tope_comida - 1].ingrediente[j].posicion.col = personaje->posicion.col;
            return;
        }
    }
}

//Pre: tener un ingrediente que si se pueda cocinar
//Pos: el estado del ingrediente pasa a estar cocinado.
void cocinar_ingrediente(juego_t* juego, personaje_t* personaje) {
    bool cocinado = false;

    for (int i = 0; i < juego->tope_herramientas; i++) {
        if (juego->herramientas[i].tipo == HORNO) {
            if (personaje->objeto_en_mano != MANOS_VACIAS) {
                if (calcular_distancia_manhatan(personaje->posicion, juego->herramientas[i].posicion) == 1) {
                    for (int j = 0; j < juego->comida[juego->tope_comida - 1].tope_ingredientes; j++) {
                        if (personaje->objeto_en_mano == juego->comida[juego->tope_comida - 1].ingrediente[j].tipo) {
                            juego->comida[juego->tope_comida - 1].ingrediente[j].esta_cocinado = true;
                            cocinado = true;
                            printf("Se cocinó el ingrediente.\n");
                            return;
                        }
                    }
                    if (!cocinado) {
                        printf("No tienes ese ingrediente.\n");
                    }
                }else{
                    printf("Estas lejos\n");
                }
            } else {
                printf("No tienes ningún ingrediente en la mano.\n");
            }
        }
    }
}

//Pre: El vector comida_lista debe estar lleno
//Pos: Aparecen los ingredientes de la siguiente comida.
void verificar_entrega_comida(juego_t* juego) {
    if (juego->tope_comida > 0) {
        comida_t comida_actual = juego->comida[juego->tope_comida - 1];

        if (comida_actual.tope_ingredientes == juego->tope_comida_lista) {
            if (juego->comida_actual == ENSALADA) {
                juego->tope_comida_lista = 0;
                juego->comida_actual = PIZZA;
                inicializar_pizza(juego); 
            } else if (juego->comida_actual == PIZZA) {
                juego->tope_comida_lista = 0;
                juego->comida_actual = HAMBURGUESA;
                inicializar_hamburguesa(juego); 
            } else if (juego->comida_actual == HAMBURGUESA) {
                juego->tope_comida_lista = 0;
                juego->comida_actual = SANDWICH;
                inicializar_sandwich(juego); 
            } 
        }
    }
}


//Pre: el personaje debe tener un ingrediente cortado o cocinado y el personaje debe estar parado en la salida(P):
//Pos: El ingrediente se entrega y el perosnaje se queda con las manos vacias para poder seguir haciendo el resto de la comida.
void sumar_ingrediente_a_comida_lista(juego_t* juego, personaje_t* personaje) {
    if (juego->tope_comida_lista < MAX_INGREDIENTES) {
        for (int i = 0; i < juego->comida[juego->tope_comida - 1].tope_ingredientes; i++) {
            if (juego->comida[juego->tope_comida - 1].ingrediente[i].tipo == personaje->objeto_en_mano) {
                if (juego->comida[juego->tope_comida - 1].ingrediente[i].esta_cocinado || juego->comida[juego->tope_comida - 1].ingrediente[i].esta_cortado) {
                    juego->comida[juego->tope_comida - 1].ingrediente[i].posicion.fil = juego->salida.fil;
                    juego->comida[juego->tope_comida - 1].ingrediente[i].posicion.col = juego->salida.col;
                    personaje->objeto_en_mano = MANOS_VACIAS;
                    juego->comida_lista[juego->tope_comida_lista] = juego->comida[juego->tope_comida - 1].ingrediente[i];
                    juego->tope_comida_lista++;
                    printf("Ingredientes agregados correctamente\n");
                    verificar_entrega_comida(juego); 
                    return; 
                }
            }
        }
        printf("Los ingredientes no están cocinados y cortados\n");
        return;
    }
    printf("No se pudieron agregar los ingredientes\n");
}

//Pre: -
//Pos: termina el juego si se logro lo pedido.
bool ganaste(juego_t juego) {
    bool premio = false;
    
    if (juego.precio_total <= 100 && juego.comida_actual == HAMBURGUESA) {
        premio = true;
    } else if (juego.precio_total <= 150 && juego.comida_actual == SANDWICH) {
        premio = true;
    } else if (juego.precio_total > 150 && juego.comida_actual == SANDWICH) {
        premio = true;
    }
    
    return premio;
}

//Pre: -
//Pos: el personaje se podra desplasar por el tablero y hacer acciones.
void realizar_movimiento(juego_t* juego, char movimiento, personaje_t* personaje) {

    switch (movimiento) {
        case ALTERNARNADOR_DE_PERSONAJE:
            if (juego->personaje_activo == STITCH) {
                juego->personaje_activo = REUBEN;
                personaje = &(juego->reuben);
            } else {
                juego->personaje_activo = STITCH;
                personaje = &(juego->stitch);
            }
            break;
        case ARRIBA:
            if (hay_pared_arriba(*juego, *personaje) && fuego_arriba(*juego, *personaje) && horno_arriba(*juego, *personaje) && mesa_arriba(*juego, *personaje)) {
                personaje->posicion.fil = personaje->posicion.fil - 1;
                juego->movimientos++;
            } else {
                printf("No puedes atravesar la pared\n");
            }
            break;
        case ABAJO:
            if (hay_pared_abajo(*juego, *personaje) && fuego_abajo(*juego, *personaje) && horno_abajo(*juego, *personaje) && mesa_abajo(*juego, *personaje)) {
                personaje->posicion.fil = personaje->posicion.fil + 1;
                juego->movimientos++;
            } else {
                printf("No puedes atravesar la pared\n");
            }
            break;
        case IZQUIERDA:
            if (hay_pared_izquierda(*juego, *personaje) && fuego_izquierda(*juego, *personaje) && horno_izquierda(*juego, *personaje)) {
                personaje->posicion.col = personaje->posicion.col - 1;
                juego->movimientos++;
            } else {
                printf("No puedes atravesar la pared\n");
            }
            break;
        case DERECHA:
            if (hay_pared_derecha(*juego, *personaje) && fuego_derecha(*juego, *personaje) && horno_derecha(*juego, *personaje)) {
                personaje->posicion.col = personaje->posicion.col + 1;
                juego->movimientos++;
            } else {
                printf("No puedes atravesar la pared\n");
            }
            break;
        case ACTIVAR_MATAFUEGOS:
            if (personaje->objeto_en_mano != MANOS_VACIAS) {
                apagar_fuego(juego, personaje);
                juego->movimientos = 0;
            } else {
                printf("No tienes el matafuegos\n");
            }
            break;
        case AGARRAR_INGREDIENTE:
            if (personaje->objeto_en_mano == MANOS_VACIAS) {
                agarrar_ingrediente(juego, personaje);
            } else if( personaje->objeto_en_mano != MANOS_VACIAS && !esta_posicion_ocupada(*juego, personaje->posicion.fil, personaje->posicion.col)) {
                soltar_ingrediente(juego, personaje);
            }
            break;
        case CORTAR_INGREDIENTES:
            if (juego->movimientos < 15) {
                cortar_ingrediente(juego, personaje);
            }
            break;
        case SOLTAR_INGREDIENTE_MESA:
            if (calcular_distancia_manhatan(personaje->posicion, juego->mesa) == 1 && personaje->objeto_en_mano != MANOS_VACIAS && juego->movimientos < 15) {
                soltar_ingrediente_mesa(juego, personaje);
            } else {
                agarrar_ingrediente_mesa(juego, personaje);
            }
            break;
        case COCINAR_INGREDIENTES:
            if (juego->movimientos < 15) {
                cocinar_ingrediente(juego, personaje);
            }
            break;
        default:
            printf("Dirección inválida\n");
            break;
    }

    if (juego->movimientos == MOVIMIENTOS_FUEGO && !hay_fuego(*juego)) {
        inicializar_fuego(juego);

        if (juego->obstaculos[juego->tope_obstaculos - 1].posicion.fil >= 1 && juego->obstaculos[juego->tope_obstaculos - 1].posicion.fil <= 9) {
            inicializar_matafuegos_arriba(juego);
        } else {
            inicializar_matafuegos_abajo(juego);
        }
    }

    if (matafuegos(juego, personaje)) {
        printf("Tienes el matafuegos, ahora tienes que apagar el FUEGO(F) para poder seguir cocinando y cortando.\n");
    }

    if (personaje->posicion.fil == juego->salida.fil && personaje->posicion.col == juego->salida.col) {
        sumar_ingrediente_a_comida_lista(juego, personaje);
    }

    printf("Cantidad de movimientos hechos: %i\n", juego->movimientos);
    printf("Estás en la posición [%i][%i]\n", personaje->posicion.fil, personaje->posicion.col);
    printf("Objeto en mano: %c\n", personaje->objeto_en_mano);
    printf("tope ingredientes %i\n", juego->comida[juego->tope_comida - 1].tope_ingredientes);
}

//Pre: -
//Pos: carga toda la informacion del juego.
void inicializar_juego(juego_t* juego, int precio) {
    juego->tope_comida = 0;
    juego->precio_total = precio;
    inicializar_mesa(juego);
    generar_posicion_aleatoria();
    inicializar_paredes(juego);
    inicializar_obstaculos(juego);
    inicializar_herramientas(juego);
    inicializar_comida(juego);
    inicializar_puerta_salida(juego);
    inicializar_personajes(juego);
}

//Pre: tenes que ser stitch o reuben
//Pos: ejecuta las acciones validas.
void realizar_jugada(juego_t* juego, char movimiento){
     if(juego->personaje_activo == STITCH){
        realizar_movimiento(juego, movimiento,&(juego->stitch));
    } else if(juego->personaje_activo == REUBEN){
        realizar_movimiento(juego, movimiento,&(juego->reuben));
    }
}

//Pre:-
//Pos: devuelve si el juego termino.
int estado_juego(juego_t juego){
    int estado = 0;
    personaje_t personaje;
    if (juego.personaje_activo == STITCH) {
        personaje = juego.stitch;
    } else {
        personaje = juego.reuben;
    }
    if(hay_agujero(juego, personaje) ){
        estado = -1;
    }
    if(ganaste(juego)){
        estado = 1;
    }
    return estado;
}