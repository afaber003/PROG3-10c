#include "BSTree.h"
#include <iostream>
using namespace std;

BSTree::BSTree(){
    root = nullptr;
}

void BSTree::insert(const string& newdata){
    Node* newnode = new Node(newdata);
    if (root == nullptr){root = newnode; return;} // case for empty Tree
    Node* curr = root;
    while (curr->hasChild()){ //this while() only compares to internal nodes
        if (curr->getData() == newnode->getData()){ //case for data being already in tree
            curr->increaseCount();
            delete newnode;
            return;
        }
        else if (curr->getData() > newnode->getData()){ //case for bigger than curr
            curr = curr->getRightChild();
        }
        else if (curr->getData() < newnode->getData()){ //case for smaller than curr
            curr = curr->getLeftChild();
        }
    }
    if (curr->getData() > newnode->getData()){ //this + next 2 else-if statments are actually setting a new leaf with the new node
        curr->setLeftChild(newnode); 
    }
    else if (curr->getData() < newnode->getData()){ 
        curr->setRightChild(newnode);
    }
    else if (curr->getData() == newnode->getData()){
        curr->increaseCount();
        delete newnode;
    }
}

//dont question this one. its the worst function ive ever written i think
bool BSTree::search(const string& lookforthis) const{
    Node* curr = root;
    while (lookforthis != curr->getData()){
        if (curr->hasChild() == false){
            return false;
        }     
        if (lookforthis > curr->getData()){
            curr = curr->getRightChild();
        } else {
            curr = curr->getLeftChild();
        }
        if (curr == nullptr){
            return false;
        }
    }
    return true;
}

void BSTree::inOrder() const{
    inOrder(root);
}

string BSTree::inOrder(Node* start) const{
    if (start == nullptr){return;}
    inOrder(start->getLeftChild());
    cout << start->getData() << '(' << start->getCount() << ')'  << endl;
    inOrder(start->getRightChild());
}

void BSTree::postOrder() const{
    postOrder(root);
}

string BSTree::postOrder(Node* start) const{
    if (start == nullptr){return;}
    postOrder(start->getLeftChild());
    postOrder(start->getRightChild());
    cout << start->getData() << '(' << start->getCount() << ')'  << endl;
}

void BSTree::preOrder() const{
    preOrder(root);
}

string BSTree::preOrder(Node* start) const{
    if (start == nullptr){return;}
    cout << start->getData() << '(' << start->getCount() << ')'  << endl;
    preOrder(start->getLeftChild());
    preOrder(start->getRightChild());
}

BSTree::~BSTree(){
    deletetraverse(root);
}

void BSTree::deletetraverse(Node* start){
    if (start == nullptr){return;}
    deletetraverse(start->getLeftChild());
    deletetraverse(start->getRightChild());
    delete start;
}