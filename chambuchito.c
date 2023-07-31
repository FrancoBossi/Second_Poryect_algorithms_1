#include <stdio.h>
#include "chambuchito.h"

#define PAN_BLANCO  'B'
#define PAN_INTEGRAL 'I'
#define PAN_AVENA_Y_MIEL 'A'
#define PAN_QUESO_Y_OREGANO  'Q'

const int MEDIDA_MINIMA_PAN = 15;
const int MEDIDA_MAXIMA_PAN = 30;

#define QUESO_DAMBO  'D'
#define QUESO_CHEDDAR  'C'
#define QUESO_GRUYERE 'G'
#define SIN_QUESO 'S'

#define ROAST_BEEF 'R'
#define ATUN  'A'
#define SOJA  'S'
#define POLLITO  'P'
#define NADA_DE_PROTE  'N'

const char CALENTAR_SI = 'S';
const char CALENTAR_NO = 'N';

#define  PAN_BASICO  5
#define PAN_ESPECIAL  8

#define  QUESO_BASICO  5
#define  QUESO_ESPECIAL  8
#define VALOR_SIN_QUESO  0

#define VALOR_ROAST_BEEF 7
#define VALOR_ATUN  9
#define VALOR_POLLO  5
#define VALOR_SOJA  3
#define VALOR_NADA_DE_PROTE  0

const float MULTIPLICADOR = 0.3f;


//Pre:-
//Pos: Muestra un mensaje preguntando que tan largo quiere su chambuchito y carga la variable con la respuesta valida del usuario.
  void preguntar_medida_pan(int* medidas) {
	  printf("¿De que medida desea su chambuchito? podes elegir entre 15 y 30 centimetro. 15 y 30 inclusive.\n");
	  scanf("%i", medidas);
      while(*medidas < MEDIDA_MINIMA_PAN || *medidas > MEDIDA_MAXIMA_PAN ){
	        printf("No tenemos esas medidas.\n");
		    printf("Te repito que nuestras medidas varian entre 15 y 30 centimetros\n");
		     scanf("%i", medidas);
	        } 
            }
