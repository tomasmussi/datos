Palabras = load 'AFINN-111.txt' using PigStorage ('\t') AS (pal:chararray, puntaje:int);

Calif = load 'labeledTrainData.tsv' using PigStorage ('\t') AS (nro_calif:chararray, 

pts_calif:int, desc_calif:chararray);

TopCalif_Pals = foreach Calif generate nro_calif, pts_calif, TOKENIZE(desc_calif) AS 

pals_calif_pts;

Pals_Calif = foreach TopCalif_Pals {

	pal = foreach pals_calif_pts generate token;

	generate nro_calif, pal.token;

};

Pals_Calif_FL = foreach Pals_Calif generate $0 as id , FLATTEN($1) as palabra;

/* YOUR CODE HERE */
/* Dumps de prueba */
--prueba = sample Pals_Calif_FL 0.1;
--dump prueba;

--prueba = sample Palabras 0.1;
--dump prueba;
/* Fin Dumps de prueba */

joined = join Pals_Calif_FL by palabra, Palabras by pal;

grouped = group joined by id;
-- Hasta aca anda bien

/* FUNCIONA
consolidado = foreach grouped generate $0 as id, SUM($1.Palabras::puntaje) as suma;
dump consolidado;*/
/*
FUNCIONA
consolidado = foreach grouped generate $0 as id, COUNT($1.Pals_Calif_FL::id) as cuenta;
dump consolidado;*/
/*
FUNCIONA
consolidado = foreach grouped generate $0 as id, SUM($1.Palabras::puntaje) as suma, COUNT($1.Pals_Calif_FL::id) as cuenta;
dump consolidado;
*/

consolidado = foreach grouped generate $0 as id, (double)SUM($1.Palabras::puntaje) / COUNT($1.Pals_Calif_FL::id) as promedio;
--dump consolidado;


ordenado = order consolidado by promedio DESC;
cinco = limit ordenado 5;
dump cinco;

ordenado = order consolidado by promedio ASC;
cinco = limit ordenado 5;
dump cinco;



