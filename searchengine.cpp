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
        if (i >= 15)
			break;
        std::cout << i+1 << ". " << searchresults.at(i).getTitle() << " @ " << searchresults.at(i).getIDNumber() << " by " << searchresults.at(i).getAuthor() << " with rank " << searchresults.at(i).getRank() << "\n";
	}

    bool incorrect = false;
        do
        {
        std::cout << "Which page would you like to view (-1 to return)\n>> ";
        std::cin >> pageToView;
        pageToView --;
        if(pageToView < 0)
        {
            incorrect = false;
            return;
        }
        else if(pageToView < 15)
        {
            std::cout << "Title :: " << searchresults.at(pageToView).getTitle() << "\n";
            std::cout << "Author :: " << searchresults.at(pageToView).getAuthor() << "\n";
            std::cout << "Text ################################\n";
            std::cout << searchresults.at(pageToView).getText() << "\n";
            std::cout << "Text ################################\n";
            incorrect = true;
        }
        else
        {
            std::cout << "Invalid page index.\n";
            std::cout << "Please reenter the page ID or -1 to quit\n>> ";
            std::cin >> pageToView;
            incorrect = true;
        }
    }while(incorrect == true);
}

void SearchEngine::parseDocument() {
	//Indexer* index = new HashIndex();
	dp.setDocumentIndex(ii);
    dp.parse(document);
}

void SearchEngine::readPersistent() {
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
    document = location;
}

//Must set index before using any other methods
void SearchEngine::setIndexPtr(Indexer* mainIndexPtr) {
	ii = mainIndexPtr;
    dp.setDocumentIndex(ii);
}

void SearchEngine::clearIndex() {
    ii->clear();
	std::cout << "Cleared index.";
}

void SearchEngine::close()
{
    delete ii;
}
