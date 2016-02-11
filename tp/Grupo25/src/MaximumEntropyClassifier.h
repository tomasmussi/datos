
#ifndef MAXIMUMENTROPYCLASSIFIER_H_
#define MAXIMUMENTROPYCLASSIFIER_H_

#include <iostream>
#include <vector>
#include <list>
#include <map>
#include <math.h>
#include "Review.h"
#include "MatrizDispersa.h"


#include <fstream>
#include <map>

#define MAX_ITERACIONES 1000
#define VALGRIND_ITERACIONES 10

class MaximumEntropyClassifier {
public:
	MaximumEntropyClassifier(size_t columnas);
	~MaximumEntropyClassifier();
	void entrenar(MatrizDispersa* trainData, std::vector<bool>* sentiment);
	std::map<std::string, double>* clasificar(std::vector<std::vector<bool>*>* datos, std::list<Review*>* nuevos);
	double costo(MatrizDispersa* trainData, std::vector<bool>* sentiments);

private:
	std::vector<double>* pesos;
	double alfa;
	double lambda;
	void gradiente(MatrizDispersa* trainData, std::vector<bool>* sentiments);
	double estimarProbabilidad(std::map<size_t, double>* features);
	double estimarProbabilidad(std::vector<bool>* features);
	double sigmoid(double x);
};

#endif // MAXIMUMENTROPYCLASSIFIER_H_
