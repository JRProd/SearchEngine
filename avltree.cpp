/*!
 * \brief Creates and manages a AVL binary search tree.
 * The index for each node will be a \see Word object and the data payload will
 * be a vector of \see Page classes.
 * \author Jake Rowland
 * \version 1.0
 * \date 4\17\2016
 */

#include "indexer.h"
#include "avltree.h"

#include <iostream>

//PRIVATE
/*!
 * \brief Gets the height from the bottem of the tree
 * \param node Node to find height for
 * \return Returns the height
 */
int AVLTree::height(AVLTreeNode* node)
{
    return node == nullptr ? -1 : node->getHeight();
}

/*!
 * \brief Finds the max of two numbers
 * \param leftHeight First Number
 * \param rightHeight Second Number
 * \return The greater number
 */
int AVLTree::max(int leftHeight, int rightHeight)
{
    return leftHeight > rightHeight ? leftHeight : rightHeight;
}

/*!
 * \brief Inserts a node into the tree. All nodes are dynamic
 * \param node The node to add
 * \param root Recursice tace node. Starts at this.root
 */
void AVLTree::insert(AVLTreeNode*& node, AVLTreeNode*& curr)
{
    //If the root value has no node, set the node to this root pointer.
    // The changes propogate to the AVLTreeNode because pass by refrence
    if(curr == nullptr)
    {
        //Equates the root to the node and sets the number of times
        // the word is indexed to 1
        curr = node;
        //If node has default frequency set to 1
        if(node->getIndex().getNumber()== -1)
        {
            curr->getIndex().setNumber(1);

        }
        //Else set to node's frequency
        else
        {
            curr->getIndex().setNumber(node->getIndex().getNumber());
            //setNumIndexed(getNumIndexed() + curr->getIndex().getNumber());
        }
        setNumIndexed(getNumIndexed()+1);
    }
    else if(node->getIndex() < curr->getIndex()) //If the node's index is lower (on the left) of the root's value
    {
        //Recursivly call insert
        insert(node, curr->getLeft());
        //Check if tree is balance
        if(height(curr->getLeft())-height(curr->getRight())==2)
        {
            //Tree not balanced, rebalance tree
            if(node->getIndex() < curr->getLeft()->getIndex())
                rotateLeftChild(curr);
            else
                doubleLeftChild(curr);
        }
    }
    //If the root's index is lower (on the right) of the node's value
    else if(curr->getIndex() < node->getIndex())
    {
        //Recersivly call insert
        insert(node, curr->getRight());
        //Check if tree is balance
        if(height(curr->getRight())-height(curr->getLeft())==2)
        {
            //Tree not balanced, rebalance tree
            if(curr->getRight()->getIndex() < node->getIndex())
                rotateRightChild(curr);
            else
                doubleRightChild(curr);
        }
    }
    else //Node's value is not > or < root's value
    {
        //Do not create new node, update statistical data and copy over pages
        curr->getIndex().setNumber(curr->getIndex().getNumber()+1);

        std::vector<int> copy = node->getData();

        for(unsigned i = 0; i < copy.size(); i++)
        {
            curr->addPage(copy.at(i));
        }
        //Delete the node because its not needed anymore.
        if(node!=nullptr)
            delete node;
    }
    //Update the height of the current node
    curr->setHeight( max( height( curr->getLeft() ), height( curr->getRight() ) ) +1 );
}

/*!
 * \brief Gets a AVLTreeNode associated with a Word.
 * \param node The Word to find the node for
 * \param root Recursice tace node. Starts at this.root
 * \return A Reference to node that matched the Word
 */
AVLTreeNode* AVLTree::get(Word& node, AVLTreeNode* root)
{
    if(root->getIndex().getWord().compare(node.getWord())==0)
    {
        return root;
    }
    else if(node < root->getIndex())
    {
        if(root->getLeft()!=nullptr)
            return get(node, root->getLeft());
    }
    else if(root->getIndex() < node)
    {
        if(root->getRight()!=nullptr)
            return get(node, root->getRight());
    }
    return nullptr;
}

/*!
 * \brief Checks if the Word is in the AVLTree
 * \param node The Word to see if it is inside the tree
 * \param root Recursice tace node. Starts at this.root
 * \return True if node is found
 */
bool AVLTree::contains(Word& node, AVLTreeNode* root)
{
    if(root == nullptr)
    {
        return false;
    }
    if(root->getIndex().getWord().compare(node.getWord())==0)
    {
        return true;
    }
    if(node < root->getIndex())
    {
        return contains(node, root->getLeft());
    }
    if(root->getIndex() < node)
    {
        return contains(node, root->getRight());
    }
    return false;
}

/*!
 * \brief Finds the most frequent node
 * \param root Recursice tace node. Starts at this.root
 */
