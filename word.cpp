/*!
 * \brief The Word class store data related to the string associated
 *        with it.
 * It will store the number of times that the word is found as well.
 * Words can be compaired with the == operator and the < operator
 * \author Jake Rowland
 * \author Calum Aldridge
 * \version 1.1
 * \date 4\12\2016
*/

#include "word.h"


/*!
 * \brief Default consturctor.
 * Initalizes word to "" and the number of time appeared to -1.
*/
Word::Word() {
	word = "";
    numAppear = -1;
}


/*!
 * \brief Constructor that that associates this class with a string word.
 * This constructor will create a wordwith a specific string word attached
 * to it but will still have appeared -1 times.
 * \param w string word to associate this class with
*/
Word::Word(std::string w) {
	word = w;
    numAppear = -1;
}

/*!
 * \brief Constructor that that associates this class with a string word and a given number of times its appeared.
 * \param w string word to associate this class with
 * \param i integer related to the number of times the string word has appreaed
*/
Word::Word(std::string w, int i) {
	word = w;
	numAppear = i;
}

/*!
 * \brief Gets string word associated with this Word.
 * \return The string word associated with this Word
 */
std::string Word::getWord() {
	return word;
}

/*!
 * \brief Sets the string associated with this Word
 * \param w
 */
void Word::setWord(std::string w) {
	word = w;
}

/*!
 * \brief Gets the number of times Word has appeared
 * \return The number of times the word has appeared
 */
int Word::getNumber() {
	return numAppear;
}

/*!
 * \brief Sets the number of times the word has appeared
 * \param i Value to be set. Will be adjusted to -1 if below
 */
void Word::setNumber(int i) {
    if(i < -1)
        numAppear = -1;
	numAppear = i;
}

//*************************************
//*          RELEVANT STUFF           *
//*************************************

/*!
 * \brief Determines which word appears more
 * \param w Is a refrence to another Word to compare to
 * \return True if this Word appears more then the passed Word
 */
bool Word::operator<(Word& w) {
    if (word < w.word)
		return true;
	else
		return false;
}

/*!
 * \brief Checks if this Word's word equals anothers0
 * \param w Is a refrence to another Word to compare to
 * \return True if this Word's string equals the passed Word's string
 */
bool Word::operator==(Word& w) {
	if (numAppear == w.numAppear)
		return true;
	else
		return false;
}
