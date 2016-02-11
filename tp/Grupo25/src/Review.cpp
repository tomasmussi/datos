#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>
#include <list>
#include "Review.h"


Review::Review(std::string id, bool sentiment, std::string review, const std::list<std::string>* stopwords){
	this->id = id;
	this->sentiment = sentiment;
	this->review = this->limpiar(review, stopwords);
}

Review::~Review() {
	delete this->review;
}


bool agregar_caracter(const char c){
	return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}

std::list<std::string>* Review::limpiar(std::string texto,const std::list<std::string>* stopwords){
	// Convertir a minusculas
	std::transform(texto.begin(), texto.end(), texto.begin(), ::tolower);

	// Borrar HTML tags
	while (texto.find("<") != texto.npos) {
		texto.replace(texto.find("<"), texto.find("/>") - texto.find("<") + 2," ");
	}

	std::string nuevo = "";
	// Sacar letras de mas
	for (std::string::iterator it = texto.begin(); it != texto.end(); ++it){
		if (agregar_caracter(*it)){
			nuevo += *it;
		} else {
			nuevo += ' ';
		}
	}

	std::istringstream iss(nuevo);
	std::string palabra = "";

	std::list<std::string> *final = new std::list<std::string>();
	while(std::getline(iss, palabra, ' ')){
		this->trim(palabra);
		if (palabra != ""){
			if (std::find(stopwords->begin(), stopwords->end(), palabra) == stopwords->end()){
				final->push_back(palabra);
			}
		}
	}
	return final;
}


// trim from start
std::string &Review::ltrim(std::string &s) {
	s.erase(s.begin(), std::find_if(s.begin(), s.end(), std::not1(std::ptr_fun<int, int>(std::isspace))));
	return s;
}

// trim from end
std::string &Review::rtrim(std::string &s) {
	s.erase(std::find_if(s.rbegin(), s.rend(), std::not1(std::ptr_fun<int, int>(std::isspace))).base(), s.end());
	return s;
}

// trim from both ends
std::string &Review::trim(std::string &s) {
	return ltrim(rtrim(s));
}
