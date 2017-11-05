//query.h

#ifndef QUERY_H
#define QUERY_H

#include "word.h"
#include <list>

class Query {
private:
	std::list<Word> Binaries;
	std::list<Word> Nots;
	bool binaryOpp;

public:
	Query();
	void setBinary(bool);
	void addBinary(Word);
	void addNot(Word);
    Word getBinary(unsigned) const;
    Word getNot(unsigned) const;
    int getBinarySize();
    int getNotSize();
    bool isBinary() const;
    bool isNot() const;
};
#endif
