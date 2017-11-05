#ifndef AVLTREE
#define AVLTREE

#include <string>
#include <map>

#include "avltreenode.h"
#include "indexer.h"

class AVLTree : public Indexer
{
private:
    AVLTreeNode* treeRoot;
    AVLTreeNode* mostFrequent;
    std::vector<Word> topFifty;

    int height(AVLTreeNode* node);
    int max(int leftHeight, int rightHeight);
    void insert(AVLTreeNode*& node, AVLTreeNode*& root);

    AVLTreeNode* get(Word& node, AVLTreeNode* root);
    bool contains(Word& index, AVLTreeNode* root);
    void mostFreq(AVLTreeNode* root);

    std::string inOrder(AVLTreeNode* root);
    std::string preOrder(AVLTreeNode* root);
    std::string postOrder(AVLTreeNode* root);

    void rotateLeftChild(AVLTreeNode*& alpha1);
    void rotateRightChild(AVLTreeNode*& alpha4);
    void doubleLeftChild(AVLTreeNode*& alpha3);
    void doubleRightChild(AVLTreeNode*& alpha2);

    void clear(AVLTreeNode*& root);

    std::string storeStructureToFile(AVLTreeNode*& root);
protected:
    AVLTreeNode* getRoot();
public:
    AVLTree();
    AVLTree(AVLTree& copy);
    ~AVLTree();
    std::vector<Page> getData(Word& index);
    void add(Word index, int pageID);
    //int addPage(Page index);
    std::vector<Word> mostFreq();
    bool contains(Word& index);
    void clear();
    std::string inOrder();
    std::string preOrder();
    std::string postOrder();

    void storeStructureToFile();

    void retrieveStructureFromFile();
};

#endif // AVLTREE

