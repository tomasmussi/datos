
#include "BigramaVectorizador.h"

BigramaVectorizador::BigramaVectorizador() {
	this->bigramas = new std::map<std::string, size_t>();
	this->datos = new MatrizDispersa();
	this->sentiments = new std::vector<bool>(25000);
	this->columnas = 0;
}

BigramaVectorizador::~BigramaVectorizador() {
	delete this->bigramas;
	delete this->sentiments;
	delete this->datos;
}

size_t BigramaVectorizador::convertir(const std::list<Review*> *reviews) {
	// Itero cada review
	std::map<std::string, size_t> ocurrencias;
	for (std::list<Review*>::const_iterator it = reviews->begin(); it != reviews->end(); ++it) {
		std::list<std::string>* lista = (*it)->getReview();

		std::list<std::string>::iterator adelantado = lista->begin();
		std::list<std::string>::iterator atrasado = lista->begin();
		adelantado++;
		std::map<std::string, size_t> ocurrenciasReview;
		while (adelantado != lista->end()){
			std::string bigrama = (*atrasado) + "#" + (*adelantado);
			ocurrenciasReview[bigrama] = 1;
			adelantado++;
			atrasado++;
		}
		for (std::map<std::string, size_t>::iterator it = ocurrenciasReview.begin(); it != ocurrenciasReview.end(); ++it){
			if (ocurrencias.find(it->first) != ocurrencias.end()){
				ocurrencias[it->first] += 1;
			} else {
				ocurrencias[it->first] = 1;
			}
		}
	}

	double tamanio = reviews->size();
	std::multimap<size_t, std::string> ocurrenciasInvertido;
	for (std::map<std::string,size_t>::iterator ocurrencia = ocurrencias.begin(); ocurrencia != ocurrencias.end(); ++ocurrencia) {
		double apariciones = ocurrencia->second / tamanio;
		if (apariciones > LIMITE_INFERIOR && apariciones < LIMITE_SUPERIOR){
			ocurrenciasInvertido.insert(std::pair<size_t, std::string>(ocurrencia->second, ocurrencia->first));
		}
	}

	size_t posicionFinal = 0;
	std::multimap<size_t, std::string>::iterator ocurrencia = ocurrenciasInvertido.begin();
	while(ocurrencia != ocurrenciasInvertido.end() && posicionFinal < MAX_BIGRAMAS) {
		(*this->bigramas)[ocurrencia->second] = posicionFinal++;
		ocurrencia++;
	}

	size_t cantidad = 0;
	for (std::list<Review*>::const_iterator it = reviews->begin(); it != reviews->end(); ++it) {

		std::list<std::string>* lista = (*it)->getReview();
		this->datos->agregarValor(cantidad, 0, 1); // La primera columna vale 1 siempre

		std::list<std::string>::iterator adelantado = lista->begin();
		std::list<std::string>::iterator atrasado = lista->begin();
		adelantado++;
		while (adelantado != lista->end()){
			std::string bigrama = (*atrasado) + "#" + (*adelantado);
			if (this->bigramas->find(bigrama) != this->bigramas->end()){
				this->datos->agregarValor(cantidad, (*this->bigramas)[bigrama] + 1, 1);
			}
			adelantado++;
			atrasado++;
		}
		(*this->sentiments)[cantidad] = (*it)->isSentiment();
		cantidad++;
	}
	this->columnas = posicionFinal + 1;
	return this->columnas;
}


std::vector<std::vector<bool>*>* BigramaVectorizador::transformar(std::list<Review*>* reviews){
	size_t cantidad = 0;
	std::vector<std::vector<bool>*>* respuesta = new std::vector<std::vector<bool>*>(25000);
	for (std::list<Review*>::const_iterator it = reviews->begin(); it != reviews->end(); ++it) {
		std::list<std::string>* lista = (*it)->getReview();
		(*respuesta)[cantidad] = new std::vector<bool>(this->columnas);
		(*(*respuesta)[cantidad])[0] = true; // La primera columna vale 1 siempre

		std::list<std::string>::iterator adelantado = lista->begin();
		std::list<std::string>::iterator atrasado = lista->begin();
		adelantado++;
		while (adelantado != lista->end()){
			std::string bigrama = (*atrasado) + "#" + (*adelantado);
			if (this->bigramas->find(bigrama) != this->bigramas->end()){
				(*(*respuesta)[cantidad])[(*this->bigramas)[bigrama] + 1] = true;
			}
			adelantado++;
			atrasado++;
		}
		cantidad++;
	}
	return respuesta;
}

MatrizDispersa* BigramaVectorizador::getDatos(){
	return this->datos;
}

std::vector<bool>* BigramaVectorizador::getSentiments(){
	return this->sentiments;
}

