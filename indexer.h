/*!
 * \brief Interface for our AVLTreeIndex and HashIndex.
 * AVLTree and HashIndex will both be templated with two different
 * data types that allow a "index" data type and a "value" data type
 * \author Jake Rowland
 * \version 1.4
 * \date 4\13\2016
*/

#ifndef INDEXER_H
#define INDEXER_H

#include "word.h"
#include "page.h"

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>

class Indexer
{
private:
    int numData; /*! The number of elements indexed*/
    int numIndexed; /*! The number of index elements indexed*/
    std::map<int,Page> idToPage;

public:
    /*!
     * \brief Indexer
     */
    Indexer()
    {
        //Do Noting
    }

    /*!
     * \brief Virtual destructor to handle dynamic memory allocation.
     * This forces the compiler to use the class specific destructor to
     * midigate memory loss and corrupted memory
     */
    virtual ~Indexer()
    {
        storePageToFile();
    }

    /*!
     * \brief Gets the data at "index"
     * \param index Value to return data for
     * \return Value of type U at "index"
     */
    virtual std::vector<Page> getData(Word& index) = 0;

    /*!
     * \brief Addes an index and data to Indexer
     * \param index Value to be used as Index
     * \param data Value to be also added to Data at index
     */
    virtual void add(Word index, int pageID) = 0;

    /*!
     * \brief Add a page to the id map
     * \param page Page to add to the idToPage map
     * \return new ID if curr id is taken
     */
    int addPage(Page page)
    {
        //get the page ID and title
        int ID = page.getIDNumber();
        std::string title = page.getTitle();
        //If page's id is alread in
        if(idToPage.find(ID) != idToPage.end())
        {
            //If the page's title does not equal the one in the map
            if(idToPage.at(ID).getText().compare(title)!=0)
            {
                //loop until page is added
                bool inserted = false;
                //Start at the beginning
                for(unsigned i = 0; i < idToPage.size(); i++)
                {
                    //If an id does not have a page
                    if(idToPage.find(i) == idToPage.end())
                    {
                        //Page was inserted
                        inserted = true;
                        //Set page to new ID
                        page.setIDNumber(i);
                        //Add page
                        idToPage.emplace(i,page);
                        ID = i;
                    }
                }
                //If not inserted (map is full)
                if(!inserted)
                {
                    //Page was inserted
                    inserted = true;
                    //Set page id to map.size()
                    page.setIDNumber(idToPage.size());
                    //Add page to map (auto resize)
                    idToPage.emplace(idToPage.size(),page);
                    ID = idToPage.size();
                }
            }
        }
        //Page id was not found
        else
        {
            //add Page id
            idToPage.emplace(ID,page);
        }
        //Return id even if not changed
        return ID;
    }

    /*!
     * \brief Finds the most frequent index
     * \return The most frequent index
     */
    virtual std::vector<Word> mostFreq() = 0;

    /*!
     * \brief Gets the map
     * \return reference to the map
     */
    std::map<int,Page>& getIdToPage()
    {
        return idToPage;
    }

    /*!
     * \brief Gets the number of indexed values in the Indexer
     * \return Number of Indexed values
     */
    int getNumIndexed()
    {
        return numIndexed;
    }
    /*!
     * \brief Gets the number of "data"  in the Indexer
     * If each index only has one data then the numbers will be the same.
     * If however, you add duplicate combos to the original index then the
     * numbers will differ. This number will never be less than numIndexed
     * however.
     * \return Number of Data values Indexed
     */
    int getNumDataIndexed()
    {
        return numData;
    }

    /*!
     * \brief Sets the number of indexed values in the Indexer
     * \param num The new number of items indexed
     */
    void setNumIndexed(int num)
    {
        numIndexed = num;
    }
    /*!
     * \brief Sets the number of "data" in the Indexer
     * \return Number of Data values Indexed
     */
    void setNumDataIndexed(int num)
    {
        numData = num;
    }

    /*!
     * \brief Checks if the Index contains a certain index
     * \param index The value to search for
     * \return True if the value is inside the Indexer
     */
    virtual bool contains(Word& index) = 0;

    /*!
     * \brief Reads the Page map from the file "PageList.dat"
     */
    void readPageFromFile()
    {
        //Create ifstream asociated with "PageList.dat"
        std::ifstream in("PageList.dat");
        //Check if open
        if(!in)
        {
            std::cerr << "ERROR OPENING PageList.dat FOR INPUT!\n";
            return;
        }
        //Get the size
        int size = 0;
        in >> size;
        //Loop for the size
        for(int i = 0; i < size; i++)
        {
            //Create varibles
            int id = 0;
            std::string title;
            std::string author;
            std::string text;
            //Get the id
            in >> id;
            //ignore '|'
            in.ignore(1);
            //Get the title, author, and text
            getline(in,title,'|');
            getline(in,author,'|');
            getline(in,text,'0');
            //Create a page with the data
            Page toInput(title,id,author,text);
            //Add page to map
            idToPage.emplace(id,toInput);
        }
        //Update the number of pages
        setNumDataIndexed(size);
        //Close ifstream
        in.close();
    }

    /*!
     * \brief Stores the map to a file
     */
    void storePageToFile()
    {
        //Create ofstream asociated to "PageList.dat"
        std::ofstream out("PageList.dat");
        //Check if file opened
        if(!out)
        {
            std::cerr << "ERROR OPENING PageList.dat FOR OUTPUT!\n";
            return;
        }
        //Prints out the size of the map
        out << idToPage.size() << "\n";
        //Loop through all the (id, page) combos
        for(std::map<int,Page>::iterator iter = idToPage.begin(); iter != idToPage.end(); iter++)
        {
            //Get the page from the iterator
            Page toOutput = iter->second;
            //Print out "pageID|title|author|text0\n"
            out << toOutput.getIDNumber() << "|"
                << toOutput.getTitle() << "|" << toOutput.getAuthor() << "|"
                << toOutput.getText() << "0\n";
        }
        //Close ofstream
        out.close();
    }

    /*!
     * \brief Store Structure Specific storage of word to page id
     */
    virtual void storeStructureToFile() = 0;

    /*!
     * \brief Retrieve Structure Specific storage of word to page id
     */
    virtual void retrieveStructureFromFile() = 0;

    /*!
     * \brief Removes all dynamically allocated memory and the persistant copy
     */
    virtual void clear() = 0;
};

#endif
