/*!
* \brief Ranks pages from highest to lowest according to word frequency and eventually by author, title, etc. as well
* \author Calum Aldridge
* \version 1.0
* \date 4\21\2016
*/
#include "rankprocessor.h"

/*!
* \brief Default constructor; nothing is declared.
*/
RankProcessor::RankProcessor() { }

/*!
* \brief Ranks pages from highest to lowest according to word frequency
* \param std::list<Page>
* \return sorted std::list<Page>
*/
void RankProcessor::getRank(Query query, std::vector<Page>& pages, int totalPages)
{
    for(unsigned i = 0; i < pages.size(); i++)
    {
        std::stringstream iss(pages.at(i).getText());
        std::vector<std::string> tokens;

        std::copy(std::istream_iterator<std::string>(iss),
             std::istream_iterator<std::string>(),
             std::back_inserter(tokens));

        double tfidfAVG = 0;
        int numWords = 0;
        //True when AND
        if(query.isBinary())
        {
            for(int j = 0;  j < query.getBinarySize(); j++)
            {
                int timesInPages = 0;
                int totalInPages = tokens.size();
                for(int k = 0; k < totalInPages; k++)
                {
                    if(query.getBinary(j).getWord().compare(tokens.at(k)) == 0)
                    {
                        timesInPages++;
                    }
                }
                double tf = (double)timesInPages / totalInPages;
                double idf = log((double)totalPages / pages.size());
                tfidfAVG += tf*idf;
                numWords++;
            }
            pages.at(i).setRank(tfidfAVG / numWords);
        }
        //False when OR
        else
        {
            double tf = 0;
            double idf = 0;
            for(int j = 0;  j < query.getBinarySize(); j++)
            {
                //if(i < 10)
                    //std::cout << query.getBinary(j).getWord();
                int timesInPages = 0;
                int totalInPages = tokens.size();
                for(int k = 0; k < totalInPages; k++)
                {
                    if(query.getBinary(j).getWord().compare(tokens.at(k)) == 0)
                    {
                        timesInPages++;
                    }
                }
                tf = (double)timesInPages / totalInPages;
                idf = log((double)totalPages / pages.size());
                tfidfAVG += tf*idf;
            }
            if(tfidfAVG == idf)
            {
                tf = (double)tokens.size()/1000;
                tfidfAVG = tf*idf;
            }
            pages.at(i).setRank(tfidfAVG);
        }
    }
}
