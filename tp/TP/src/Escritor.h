
#ifndef ESCRITOR_H_
#define ESCRITOR_H_

#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#define PESOS "pesos"

class Escritor {
public:
	Escritor();
	~Escritor();
	void escribir(std::string nombre, std::map<std::string, double>* respuestas);
	void escribirPesos(std::vector<double>* pesos, std::string directorio);
};

#endif // ESCRITOR_H_
