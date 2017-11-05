#include "documentprocessor.h"

using namespace tinyxml2;

DocumentProcessor::DocumentProcessor() {
	document = "";
    index = nullptr;
	setStopWords();
}

DocumentProcessor::DocumentProcessor(std::string d) {
	document = d;
    index = nullptr;
	setStopWords();
}

DocumentProcessor::DocumentProcessor(Indexer* idx) {
    document = "";
    index = idx;
    setStopWords();
}

void DocumentProcessor::setDocumentIndex(Indexer* idx) {
	document = "";
	index = idx;
	setStopWords();
}

void DocumentProcessor::parse(std::string dir) {
	XMLDocument xmldoc;
    xmldoc.LoadFile(dir.c_str());
	XMLElement* root_node = xmldoc.FirstChildElement();
	XMLElement* page_node = root_node->FirstChildElement("page");
    int counter = 0;
    int notIndexed = 0;

	std::cout << "Begin parsing the file" << "\n";
    while( true )
    {
		if (page_node == nullptr)
			break;
		XMLElement* title = page_node->FirstChildElement("title");
		XMLElement* id = page_node->FirstChildElement("id");
		XMLElement* revision = page_node->FirstChildElement("revision");
		XMLElement* username = revision->FirstChildElement("contributor")->FirstChildElement("username");
		XMLElement* text = revision->FirstChildElement("text");

		int numID;
		if (id == nullptr)
			numID = -1;
		else
			numID = atoi(id->GetText());

		if (text != nullptr)
		{
			if (text->GetText() == nullptr)
			{
                page_node = page_node->NextSiblingElement("page");
				continue;
			}
		}

        Page pageDoc((title == nullptr ? "" : title->GetText()), numID, (username == nullptr ? "" : username->GetText()), (text == nullptr || text->GetText() == nullptr ? "" : text->GetText()));
        if (parseText(pageDoc, index)) {
            counter++;
		}
        else
        {
            notIndexed++;
            counter++;
        }

        page_node = page_node->NextSiblingElement("page");
	}
    std::cout << "Total :: " << counter << "\n";
    std::cout << "Added :: " << counter-notIndexed << "\n";
    std::cout << "Foreign removed: " << notIndexed << "\n";
}

void DocumentProcessor::addDocument(std::string dir) {
	parse(dir);
}


void DocumentProcessor::setDocument(std::string d) {
	document = d;
}

bool DocumentProcessor::parseText(Page &page, Indexer* index)
{
    if(page.getTitle().compare(0,4,"User")==0||page.getTitle().compare(0,4,"File")==0)
        return false;
    int foriegn = 0; //make global later
    double percent;
	std::vector<std::string> tokens;
	//std::cout << "Begin to parseText" << "\n";

    std::istringstream iss(page.getTextRef());
	copy_if(std::istream_iterator<std::string>(iss),
		std::istream_iterator<std::string>(),
        std::back_inserter(tokens),[](const std::string str)
    {
        if(str.size() > 30)
        {
            return false;
        }
        else if(str.size() <= 2)
        {
            return false;
        }
        else if(str.find_first_of("1234567890`-=[]\\;',./~!@#$%^&*()_+{}|:\"<>?")!= std::string::npos)
        {
            return false;
        }
        return true;
    });
    int size = tokens.size();
	for (int i = 0; i < size; i++)
	{
        toLowerCase(tokens[i]);
        std::string temp = tokens[i];

        if (temp.find_first_not_of("abcdefghijklmnopqrstuvwxyz") != std::string::npos)
        {
           foriegn++;
           percent = (double)foriegn/size;
           if(percent >= .15)
           {
               //std::cout << "FORIEGN PAGE REMOVED\n";
               return false;
           }
           tokens[i] = "a";
		}
        else if (stopWords.find(temp) != stopWords.end())
		{
            //std::cout << "Stop Word" << "\n";
            tokens[i] = "a";
		}
		else if (stemmedWords.find(temp) != stemmedWords.end())
		{
			//std::cout << "Stemmed Word" << "\n";
            tokens[i] = stemmedWords.at(temp);
		}
		else
		{
            std::string unstemmed = tokens[i];
            Porter2Stemmer::stem(tokens[i]);
            stemmedWords.emplace(unstemmed, tokens[i]);
		}
    }

    std::string temp = "";
    for (unsigned i = 0; i < tokens.size(); i++)
    {
        if(tokens[i] !="a")
            temp += tokens[i] + " ";
    }
    page.setText(temp);

    int newID = index->addPage(page);
    page.setIDNumber(newID);

    int id = page.getIDNumber();
    for (unsigned i = 0; i < tokens.size(); i++)
    {
        if(tokens[i] != "a")
        {
            //std::cout << i << " - "  << tokens[i] << " ";
            index->add(Word(tokens[i]), id);
        }
    }
    index->setNumDataIndexed(index->getNumDataIndexed()+1);
    return true;
}

void DocumentProcessor::toLowerCase(std::string& str)
{
    for(unsigned i = 0; i < str.size(); i++)
    {
        if(str.at(i) >= 'A' && str.at(i) <= 'Z')
            str[i] = str[i]+32;
    }
}

void DocumentProcessor::setStopWords()
{
	std::ifstream in("stopwords.txt", std::ios::in);
	if (!in)
		std::cout << "ERROR OPENING STOPWORDS.TXT\n";
	else
	{
		std::string temp;
		in >> temp;
		while (!in.eof())
		{
			stopWords.emplace(temp);
			in >> temp;
		}
	}
}
