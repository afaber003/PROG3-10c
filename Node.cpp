#include "Node.h"

using namespace std;

Node::Node(){
    rightChild = leftChild = parent = nullptr;
    data = "";
}
Node::Node(string newdata){
    this->data = newdata;
    rightChild = leftChild = parent = nullptr;
}

string Node::getData(){
    return this->data;
}

Node* Node::getParent(){
    return this->parent;
}

Node* Node::getLeftChild(){
    return this->leftChild;
}

Node* Node::getRightChild(){
    return this->rightChild;
}

void Node::setData(string newdata){
    this->data = newdata;
}

void Node::setParent(Node* newparent){
    this->parent = newparent;
}

void Node::setLeftChild(Node* newleft){
    this->leftChild = newleft;
}

void Node::setRightChild(Node* newright){
    this->rightChild = newright;
}


