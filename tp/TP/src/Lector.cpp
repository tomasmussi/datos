
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "Lector.h"

using namespace std;

Lector::Lector(std::string archivo, std::string stopwords) {
	this->archivo = archivo;
	this->stopwords = new std::list<std::string>();
	this->crearStopWords(stopwords);
	this->reviews = new std::list<Review*>();
}

void Lector::crearStopWords(std::string stopwords){
	if (stopwords != ""){
		ifstream archivo(stopwords.c_str());
		if (archivo.is_open()) {
			string linea;
			while (getline(archivo, linea)) {
				this->stopwords->push_back(linea);
			}
			archivo.close();
		}
	}
}


std::list<Review*>* Lector::leer() {
	ifstream archivo(this->archivo.c_str());
	if (archivo.is_open()) {
		string linea;
		getline(archivo, linea); // Headers
		while (getline(archivo, linea)) {
			std::string id = "";
			bool sentiment = false;
			std::string review = "";

			std::istringstream iss(linea);
			std::string token;
			std::getline(iss, token, '\t');
			id = token;
			std::getline(iss, token, '\t');
			std::string segundaCol = token;
			if (segundaCol == "0" || segundaCol == "1") {
				sentiment = (segundaCol != "0");
				std::getline(iss, token, '\t');
				review = token;
			} else {
				review = segundaCol;
			}
			this->reviews->push_back(new Review(id, sentiment, review, this->stopwords));
		}
		archivo.close();
	}
	return this->reviews;
}

Lector::~Lector() {
	delete this->stopwords;
	for (std::list<Review*>::iterator it = this->reviews->begin(); it != this->reviews->end(); ++it) {
		delete (*it);
	}
	delete this->reviews;
}

bool Lector::leerPesos(std::vector<double>* pesos){
	if (!this->existeArchivo(this->archivo)){
		return false;
	}
	ifstream archivo(this->archivo.c_str());
	if (archivo.is_open()) {
		string linea;
		size_t indice = 0;
		while (getline(archivo, linea)) {
			(*pesos)[indice] = atof(linea.c_str());
			indice++;
		}
		archivo.close();
	}
	return true;
}


inline bool Lector::existeArchivo(const std::string& name) {
    ifstream f(name.c_str());
    if (f.good()) {
        f.close();
        return true;
    } else {
        f.close();
        return false;
    }
}
