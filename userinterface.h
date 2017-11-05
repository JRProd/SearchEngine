//userinterface.h

#ifndef USERINTERFACE_H
#define USERINTERFACE_H

#include "searchengine.h"
#include <vector>

class UserInterface {
private:
	SearchEngine se;
    void user();
    void maintenance();
    void loadFile();
    bool indexedParsed;
    bool stop;

public:
	UserInterface();
    void start();

};
#endif
