#include "BSTree.h"

#include <iostream>
using namespace std;

BSTree::BSTree() {
    root = nullptr;
}

void BSTree::insert(const string& newdata) {
    Node* newnode = new Node(newdata);
    if (root == nullptr) { // case for empty Tree
        root = newnode;
        return;
    }  
    Node* curr = root;
start:
    if (newdata == curr->getData()){ // if data is identical
        curr->increaseCount();
        return;
    }
    // case for if newdata is larger than curr
    if (newdata > curr->getData()){
        if (curr->getRightChild() != nullptr){ //if its not the bottom of the tree yet
            curr = curr->getRightChild();
            goto start;
        }
        else {  // if it reached the bottom of the tree
            curr->setRightChild(newnode);
            return;
        }
    }
    // case for if newdata is smaller than curr
    if (newdata < curr->getData()){
        if (curr->getLeftChild() != nullptr){
            curr = curr->getLeftChild();
            goto start;
        }
        else {
            curr->setLeftChild(newnode);
            return;
        }
    }
}

void BSTree::remove(const string& key) {
}

//dont question this one. its the worst function ive ever written i think
bool BSTree::search(const string& lookforthis) const {
    Node* curr = root;
    while (lookforthis != curr->getData()) {
        if (curr->hasChild() == false) {
            return false;
        }
        if (lookforthis > curr->getData()) {
            curr = curr->getRightChild();
        } else {
            curr = curr->getLeftChild();
        }
        if (curr == nullptr) {
            return false;
        }
    }
    return true;
}

string BSTree::largest() const {
    Node* curr = root;
    string largestString = "";
    while (curr->rightChildExists() == true) {
        curr = curr->getRightChild();
    }
    largestString = curr->getData();
    if (curr == nullptr) {
        largestString = "";
    }

    return largestString;
}

string BSTree::smallest() const {
    Node* curr = root;
    string smallestString = "";

    while (curr->leftChildExists() == true) {
        smallestString = curr->getLeftChild()->getData();
    }
    smallestString = curr->getData();
    if (curr == nullptr) {
        smallestString = "";
    }
    return smallestString;
}

int BSTree::height(const string& startString) const {
    if (!search(startString)){return -1;} // case for string doesnt exist
    Node* curr = findNode(startString, root);
    int ans = findHeight(curr); //calls recursive function
    return ans;
}

//random helper function that I just didnt want to code into the actual parent function
//the only time it is used is right below this function
int larger(int one, int two){
    if (one < two){return two;}
    return one;
}

int BSTree::findHeight(Node* start) const {
    if (start == nullptr){return 0;}
    if (start->hasChild() == false){
        return 0;
    } else {
        return 1 + larger(findHeight(start->getLeftChild()), findHeight(start->getRightChild()));
    }
}

void BSTree::inOrder() const {
    inOrder(root);
}

void BSTree::inOrder(Node* start) const {
    if (start == nullptr) {
        return;
    }
    inOrder(start->getLeftChild());
    cout << start->getData() << '(' << start->getCount() << ')' << endl;
    inOrder(start->getRightChild());
}

void BSTree::postOrder() const {
    postOrder(root);
}

void BSTree::postOrder(Node* start) const {
    if (start == nullptr) {
        return;
    }
    postOrder(start->getLeftChild());
    postOrder(start->getRightChild());
    cout << start->getData() << '(' << start->getCount() << ')' << endl;
}

void BSTree::preOrder() const {
    preOrder(root);
}

void BSTree::preOrder(Node* start) const {
    if (start == nullptr) {
        return;
    }
    cout << start->getData() << '(' << start->getCount() << ')' << endl;
    preOrder(start->getLeftChild());
    preOrder(start->getRightChild());
}

BSTree::~BSTree() {
    deletetraverse(root);
}

void BSTree::deletetraverse(Node* start) {
    if (start == nullptr) {
        return;
    }
    deletetraverse(start->getLeftChild());
    deletetraverse(start->getRightChild());
    delete start;
}

Node* BSTree::findNode(string nodeData, Node* startNode) const {
    Node* currNode = startNode;

    while (currNode != nullptr) {
        if (currNode->getData() == nodeData) {
            return currNode;
        } else if (nodeData < currNode->getData()) {
            currNode = currNode->getLeftChild();
        } else {
            currNode = currNode->getRightChild();
        }
    }

    return currNode;
}
