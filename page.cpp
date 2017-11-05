/*!
 * \brief Page will store data related to the page in question
 * The Pages author, text, title, and rank will be stored here.
 * Rank will be calculated on a query based scope and will only
 * be defined after the \see RankProcessor calculates the rank
 * for this page
 * \author Jake Rowland
 * \version 1.0
 * \date 4\12\2016
 */

#include "page.h"

/*!
 * \brief Default constuctor for Page.
 * Initalizes all the strings to "" and the rank to -1
 */
Page::Page()
{
    setTitle("");
    setAuthor("");
    setText("");
    setRank(-1);
}

/*!
 * \brief Constructor that initializes the string data members
 * The program will NEVER know the rank of the page on creation.
 * \param t The title of the page
 * \param a The author of the page
 * \param tx The text contained in the page
 */
Page::Page(std::string t, int id, std::string a, std::string tx)
{
    setTitle(t);
    setIDNumber(id);
    setAuthor(a);
    setText(tx);
}

/*!
 * \brief Compares the rank of this Page to another Page
 * \param other Refrence to another Page to compare to
 * \return True if this Page's rank is greater than the other's rank
 */
bool Page::operator <(Page& other)
{
    if(rank < other.getRank())
        return true;
    else return false;
}

/*!
 * \brief Determines is idNumber or title of this Page equals other Page
 * \param other Refrence to other Page to be compared to
 * \return True if idNumber or title are the same
 */
bool Page::operator ==(Page& other)
{
    if(idNumber == other.getIDNumber())
        return true;
    if(title.compare(other.getTitle()) == 0)
        return true;
    else return false;
}

//*****************************//
//                             //
//     GETTERS   &   SETTERS   //
//                             //
//*****************************//

/*!
 * \brief Returns the title of the Page
 * \return The title
 */
std::string Page::getTitle()
{
    return title;
}

/*!
 * \brief Sets the title associated with this Page
 * \param t The new title to be set
 */
void Page::setTitle(std::string t)
{
    title = t;
}

/*!
 * \brief Returns the idNumber of the Page
 * \return The ID
 */
int Page::getIDNumber()
{
    return idNumber;
}

/*!
 * \brief Sets the idNumber associated with this Page
 * \param id The new idNumber to be set
 */
void Page::setIDNumber(int id)
{
    idNumber = id;
}

/*!
 * \brief Returns the author of the Page
 * \return The author
 */
std::string Page::getAuthor()
{
    return author;
}

/*!
 * \brief Sets the author associated with this Page
 * \param t The new author to be set
 */
void Page::setAuthor(std::string s)
{
    author = s;
}

/*!
 * \brief Returns the text of the Page
 * \return The text
 */
std::string Page::getText()
{
    return text;
}

/*!
 * \brief Returns a refrence text of the Page
 * \return The text
 */
std::string& Page::getTextRef()
{
    return text;
}

/*!
 * \brief Sets the text associated with this Page
 * \param t The new text to be set
 */
void Page::setText(std::string tx)
{
    text = tx;
}

/*!
 * \brief Returns the rank of the Page
 * \return The rank
 */
double Page::getRank()
{
    return rank;
}

/*!
 * \brief Sets the text associated with this Page
 * \param t The new text to be set
 */
void Page::setRank(double r)
{
    rank = r;
}


