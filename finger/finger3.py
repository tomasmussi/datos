
import pandas as pd

def review_to_words(raw_review):
	review_text = BeautifulSoup(raw_review).get_text() 
	letters_only = re.sub("[^a-zA-Z]", " ", review_text)
	words = letters_only.lower().split()                             
	stops = set(stopwords.words("english"))
	meaningful_words = [w for w in words if not w in stops]   
	return(" ".join( meaningful_words ))

def limpiar(archivo):
	clean_reviews = []
	num_reviews = len(archivo["review"])
	for i in xrange( 0,  num_reviews):
		if( (i+1)%1000 == 0 ):
			print "Review %d of %d\n" % ( i+1, num_reviews )                                                                    
		clean_reviews.append( review_to_words( archivo["review"][i] ))
	return clean_reviews
	
def extraer(reviews, dim = 500):
	feat = {}
	for i in reviews:
		palabras = i.split()
		d = {}
		for pal in palabras:
			h = hash(pal) % dim
			d[h] = 1
		feat[i] = d
	return feat


def finger():
	train = pd.read_csv("labeledTrainData.tsv", header=0, delimiter="\t", quoting=3)
	clean_train_reviews = limpiar(train)
	print "Extrayendo features de training data"	
	features = extraer(clean_train_reviews)
	
	test = pd.read_csv("testData.tsv", header=0, delimiter="\t", quoting=3)
	clean_test_reviews = limpiar(test)

	features_test = extraer(clean_test_reviews)



	output = pd.DataFrame( data={"id":test["id"], "sentiment":resultado} )
	output.to_csv(archivo_output, index=False, quoting=3)
