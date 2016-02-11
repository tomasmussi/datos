
#ifndef ESCRITOR_H_
#define ESCRITOR_H_

#include <iostream>
#include <fstream>
#include <map>

class Escritor {
public:
	Escritor();
	~Escritor();
	void escribir(std::string nombre, std::map<std::string, double>* respuestas);
};

#endif // ESCRITOR_H_
