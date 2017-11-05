#include "userinterface.h"

UserInterface::UserInterface() {

}

void UserInterface::start(std::string x) {
	SearchEngine se;
	running = true;
	while (running) {
		if (x == "m") {
			if (maintenance())
				running = !running;
		}
		else if(x == "u") {
			if (user())
				running = !running;
		}
		else {
			std::cout << "Incorrect letter." << std::endl;
			running = !running;
		}
	}
}

bool UserInterface::user() {
	std::string input;
	bool stop = false;
	std::cout << "Standard User Mode" << std::endl;
	std::cout << "Options (type the corresponding number): " << std::endl;
	std::cout << "1. Choose between loading into an AVL tree or a hash table" << std::endl;
	std::cout << "2. Enter a query" << std::endl;
	std::cout << "3. Print statistics" << std::endl;
	std::cout << "4. Exit" << std::endl;
	std::cout << "NOTE: Must load index into a data structure before querying." << std::endl;
	std::cin >> input;

	//AVL Tree or Hash Table
	if (input == "1") {
		input = "";
		std::cout << "Options (type the corresponding number): " << std::endl;
		std::cout << "1. AVL Tree" << std::endl;
		std::cout << "2. Hash Table" << std::endl;
		std::cin >> input;
		if (input == "1") {
			Indexer* i = new AVLTree();
			se.setIndexPtr(i);
			std::cout << "Index loaded into AVL tree." << std::endl;
		}
		else if (input == "2") {
			Indexer* i = new HashIndex();
			se.setIndexPtr(i);
			std::cout << "Index loaded into hash table." << std::endl;
		}
		else {
			std::cerr << "Invalid entry.";
		}
	}
	//Enter a query
	else if (input == "2") {
		input = "";
		std::cout << "Enter query: ";
		std::cin >> input;
		se.querySearch(input); //returns pages of results
	}
	//Print stats
	else if (input == "3") {
		input = "";
		se.printStats();
	}
	else if (input == "4") {
		input = "";
		std::cout << "Exiting program.";
		stop = !stop;
	}
	//Error message
	else {
		input = "";
		std::cerr << "Invalid entry.";
	}

	return stop;
}

//allows the user to add documents to the index by supplying the path to a new file containing properly marked - up documents
//allows the user to clear the index completely
bool UserInterface::maintenance() {
	std::string input;
	bool stop = false;
	std::cout << "Maintenance Mode" << std::endl;
	std::cout << "Options (type the corresponding number): " << std::endl;
	std::cout << "1. Add documents to the index" << std::endl;
	std::cout << "2. Clear the index" << std::endl;
	//std::cout << "3. Enter user mode" << std::endl;
	std::cout << "3. Exit" << std::endl;
	std::cin >> input;

	if (input == "1") {
		std::cout << "Enter name of file: ";
		std::string loc;
		std::cin >> loc;
		se.addDocument(loc);
	}
	else if (input == "2") {
		se.clearIndex();
	}
	else if (input == "3") {
		stop = !stop;
	}
	else {
		std::cout << "Invalid entry" << std::endl;
	}
	return stop;
}
