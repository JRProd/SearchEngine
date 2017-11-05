/*!
 * \brief Creates a unordered map (hash table) and handles collisions with a list.
 * Takes the Word's string as the key and can pass that key to 11 hashes picked by
 * the user to evaluate which hash is the best for the data set.
 */

#include "hashindex.h"

/*!
 *
 */
HashIndex::HashIndex()
{
    useHash = "rs";
    size = 65536;
    collisions = 0;

    list =new HashIndexContainer*[size];
}

/*!
 * \brief Creates a default hash table of size 65536 using RSHash
 *  Initalizes a list to the beginning table size
 * \param hs the hash to use for indexing
 */
HashIndex::HashIndex(std::string hs)
{
    useHash = hs;
    size = 65536;
    collisions = 0;

    list = new HashIndexContainer*[size];
}

/*!
 * \brief Destructor
 */
HashIndex::~HashIndex()
{
    storeStructureToFile();
    clear();
    delete[] list;
}

/*!
 * \brief Gets page data for a specific word
 * \param index the word to get the data for
 * \return vector<Page> containing all the pages
 */
std::vector<Page> HashIndex::getData(Word &index)
{
    //Creates the vector to return
    std::vector<Page> toReturn;
    //Checks if word is in the HashIndex
    if(contains(index))
    {
        //Gets a HashIndexContainer for linear chaining
        HashIndexContainer* loc = list[hash(index.getWord())%size];
        //While not empty
        while(loc != nullptr)
        {
            //If the loc has the correct value
            if(loc->getWord().getWord().compare(index.getWord()) == 0)
            {
                //Gets the data associated with index
                std::vector<int> id = loc->getData();
                //For all the pageID's get the assicated page
                for(unsigned i = 0; i < id.size(); i++)
                {
                    toReturn.push_back(getIdToPage().at(id.at(i)));
                }
                break;
            }
            //Get next link in chain
            loc = loc->getNext();
        }
    }
    //Returns the page list
    return toReturn;
}

/*!
 * \brief Adds a (Word, pageID) combo the the HashIndex
 * \param index Word to add
 * \param pageID pageID to add with the word
 */
void HashIndex::add(Word index, int pageID)
{
    //Checks if HashIndex should be rehashed
    //because to full or to many collisions
    if((double)added/size >=.75)
    {
        rehash();
    }
    else if((double)collisions/size>=.20)
    {
        rehash();
    }
    //After potential rehash get the index for the word
    unsigned numIndex = hash(index.getWord())%size;
    //Get the Container at that location
    HashIndexContainer* loc = list[numIndex];
    //If the location is empty
    if(loc == nullptr)
    {
        //Add new HashIndexContainer to the location
        list[numIndex] = new HashIndexContainer(index,pageID);
        //Updates frequency based on current frequency
        if(index.getNumber() == -1)
            list[numIndex]->getWord().setNumber(1);
        else
            list[numIndex]->getWord().setNumber(index.getNumber());
        //Updates number of words added
        setNumIndexed(getNumIndexed()+1);
        added++;
    }
    else
    {
        //Location is not empty
        bool isAdded = false;
        HashIndexContainer* nextToLast = nullptr;
        //While there are more links in the chain
        while(loc != nullptr)
        {
            //Set nextToLast at nextToLast value
            if(loc->getNext() == nullptr)
            {
                nextToLast = loc;
            }
            //If the word is alread a link
            if(loc->getWord().getWord().compare(index.getWord())==0)
            {
                //Add the pageID to the link
                loc->addPage(pageID);
                //increments based on frequency of the word passed
                if(index.getNumber() == -1)
                    loc->getWord().setNumber(loc->getWord().getNumber()+1);
                //Updates the boolean
                isAdded = true;
                //Breaks the linear chain parse
                break;
            }
            //Get next link in chain
            loc = loc->getNext();
        }
        //If not added. Add to the end of the list
        if(!isAdded)
        {
            nextToLast->setNext(new HashIndexContainer(index,pageID));
            //Updates frequency based on current frequency
            if(index.getNumber() == -1)
                nextToLast->getNext()->getWord().setNumber(1);
            else
                nextToLast->getNext()->getWord().setNumber(index.getNumber());
            //Updates collisions and other statistical data
            collisions++;
            added++;
            setNumIndexed(getNumIndexed()+1);
            isAdded = true;
        }
    }
}

