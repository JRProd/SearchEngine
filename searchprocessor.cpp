#include "searchprocessor.h"

SearchProcessor::SearchProcessor() { }


std::vector<Page> SearchProcessor::search(Query q, Indexer* i) {
	//If and
	if (q.isBinary()) {
		//If not not
		if (!q.isNot()) {
			//If size of binary is 2
			if (q.getBinarySize() == 2) {
				if (i->contains(q.getBinary(0)) && i->contains(q.getBinary(1))) {
					std::vector<Page> bool1 = i->getData(q.getBinary(0)); //store all pages containing binary_1 in bool1
					std::vector<Page> bool2 = i->getData(q.getBinary(1)); //store all pages containing binary_2 in bool2

					std::vector<Page> searchresults = vectorAddition(bool1, bool2); //add all the pages together and delete dupes
				}
			}
			//bin size is 3
			if (q.getBinarySize() == 3) {
				if (i->contains(q.getBinary(0)) && i->contains(q.getBinary(1)) && i->contains(q.getBinary(2))) {
					std::vector<Page> bool1 = i->getData(q.getBinary(0)); //store all pages containing binary_1 in bool1
					std::vector<Page> bool2 = i->getData(q.getBinary(1)); //store all pages containing binary_2 in bool2
					std::vector<Page> bool3 = i->getData(q.getBinary(2)); //store all pages containing binary_3 in bool3

					std::vector<Page> searchresults = vectorAddition(vectorAddition(bool1, bool2), bool3); //add all the pages together and delete dupes
				}
			}
		}
		else {
			if (q.getBinarySize() == 2) {
				if (i->contains(q.getBinary(0)) && i->contains(q.getBinary(1))) {
					std::vector<Page> bool1 = i->getData(q.getBinary(0)); //store all pages containing binary_1 in bool1
					std::vector<Page> bool2 = i->getData(q.getBinary(1)); //store all pages containing binary_2 in bool2
					std::vector<Page> not1 = i->getData(q.getNot(0)); //store all pages containing not_1 in not1

					std::vector<Page> searchresults = vectorDeletion(vectorAddition(bool1, bool2), not1); //add all the pages together, delete dupes, and delete nots
				}
			}
			if (q.getBinarySize() == 3) {
				if (i->contains(q.getBinary(0)) && i->contains(q.getBinary(1)) && i->contains(q.getBinary(2))) {
					std::vector<Page> bool1 = i->getData(q.getBinary(0)); //store all pages containing binary_1 in bool1
					std::vector<Page> bool2 = i->getData(q.getBinary(1)); //store all pages containing binary_2 in bool2
					std::vector<Page> bool3 = i->getData(q.getBinary(2)); //store all pages containing binary_3 in bool3
					std::vector<Page> not1 = i->getData(q.getNot(0)); //store all pages containing not_1 in not1

					std::vector<Page> searchresults = vectorDeletion(vectorAddition(vectorAddition(bool1, bool2), bool3), not1);
				}
			}
		}
	}
	//If or or just a singular query
	else {
		if (!q.isNot()) {
			if (q.getBinarySize() == 1) {
				if (i->contains(q.getBinary(0))) {
					std::vector<Page> searchresults = i->getData(q.getBinary(0));
				}
			}
			if (q.getBinarySize() == 2) {
				if (i->contains(q.getBinary(0)) || i->contains(q.getBinary(1))) {
					std::vector<Page> bool1 = i->getData(q.getBinary(0)); //store all pages containing binary_1 in bool1
					std::vector<Page> bool2 = i->getData(q.getBinary(1)); //store all pages containing binary_2 in bool2

					std::vector<Page> searchresults = vectorAddition(bool1, bool2); //add all the pages together and delete dupes
				}
			}
			if (q.getBinarySize() == 3) {
				if (i->contains(q.getBinary(0)) || i->contains(q.getBinary(1)) || i->contains(q.getBinary(2))) {
					std::vector<Page> bool1 = i->getData(q.getBinary(0)); //store all pages containing binary_1 in bool1
					std::vector<Page> bool2 = i->getData(q.getBinary(1)); //store all pages containing binary_2 in bool2
					std::vector<Page> bool3 = i->getData(q.getBinary(2)); //store all pages containing binary_3 in bool3

					std::vector<Page> searchresults = vectorAddition(vectorAddition(bool1, bool2), bool3); //add all the pages together and delete dupes
				}
			}
		}
		else {
			if (q.getBinarySize() == 1) {
				if (i->contains(q.getBinary(0))) {
					std::vector<Page> searchresults = vectorDeletion(i->getData(q.getBinary(0)), i->getData(q.getNot(0)));
				}
			}
			if (q.getBinarySize() == 2) {
				if (i->contains(q.getBinary(0)) || i->contains(q.getBinary(1))) {
					std::vector<Page> bool1 = i->getData(q.getBinary(0)); //store all pages containing binary_1 in bool1
					std::vector<Page> bool2 = i->getData(q.getBinary(1)); //store all pages containing binary_2 in bool2
					std::vector<Page> not1 = i->getData(q.getNot(0)); //store all pages containing not_1 in not1

					std::vector<Page> searchresults = vectorDeletion(vectorAddition(bool1, bool2), not1); //add all the pages together, delete dupes, and delete nots
				}
			}
			if (q.getBinarySize() == 3) {
				if (i->contains(q.getBinary(0)) || i->contains(q.getBinary(1)) || i->contains(q.getBinary(2))) {
					std::vector<Page> bool1 = i->getData(q.getBinary(0)); //store all pages containing binary_1 in bool1
					std::vector<Page> bool2 = i->getData(q.getBinary(1)); //store all pages containing binary_2 in bool2
					std::vector<Page> bool3 = i->getData(q.getBinary(2)); //store all pages containing binary_3 in bool3
					std::vector<Page> not1 = i->getData(q.getNot(0)); //store all pages containing not_1 in not1

					std::vector<Page> searchresults = vectorDeletion(vectorAddition(vectorAddition(bool1, bool2), bool3), not1);
				}
			}
		}
	}
	std::vector<Page> searchresults;
	Page p("Title", 12345, "Author", "Text");
	searchresults.push_back(p);
	return searchresults;
}


