#include "Node.h"

std::string Node::getName() const{
    return name;
}

int Node::getID() const{
    return empID;
}

void Node::setName(std::string newName){
    name = newName;
}

void Node::setID(int newID){
    empID = newID;
}

Node* Node::getLeft() const{
    return left;
}

Node* Node::getRight() const{
    return right;
}

void Node::setLeft(Node* child){
    left = child;
}

void Node::setRight(Node* child){
    right = child;
}