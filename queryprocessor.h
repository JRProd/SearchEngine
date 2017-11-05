//queryprocessor.h

#ifndef QUERYPROCESSOR_H
#define QUERYPROCESSOR_H

#include "query.h"
#include "porter2_stemmer.h"

class QueryProcessor {
private:
	Query q;

public:
	QueryProcessor();
	Query newQuery(std::string);
};
#endif