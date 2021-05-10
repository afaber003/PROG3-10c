#include "Node.h"

using namespace std;

Node::Node(){
    rightChild = leftChild = parent = nullptr;
    data = "";
    count = 1;
}
Node::Node(string newdata){
    this->data = newdata;
    rightChild = leftChild = parent = nullptr;
    count = 1;
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
    newleft->parent = this;
}

void Node::setRightChild(Node* newright){
    this->rightChild = newright;
    newright->parent = this;
}

bool Node::hasChild(){
    if (rightChild != nullptr or leftChild != nullptr){
        return true;
    }
    return false;
}

int Node::getCount(){
    return count;
}

void Node::increaseCount(){
    count++;
}

bool Node::leftChildExists()
{
  if (leftChild != nullptr)
  {
    return true;
  }

  return false;
}

bool Node::rightChildExists()
{
  if (rightChild != nullptr)
  {
    return true;
  }

  return false;
}

