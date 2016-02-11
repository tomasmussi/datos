
#ifndef MATRIZDISPERSA_H_
#define MATRIZDISPERSA_H_

#include <iostream>
#include <map>

class MatrizDispersa {
public:
	MatrizDispersa();
	~MatrizDispersa();
	size_t filas();
	void agregarValor(size_t fila, size_t columna, double valor);
	void adicionarValor(size_t fila, size_t columna, double valor);
	std::map<size_t, double>* getFila(size_t fila);

private:
	std::map<size_t, std::map<size_t, double>* >* matriz;
};

#endif /* MATRIZDISPERSA_H_ */
