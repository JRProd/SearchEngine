#include "userinterface.h"

UserInterface::UserInterface() {
    stop = false;
}

void UserInterface::start() {
    std::cout << "Before you begin. Would you like to use the \n\t0 - AVLTree\n\t1 - HashIndex\n>> ";
    std::string input = "";
    std::cin >> input;
    if(input == "0")
    {
        Indexer* index = new AVLTree();
        se.setIndexPtr(index);
    }
    else if(input == "1")
    {
        Indexer* index = new HashIndex();
        se.setIndexPtr(index);
    }
    else
    {
        std::cout << "Invalid command. Using HashIndex.\n";
        Indexer* index = new HashIndex();
        se.setIndexPtr(index);
    }

    std::cout << "Now, would you like to load in a file? \n(You must load a file before you can Query) \n\tyes - Load File\n\tno  - Load File Later\n>> ";
    input = "";
    bool incorrect = false;
    std::cin >> input;
    do
    {
        if(input == "yes")
        {
            loadFile();
            incorrect = false;
            break;
        }
        else if(input == "no")
        {
            indexedParsed = false;
            incorrect = false;
        }
        else
        {
            std::cout << "Invalid command.\n";
            std::cout << "Would you like to load in a \nfile? (You must load a file before you can Query) yes/no >> ";
            std::getline(std::cin, input , '\n');
            std::cin >> input;
            incorrect = true;
        }
    }while(incorrect == true);

    std::cout << "Finally would you like to enter User Mode or Maintanance Mode?\n\tu - User Mode\n\tm - Maintanance Mode\n>> ";
    input = "";
    incorrect = false;
    std::cin >> input;
    do
    {
        if(input == "u")
        {
            user();
            incorrect = false;
        }
        else if(input == "m")
        {
            maintenance();
            incorrect = false;
        }
        else
        {
            std::cout << "Invalid command.\n";
            std::cout << "Would you like to enter User Mode or Maintanance Mode?\n\tu - User Mode\n\tm - Maintanance Mode\n>> ";
            std::getline(std::cin, input , '\n');
            std::cin >> input;
            incorrect = true;
        }
    }while(incorrect == true);
    se.close();
    std::cout << "Endding Program\n";
}

void UserInterface::loadFile()
{
    std::cout << "Would you like to load from\n";
    std::cout << "\t0 - Persistent File\n";
    std::cout << "\t1 - Wikibooks (XML)\n";
    std::cout << "\t2 - Own XML File\n";
    std::cout << ">> ";
    bool incorrect = false;
    std::string input = "";
    std::cin >> input;
    do
    {
        if(input == "0")
        {
            se.readPersistent();
            indexedParsed = true;
            incorrect = false;
            return;
        }
        else if(input == "1")
        {
            se.addDocument("enwikibooks-latest-pages-meta-current.xml");
            se.parseDocument();
            indexedParsed = true;
            incorrect = false;
            return;
        }
        else if(input == "2")
        {
            std::cout << "Enter the document to parse >> ";
            std::cin >> input;
            se.addDocument(input);
            se.parseDocument();
            indexedParsed = true;
            incorrect = false;
            return;
        }
        else
        {
            std::cout << "Invalid command. Would you like to load from\n";
            std::cout << "\t0 - Persistent File\n";
            std::cout << "\t1 - Wikibooks (XML)\n";
            std::cout << "\t2 - Own XML File\n";
            std::cout << ">> ";
            std::getline(std::cin, input , '\n');
            std::cin >> input;
            incorrect = true;
        }
    }while(incorrect == true);
    indexedParsed = true;
}

void UserInterface::user() {
    std::string input;
	std::cout << "Standard User Mode" << std::endl;
    std::cout << "Choose what you would like to do. " << std::endl;
    std::cout << "\t0 - Enter a query" << std::endl;
    std::cout << "\t1 - Print statistics" << std::endl;
    std::cout << "\t2 - Goto Maintenance Mode\n";
    std::cout << "\tEND - Exit" << std::endl;
    std::cout << "NOTE: Must load index into a data structure before querying.\n>> ";
    stop = false;
    while(stop == false)
    {
        std::cin >> input;
        bool incorrect = false;
        do
        {
            if (input == "0") {
                input = "";
                if(indexedParsed == false)
                    loadFile();
                std::cout << "Enter query >> ";
                std::getline(std::cin, input , '\n');
                std::getline(std::cin, input , '\n');
                se.querySearch(input); //returns pages of results
                incorrect = false;
                input = "";
                std::cout << "Enter another command?\n";
                std::cout << "\t0 - Enter a query" << std::endl;
                std::cout << "\t1 - Print statistics" << std::endl;
                std::cout << "\t2 - Goto Maintenance Mode\n";
                std::cout << "\tEND - Exit" << std::endl;
                std::cout << ">> ";
            }
            //Print stats
            else if (input == "1") {
                se.printStats();
                std::cout << "Enter another command?\n";
                std::cout << "\t0 - Enter a query" << std::endl;
                std::cout << "\t1 - Print statistics" << std::endl;
                std::cout << "\t2 - Goto Maintenance Mode\n";
                std::cout << "\tEND - Exit\n>> ";
                incorrect = false;
            }
            else if (input == "2") {
                maintenance();
                incorrect = false;
            }
            else if (input == "END") {
                stop = true;
                incorrect = false;
                return;
            }
            else if(stop)
            {
                return;
            }
            //Error message
            else {
                std::cerr << "Invalid entry.\n";
                std::cout << "Please reenter the command >> ";
                std::cin >> input;
                incorrect = true;
            }
        }while(incorrect == true);
    }
}

//allows the user to add documents to the index by supplying the path to a new file containing properly marked - up documents
//allows the user to clear the index completely
void UserInterface::maintenance() {
    std::string input;
	std::cout << "Maintenance Mode" << std::endl;
	std::cout << "Options (type the corresponding number): " << std::endl;
    std::cout << "\t0 - Add documents to the index" << std::endl;
    std::cout << "\t1 - Clear the index" << std::endl;
    std::cout << "\t2 - Goto User Mode\n";
    std::cout << "\tEND - Exit" << std::endl;
    stop = false;
    while(stop == false)
    {
        std::cin >> input;
        bool incorrect = false;
        do
        {
            if (input == "0") {
                std::cout << "Enter name of file >> ";
                std::string loc;
                std::cin >> loc;
                se.addDocument(loc);
                se.parseDocument();
                std::cout << "Enter another command?\n";
                std::cout << "\t0 - Add documents to the index" << std::endl;
                std::cout << "\t1 - Clear the index" << std::endl;
                std::cout << "\t2 - Goto User Mode\n";
                std::cout << "\tEND - Exit\n>> ";
                incorrect = false;
            }
            else if (input == "1") {
                se.clearIndex();
                std::cout << "Enter another command?\n";
                std::cout << "\t0 - Add documents to the index" << std::endl;
                std::cout << "\t1 - Clear the index" << std::endl;
                std::cout << "\t2 - Goto User Mode\n";
                std::cout << "\tEND - Exit\n>> ";
                incorrect = false;
            }
            else if (input == "2") {
                user();
                incorrect = false;
            }
            else if (input == "END") {
                stop = true;
                incorrect = false;
                return;
            }
            else {
                std::cout << "Invalid entry" << std::endl;
                std::cout << "Please reenter your command >> ";
                std::cin >> input;
                incorrect = true;
            }
        }while(incorrect == true);
    }
}
