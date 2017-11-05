#include "searchprocessor.h"

SearchProcessor::SearchProcessor() { }


std::vector<Page> SearchProcessor::search(Query q, Indexer* i) {

    std::vector<Page> searchresults;
    if(q.isBinary())
    {
        searchresults = i->getData(q.getBinary(0));
        for(int j = 1; j < q.getBinarySize(); j++)
        {
            std::vector<Page> temp = i->getData(q.getBinary(j));
            searchresults = vectorUnion(searchresults, temp);
        }
    }
    else if(!q.isBinary())
    {
        searchresults = i->getData(q.getBinary(0));
        for(int j = 1; j < q.getBinarySize(); j++)
        {
            std::vector<Page> temp = i->getData(q.getBinary(j));
            searchresults = vectorAddition(searchresults, temp);
        }
    }

    if(q.isNot())
    {
        for(int j = 0; j < q.getNotSize(); j++)
        {
            std::vector<Page> temp = i->getData(q.getNot(j));
            searchresults = vectorDeletion(searchresults, temp);
        }
    }
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