//Pre:-
//Pos: Muestra un mensaje preguntando que tipo de pan quiere que sea su chambuchito y carga la variable con la respuesta valida del usuario.
void preguntar_tipo_pan(char* tipo_de_pan){
		printf("¿Que pan desea en su chambuchito?\nTenemos:\n B:Blanco\n I:Integral\n A:Avena y Miel\n Q:Queso y Oregano\n La opcion que usted eliga debe ser en Mayuscula.\n");
        scanf(" %c", tipo_de_pan); 
	      while( *tipo_de_pan != PAN_BLANCO && *tipo_de_pan != PAN_INTEGRAL  &&  *tipo_de_pan != PAN_AVENA_Y_MIEL && *tipo_de_pan != PAN_QUESO_Y_OREGANO ){
			                       printf("Notenemos ese pan. Por favor eliga los sabores que le indicamos.\n"); 
				                   scanf(" %c", tipo_de_pan);
			                        }
	                        }

       //Pre: que haya elegido un tipo de pan valido			
      //Pos: asigna el valor correspondido dependiendo de que tipo es el pan
            int calcular_precio_pan(int tipo_de_pan, int precio_pan){
				  switch (tipo_de_pan) {
                        case PAN_BLANCO:
		                precio_pan = PAN_BASICO;
			            break;

                        case PAN_INTEGRAL:
                        precio_pan =  PAN_BASICO;
                        break;

                        case PAN_AVENA_Y_MIEL:
		                precio_pan =  PAN_ESPECIAL;
			            break;

                        case PAN_QUESO_Y_OREGANO:
						precio_pan = PAN_ESPECIAL;
                        break;

                        default:
                        printf("Opción de pan inválida.\n");
			            break;
                     }
					 return precio_pan;
			}


    //Pre:-
    //Pos: Muestra un mensaje preguntando que tipo de queso quiere en su chambuchito y carga la variable con la respuesta valida del usuario.
	   void preguntar_tipo_queso(char* tipo_de_queso)	{
	   	                        printf("¿Que queso queres en tu chambuchito?\n Tenemos:\n D:Dambo\n C:Cheddar\n G:Gruyere\n S:Sin Queso\nLa opcion que usted eliga debe ser en Mayuscula.\n");
                                scanf(" %c", tipo_de_queso);
	                            while(  *tipo_de_queso != QUESO_DAMBO && *tipo_de_queso != QUESO_CHEDDAR  &&  *tipo_de_queso != QUESO_GRUYERE && *tipo_de_queso != SIN_QUESO ){
	                                     printf("No tenemos ese queso.\n ");
	                                    scanf(" %c", tipo_de_queso);  
	                                         }  
	                             }

      //Pre: que haya elegido un tipo de queso valido			
      //Pos: asigna el valor correspondido dependiendo de que tipo es el queso
      int calcular_precio_queso(int tipo_de_queso, int precio_queso){
		                switch (tipo_de_queso) {
                                     case QUESO_DAMBO:
		                            precio_queso = QUESO_BASICO;
			                        break;

                                    case QUESO_CHEDDAR:
                                    precio_queso = QUESO_BASICO;
                                    break;

                                    case QUESO_GRUYERE:
		                            precio_queso = QUESO_ESPECIAL;
			                        break;

                                    case SIN_QUESO:
                                    precio_queso =  VALOR_SIN_QUESO;
                                    break;

                                    default:
                                    printf("Opción de queso inválida.\n");
			                        break;
                                    }
		        return precio_queso;
	            }

  
     //Pre:-
     //Pos: Muestra un mensaje preguntando que tipo de prote quiere en su chambuchito y carga la variable con la respuesta valida del usuario.
     void preguntar_tipo_prote(char* tipo_de_prote){
                      printf("¿Que proteina queres en tu chambuchito?\nTenemos:\n R:Roast Beef\n A:Atún\n P:Pollo\n S:Soja\n N:Nada de prote\nLa opcion que usted eliga debe ser en Mayuscula.\n");
                      scanf(" %c", tipo_de_prote);

	                  while( *tipo_de_prote != ROAST_BEEF && *tipo_de_prote != ATUN &&  *tipo_de_prote != SOJA &&  *tipo_de_prote != POLLITO  && *tipo_de_prote != NADA_DE_PROTE){
                                              printf("no tenemos esa prote.\n");
			                                 scanf(" %c", tipo_de_prote);
					                                 }
				
	                   } 

        //Pre:- Que el usuario alla elegido un tipo de prote valido y que no sea atun.
		//Pos: Muestra al usuario si quiere calentar su chambuchito y carga la variable con la respuesta valida.

			void asegurar_querer_calentito(char* calentito, char* tipo_de_prote){
		  
				  if((*tipo_de_prote == ROAST_BEEF) ){
				            printf("¿Deseas calentito tu chambuchito? S:SI / N:NO\n");
				            scanf(" %c", calentito);
				       }
		          else if( (*tipo_de_prote == SOJA) ){
                            printf("Deseas calentito tu chambuchito? S:SI / N:NO\n");
					       scanf(" %c", calentito);
				      }   
		         else if( (*tipo_de_prote == POLLITO) ){
					          printf("Deseas calentito tu chambuchito? S:SI / N:NO\n");
					          scanf(" %c", calentito);
				      }
		        else if( (*tipo_de_prote == NADA_DE_PROTE) ){
					         printf("Deseas calentito tu chambuchito? S:SI / N:NO\n");
					         scanf(" %c", calentito);
				      }
		       else{ printf("Entonces no sera necesario calentarlo\n");}

			while(*calentito != CALENTAR_SI && *calentito != CALENTAR_NO && *tipo_de_prote != ATUN){
			     printf("No me dijiste si lo queres calentito o no.\n");
			      scanf(" %c", calentito); }
			    }
		    
        //Pre: que haya elegido un tipo de prote valido			
      //Pos: asigna el valor correspondido dependiendo de que prote se haya elegido
		int calcular_precio_prote(int tipo_de_prote, int precio_prote){
			 switch (tipo_de_prote) {
                         case ROAST_BEEF:
		                 precio_prote = VALOR_ROAST_BEEF;
			             break;

                         case ATUN:
                         precio_prote = VALOR_ATUN;
                         break;

                         case POLLITO:
		                 precio_prote = VALOR_POLLO;
			             break;

                         case SOJA:
                         precio_prote =  VALOR_SOJA;
                         break;

		                 case NADA_DE_PROTE:
		                 precio_prote = VALOR_NADA_DE_PROTE;
			             break;
						 
                         default:
                         printf("Opción de queso inválida.\n");
			             break;
                        }   
						return precio_prote;
		   }
          
		  //Pre: que a cada elemento se le haya asignado correctamente su precio
		  //Pos: asignar el valor total del chambuchito y que sea un entero su precio
		  float calcular_precio_total(float precio_pan_flotante, float precio_queso_flotante, float precio_prote_flotante, float valor_medida_flotante){
      
		     float precio_total = (precio_pan_flotante + precio_queso_flotante + precio_prote_flotante) * (valor_medida_flotante);
  
			return precio_total;
		 }

//int main(){
  void calcular_precio_chambuchito(int* precio){
    int medidas = 0;
     preguntar_medida_pan(&medidas);
        
    char tipo_de_pan = ' ';
	preguntar_tipo_pan(&tipo_de_pan);
	int precio_pan = 0;
	precio_pan = (int)tipo_de_pan;
	precio_pan = calcular_precio_pan(  tipo_de_pan, precio_pan);
	float precio_pan_flotante = (float)precio_pan;
	     	        
	char tipo_de_queso = ' ';
	preguntar_tipo_queso(&tipo_de_queso);
	int precio_queso = 0;
	precio_queso = (int)tipo_de_queso;
	precio_queso = calcular_precio_queso( tipo_de_queso, precio_queso);
	float precio_queso_flotante = (float)precio_queso; 

	char tipo_de_prote = ' ';
	char calentito = ' ';
    preguntar_tipo_prote(&tipo_de_prote);  
	 
    asegurar_querer_calentito(&calentito, &tipo_de_prote);


	int precio_prote = 0; 
	   
	precio_prote = (int)tipo_de_prote;

	precio_prote = calcular_precio_prote(tipo_de_prote, precio_prote);
	float precio_prote_flotante = (float)precio_prote;

	float medida_flotante = (float)medidas;

	float valor_medida_flotante = (MULTIPLICADOR * medida_flotante);

    float precio_total = 0.0; 
	precio_total = calcular_precio_total(precio_pan_flotante, precio_queso_flotante, precio_prote_flotante, valor_medida_flotante);

	 *precio = (int)precio_total;

	 printf("El Precio total  es: -%i-\n", *precio);
      			    	
	//return 0;
 //}
  }