std::vector<Page> SearchProcessor::vectorUnion(std::vector<Page>& vect1, std::vector<Page>& vect2)
{
	std::vector<Page> toReturn;
	for (int i = 0; i < vect1.size(); i++)
	{
		for (int j = 0; j < vect2.size(); j++)
		{
			if (vect1.at(i).getIDNumber() == vect2.at(j).getIDNumber())
			{
				toReturn.push_back(vect1.at(i));
				break;
			}
		}
	}
	return toReturn;
}

std::vector<Page> SearchProcessor::vectorAddition(std::vector<Page>& vect1, std::vector<Page>& vect2)
{
	std::vector<Page> toReturn;
	for (int i = 0; i < vect1.size(); i++)
	{
		bool notIn = true;
		for (int j = 0; j < vect2.size(); j++)
		{
			if (vect1.at(i).getIDNumber() == vect2.at(j).getIDNumber())
			{
				notIn = false;
				break;
			}
		}
		if (notIn)
			toReturn.push_back(vect1.at(i));
	}
	for (int i = 0; i < vect2.size(); i++)
	{
		bool notIn = true;
		for (int j = 0; j < vect1.size(); j++)
		{
			if (vect2.at(i).getIDNumber() == vect1.at(j).getIDNumber())
			{
				notIn = false;
				break;
			}
		}
		if (notIn)
			toReturn.push_back(vect2.at(i));
	}
	for (int i = 0; i < vect1.size(); i++)
	{
		for (int j = 0; j < vect2.size(); j++)
		{
			if (vect1.at(i).getIDNumber() == vect2.at(j).getIDNumber())
			{
				toReturn.push_back(vect1.at(i));
				break;
			}
		}
	}
	return toReturn;
}

std::vector<Page> SearchProcessor::vectorDeletion(std::vector<Page>& vect1, std::vector<Page>& vect2)
{
	std::vector<Page> toReturn;
	for (int i = 0; i < vect1.size(); i++)
	{
		bool notIn = true;
		for (int j = 0; j < vect2.size(); j++)
		{
			if (vect1.at(i).getIDNumber() == vect2.at(j).getIDNumber())
			{
				notIn = false;
				break;
			}
		}
		if (notIn)
			toReturn.push_back(vect1.at(i));
	}
	return toReturn;
}