/*!
 * \brief Find top 50 most frequent words
 * \return vector<Word> containing the words that appear most frequently
 */
std::vector<Word> HashIndex::mostFreq()
{
    //Create the vector to return
    std::vector<Word> toReturn;
    //Loop for fifty times
    for(int i = 0; i < 50; i++)
    {
        Word mostFrequent;
        //Loop through the whole hashIndex
        for(unsigned j = 0; j < size; j++)
        {
            //Get container for linear chaining;
            HashIndexContainer* curr = list[j];
            //While loc != nullptr
            while(curr!=nullptr)
            {
                //If the frequency of curr is greater then mostFrequent
                if(curr->getWord().getNumber() > mostFrequent.getNumber())
                {
                    //and toReturn's is greater then 0
                    if(toReturn.size() != 0)
                    {
                        //Check if word is already part of the vector
                        bool notIn = true;
                        for(unsigned i = 0; i < toReturn.size(); i++)
                        {
                            //If a vector value has the same value as current word then dont add
                            if(curr->getWord().getWord().compare(toReturn.at(i).getWord()) == 0)
                            {
                                notIn = false;
                            }
                        }
                        //If not found in vector it becomes the new mostFrequent
                        if(notIn)
                        {
                            mostFrequent = curr->getWord();
                        }
                    }
                    //or if toReturn's size == 0
                    else
                        //Curr becomes mostFrequent
                        mostFrequent = curr->getWord();
                }
                //Continue linear chaining
                curr = curr->getNext();
            }
        }
        //Add the mostFrequent word found to the vector
        toReturn.push_back(mostFrequent);
    }
    //return the vector
    return toReturn;
}

/*!
 * \brief Checks if value is inside hashIndex
 * \param index value to search for
 * \return bool if value is in index
 */
bool HashIndex::contains(Word &index)
{
    //Get number index and HAshIndexContainer for linear chaining
    unsigned numIndex = hash(index.getWord())%size;
    HashIndexContainer* loc = list[numIndex];
    while(loc != nullptr)
    {
        //If value at loc == index value
        if(loc->getWord().getWord().compare(index.getWord()) == 0)
        {
            //Returns true
            return true;
        }
        //Get next in chain
        loc = loc->getNext();
    }
    //If none found return false
    return false;
}

/*!
 * \brief Clears the list of values but does not delete the list
 */
void HashIndex::clear()
{
    //Loop throught the list
    for(unsigned i = 0; i < size; i++)
    {
        //Delete if not nullptr
        if(list[i]!=nullptr)
            delete list[i];
    }
}

/*!
 * \brief Gets the size
 * \return unsigned the Size
 */
unsigned HashIndex::getSize()
{
    return size;
}

/*!
 * \brief HashIndex::getcollisions
 * \return unsigned number of collisions
 */
unsigned HashIndex::getCollisions()
{
    return collisions;
}

/*!
 * \brief Sets the hash fucntion that will be used
 * \param hsh value to use for hash fuction
 */
void HashIndex::setHash(std::string hsh)
{
    useHash = hsh;
}

/*!
 * \brief HashIndex::getHash
 * \return
 */
std::string HashIndex::getHash()
{
    return useHash;
}

/*!
 * \brief Creates the hash for a string.
 * The hash used is based on a value stored in useHash
 * \param str value to be hashed
 * \return unsigned Hash asociated with str
 */
unsigned HashIndex::hash(std::string str)
{
    //Check if useHash equals x hash and returns
    //x hash as unsigned int
    if(useHash.compare("rs")==0)
        return RSHash(str);
    else if(useHash.compare("js")==0)
        return JSHash(str);
    else if(useHash.compare("pjw")==0)
        return PJWHash(str);
    else if(useHash.compare("elf")==0)
        return ELFHash(str);
    else if(useHash.compare("bkdr")==0)
        return BKDRHash(str);
    else if(useHash.compare("sdbm")==0)
        return SDBMHash(str);
    else if(useHash.compare("djb")==0)
        return DJBHash(str);
    else if(useHash.compare("dek")==0)
        return DEKHash(str);
    else if(useHash.compare("fnv")==0)
        return FNVHash(str);
    else if(useHash.compare("bp")==0)
        return BPHash(str);
    else if(useHash.compare("ap")==0)
        return APHash(str);
    //Default hash is RSHash
    else
        return RSHash(str);
}

