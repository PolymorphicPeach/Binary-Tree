#include "BinaryTree.h"
#include <iostream>

using std::cout;
using std::endl;

// Method: addNode
//
// Parameters: int, std::string
//
// Returns: bool
//
// Purpose: 
//   Public method for adding a node - returns true if there is no duplicate emplyeeID (integer) value,
// returns false if a duplicate employeeID value is found and no node is added to the tree. 
//   The arguments are used in the Node constructor, if a duplicate employee ID is found, then the
// newly created node is deleted. If the new value is unique, addNodeRecursive() is called to add
// the node to the tree.

bool BinaryTree::addNode(int empID, std::string name){
    
    bool successFlag {false};
    Node* newNodePtr = new Node(empID, name);
    Node* traversalPtr = rootPtr;
    
    // If the binary tree is empty, set the new node as the root of the tree
    if(!rootPtr){
        rootPtr = newNodePtr;
        successFlag = true;
    }
    // If this search returns true, then the employee ID is already in-use.
    //  The new node is deleted (the pointer is set to nullptr at the end of
    //   this method).
    else if(searchTree(newNodePtr->getID())){
        delete newNodePtr;
        successFlag = false;
    }
    else{
        addNodeRecursive(traversalPtr, newNodePtr);
        successFlag = true;
    }
    
    traversalPtr = nullptr;
    newNodePtr = nullptr;
    return successFlag;
}

// Method: addNodeRecursive
//
// Parameters: Node*, Node*
//
// Returns: void
//
// Purpose: 
//   Private helper method called by the addNode() method - the arguments will be passed in by
// addNode(). addNode() also traverses the tree to check for a duplicate value before calling
// this method. newNodePtr remains separate from the tree until traversalPtr finds a place for it.

void BinaryTree::addNodeRecursive(Node* traversalPtr, Node* newNodePtr){
    // Traverse left if the new node is less than where the traversal node is and
    // there are still values to the left
    if((newNodePtr->getID() < traversalPtr->getID()) && (traversalPtr->getLeft())){
        traversalPtr = traversalPtr->getLeft();
        addNodeRecursive(traversalPtr, newNodePtr);
    }
    // Traverse right if the new node is greater than where the traversal node is and
    // there are still values to the right
    else if(newNodePtr->getID() > traversalPtr->getID() && (traversalPtr->getRight())){
        traversalPtr = traversalPtr->getRight();
        addNodeRecursive(traversalPtr, newNodePtr);
    }
    // traversalPtr has arrived at a node with no left child and the new node that needs a home
    // has a value less than the node traversalPtr is on.
    else if((newNodePtr->getID() < traversalPtr->getID()) && !traversalPtr->getLeft()){
        traversalPtr->setLeft(newNodePtr);
    }
    // traversalPtr has arrived at a node with no right child and the new node that needs a home
    // has a value greater than the node traversalPtr is on.
    else if((newNodePtr->getID() > traversalPtr->getID()) && !traversalPtr->getRight()){
        traversalPtr->setRight(newNodePtr);
    }
    
    newNodePtr = nullptr;
    traversalPtr = nullptr;
}

// Method: searchTree
//
// Parameters: int
//
// Returns: bool
//
// Purpose: 
//   traversalPtr starts on root and traverses the tree until a matching value is found.
// if a matching value is never found, traversalPtr will simply "fall off" the tree and "enter"
// a nullptr without ever setting foundID to true. Returns true if a matching ID is found.

bool BinaryTree::searchTree(int searchID){
    bool foundID {false};
    Node* traversalPtr = rootPtr;
    
    // Loops until traversalPtr becomes null by making it to the end of the tree
    //  or finding the employee ID
    while(traversalPtr && !foundID){
        if(traversalPtr->getID() == searchID){
            foundID = true;
            cout << "ID " << searchID << " belongs to " << traversalPtr->getName() << endl;
            // employee ID found - the while-loop will not loop again
        }
        // go left
        if(traversalPtr->getID() > searchID){
            traversalPtr = traversalPtr->getLeft();
        }
        // go right
        else if(traversalPtr->getID() < searchID){
            traversalPtr = traversalPtr->getRight();
        }
    }
    traversalPtr = nullptr;
    
    return foundID;
}


// Method: displayTree
//
// Parameters: N/A
//
// Returns: void
//
// Purpose: 
//   Public method that displays the tree by calling a private inorder
// traversal method.

void BinaryTree::displayTree(){
    if(rootPtr){
        cout << endl << "===================================" << endl
             << "Employee ID | Name" << endl
             << "-----------------------------------" << endl;
        Node* traversalPtr = rootPtr;
        
        inorderTraversal(traversalPtr);
        
        traversalPtr = nullptr;
    }
    else{
        cout << "====================================" << endl
             << "|         The tree is empty        |" << endl
             << "====================================" << endl;
    }
    
    
}

// Method: inorderTraversal
//
// Parameters: Node*
//
// Returns: void
//
// Purpose: 
//   Called by the displayTree() public method. Uses recursion to print each node
// in the tree in order.

