//queryprocessor.h

#ifndef QUERYPROCESSOR_H
#define QUERYPROCESSOR_H

#include "query.h"
#include "porter2_stemmer.h"
#include <vector>
#include <sstream>
#include <iterator>
#include <algorithm>

class QueryProcessor {
private:
	Query q;

public:
	QueryProcessor();
	Query newQuery(std::string);
};
#endif
