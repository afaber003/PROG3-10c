#include "BSTree.h"

#include <iostream>
using namespace std;

BSTree::BSTree() {
    root = nullptr;
}

void BSTree::insert(const string& newdata) {
    Node* newnode = new Node(newdata);
    if (root == nullptr) {  // case for empty Tree
        root = newnode;
        return;
    }
    Node* curr = root;
start:
    if (newdata == curr->getData()) {  // if data is identical
        curr->increaseCount();
        delete newnode;
        return;
    }
    // case for if newdata is larger than curr
    if (newdata > curr->getData()) {
        if (curr->getRightChild() != nullptr) {  //if its not the bottom of the tree yet
            curr = curr->getRightChild();
            goto start;
        } else {  // if it reached the bottom of the tree
            curr->setRightChild(newnode);
            newnode->setParent(curr);
            return;
        }
    }
    // case for if newdata is smaller than curr
    if (newdata < curr->getData()) {
        if (curr->getLeftChild() != nullptr) {
            curr = curr->getLeftChild();
            goto start;
        } else {
            curr->setLeftChild(newnode);
            newnode->setParent(curr);
            return;
        }
    }
}

void BSTree::remove(const string& key) {
  //Nodes related to Key
  Node* nodeToDelete = findNode(key, root);
  Node* keyParent = nodeToDelete->getParent();

  //Nodes related to Key's Successor
  Node* keySuccessor = findSuccessor(nodeToDelete);
  Node* SuccessorParent = keySuccessor->getParent();
  Node* SuccessorChild = keySuccessor->getRightChild();
  
  //Nodes related to Key's Predecessor
  Node* keyPredecessor = findPredecessor(nodeToDelete);
  Node* PredecessorParent = keySuccessor->getParent();
  Node* PredecessorChild = keySuccessor->getLeftChild();

  //If the node has a count greater than 1
  if (nodeToDelete->getCount() > 1)
  {
    nodeToDelete->decreaseCount();
    return;
  }
  //If root
  if (nodeToDelete == root)
  {
    if (keySuccessor != nullptr)
    {
      if (SuccessorChild == nullptr)
      {
        SuccessorChild = nullptr;
        if (SuccessorParent == root)
        {
          root->getData() = keySuccessor->getData();
          delete keySuccessor;
          return;
          //set the root's right child's left child to be root's left child
          //Dont look at anything beyond this point
        }
        SuccessorParent->setLeftChild(SuccessorChild);
      }
      else
      {
        SuccessorParent->setLeftChild(SuccessorChild);
        SuccessorChild->setParent(SuccessorParent);
      }

      root->getData() = keySuccessor->getData();
      delete keySuccessor;
      
      
      /*
      if(SuccessorParent->getRightChild() == keySuccessor){
        SuccessorParent->setRightChild(SuccessorChild);
      }
      else
      {
        SuccessorParent->setLeftChild(SuccessorChild);
      }
      SuccessorChild->setParent(SuccessorParent);

      root->getData() = keySuccessor->getData();
      
      if (nodeToDelete->rightChildExists())
      {
        nodeToDelete->getRightChild()->setParent(root);
      }
      if (nodeToDelete->leftChildExists())
      {
        nodeToDelete->getLeftChild()->setParent(root);
      }
      */

      //delete keySuccessor;
    }
    else if (keyPredecessor != nullptr)
    {
      if(PredecessorParent->getLeftChild() == keySuccessor){
        SuccessorParent->setLeftChild(SuccessorChild); //todo add setparent
      }
      else
      {
        SuccessorParent->setRightChild(SuccessorChild);
      }
      SuccessorChild->setParent(SuccessorParent);

      root->getData() = keyPredecessor->getData();

      delete keyPredecessor;
    }
  }
  //If key is a leaf node
  else if (nodeToDelete->hasChild() == false && keyParent->getData() > nodeToDelete->getData())
  {
    delete nodeToDelete;
    keyParent->setLeftChild(nullptr);
  }
  else if (nodeToDelete->hasChild() == false && keyParent->getData() < nodeToDelete->getData())
  {
    delete nodeToDelete;
    keyParent->setRightChild(nullptr);
  }

  //If Successor Exists
  //if (keySuccessor != nullptr && )

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
    if (root == nullptr) {
        return "";
    }
    while (curr->rightChildExists() == true) {
        curr = curr->getRightChild();
    }
    largestString = curr->getData();
    if (root == nullptr) {
        return "";
    }

    return largestString;

}

string BSTree::smallest() const {
    Node* curr = root;
    string smallestString = "";

    if (root == nullptr) {
        return "";
    }
    while (curr->leftChildExists() == true) {
       curr = curr->getLeftChild();
    }
    smallestString = curr->getData();
    if (root == nullptr) {
        return "";
    }
    return smallestString;
}

int BSTree::height(const string& startString) const {
    if (!search(startString)) {  // case for string doesnt exist
        return -1;
    }
    Node* curr = findNode(startString, root);
    int ans = findHeight(curr);  //calls recursive function
    return ans;
}

//random helper function that I just didnt want to code into the actual parent function
//the only time it is used is right below this function
int larger(int one, int two) {
    if (one < two) {
        return two;
    }
    return one;
}

int BSTree::findHeight(Node* start) const {
    if (start == nullptr) {
        return 0;
    }
    if (start->hasChild() == false) {
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

Node* BSTree::findSuccessor(Node* startNode)
{
  Node* currNode = startNode->getRightChild();
  while (currNode->getLeftChild() != nullptr)
  {
    currNode = currNode->getLeftChild();
  }

  return currNode;
}

Node* BSTree::findPredecessor(Node * startNode)
{
  Node* currNode = startNode->getLeftChild();
  while (currNode->getRightChild() != nullptr)
  {
    currNode = currNode->getRightChild();
  }

  return currNode;
}