/*!
* \brief Converts string query from user to a Query object in order to be
* used properly in search engine.
* \author Calum Aldridge
* \version 1.0
* \date 5\1\2016
*/

#include "queryprocessor.h"

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
	std::string x;
	Word y;
	bool nawt;
	bool bin;
	for (int i = 0; i < userquery.length(); i++) {        //AND boston seattle NOT tokyo
		if (userquery.at(i) == ' ') {                   //OR boston seattle NOT tokyo
			//if first term is not, set not bool to true and clear temp x string
			if (x == "NOT") {
				nawt = true;
				x = "";
			}
			//if first term is or or and, set bin bool to true and clear temp x string
			else if (x == "OR" || x == "AND") {
				bin = true;
				if (x == "OR")
					query.setBinary(false);
				else
					query.setBinary(true);
				x = "";
			}
			//if word is anything else, then put in either not library or binary library
			else {
				if (nawt) {
					Porter2Stemmer::stem(x);
					y.setWord(x);
					query.addNot(y);
					x = "";
				}
				if (bin) {
					if (nawt) { }
					else {
						Porter2Stemmer::stem(x);
						y.setWord(x);
						query.addBinary(y);
						x = "";
					}
				}
			}
		}
		else {
			x += userquery.at(i);
		}
		if (!nawt && !bin)
			Porter2Stemmer::stem(x);
			y.setWord(x);
			query.addBinary(y);
	}


	return query;
}