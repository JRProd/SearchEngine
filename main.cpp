//main.cpp

#include "userinterface.h"

int main() {
	UserInterface ui;
	std::string init;
	std::cout << "1. Maintenance Mode (m)" << std::endl;
	std::cout << "2. User Mode (u)" << std::endl;
	std::cin >> init;
	ui.start(init);

	/*
	// DOCUMENT PROCESSOR TESTER
	chrono::time_point<chrono::system_clock> start, end;
	start = chrono::system_clock::now();
	try {
		cout << "Trying to parse\n";
        //d.parse("enwikibooks-latest-pages-meta-current.xml");
        index->readPageFromFile();
        index->retrieveStructureFromFile();
	}
	catch (...) {
		std::cout << "\n\nCRASHERINO\n\n";
	}
	end = chrono::system_clock::now();

	chrono::duration<double> elapsed_seconds = end - start;
	time_t end_time = chrono::system_clock::to_time_t(end);

	std::cout << "finished computation at " << std::ctime(&end_time) << "elapsed time: " << elapsed_seconds.count() << "s\n";
	if (index != nullptr)
	{
        std::cout << "Number of words indexed :: " << index->getNumIndexed() << "\n";
        std::cout << "Number of pages indexed :: " << index->getNumDataIndexed() << "\n";
        if(HashIndex* casted = dynamic_cast<HashIndex*>(index))
        {
            std::cout << "Using " << casted->getHash() << "\n";
            std::cout << "Number of colisions :: " << casted->getCollisions() << "\n";
        }
        std::vector<Word> mostFreq = index->mostFreq();
        for(unsigned i = 0; i < mostFreq.size()-40; i++)
        {
            if(mostFreq.at(i).getWord()!="")
                std::cout << (i + 1) << " Most Frequent Word :: " << mostFreq.at(i).getWord() << " @ " << mostFreq.at(i).getNumber() << "\n";
        }
        if(index->contains(word1) && index->contains(word2))
        {
            std::vector<Page> bool1 = index->getData(word1);
            std::cout << "Size of bool1 :: " << bool1.size();
            std::vector<Page> bool2 = index->getData(word2);
            std::cout << " Size of bool2 :: " << bool2.size();
            std::sort(bool1.begin(),bool1.end(), [] (Page p1, Page p2) -> bool
            {
                if(p1.getIDNumber() < p2.getIDNumber())
                    return true;
                return false;
            });
            std::sort(bool2.begin(),bool2.end(), [] (Page p1, Page p2) -> bool
            {
                if(p1.getIDNumber() < p2.getIDNumber())
                    return true;
                return false;
            });

            std::vector<Page> pageUnion = vectorAddition(bool1,bool2);

            rp.getRank(q, pageUnion, index->getNumDataIndexed());

            std::sort(pageUnion.begin(),pageUnion.end(), [] (Page p1, Page p2) -> bool
            {
                if(p1.getRank() > p2.getRank())
                    return true;
                return false;
            });

            std::cout << " Size of pageUnion :: " << pageUnion.size() << "\n";
            std::cout << "SEARCHING FOR :: \"" << word1.getWord() << "\" &  \"" << word2.getWord() << "\"\n";
            std::cout << "PAGE LIST(#" << pageUnion.size() << "):::::::::::::::\n";
            for(unsigned i = 0; i < pageUnion.size(); i++)
            {
                if(i > 15)
                    break;
                std::cout << pageUnion.at(i).getTitle() << " @ " << pageUnion.at(i).getIDNumber()<< " with rank " << pageUnion.at(i).getRank() << "\n";
            }
        }
        else
            std::cout << "Test not in index" << "\n";
	}
	else
        std::cout << "NULLPTR" << "\n";
    delete index;
	cout << "\n\n" << "END PROGRAM";*/
	return 0;
}
