#!/usr/python
import csv
import sys
from time import *
"""
Finalidad de este script
Con el archivo "labeledTrainData.tsv" obtener las siguientes estadisticas

1) Reviews positivos y negativos: Cantidad
positivos + negativos = 25000
P = 12500
N = 12500

2) Longitud del comentario del review (promedio)
1326


3) Verificar si encuentro la palabra "amazing" y review = 0
Amazing no se usa siempre en reviews positivos

"""
def algoritmo_2(file):
	positivos = 0
	negativos = 0
	longitud = 0
	promedio = 0.0
	max = 0
	min = 100
	amazing_positivo = True
	primera_linea = True
	comienzo = time()	
	with open(file) as tsv:
		for line in csv.reader(tsv, dialect="excel-tab"):
			if (primera_linea):
				primera_linea = False
				continue
			if (line[1] == '1'):
				positivos += 1
			elif (line[1] == '0'):
				negativos += 1
			if (len(line[2]) > max):
				max = len(line[2])
			if (len(line[2]) < min):
				min = len(line[2])
			promedio += (len(line[2]) - 2)
			if (("amazing" in line[2].lower()) and (line[1] == '0')):				
				amazing_positivo = False
		
	comienzo = time() - comienzo
	print "Cantidad positivos: " + str(positivos)
	print "Cantidad negativos: " + str(negativos)
	print "Promedio longitud comentarios: " + str(promedio / (positivos + negativos))
	print "Maximo longitud: " + str(max)
	print "Minimo longitud: " + str(min)
	print "Amazing comentario positivo: " + str(amazing_positivo)
	print "Tardo: " + str(comienzo) + " segundos"


def algoritmo_1(file):
	cantidad = 0
	positivos = 0
	longitud = 0.0
	amazing_positivo = True
	comienzo = time()
	primera_linea = True
	with open(file) as tsv:
		for line in csv.reader(tsv, dialect="excel-tab"):
			if (primera_linea):
				primera_linea = False
				continue
			cantidad += 1
			positivos += int(line[1])
			longitud += len(line[2])						
			if ("amazing" in line[2].lower() and (line[1] == '0')):
				amazing_positivo = False
	comienzo = time() - comienzo
	print "Cantidad positivos: " + str(positivos)
	print "Cantidad negativos: " + str(cantidad - positivos)
	print "Promedio longitud comentarios: " + str(longitud/cantidad)
	print "Amazing comentario positivo: " + str(amazing_positivo)
	print "Tardo: " + str(comienzo) + " segundos"


def main():
	if (len(sys.argv) > 1):
		file = sys.argv[1] 
	else:
		file = "labeledTrainData.tsv"
	algoritmo_2(file)

main()

