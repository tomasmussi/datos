
#ifndef LECTOR_H_
#define LECTOR_H_
#include <strings.h>
#include <list>
#include "Review.h"

class Lector {

public:
	Lector(std::string archivo, std::string stopwords);
	~Lector();
	std::list<Review*>* leer();

private:
	std::string archivo;
	std::list<std::string>* stopwords;
	std::list<Review*>* reviews;
	void crearStopWords(std::string stopwords);
};

#endif // LECTOR_H_
