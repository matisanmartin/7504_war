#ifndef COMMON_H
#define COMMON_H

#include "lista.hpp"
#include "soldado.hpp"
#include "nodo.hpp"

#define MSJ_ERROR_VALIDAR_ARGUMENTOS "Argumentos incorrectos"
#define MSJ_ERROR_ABRIR_ARCHIVO "No se ha podido leer el archivo o algun dato es invalido"
#define SEP_ESPACIO " "
#define MSJ_MODO_INCOMPATIBLE "Modo Incompatible"

#define NOMBRE_EQUIPO "#VinePorLosPuntos"

#define MODO_EVASIVO "evasivo"
#define MODO_DEFAULT "default"
#define MODO_AGRESIVO "agresivo"

#define EVASIVO 'E'
#define DEFAULT 'D'
#define AGRESIVO 'A'

#define ATAQUE 'A'
#define DEFENSA 'D'

#define FACTOR_VIDA_MAX 0.9
#define FACTOR_VIDA_MIN 0.25
#define FACTOR_TURNO_DEFECTO 0.8
#define FACTOR_ENERGIA_DEFECTO 1.41

#define LIMITE_RANDOM 2

#define PRECISION_DEFENSA 1
#define PRECISION_ATAQUE 0


typedef enum{OK,ERROR_ABRIR_ARCHIVO,ERROR_TERRITORIO_INVALIDO,
			 ERROR_CANTIDAD_ARGUMENTOS,ERROR_ARGUMENTO_INVALIDO,ERROR_NUMERO_TURNO,
			 ERROR_NOMBRE_REPETIDO,ERROR_POSICION_INVALIDA,ERROR_ENERGIA,ERROR_INFLUENCIA}StatusT;
			 



#endif
