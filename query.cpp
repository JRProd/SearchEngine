/*!
 * \brief Stores the real text query in a format understandable to our program.
 * The possible binary searched words (the ones after AND or OR but before NOT)
 * will be stored in their on list. If the list is size one then binary opperator
 * must be AND. If the list is greater then one, the bool binaryOpp is taken into
 * account. 1 = AND :: 0 = OR. Words after the NOT are stored into the Nots list.
 * If the list is empty, NOT will be false. If the list has one or more elements
 * then NOT will be ture.
 * \author Jake Rowland
 * \version 1.0
 * \date 4\12\2016
 */

#include "query.h"
#include <stdexcept>

/*!
 * \brief Default constructor; nothing is declared.
 */
Query::Query()
{
    //BLANK
}

/*!
 * \brief Sets the binary operator.
 * AND is true and OR is false
 * \param b The value to be set
 */
void Query::setBinary(bool b)
{
    binaryOpp = b;
}

/*!
 * \brief Adds a word to the Binaries list.
 * \param w The Word to be added
 */
void Query::addBinary(Word w)
{
    Binaries.push_back(w);
}

/*!
 * \brief Adds a word to the Nots list.
 * \param w The Word to be added
 */
void Query::addNot(Word w)
{
    Nots.push_back(w);
}

/*!
 * \brief Gets a word at a given index of Binaries.
 * Looks through the list and finds the Word at index i. Uses
 * const_iterators to find the correct index
 * \throws std::out_of_range Throws exception if index is outside the list
 * \param i The index to be searched for
 * \return Returns the Word found at i
 */
Word& Query::getBinary(unsigned i)
{
    return Binaries.at(i);
}

/*!
 * \brief Gets a word at a given index of Nots.
 * Looks through the list and finds the Word at index i. Uses
 * const_iterators to find the correct index
 * \throws std::out_of_range Throws exception if index is outside the list
 * \param i The index to be searched for
 * \return Returns the Word found at i
 */
Word& Query::getNot(unsigned i)
{
    return Nots.at(i);
}

int Query::getBinarySize()
{
    return Binaries.size();
}

int Query::getNotSize()
{
    return Nots.size();
}

/*!
 * \brief Returns the value of binaryOpp.
 * If the list Binaries is of size 1, return AND
 * \return The Binary operator
 */
bool Query::isBinary()
{
    if(Binaries.size()<=1)  //If at most one element is prsent the binaryOpp MUST be AND
        return true;
    return binaryOpp;
}

/*!
 * \brief Returns if a NOT operator was present
 * \return If Words need to be NOT'ed
 */
bool Query::isNot()
{
    if(Binaries.size()<1)   //If no elements are in Nots, then there is no NOT fuction
        return false;
    return true;
}
