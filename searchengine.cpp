//searchengine.cpp

#include "searchengine.h"


SearchEngine::SearchEngine() {}

void SearchEngine::querySearch(std::string search) {
	int pageToView;
	std::vector<Page> searchresults = sp.search(qp.newQuery(search), ii);
	rp.getRank(qp.newQuery(search), searchresults, ii->getNumDataIndexed());
	std::sort(searchresults.begin(), searchresults.end(), [] (Page p1, Page p2) -> bool
	{
		if (p1.getRank() > p2.getRank())
			return true;
		return false;
	});
	for (unsigned i = 0; i < searchresults.size(); i++)
	{
		if (i > 15)
			break;
		std::cout << i << ". " << searchresults.at(i).getTitle() << " @ " << searchresults.at(i).getIDNumber() << " by " << searchresults.at(i).getAuthor() << " with rank " << searchresults.at(i).getRank() << "\n";
	}
	std::cout << "Which page would you like to view: ";
	std::cin >> pageToView;
	for (unsigned i = 0; i < searchresults.size(); i++) {
		if (i > 15) {
			std::cout << "Page out of range.";
		}
		if (pageToView == i) {
			std::cout << searchresults.at(i).getText() << std::endl;
		}
	}
}

void SearchEngine::parseDocument() {
	//Indexer* index = new HashIndex();
	dp.setDocumentIndex(ii);
	dp.parse("enwikibooks-latest-pages-meta-current.xml");
}

void SearchEngine::readDocument() {
	ii->readPageFromFile();
	ii->retrieveStructureFromFile();
}

void SearchEngine::printStats() {
	std::cout << "Number of words indexed: " << ii->getNumIndexed() << std::endl;
	std::cout << "Number of pages indexed: " << ii->getNumDataIndexed() << std::endl;

	std::vector<Word> mostFreq = ii->mostFreq();
	std::cout << "Top 50 Most Frequent Words: " << std::endl;

	for (unsigned i = 0; i < mostFreq.size(); i++) {
		if (mostFreq.at(i).getWord() != "")
			std::cout << mostFreq.at(i).getWord() << ", ";
	}
	std::cout << std::endl;
}

//needs to be completed I think
void SearchEngine::addDocument(std::string location) {
	dp.addDocument(location);
}

//Must set index before using any other methods
void SearchEngine::setIndexPtr(Indexer* mainIndexPtr) {
	ii = mainIndexPtr;
}

void SearchEngine::clearIndex() {
	try {
		std::remove("PageList.dat");
		std::remove("HashIndexStore.dat");
	}
	catch (...) {
		std::cerr << ".";
	}
	std::cout << "Cleared index.";
}