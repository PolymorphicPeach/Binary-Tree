#ifndef BINARYTREE_H
#define BINARYTREE_H

#include "Node.h"
#include <string>

class BinaryTree {
private:
    Node* rootPtr;
    
    // Private helper methods
    void addNodeRecursive(Node* traversalPtr, Node* newNodePtr);
    void inorderTraversal(Node* traversalPtr);
    void deleteNodeNoChildren(Node* deleterPtr);
    void deleteNodeOneChild(Node* deleterPtr);
    void deleteNodeTwoChildren(Node* deleterPtr);
    void postorderDeletion(Node* traversalPtr);

public:
    BinaryTree() : rootPtr{nullptr} {}
    ~BinaryTree();
    
    bool addNode(int empID, std::string name);
    bool searchTree(int searchID);
    void displayTree();
    bool deleteNode(int deleteID);
    void clearTree();
    
};
#endif // BINARYTREE_H