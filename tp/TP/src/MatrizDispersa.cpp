
#include "MatrizDispersa.h"


MatrizDispersa::MatrizDispersa() {
	this->matriz = new std::map<size_t, std::map<size_t, double>* >();
}

MatrizDispersa::~MatrizDispersa() {
	for (std::map<size_t,  std::map<size_t, double>*>::iterator iter = this->matriz->begin(); iter != this->matriz->end(); ++iter){
		delete iter->second;
	}
	delete this->matriz;
}

size_t MatrizDispersa::filas(){
	return this->matriz->size();
}

void MatrizDispersa::agregarValor(size_t fila, size_t columna, double valor){
	if ((*this->matriz)[fila] == NULL){
		(*this->matriz)[fila] = new std::map<size_t, double>();
	}
	(*(*this->matriz)[fila])[columna] = valor;
}

void MatrizDispersa::adicionarValor(size_t fila, size_t columna, double valor){
	if ((*this->matriz)[fila] == NULL){
		(*this->matriz)[fila] = new std::map<size_t, double>();
	}
	(*(*this->matriz)[fila])[columna] += valor;
}

std::map<size_t, double>* MatrizDispersa::getFila(size_t fila){
	return (*this->matriz)[fila];
}

