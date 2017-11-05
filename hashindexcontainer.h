#ifndef HASHINDEXCONTAINER
#define HASHINDEXCONTAINER

#include "word.h"
#include "page.h"

#include <vector>

class HashIndexContainer
{
private:
    Word index;
    std::vector<int> data;
    HashIndexContainer* next;
public:
    HashIndexContainer();
    HashIndexContainer(HashIndexContainer& copy);
    HashIndexContainer(Word idx, int d);
    ~HashIndexContainer();

    Word& getWord();
    void setWord(Word idx);
    std::vector<int> getData();
    void setData(std::vector<int> d);
    void addPage(int d);
    HashIndexContainer* getNext();
    void setNext(HashIndexContainer* n);
};

#endif // HASHINDEXCONTAINER

