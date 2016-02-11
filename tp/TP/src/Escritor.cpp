
#include "Escritor.h"

Escritor::Escritor() {
}

Escritor::~Escritor() {
}

void Escritor::escribir(std::string nombre, std::map<std::string, double>* respuestas){
	std::ofstream archivo;
	archivo.open(nombre.c_str());
	if (archivo.is_open()){
		// Headers
		archivo << "\"id\",\"sentiment\"" << std::endl;
		for (std::map<std::string, double>::iterator iter = respuestas->begin(); iter != respuestas->end(); ++iter){
			archivo << iter->first << "," << iter->second << std::endl;
		}
		archivo.close();
	}
}

void Escritor::escribirPesos(std::vector<double>* pesos, std::string nombreArchivo){
	std::ofstream archivo;
	archivo.open(nombreArchivo.c_str());
	if (archivo.is_open()){
		for (std::vector<double>::iterator iter = pesos->begin(); iter != pesos->end(); ++iter){
			archivo << (*iter) << std::endl;
		}
		archivo.close();
	}
}
