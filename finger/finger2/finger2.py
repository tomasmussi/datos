
import os
import lzw

def comprimir_archivos(origen, destino):	
	for archivo in os.listdir(origen):		
		comprimir = lzw.readbytes(os.path.abspath(origen + "/" + archivo))
		out = lzw.compress(comprimir)
		archivo_destino = os.path.abspath(destino + "/" + archivo + ".compressed")
		lzw.writebytes(archivo_destino, out)


def calcular_distancia(buscados, comprimidos):
	for archivo in os.listdir(buscados):
		bytes_archivo = lzw.readbytes(os.path.abspath(buscados + "/" + archivo)) # X
		archivo_comprimido = lzw.compress(bytes_archivo) # C(X)
		for comprimido in os.listdir(comprimidos):
			bytes_comprimido = lzw.readbytes(os.path.abspath(comprimidos + "/" + comprimido)) # C(Y)
			bytes_descomprimido = lzw.decompress(bytes_comprimido) # C(Y)

