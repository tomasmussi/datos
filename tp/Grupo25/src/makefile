CC = g++
CFLAGS = -Wall -Wextra -g -pedantic
CPPFLAGS = -Wall -Wextra -g -pedantic -lstdc++ -lm -O3

OBJECTS = Escritor.o HashVectorizador.o Lector.o MatrizDispersa.o MaximumEntropyClassifier.o Review.o

all: TP

Escritor.o: Escritor.cpp Escritor.h
	$(CC) $(CFLAGS) -c Escritor.cpp
	
HashVectorizador.o: HashVectorizador.cpp HashVectorizador.h
	$(CC) $(CPPFLAGS) -c HashVectorizador.cpp

Lector.o: Lector.cpp Lector.h
	$(CC) $(CPPFLAGS) -c Lector.cpp

Review.o: Review.cpp Review.h
	$(CC) $(CPPFLAGS) -c Review.cpp

MatrizDispersa.o: MatrizDispersa.cpp MatrizDispersa.h
	$(CC) $(CPPFLAGS) -c MatrizDispersa.cpp
	
MaximumEntropyClassifier.o: MaximumEntropyClassifier.cpp MaximumEntropyClassifier.h
	$(CC) $(CPPFLAGS) -c MaximumEntropyClassifier.cpp

TP: TP.cpp $(OBJECTS)
	$(CC) $(CPPFLAGS) $(OBJECTS) TP.cpp -o TP

clean:
	rm -rf *.o *~ TP

run: TP
	./TP

valgrind: TP
	valgrind ./TP