/*!
 * \brief Increases the size of the array and rehashs all the values.
 * Increases the size exponetally currently 2^x but can be changed by
 * changing the scaleFactor. Deletes the old list and handles all the
 * dynamic memory allocation for copying the array to a new location.
 */
void HashIndex::rehash()
{
    //Reset collisions and added indexes (Possiblly change during rehash)
    collisions = 0;
    added = 0;
    //Create a new array with size*scaleFactor(2)
    HashIndexContainer** temp = new HashIndexContainer*[size*scaleFactor];
    //Loop through the original size
    for(unsigned i = 0; i < size; i++)
    {
        //Get HashIndexContainer for linear chaining
        HashIndexContainer* loc = list[i];
        while(loc != nullptr)
        {
            //Create a new HashIndexContainer to perserve data after delete
            HashIndexContainer* newLoc = new HashIndexContainer(*loc);
            //Call the helper
            rehashHelper(temp, newLoc);
            //Get next value in chain
            loc = loc->getNext();
        }
    }
    //Clear and delete the old list
    clear();
    delete[] list;
    //Set old list to new list and update size;
    list = temp;
    size = size*scaleFactor;
}

/*!
 * \brief Helps in the rehash process of adding a new HashIndexContainer to the list
 * \param newList pointer to the HashIndexContainer* array
 * \param idx HashIndexContainer to add the the list
 */
void HashIndex::rehashHelper(HashIndexContainer **newList, HashIndexContainer *idx)
{
    //Gets the new hash index location
    unsigned numLoc = hash(idx->getWord().getWord())%(size*scaleFactor);
    //Gets the new locations HashIndexContainer
    HashIndexContainer* loc = newList[numLoc];
    //If that location is empty
    if(loc == nullptr)
    {
        //Add idx to the new location
        added++;
        newList[numLoc] = idx;
    }
    else
    {
        //Find the last value in the chain that is not null
        while(loc->getNext()!=nullptr)
        {
            loc = loc->getNext();
        }
        //Add idx to the end of the chain
        loc->setNext(idx);
        added++;
        collisions++;
    }
}

/*!
 * \brief Retrieves the HashIndex from the "HashIndexStore.dat" file
 */
void HashIndex::retrieveStructureFromFile()
{
    std::ifstream in("HashIndexStore.dat");
    if(!in)
    {
        std::cerr << "ERROR OPENING HashIndexStore.dat FOR INPUT!\n";
        return;
    }
    int entries = 0;
    //Get the number of entries
    in >> entries;
    //Loop for all entries
    for(int i = 0; i < entries; i++)
    {
        std::string word;
        int freq;
        //Get the word and the frequency
        in >> word;
        in >> freq;
        //Ignore the ':'
        in.ignore();
        //Create Word with word and freq
        Word toAdd(word, freq);
        int pageID = 0;
        //Get first page id
        in >> pageID;
        //Stop case is -1 but if no int is nex pageID = 0
        // This catches both conditions.
        while(pageID > 0)
        {
            //Add the (Word,pageID) to the hashIndex
            add(toAdd,pageID);
            //Get the next pageID
            in >> pageID;
        }
    }
    //Close the ifstream
    in.close();
}

/*!
 * \brief Stores this data structure to the file "HashIndexStore.dat"
 */
void HashIndex::storeStructureToFile()
{
    //Create ofstream object at "HashIndexStore.dat"
    std::ofstream out("HashIndexStore.dat");
    //Checks if out opened correctly
    if(!out)
    {
        std::cerr << "ERROR OPENING HashIndexStore.dat FOR OUTPUT!\n";
        return;
    }
    //Prints the number of added elements to the file
    out << added << "\n";
    //Loops from 0-size. size
    for(unsigned i = 0; i < size; i++)
    {
        //Used for the linear chaining
        HashIndexContainer* curr = list[i];
        while(curr != nullptr)
        {
            //Get word/freq/and pageID list
            std::string word = curr->getWord().getWord();
            int freq = curr->getWord().getNumber();
            std::vector<int> pageID = curr->getData();
            //Prints ous "word freq: " followed by page numbers
            out << word << " " << freq << ": ";
            for(unsigned j = 0; j < pageID.size(); j++)
            {
                out << pageID.at(j) << " ";
            }
            //Adds a -1 at then end as stop case
            out << "-1\n";
            //Gets the next node in the linear chain
            curr = curr->getNext();
        }
    }
    //Closes ofstream
    out.close();
}
