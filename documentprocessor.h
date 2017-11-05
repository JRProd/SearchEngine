//documentprocessor.h

#ifndef DOCUMENTPROCESSOR_H
#define DOCUMENTPROCESSOR_H

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <algorithm>
#include <iterator>
#include <fstream>
#include <vector> //may remove later, only here for testing in parse method
#include <unordered_set>
#include <unordered_map>

#include "page.h" //do i need this?
#include "avltree.h"
#include "tinyxml2.h"
#include "porter2_stemmer.h"
#include "indexer.h"
#include "avltree.h"



class DocumentProcessor {
private:
	std::string document;
	std::ifstream in;

    Indexer* index;

	std::unordered_set<std::string> stopWords;
	std::unordered_map<std::string, std::string> stemmedWords;

    bool parseText(Page& page, Indexer* index);

    void toLowerCase(std::string& str);

public:
	DocumentProcessor();
	DocumentProcessor(std::string);
    DocumentProcessor(Indexer* idx);
    void parse(std::string);
	void addDocument(std::string);
	void setDocument(std::string);
	void setDocumentIndex(Indexer*);
	void setStopWords();
	void setIndex(Indexer*);
};
#endif
