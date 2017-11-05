//page.h

#ifndef PAGE_H
#define PAGE_H

#include <iostream>
#include <string>

class Page {
private:
    std::string title;
    int idNumber;
    std::string author;
    std::string text;
    double rank;

public:
    Page();
    Page(std::string, int, std::string, std::string);
    std::string getTitle();
    void setTitle(std::string);
    int getIDNumber();
    void setIDNumber(int);
    std::string getAuthor();
	void setAuthor(std::string);
    std::string getText();
    std::string& getTextRef();
    void setText(std::string);
    double getRank();
    void setRank(double);
    bool operator<(Page &); //in planning the return value is a Page &, should be bool I think
    bool operator==(Page &);
};
#endif
