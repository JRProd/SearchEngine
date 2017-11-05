#include "hashindexcontainer.h"

/*!
 * \brief Default constructor
 */
HashIndexContainer::HashIndexContainer()
{
    //Do Noting
    next = nullptr;
}

/*!
 * \brief Copy Constructor
 * \param copy HashIndexContainer to copy data from
 */
HashIndexContainer::HashIndexContainer(HashIndexContainer& copy)
{
    index = copy.getWord();
    data = copy.getData();
    next = nullptr;
}

/*!
 * \brief Constructor with Word value and pageID
 * \param idx Word to add
 * \param d pageID to add
 */
HashIndexContainer::HashIndexContainer(Word idx, int d)
{
    index = idx;
    data.push_back(d);
    next = nullptr;
}

/*!
 * \brief Destructor. Destroys the chain as well
 */
HashIndexContainer::~HashIndexContainer()
{
    //Chain destroying
    if(next!=nullptr)
        delete next;
}

/*!
 * \brief Gets the word
 * \return reference to the word
 */
Word& HashIndexContainer::getWord()
{
    return index;
}

/*!
 * \brief Set the word
 * \param idx sets word to idx value
 */
void HashIndexContainer::setWord(Word idx)
{
    index = idx;
}

/*!
 * \brief Gets the page ID data
 * \return vector<int> pageID data
 */
std::vector<int> HashIndexContainer::getData()
{
    return data;
}

/*!
 * \brief Set the page list to d
 * \param d vector<int> to set data to
 */
void HashIndexContainer::setData(std::vector<int> d)
{
    data = d;
}

/*!
 * \brief Add page to list
 * \param d pageID to add
 */
void HashIndexContainer::addPage(int d)
{
    //Checks if alread in
    bool isAdded = false;
    for(int i = 0; i < data.size(); i++)
    {
        //If value in vector equals d
        if(data.at(i) == d)
            //Dont add
            isAdded = true;
    }
    //If not added
    if(!isAdded)
        //Add to vector
        data.push_back(d);
}

/*!
 * \brief Get next HashIndexContainer
 * \return the next HashIndexContainer
 */
HashIndexContainer* HashIndexContainer::getNext()
{
    return next;
}

/*!
 * \brief Set the location of the next HashIndexContainer
 * \param n pointer to next HashIndexContainer
 */
void HashIndexContainer::setNext(HashIndexContainer *n)
{
    next = n;
}
