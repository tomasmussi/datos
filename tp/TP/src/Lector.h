
#ifndef LECTOR_H_
#define LECTOR_H_
#include <strings.h>
#include <list>
#include <vector>
#include <stdlib.h>
#include "Review.h"

class Lector {

public:
	Lector(std::string archivo, std::string stopwords);
	~Lector();
	std::list<Review*>* leer();
	bool leerPesos(std::vector<double>* pesos);

private:
	std::string archivo;
	std::list<std::string>* stopwords;
	std::list<Review*>* reviews;
	void crearStopWords(std::string stopwords);
	inline bool existeArchivo(const std::string& name);
};

#endif // LECTOR_H_
