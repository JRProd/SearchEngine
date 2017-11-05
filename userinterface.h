//userinterface.h

#ifndef USERINTERFACE_H
#define USERINTERFACE_H

#include "searchengine.h"
#include <vector>

class UserInterface {
private:
	SearchEngine se;
	bool user();
	bool maintenance();
	bool running;

public:
	UserInterface();
	void start(std::string);

};
#endif