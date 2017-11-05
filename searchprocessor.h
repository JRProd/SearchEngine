//searchprocessor.h

#ifndef SEARCHPROCESSOR_H
#define SEARCHPROCESSOR_H

#include "page.h"
#include "query.h"
#include "indexer.h"
#include <vector>

class SearchProcessor {
private:
	//still none

public:
	SearchProcessor();
	std::vector<Page> search(Query, Indexer*);
	std::vector<Page> vectorUnion(std::vector<Page>, std::vector<Page>);
	std::vector<Page> vectorAddition(std::vector<Page>, std::vector<Page>);
	std::vector<Page> vectorDeletion(std::vector<Page>, std::vector<Page>);
};
#endif
