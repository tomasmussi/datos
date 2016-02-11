
#include "HashVectorizador.h"

HashVectorizador::HashVectorizador() {
	this->datos = new MatrizDispersa();
	this->sentiments = new std::vector<bool>(25000);
	this->columnas = 0;
}

HashVectorizador::~HashVectorizador() {
	delete this->sentiments;
	delete this->datos;
}

unsigned HashVectorizador::hash_str(const char* s) {
   unsigned h = 31 /* also prime */;
   while (*s) {
     h = (h * A) ^ (s[0] * B);
     s++;
   }
   return h % C; // or return h % C;
}

size_t HashVectorizador::convertir(const std::list<Review*> *reviews) {
	// Itero cada review

	size_t cantidad = 0;
	for (std::list<Review*>::const_iterator it = reviews->begin(); it != reviews->end(); ++it) {
		std::list<std::string>* lista = (*it)->getReview();
		// La primera columna vale 1 siempre
		this->datos->agregarValor(cantidad, 0, 1);
		for (std::list<std::string>::iterator palabra = lista->begin(); palabra != lista->end(); ++palabra) {
			unsigned hash = this->hash_str((*palabra).c_str());
			this->datos->agregarValor(cantidad, hash + 1, 1);
		}
		(*this->sentiments)[cantidad] = (*it)->isSentiment();
		cantidad++;
	}
	this->columnas = C + 1;
	return this->columnas;
}

std::vector<std::vector<bool>*>* HashVectorizador::transformar(std::list<Review*>* reviews){
	size_t cantidad = 0;
	std::vector<std::vector<bool>*>* respuesta = new std::vector<std::vector<bool>*>(25000);
	for (std::list<Review*>::const_iterator it = reviews->begin(); it != reviews->end(); ++it) {
		std::list<std::string>* lista = (*it)->getReview();
		(*respuesta)[cantidad] = new std::vector<bool>(this->columnas);
		// La primera columna vale 1 siempre
		(*(*respuesta)[cantidad])[0] = true;
		for (std::list<std::string>::iterator palabra = lista->begin(); palabra != lista->end(); ++palabra) {
			unsigned hash = this->hash_str((*palabra).c_str());
			(*(*respuesta)[cantidad])[hash +1] = true;
		}
		cantidad++;
	}
	return respuesta;
}

MatrizDispersa* HashVectorizador::getDatos(){
	return this->datos;
}

std::vector<bool>* HashVectorizador::getSentiments(){
	return this->sentiments;
}