void AVLTree::mostFreq(AVLTreeNode* root)
{
    if(root!=nullptr)
    {
        //Gets left node first
        mostFreq(root->getLeft());
        //If root's value is greater then mostFrequent
        if(root->getIndex().getNumber() > mostFrequent->getIndex().getNumber())
        {
            //And topFifty's size greater then 0
            if(topFifty.size()!=0)
            {
                //Check if word is in topFifty
                bool notIn = true;
                for(unsigned i = 0; i < topFifty.size(); i++)
                {
                    //If vector contains value equal to word
                    if(root->getIndex().getWord().compare(topFifty.at(i).getWord()) == 0)
                    {
                        //Dont add
                        notIn = false;
                    }
                }
                //If not in
                if(notIn)
                {
                    //mostFrequent equals the root
                    mostFrequent = root;
                }
            }
            //Or if topFifty's size equals 0
            else
            {
                //mostFrequent = root;
                mostFrequent = root;
            }
        }
        //Move to the nodes right node
        mostFreq(root->getRight());
    }
}

/*!
 * \brief Creates a string of the tree in inOrder format
 * \param root Recursice tace node. Starts at this.root
 * \return String inOrder
 */
std::string AVLTree::inOrder(AVLTreeNode* root)
{
    if(root != nullptr)
        return inOrder(root->getLeft()) + " " + root->getIndex().getWord() + " " + inOrder(root->getRight());
    else
        return "";
}

/*!
 * \brief Creates a string of the tree in preOrder format
 * \param root Recursice tace node. Starts at this.root
 * \return String preOrder
 */
std::string AVLTree::preOrder(AVLTreeNode* root)
{
    if(root != nullptr)
        return root->getIndex().getWord() + " " + postOrder(root->getLeft())  + " " + postOrder(root->getRight());
    else
        return "";
}

/*!
 * \brief Creates a string of the tree in postOrder format
 * \param root Recursice tace node. Starts at this.root
 * \return String postOrder
 */
std::string AVLTree::postOrder(AVLTreeNode* root)
{
    if(root != nullptr)
        return postOrder(root->getLeft())  + " " + postOrder(root->getRight())+ " " + root->getIndex().getWord();
    else
        return "";
}

/*!
 * \brief Single rotate left child to balance tree
 * \param alpha1 The node needed to rotate
 */
void AVLTree::rotateLeftChild(AVLTreeNode*& alpha1)
{
    AVLTreeNode* tempChild = alpha1->getLeft();
    alpha1->setLeft(tempChild->getRight());
    tempChild->setRight(alpha1);
    alpha1->setHeight(max(height(alpha1->getLeft()), height(alpha1->getRight()))+1);
    tempChild->setHeight(max(height(tempChild->getLeft()), alpha1->getHeight())+1);
    alpha1 = tempChild;
}

/*!
 * \brief Single rotate right child to balance tree
 * \param alpha4 The node needed to rotate
 */
void AVLTree::rotateRightChild(AVLTreeNode*& alpha4)
{
    AVLTreeNode* tempChild = alpha4->getRight();
    alpha4->setRight(tempChild->getLeft());
    tempChild->setLeft(alpha4);
    alpha4->setHeight(max(height(alpha4->getLeft()), height(alpha4->getRight()))+1);
    tempChild->setHeight(max(height(tempChild->getLeft()), alpha4->getHeight())+1);
    alpha4 = tempChild;
}

/*!
 * \brief Double left swap to balance the tree
 * \param alpha3 the AVLTreeNode for the double left switch
 */
void AVLTree::doubleLeftChild(AVLTreeNode*& alpha3)
{
    rotateRightChild(alpha3->getLeft());
    rotateLeftChild(alpha3);
}

/*!
 * \brief Double right swap to balance the tree
 * \param alpha2 the AVLTreeNode for the double right switch
 */
void AVLTree::doubleRightChild(AVLTreeNode*& alpha2)
{
    rotateLeftChild(alpha2->getRight());
    rotateRightChild(alpha2);
}

/*!
 * \brief Clears the tree
 * \param root Recursice tace node. Starts at this.root
 */
void AVLTree::clear(AVLTreeNode*& root)
{
    if(root == nullptr)
        return;
    clear(root->getLeft());
    clear(root->getRight());
    delete root;
}

/*!
 * \brief Recusive form of storeStuctureToFile
 * \param root Recursice tace node. Starts at this.root
 * \return AVLTree as a string
 */
std::string AVLTree::storeStructureToFile(AVLTreeNode *& root)
{
    //While root != nullptr
    if(root!=nullptr)
    {
        //Return root's string followed by root's left and root's right string
        return  root->toString() + "\n" + storeStructureToFile(root->getLeft())
                + storeStructureToFile(root->getRight());
    }
    else
        return "";
}

//PROTECTED
/*!
 * \brief Gets the root of the tree
 * \return The root pointer of the tree
 */
AVLTreeNode* AVLTree::getRoot()
{
    return treeRoot;
}

//PUBLIC
/*!
 * \brief Default constructor
 */
AVLTree::AVLTree()
{
    treeRoot = nullptr;
    setNumIndexed(0);
    setNumDataIndexed(0);
}

