#ifndef HASHINDEX
#define HASHINDEX

#include "indexer.h"
#include "hashindexcontainer.h"
#include "GeneralHashFunctions.h"

class HashIndex : public Indexer
{
private:
    HashIndexContainer** list;
    std::string useHash;

    unsigned size;
    unsigned added;
    unsigned collisions;
    const unsigned scaleFactor = 2;

    unsigned hash(std::string str);
    void rehash();
    void rehashHelper(HashIndexContainer** newList, HashIndexContainer* idx);
public:
    HashIndex();
    HashIndex(std::string hs);
    ~HashIndex();

    std::vector<Page> getData(Word &index);
    void add(Word index, int pageID);
    std::vector<Word> mostFreq();
    bool contains(Word &index);
    void clear();
    unsigned getSize();
    unsigned getCollisions();
    void setHash(std::string hsh);
    std::string getHash();

    void retrieveStructureFromFile();
    void storeStructureToFile();
};

#endif // HASHINDEX

