#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "lector.h"

int main(int argc, char** argv){
	char file[150] = "prueba.tsv";
	if (argc > 1){
		strcpy(file, argv[1]);
	}
	printf("Tratando de leer: %s\n", file);
	lector_t *lector = lector_crear(file);	
	leer(lector);

	lec_iterador_t *iter = lec_iter_crear(lector);
	while (! lec_iter_al_final(iter)){
		linea_t *actual = lec_iter_ver_actual(iter);
		printf("%s\n", actual->id);
		lec_iter_avanzar(iter);
	}
	lec_iter_destruir(iter);
	lector_destruir(lector);
	return 0;
}
