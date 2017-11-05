/*!
 * \brief Creates an AVLTreeNode that allows binary searching.
 * The index for each node will be a \see Word object and the data payload will
 * be a vector of \see Page classes. The node will also store the left and right
 * AVLTreeNodes as pointers.
 * \author Jake Rowland
 * \version 1.3
 * \date 4\17\2016
 */

#include "avltreenode.h"

/*!
 * \brief Default constructor
 */
AVLTreeNode::AVLTreeNode()
{
    index = Word();
    data = std::vector<int>();
    data.reserve(1000);
    setLeft(nullptr);
    setRight(nullptr);
    height = 0;
}

/*!
 * \brief Constructor with the minimun about of data
 * \param idx The value of type T that will be used as the index
 * \param d The value of type U that will be used as the data
 * \param parent The location of the node that points to this node
 */
AVLTreeNode::AVLTreeNode(Word idx, int d)
{
    setIndex(idx);
    data = std::vector<int>();
    data.reserve(1000);
    data.push_back(d);
    setLeft(nullptr);
    setRight(nullptr);
    height = 0;
}

/*!
 * \brief Constructor with the right and left nodes as well as other data
 * \param idx The value of type T that will be used as the index
 * \param d The value of type U that will be used as the data
 * \param parent The location of the node that points to this node
 * \param right The location of the pointer that is greater then this index
 * \param left The location of the pointer that is less then this index
 */
AVLTreeNode::AVLTreeNode(Word idx, int d, AVLTreeNode* right, AVLTreeNode* left)
{
    setIndex(idx);

    data = std::vector<int>();
    data.reserve(1000);
    data.push_back(d);

    setRight(right);
    setLeft(left);

    height = 0;
}

/*!
 *  \brief Recusivly destroyes all the nodes in a tree
 */
AVLTreeNode::~AVLTreeNode()
{
    if(right!=nullptr)
        delete right;
    if(left!=nullptr)
        delete left;
    data.clear();
}

/*!
 * \brief Determines if the indexes are the same
 * \param other The AVLTreeNode to compare to.
 * \return True if this index equals other's index
 */
bool AVLTreeNode::operator==(AVLTreeNode& other)
{
    if(this->getIndex()==other.getIndex())
        return true;
    else return false;
}

/*!
 * \brief Determ;ines if this index is greater than another
 * \param other The AVLTreeNode to compare to.
 * \return True if this index is greater than other's index
 */
bool AVLTreeNode::operator<(AVLTreeNode& other)
{
    if(this->getIndex() < this->getIndex())
        return true;
    return false;
}

/*!
 * \brief Get the index of the AVLTreeNode
 * \return Index with value of type T
 */
Word& AVLTreeNode::getIndex()
{
    return index;
}

/*!
 * \brief Sets the index of the AVLTreeNode
 * \param idx Value of type T to be used as the Index
 */
void AVLTreeNode::setIndex(Word idx)
{
    index = idx;
}

/*!
 * \brief Gets the height of this node in the \see AVLTree (Specific to Tree).
 * \return The height
 */
int AVLTreeNode::getHeight()
{
    return height;
}

/*!
 * \brief Sets the height of this node in the \see AVLTree (Specific to Tree).
 * \param h The new height of this node
 */
void AVLTreeNode::setHeight(int h)
{
    height = h;
}

/*!
 * \brief Get the data of the AVLTreeNode
 * \return DAta with value of type U
 */
std::vector<int>& AVLTreeNode::getData()
{
    return data;
}

/*!
 * \brief Sets the data of the AVLTreeNode
 * \param idx Value of type U to be used as the Data
 */
void AVLTreeNode::setData(std::vector<int> d)
{
    data = d;
}

/*!
 * \brief Add a pageID to the vector. Removes duplicates
 * \param d pageID to add
 */
void AVLTreeNode::addPage(int d)
{
    //Checks if d is in the vector
    bool isIn = false;
    for(int j = 0; j < data.size(); j++)
    {
        //If vector value equals d
        if(d==data.at(j))
            //d is already in the vector
            isIn = true;
    }
    //If d has not been added
    if(!isIn)
        //Add d
        data.push_back(d);
}

/*!
 * \brief Get the pointer of the AVLTreeNode to the right
 * \return AVLTreeNode* with value of type <T,U>
 */
AVLTreeNode*& AVLTreeNode::getRight()
{
    return right;
}

/*!
 * \brief Sets the right AVLTreeNode of the AVLTreeNode
 * \param idx Value of type AVLTreeNode to be used as the right pointer
 */
void AVLTreeNode::setRight(AVLTreeNode* r)
{
    right = r;
}

/*!
 * \brief Get the pointer of the AVLTreeNode to the left
 * \return AVLTreeNode* with value of type <T,U>
 */
AVLTreeNode*& AVLTreeNode::getLeft()
{
    return left;
}

/*!
 * \brief Sets the left AVLTreeNode of the AVLTreeNode
 * \param idx Value of type AVLTreeNode to be used as the left pointer
 */
void AVLTreeNode::setLeft(AVLTreeNode* l)
{
    left = l;
}

/*!
 * \brief Transforms the node to a stirng
 * \return string formated to print out readable data assocaited with this node
 */
std::string AVLTreeNode::toString()
{
    //If the node is not empty
    if(index.getWord() != "")
    {
        //Adds "word frequency: " to the string
        std::string toReturn = index.getWord() + " " + std::to_string(index.getNumber()) + ": ";
        //Adds all the pageID data after
        for(int i = 0; i < data.size(); i++)
        {
            std::string temp = std::to_string(data.at(i));
            toReturn += temp + " ";
        }
        //Creates a stop case at the end
        toReturn += "-1";
        //returns the string
        return toReturn;
    }
    //Returns empty string
    return "";
}
