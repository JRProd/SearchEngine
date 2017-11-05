/*!
* \brief Converts string query from user to a Query object in order to be
* used properly in search engine.
* \author Calum Aldridge
* \version 1.0
* \date 5\1\2016
*/

#include "queryprocessor.h"
#include <iostream>

/*!
* \brief Default constructor; nothing is declared.
*/
QueryProcessor::QueryProcessor() {

}

/*!
* \brief Creates new query.
* \param userquery The user query to be converted to Query object.
*/
Query QueryProcessor::newQuery(std::string userquery) {
	Query query;

    std::vector<std::string> tokens;
    std::istringstream iss(userquery);
    copy(std::istream_iterator<std::string>(iss),
        std::istream_iterator<std::string>(),
        std::back_inserter(tokens));


    bool binary = false;
    bool isNot = false;

    if(tokens.at(0).compare("OR") == 0)
    {
        query.setBinary(false);
        binary = true;
    }
    else if(tokens.at(0).compare("AND") == 0)
    {
        query.setBinary(true);
        binary = true;
    }
    else
    {
        std::string temp = tokens.at(0);
        Porter2Stemmer::stem(temp);
        query.addBinary(temp);
        query.setBinary(true);
        binary = true;
    }
    std::string temp;
    for(int i = 1; i < tokens.size(); i++)
    {
        temp = tokens.at(i);
        Porter2Stemmer::stem(temp);
        if(temp.compare("NOT") == 0)
        {
            isNot = true;
            binary = false;
            continue;
        }
        if(binary)
        {
            std::cout << "Adding multipe binaries\n";
            query.addBinary(temp);
        }
        if(isNot)
        {
            query.addNot(temp);
        }
    }
	return query;
}
