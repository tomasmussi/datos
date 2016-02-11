
#include "MaximumEntropyClassifier.h"


MaximumEntropyClassifier::MaximumEntropyClassifier(size_t columnas) {
	this->pesos = new std::vector<double>(columnas);
	this->alfa = 1;
	this->lambda = 10/9;
	for (size_t i = 0; i < columnas; i++){
		(*this->pesos)[i] = 0;
	}
}

MaximumEntropyClassifier::~MaximumEntropyClassifier() {
	delete this->pesos;
}

/*
 * Calculo del gradiente. Para mas informacion ver el codigo que mando Luis de Logistict Regression
 * */
void MaximumEntropyClassifier::gradiente(MatrizDispersa* trainData, std::vector<bool>* sentiments){
	std::vector<double> gradiente(this->pesos->size());
	std::vector<double> regulacion(this->pesos->size());
	// Aprovecho la misma iteracion para inicializar los vectores
	for (size_t i = 0; i < gradiente.size(); i++){
		gradiente[i] = 0;
		regulacion[i] = (this->lambda / trainData->filas()) * (*this->pesos)[i];
	}
	regulacion[0] = 0; // No penalizar el feature 0

	for (size_t review = 0; review < trainData->filas(); review++){
		double sentiment = (*sentiments)[review] ? 1 : 0;
		double estimacion = this->sigmoid(this->estimarProbabilidad(trainData->getFila(review)));
		double error = estimacion - sentiment;

		// Actualizo los features que afecta este review
		for (std::map<size_t, double>::iterator it = trainData->getFila(review)->begin(); it != trainData->getFila(review)->end(); ++it){
			gradiente[it->first] = gradiente[it->first] + error;
		}
	}
	// Actualizo los pesos segun diga el gradiente: peso = peso - alfa * gradiente + regularizacion
	for (size_t i = 0; i < gradiente.size(); i++){
		// Actualizo los pesos
		double grad = this->alfa * (gradiente[i] / trainData->filas());
		(*this->pesos)[i] = (*this->pesos)[i] - grad + regulacion[i];
	}
}

void MaximumEntropyClassifier::entrenar(MatrizDispersa* trainData, std::vector<bool>* sentiments){
	size_t iteracion = 0;
	while (iteracion < MAX_ITERACIONES){
		this->gradiente(trainData, sentiments);
		iteracion++;
	}
}

double MaximumEntropyClassifier::costo(MatrizDispersa* trainData, std::vector<bool>* sentiments){
	double regulacion = 0;
	for (size_t i = 0; i < this->pesos->size(); i++){
		regulacion += (*this->pesos)[i];
	}
	regulacion = (this->lambda / trainData->filas()) * regulacion;

	double total = 0;
	for (size_t review = 0; review < trainData->filas(); review++){
		double estimacion = this->sigmoid(this->estimarProbabilidad(trainData->getFila(review)));
		if ((*sentiments)[review]){
			total += ((-1) * log10(estimacion)) / trainData->filas();
		} else {
			total += ((-1) * log10(1 - estimacion)) / trainData->filas();
		}
	}
	return total + regulacion;
}

double MaximumEntropyClassifier::estimarProbabilidad(std::map<size_t, double>* features){
	double resultado = 0;
	for (std::map<size_t, double>::iterator it = features->begin(); it != features->end(); ++it){
		resultado += (*this->pesos)[it->first];
	}
	return resultado;
}

double MaximumEntropyClassifier::estimarProbabilidad(std::vector<bool>* features){
	double resultado = 0;
	size_t cont = 0;
	for (std::vector<double>::iterator it = this->pesos->begin(); it != this->pesos->end(); ++it){
		if ((*features)[cont]){
			resultado += (*it);
		}
		cont++;
	}
	return resultado;
}

double MaximumEntropyClassifier::sigmoid(double x){
	return 1 / (1 + exp((-1) * x));
}


std::map<std::string, double>* MaximumEntropyClassifier::clasificar(std::vector<std::vector<bool>*>* datos, std::list<Review*>* nuevos){
	std::map<std::string, double>* respuesta = new std::map<std::string, double>();
	std::list<Review*>::iterator it = nuevos->begin();
	for (size_t review = 0; review < datos->size() && review < nuevos->size(); review++){
		double predict = this->estimarProbabilidad((*datos)[review]);
		double resultado = this->sigmoid(predict);
		std::string id = (*it)->getId();
		(*respuesta)[id] = resultado;
		(*it++);
	}
	return respuesta;
}


