//word.h

#ifndef WORD_H
#define WORD_H

#include <iostream>
#include <string>

class Word {
private:
	std::string word;
	int numAppear;

public:
	Word();
	Word(std::string);
	Word(std::string, int);
	std::string getWord();
	void setWord(std::string);
	int getNumber();
	void setNumber(int);
    bool operator<(Word &); //in planning return value is int, should be bool I think
    bool operator==(Word &);

};
#endif
