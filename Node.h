#ifndef NODE_H
#define NODE_H

#include <string>

class Node {
private:
    std::string name;
    int empID;
    Node* left;
    Node* right;

public:
    Node(int newID, std::string newName) : empID{newID}, name{newName}, left{nullptr}, right{nullptr} {}
    ~Node(){
        left = nullptr;
        right = nullptr;
    }
    
    // Accessors
    std::string getName() const;
    int getID() const;
    Node* getLeft() const;
    Node* getRight() const;
    
    //Mutators
    void setName(std::string newName);
    void setID(int newID);
    void setLeft(Node* child);
    void setRight(Node* child);
};


#endif // NODE_H