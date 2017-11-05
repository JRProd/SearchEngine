//query.h

#ifndef QUERY_H
#define QUERY_H

#include "word.h"
#include <vector>

class Query {
private:
    std::vector<Word> Binaries;
    std::vector<Word> Nots;
	bool binaryOpp;

public:
	Query();
	void setBinary(bool);
	void addBinary(Word);
	void addNot(Word);
    Word& getBinary(unsigned) ;
    Word& getNot(unsigned) ;
    int getBinarySize();
    int getNotSize();
    bool isBinary() ;
    bool isNot() ;
};
#endif