void BinaryTree::inorderTraversal(Node* traversalPtr){
    // If traversalPtr is null, "go back"
    if(!traversalPtr){
        return;
    }
    
    inorderTraversal(traversalPtr->getLeft());

    // print when traversalPtr cannot go any more left than this point
    cout << traversalPtr->getID() << "        | " << traversalPtr->getName() << endl;
    
    inorderTraversal(traversalPtr->getRight());

    traversalPtr = nullptr;
}


// Method: deleteNode
//
// Parameters: integer
//
// Returns: bool
//
// Purpose: 
//   Deletes a node with the employee ID entered by the user. I tried not using helper methods for this
// method, but it quickly grew out-of-hand. So, this method can call three different helper methods 
// depending on how many children the node-to-delete has (deleteNodeNoChildren(), deleteNodeOneChild(),
// and deleteNodeTwoChildren()). If the node-to-delete is root and has no children or one child, those 
// cases are handled in this method. Returns true if a node was deleted and false if there was no node
// with the entered deleteID.

bool BinaryTree::deleteNode(int deleteID){
    bool matchFound {false};
    // deleterPtr will be used to mark which node should be deleted
    Node* deleterPtr = rootPtr;
    
    // ----- Part 1: Find the Node ------
    while(deleterPtr && !matchFound){
        if(deleterPtr->getID() == deleteID){
            matchFound = true;
        }
        // go left
        else if(deleterPtr->getID() > deleteID){
            deleterPtr = deleterPtr->getLeft();
        }
        // go right
        else{
            deleterPtr = deleterPtr->getRight();
        }
    }
    
    // ----- Part 2: Delete the Node ------
    if(matchFound){
        // Case 1: Node has no children
        if(!deleterPtr->getLeft() && !deleterPtr->getRight()){
            // Case 1.1: Node is childless and root
            if(deleterPtr == rootPtr){
                rootPtr = nullptr;
                delete deleterPtr;
            }
            else{
                deleteNodeNoChildren(deleterPtr);
            }
        }
        // Case 2: Node has one child
        else if((deleterPtr->getLeft() && !deleterPtr->getRight()) || (!deleterPtr->getLeft() && deleterPtr->getRight())){
            // Case 2.1: Node has one child and is root
            // (Set root to the child node then delete the old root)
            if(deleterPtr == rootPtr){
                if(deleterPtr->getLeft()){
                    rootPtr = deleterPtr->getLeft();
                }
                else if(deleterPtr->getRight()){
                    rootPtr = deleterPtr->getRight();
                }
                delete deleterPtr;
            }
            // Case 2.2: Node has one child and is NOT root
            else{
                deleteNodeOneChild(deleterPtr);
            }
        }
        // Case 3: Node has two children
        // (Same for if the root is to be deleted)
        else if((deleterPtr->getLeft()) && (deleterPtr->getRight())){
            deleteNodeTwoChildren(deleterPtr);
        }
        
    }
    deleterPtr = nullptr;
    return matchFound;
}


// Method: deleteNodeNoChildren
//
// Parameters: Node* (deleterPtr is passed in from the deleteNode() method)
//
// Returns: void
//
// Purpose: 
//   traversalPtr is set to root, then moves down towards deleterPtr until it is deleterPtr's
// parent node. traversalPtr sets its connection to deleterPtr as nullptr, then deleterPtr
// deletes its node.

void BinaryTree::deleteNodeNoChildren(Node* deleterPtr){
    Node* traversalPtr = rootPtr;
    
    // Moving traversalPtr towards deleterPtr until deleterPtr
    //  is traversalPtr's child
    while((traversalPtr->getLeft() != deleterPtr) && (traversalPtr->getRight() != deleterPtr)){
        if(traversalPtr->getID() > deleterPtr->getID()){
            traversalPtr = traversalPtr->getLeft();
        }
        else if(traversalPtr->getID() < deleterPtr->getID()){
            traversalPtr = traversalPtr->getRight();
        }
    }
    if(traversalPtr->getLeft() == deleterPtr){
        traversalPtr->setLeft(nullptr);
    }
    else{
        traversalPtr->setRight(nullptr);
    }
    delete deleterPtr;
    deleterPtr = nullptr;
    traversalPtr = nullptr;
}

// Method: deleteNodeOneChild
//
// Parameters: Node* (deleterPtr is passed in from the deleteNode() method)
//
// Returns: void
//
// Purpose: 
//   traversalPtr is set to root, then moves down towards deleterPtr until it is deleterPtr's
// parent node. traversalPtr changes its link (either left or right) to deleterPtr to deleterPtr's
// child. deleterPtr then deletes its node.

