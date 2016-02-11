#ifndef HASHVECTORIZADOR_H_
#define HASHVECTORIZADOR_H_


#include "Review.h"
#include <map>
#include <vector>
#include "MatrizDispersa.h"


#define A 54059 /* a prime */
#define B 76963 /* another prime */
#define C 28879

class HashVectorizador {
public:
	HashVectorizador();
	~HashVectorizador();
	unsigned hash_str(const char* s);
	size_t convertir(const std::list<Review*> *reviews);
	MatrizDispersa* getDatos();
	std::vector<bool>* getSentiments();
	std::vector<std::vector<bool>*>* transformar(std::list<Review*>* reviews);

private:
	MatrizDispersa* datos;
	std::vector<bool>* sentiments;
	size_t columnas;
};

#endif /* HASHVECTORIZADOR_H_ */
