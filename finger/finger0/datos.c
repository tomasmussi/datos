#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#define MAX 10000

typedef struct datos {
	size_t positivos, cantidad;
	unsigned long longitud;
	bool amazing_positivo;	
} datos_t;


void agregar_informacion(datos_t *datos, char *linea){
	int i;
	for (i = 0; i < strlen(linea) && linea[i] != '\t'; i++){		
	}
	i++;
	if (linea[i] == '1'){
		datos->positivos++;
	}
	datos->cantidad++;

}


void algoritmo_1(){
	FILE *archivo = fopen("labeledTrainData.tsv", "r");
	int caracter;
	char buffer[MAX];
	size_t indice = 0;
	datos_t *datos = malloc(sizeof(datos_t));
	datos->cantidad = 0;
	datos->positivos = 0;
	size_t cantidad = 0;
	while ((caracter = fgetc(archivo)) != EOF){		
		if (caracter == '\n' && caracter != EOF){
			cantidad++;
			buffer[indice++] = '\0';
			/*if (cantidad >= 24500)
				printf("%s\n", buffer);*/
			indice = 0;
			agregar_informacion(datos, buffer);
		} else if (caracter != EOF){
			buffer[indice++] = caracter;
		}		
	}
	fclose(archivo);
	printf("Cantidad: %zd\n", cantidad);
	printf("Cantidad positivos: %zd\n", datos->positivos);
	printf("Cantidad negativos: %zd\n", datos->cantidad - datos->positivos);
	free(datos);
}



int main(void){
	algoritmo_1();
}
