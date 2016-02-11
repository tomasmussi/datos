#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "lector.h"

#define MAX_ARCHIVO 150
#define TAM_INICIAL 25000
#define OFFSET 32

/* Estructura interna del lector del archivo */
struct lector {
	char archivo[MAX_ARCHIVO];
	size_t cantidad; // Tamanio del vector
	size_t ultimo; // Posicion del vector de la ultima linea
	linea_t **vector;
};

/* Estructura interna del iterador del archivo */
struct lec_iterador {
	lector_t *lector;
	size_t posicion_vector;
};

/****************************************
 * 										*
 * 		FUNCIONES AUXILIARES			*
 * 										*
 * **************************************/
/* Cuenta la cantidad ocurrencias de un tab en la linea */
size_t contar_tabs(const char *buffer);

/* Si encuentra un tag de HTML, avanza posiciones para evitar guardarlo */
void avanzar_siguiente_tag(int *posicion, const char *buffer);

/* Define si hay que agregar un caracter al comentario de lo leido del archivo */
bool agregar_caracter(const char caracter);

size_t contar_tabs(const char *buffer){
	int subindice = 0;
	size_t cantidad = 0;
	while (buffer[subindice]){
		if (buffer[subindice] == '\t')
			cantidad++;
		subindice++;
	}
	return cantidad;
}

void avanzar_siguiente_tag(int *posicion, const char *buffer){
	if (buffer[*posicion] == '<'){
		while (buffer[*posicion] != '>' && buffer[*posicion] != '\n')
			(*posicion)++;
		(*posicion)++;
		avanzar_siguiente_tag(posicion, buffer);
	}
}
bool agregar_caracter(const char caracter){
	return caracter != '\"' && caracter != '\\';
}

void parsear_columna(int *posicion, char *columna, const char *buffer){
	int sub_linea = 0;
	while (buffer[*posicion] != '\t' && buffer[*posicion] != '\n'){
		avanzar_siguiente_tag(posicion, buffer);
		if (agregar_caracter(buffer[*posicion])){
			// Guardar en minusculas.
			if (buffer[*posicion] >= 'A' && buffer[*posicion] <= 'Z'){
				columna[sub_linea++] = buffer[*posicion] + OFFSET;
			} else {
				columna[sub_linea++] = buffer[*posicion];
			}
		}
		(*posicion)++;
	}
	columna[sub_linea] = '\0';
	(*posicion)++;
}

linea_t* parsear(const char *buffer){
	linea_t *linea = malloc(sizeof(linea_t));
	int subindice = 0;

	// Parsear el id
	parsear_columna(&subindice, linea->id, buffer);

	// Parseo el sentimiento del review 
	// SI LO HAY
	linea->sentiment = false;
	if (contar_tabs(buffer) > 1){ // 1 tab = 2 columnas, 2 tabs = 3 columnas
		char sens[2];
		parsear_columna(&subindice, sens, buffer);
		linea->sentiment = sens[0] == '1';
	}
	
	// Parseo el comentario	
	parsear_columna(&subindice, linea->comentario, buffer);
	return linea;
}

bool realocar_vector(lector_t *lector){
	linea_t **nuevo_vector = realloc(lector->vector, (lector->cantidad * 2) * sizeof(linea_t));
	if (nuevo_vector == NULL){
		return false;
	}
	lector->vector = nuevo_vector;
	lector->cantidad *= 2;
	return true;
}

bool leer(lector_t *lector){
	FILE *archivo = fopen(lector->archivo, "r");
	char buffer[MAX_BUFFER];
	fgets(buffer, MAX_BUFFER, archivo); // Skip de los headers		
	while(fgets(buffer, MAX_BUFFER, archivo) != NULL){
		if (lector->ultimo == lector->cantidad){
			if (!realocar_vector(lector)){
				fclose(archivo);
				return false;
			}
		}
		lector->vector[lector->ultimo++] = parsear(buffer);
	}
	return fclose(archivo) == 0;
}

/****************************************
 * 										*
 * 		FIN FUNCIONES AUXILIARES		*
 * 										*
 * **************************************/


/****************************************
 * 										*
 * 		PRIMITIVAS						*
 * 										*
 * **************************************/
lector_t* lector_crear(const char* archivo){
	lector_t* lector = malloc(sizeof(lector_t));
	if (lector == NULL)
		return NULL;
	strcpy(lector->archivo, archivo);	
	lector->vector = malloc(TAM_INICIAL * sizeof(linea_t));
	if (lector->vector == NULL){
		free(lector);
		return NULL;
	}
	lector->cantidad = TAM_INICIAL;
	lector->ultimo = 0;
	return lector;
}

void lector_destruir(lector_t *lector){
	size_t i = 0;
	for (i = 0; i < lector->ultimo; i++){
		free(lector->vector[i]);
	}
	free(lector->vector);
	free(lector);
}
/****************************************
 * 										*
 * 		FIN PRIMITIVAS					*
 * 										*
 * **************************************/

lec_iterador_t* lec_iter_crear(lector_t *lector){
	lec_iterador_t *iter = malloc(sizeof(lec_iterador_t));
	if (iter == NULL)
		return NULL;
	iter->lector = lector;
	iter->posicion_vector = 0;
	return iter;
}

void lec_iter_destruir(lec_iterador_t *iter){
	free(iter);
}

bool lec_iter_al_final(lec_iterador_t *iter){
	return iter->lector->ultimo == iter->posicion_vector;
}

bool lec_iter_avanzar(lec_iterador_t *iter){
	if (lec_iter_al_final(iter))
		return false;
	iter->posicion_vector++;
	return iter->posicion_vector == iter->lector->ultimo;
}

linea_t* lec_iter_ver_actual(lec_iterador_t *iter){
	if (!lec_iter_al_final(iter))
		return iter->lector->vector[iter->posicion_vector];
	return NULL;
}
