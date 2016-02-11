
#include "Lector.h"
#include "Review.h"
#include "HashVectorizador.h"
#include "MaximumEntropyClassifier.h"
#include "Escritor.h"
#include "MatrizDispersa.h"

#define STOPWORDS "stopwords"
#define ENTRENAMIENTO "labeledTrainData.tsv"
#define TEST "testData.tsv"
#define SUBMISION "hash_tp_final.csv"

std::string obtenerDirectorio(int argc, char* argv[]){
	std::string directorio = "";
	if (argc >= 2){
		directorio = argv[1];
	} else {
		directorio = "/home/tomas/repos/datos/tp/archivos/";
	}
	if (directorio[directorio.size() - 1] != '/'){
		directorio += '/';
	}
	return directorio;
}


int main(int argc, char* argv[]) {

	std::string directorio = obtenerDirectorio(argc,argv);
	std::cout << "Leyendo y escribiendo del directorio: " << directorio << std::endl;

	Lector archivoEntrenamiento(directorio + ENTRENAMIENTO, directorio + STOPWORDS);
	std::list<Review*>* reviewsEntrenamiento = archivoEntrenamiento.leer();
	std::cout << "Archivo de entrenamiento leido\n";

	HashVectorizador vectorizador;
	size_t columnas = vectorizador.convertir(reviewsEntrenamiento);
	std::cout << "Features de entrenamiento extraidos. Utilizando " << columnas << " columnas\n";

	clock_t begin = clock();
	MaximumEntropyClassifier clasificador(columnas);
	clasificador.entrenar(vectorizador.getDatos(), vectorizador.getSentiments());
	clock_t end = clock();
	double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
	std::cout << "Entrenamiento del clasificador tardo " << elapsed_secs << " segundos" << std::endl;

	Lector lectorNuevo(directorio + TEST, directorio + STOPWORDS);
	std::list<Review*>* reviewsClasificar = lectorNuevo.leer();

	std::vector<std::vector<bool>*>* featuresClasificar = vectorizador.transformar(reviewsClasificar);
	std::cout << "Features a clasificar extraidos\n";

	std::map<std::string, double>* respuestas = clasificador.clasificar(featuresClasificar, reviewsClasificar);
	std::cout << "Features clasificados\n";

	Escritor escritor;
	escritor.escribir(directorio + SUBMISION, respuestas);
	std::cout << "Archivo de submision escrito: " << directorio << SUBMISION << "\n";

	for (std::vector<std::vector<bool>*>::iterator it = featuresClasificar->begin(); it != featuresClasificar->end(); ++it){
		delete (*it);
	}
	delete featuresClasificar;
	delete respuestas;
	return 0;
}