void BinaryTree::deleteNodeOneChild(Node* deleterPtr){
    Node* traversalPtr = rootPtr;
    
    // Moving traversalPtr towards deleterPtr until deleterPtr
    //  is traversalPtr's child
    while((traversalPtr->getLeft() != deleterPtr) && (traversalPtr->getRight() != deleterPtr)){
        if(traversalPtr->getID() > deleterPtr->getID()){
            traversalPtr = traversalPtr->getLeft();
        }
        else if(traversalPtr->getID() < deleterPtr->getID()){
            traversalPtr = traversalPtr->getRight();
        }
    }
    
    // traversalPtr should now be deleterPtr's parent
    // traversalPtr must be connected to deleterPtr's child,
    // then deleterPtr can delete the data it is pointing to
    
    // If deleterPtr is the left child of traversalPtr
    if(traversalPtr->getLeft() == deleterPtr){
        if(deleterPtr->getLeft()){
            traversalPtr->setLeft(deleterPtr->getLeft());
        }
        else if(deleterPtr->getRight()){
            traversalPtr->setLeft(deleterPtr->getRight());
        }
        delete deleterPtr;
    }
    
    //If deleterPtr is the right child of traversalPtr
    else if(traversalPtr->getRight() == deleterPtr){
        if(deleterPtr->getLeft()){
            traversalPtr->setRight(deleterPtr->getLeft());
        }
        else if(deleterPtr->getRight()){
            traversalPtr->setRight(deleterPtr->getRight());
        }
        delete deleterPtr;
    } 
    
    traversalPtr = nullptr;
    deleterPtr = nullptr;
}


// Method: deleteNodeTwoChildren
//
// Parameters: Node* (deleterPtr is passed in from the deleteNode() method)
//
// Returns: void
//
// Purpose: 
//   traversalPtr is set to the left child of deleterPtr, instead of root in this method.
// traversalPtr then attempts to travel right until it is the PARENT of the rightmost node.
// deleterPtr sets its data to that of traversalPtr's right child, then deleterPtr moves
// from this now edited node to be traversalPtr's right child. Then, deleterPtr deletes the node
// and traversalPtr sets its right child to nullptr.
//   If traversalPtr has no right children, deleterPtr copies traversalPtr's data. Then
// if traversalPtr has left children (it is known to not have right children at this point), 
// deleterPtr sets its left child to traversalPtr's left child and traversalPtr deletes its
// now disconnected node.
//   If traversalPtr starts as a leaf, deleterPtr copies the data of traversalPtr. Then 
// deleterPtr sets its left child to nullptr and traversalPtr deletes the now disconnected node.

void BinaryTree::deleteNodeTwoChildren(Node* deleterPtr){
    // Traversal will start as the left child of deleterPtr this time, instead of on root
    Node* traversalPtr = deleterPtr->getLeft();
    
    // The node to be deleted will be replaced by the highest
    // value node value in its left subtree
    while(traversalPtr->getRight()->getRight()){
        traversalPtr = traversalPtr->getRight();
    }
    
    // traversalPtr is now one right movement from being on the highest value in
    // the subtree
    if(traversalPtr->getRight()){
        deleterPtr->setID(traversalPtr->getRight()->getID());
        deleterPtr->setName(traversalPtr->getRight()->getName());
        // Set deleterPtr to the right child of traversalPtr
        deleterPtr = traversalPtr->getRight();
        delete deleterPtr;
    
        // The traversal method kept entering deleted nodes,
        // this must be set to nullptr to prevent that.
        traversalPtr->setRight(nullptr);
    }
    
    // deleterPtr's left child had no right children
    else{
        deleterPtr->setID(traversalPtr->getID());
        deleterPtr->setName(traversalPtr->getName());
        
        // deleterPtr's left child has left children
        // (it did not have a right child or traversalPtr would have gone there)
        if(traversalPtr->getLeft()){
            deleterPtr->setLeft(traversalPtr->getLeft());
            delete traversalPtr;
        }
        else{
            deleterPtr->setLeft(nullptr);
            delete traversalPtr;
        }
    }
    
    traversalPtr = nullptr;
    deleterPtr = nullptr;
}


// Method: clearTree
//
// Parameters: N/A
//
// Returns: void
//
// Purpose: 
//   Public method that calls the private helper method, postorderDeletion. Once control comes
// back to clearTree(), it sets rootPtr to nullptr. The deleteNode() method does consider a case
// where there is only a root node and deleting it sets root to nullptr, but the change is here too
// just in case.

void BinaryTree::clearTree(){
    Node* traversalPtr = rootPtr;
    postorderDeletion(traversalPtr);
    traversalPtr = nullptr;
    rootPtr = nullptr;
}

// Method: postorderDeletion
//
// Parameters: Node*
//
// Returns: void
//
// Purpose: 
//   clearTree() passes a traversalPtr into this method, which I realize is weird, but I wasn't sure
// the recursion would work right if declaring a pointer *inside* of the recursive method. On the last visit of
// of a node, that node is deleted.

void BinaryTree::postorderDeletion(Node* traversalPtr){
    // "go back"
    if(!traversalPtr){
        return;
    }
    postorderDeletion(traversalPtr->getLeft());
    postorderDeletion(traversalPtr->getRight());
    
    delete traversalPtr;
}

// Method: ~BinaryTree() (destructor)
//
// Parameters: N/A
//
// Returns: N/A
//
// Purpose: 
//   Calls clearTree() if root is not nullptr. I thought this would be good to include; I'm not sure
// if using the default destructor would actually delete the memory in the tree.

BinaryTree::~BinaryTree(){
    if(rootPtr){
        clearTree();
    }
}