/*!
 * \brief Copy constructor
 * \param copy AVLTree to copy to
 */
AVLTree::AVLTree(AVLTree& copy)
{
    treeRoot = copy.getRoot();
    setNumIndexed(0);
    setNumDataIndexed(0);
}

/*!
 * \brief Deallocates the memory for the Tree.
 * Calls the desturctor for the root node with recusively class
 * its childrends nodes until all are deallocated.
 */
AVLTree::~AVLTree()
{
    storeStructureToFile();
    if(treeRoot!=nullptr)
        delete treeRoot;
}

/*!
 * \brief Gets the Data associated with a Word
 * \param index The Word to retrive data for
 * \return Returns a referenc to the Data with the index Word
 */
std::vector<Page> AVLTree::getData(Word& index)
{
    //Gets the pageID vector asociated with index
    std::vector<int> temp = get(index, treeRoot)->getData();
    std::vector<Page> toReturn;
    //Reserve to speed up
    toReturn.reserve(temp.size());

    //For all int's of temp
    for(unsigned i = 0; i < temp.size(); i++)
    {
        //Add the page asociated with an int in temp
        toReturn.push_back(getIdToPage().at(temp.at(i)));
    }
    //Return page vector
    return toReturn;
}

/*!
 * \brief Adds a Word/Page combo to the index
 * \param index The Word to add
 * \param data The Page to add
 */
void AVLTree::add(Word index, int pageID)
{
    //Create new AVLTreeNode
    AVLTreeNode* temp = new AVLTreeNode(index, pageID, nullptr, nullptr);
    //If first node, set to treeRoot
    if(treeRoot == nullptr)
        treeRoot = temp;
    else
        //Call recuse insert
        insert(temp, treeRoot);
}

/*!
 * \brief Finds the most frequent node
 * \return The Word that is the most frequent
 */
std::vector<Word> AVLTree::mostFreq()
{
    //Create temp AVLTreeNode with default values
    AVLTreeNode* temp = new AVLTreeNode();
    //Find the fifty most frequent words
    for(int i = 0; i < 50; i++)
    {
        //Set mostFrequent to temp and find next mostFrequent
        mostFrequent = temp;
        mostFreq(treeRoot);
        //Add that word to the vector
        topFifty.push_back(mostFrequent->getIndex());
    }
    //Delete temp and return topFifty
    delete temp;
    return topFifty;
}

/*!
 * \brief Checks it the tree contains a word
 * \param index The Word to be searched for
 * \return True if the word is found
 */
bool AVLTree::contains(Word& index)
{
    return contains(index, treeRoot);
}

/*!
 * \brief Clears the tree of all dynamic nodes
 */
void AVLTree::clear()
{
    if(treeRoot!=nullptr)
        delete treeRoot;
}

/*!
 * \brief In Order Transversal
 * \return In Order Transversal
 */
std::string AVLTree::inOrder()
{
    return inOrder(treeRoot);
}

/*!
 * \brief Pre Order Transversal
 * \return Pre Order Transversal
 */
std::string AVLTree::preOrder()
{
    return preOrder(treeRoot);
}

/*!
 * \brief Post Order Transversal
 * \return Post Order Transversal
 */
std::string AVLTree::postOrder()
{
    return postOrder(treeRoot);
}

/*!
 * \brief Retrieve the AVLTree Data form the file and structures is appropriately
 */
void AVLTree::retrieveStructureFromFile()
{
    //Creat ifstream asociated with "AVLTreStore.dat"
    std::ifstream in("AVLTreeStore.dat");
    //While in is not at the end of file
    while(!in.eof())
    {
        std::string word;
        int frequency;
        //Get the word are frequency
        in >> word;
        in >> frequency;
        //Ignore ':'
        in.ignore();
        //If word is the "END" break
        if(word.compare("END") == 0)
        {
            break;
        }
        //Create new AVLTreeNode
        AVLTreeNode* adding = new AVLTreeNode;
        //Add the Word to the AVLTreeNode
        adding->setIndex(Word(word,frequency));

        //Get PageID
        int pageID = 0;
        in >> pageID;
        //Stop case is -1 but if no int is nex pageID = 0
        // This catches both conditions.
        while(pageID > 0)
        {
            //Add pageID to the vector
            adding->addPage(pageID);
            //Get next pageID
            in >> pageID;
        }
        //Insert full AVLTreeNode to the tree
        insert(adding,treeRoot);
    }
}

/*!
 * \brief Stores the AVLTree to file: "AVLTreeStore.dat"
 */
void AVLTree::storeStructureToFile()
{
    //Creates the ofstream assocated with "AVLTreeStore.dat"
    std::ofstream out("AVLTreeStore.dat");
    //Prints the recusive store to file method to the file
    out << storeStructureToFile(treeRoot);
    //Addes stop case
    out << "END";
    //Closes the ofstream object
    out.close();
}
