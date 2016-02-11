
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

