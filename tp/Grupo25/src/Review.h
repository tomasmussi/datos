

#ifndef REVIEW_H_
#define REVIEW_H_
#include <string>
#include <list>
#include <algorithm>
#include <functional>
#include <cctype>
#include <locale>

class Review {
public:
	Review(std::string id, bool sentiment, std::string review, const std::list<std::string>* stopwords);
	~Review();
	friend std::ostream& operator<< (std::ostream &out, Review &cPoint);

	const std::string& getId() const {
		return id;
	}

	std::list<std::string>* getReview() {
		return review;
	}

	bool isSentiment() const {
		return sentiment;
	}

private:
	std::string id;
	bool sentiment;
	std::list<std::string>* review;
	std::list<std::string>* limpiar(std::string texto,const std::list<std::string>* stopwords);
	std::string &trim(std::string &s);
	std::string &ltrim(std::string &s);
	std::string &rtrim(std::string &s);

};

#endif /* REVIEW_H_ */
