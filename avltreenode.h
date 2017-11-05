/*!
 * \brief AVLTreeNode stores data for a BinarySearch tree.
 * This specific node i templated with type T - index and type U - data.
 * It has pointers to left and right nodes and its parent node.
 * Operator compate the index only
 * \author Jake Rowland
 * \version 1.2
 * \date 4\13\2016
 */

#ifndef AVLTREENODE
#define AVLTREENODE

#include "word.h"
#include "page.h"

#include <vector>


class AVLTreeNode
{
private:
    Word index; /*! The index value for this node*/
    std::vector<int> data; /*! The data stored inside this node*/
    int height; /*! The height of this AVLTreeNode in the \see AVLTree*/
    AVLTreeNode* right; /*! The location of the pointer that is greater then this index*/
    AVLTreeNode* left; /*! The location of the pointer that is less then this index*/

public:
    AVLTreeNode();
    AVLTreeNode(Word idx, int d);
    AVLTreeNode(Word idx, int d, AVLTreeNode* right, AVLTreeNode* left);

    ~AVLTreeNode();
    bool operator==(AVLTreeNode& other);
    bool operator<(AVLTreeNode& other);
    Word& getIndex();
    void setIndex(Word idx);
    int getHeight();
    void setHeight(int h);
    std::vector<int>& getData();
    void setData(std::vector<int> d);
    void addPage(int d);
    AVLTreeNode*& getRight();
    void setRight(AVLTreeNode* r);
    AVLTreeNode*& getLeft();
    void setLeft(AVLTreeNode* l);
    std::string toString();
};

#endif // AVLTREENODE

