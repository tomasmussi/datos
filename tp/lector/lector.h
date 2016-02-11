#ifndef LECTOR_H
#define LECTOR_H

#include <stdbool.h>

#define MAX_BUFFER 15000

/*
 * Estructura creada para poder parsear con facilidad los archivos de entrenamiento
 * Tanto el "labeledTrainData.tsv" que tiene 3 columnas como el "unlabeledTrainData.tsv" que tiene 2 columnas
 * Se creara un lector que tiene:
 * 		1) El archivo a leer.
 * 		2) La cantidad de lineas leidas del archivo.
 * 		3) Cada una de las lineas para pedir los valores necesarios.
 * Cada linea esta representada por: ID, Sentiment y Comentario (Review).
 * Si el archivo no contiene sentiments, se guarda 0.
 * Es responsabilidad del usuario no usar este campo.
 * 
 * */
 
typedef struct linea {
	char id[10];
	bool sentiment;
	char comentario[MAX_BUFFER];
} linea_t;

/* Estructura del lector */
typedef struct lector lector_t;

/* Estructura del iterador */
typedef struct lec_iterador lec_iterador_t;

/* Constructor: crea un lector 
 * PRE: El archivo existe y esta separado por 2 o 3 tabs
 * POST: El lector creado y listo para comenzar a leer
 * */
lector_t* lector_crear(const char* archivo);

/* Destructor: destruye el lector
 * PRE: El lector fue creado.
 * POST: Se destruyen todas las lineas del archivo y el lector mismo.
 * */
void lector_destruir(lector_t* lector);

/* Lectura en si del archivo
 * PRE: El lector fue creado
 * POST: Lee el archivo, guarda internamente las lineas.
 * Devuelve TRUE si la lectura fue exitosa. FALSE si hubo algun error (Seguramente error I/O).
 * */
bool leer(lector_t *lector);

/* PRIMITIVAS DEL ITERADOR */

/* Crea el iterador del archivo
 * PRE: El lector fue creado.
 * POST: Devuelve un iterador
 * */
lec_iterador_t* lec_iter_crear(lector_t *lector);

/* Destruye el iterador
 * PRE: El iterador fue creado.
 * POST: Se destruye el iterador.
 * */
void lec_iter_destruir(lec_iterador_t *iter);

/* Informa si el iterador llego al final de lineas 
 * PRE: El iterador fue creado
 * POST: Devuelve TRUE si esta al final y no hay lineas restantes. FALSE de lo contrario
 * */
bool lec_iter_al_final(lec_iterador_t *iter);

/* Mueve una posicion hacia la siguiente linea del archivo
 * PRE: El iterador fue creado
 * POST: Se mueve a la siguiente linea. Devuelve TRUE si habia una linea nueva, FALSE si la anterior
 * era la ultima linea del archivo.
 * */
bool lec_iter_avanzar(lec_iterador_t *iter);

/*
 * Devuelve la linea actual del archivo.
 * PRE: El iterador fue creado
 * POST: Si esta en una posicion valida, devuelve la linea del archivo.
 * */
linea_t* lec_iter_ver_actual(lec_iterador_t *iter);

#endif // LECTOR_H
