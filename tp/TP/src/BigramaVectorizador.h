
#ifndef BIGRAMAVECTORIZADOR_H_
#define BIGRAMAVECTORIZADOR_H_

#include "Review.h"
#include <map>
#include <vector>
#include "MatrizDispersa.h"

#define MAX_BIGRAMAS 30000
#define LIMITE_SUPERIOR 0.999
#define LIMITE_INFERIOR 0.001


class BigramaVectorizador {
public:
	BigramaVectorizador();
	~BigramaVectorizador();
	size_t convertir(const std::list<Review*> *reviews);
	MatrizDispersa* getDatos();
	std::vector<bool>* getSentiments();
	std::vector<std::vector<bool>*>* transformar(std::list<Review*>* reviews);

private:
	std::map<std::string, size_t>* bigramas;
	MatrizDispersa* datos;
	std::vector<bool>* sentiments;
	size_t columnas;
};

#endif /* BIGRAMAVECTORIZADOR_H_ */
