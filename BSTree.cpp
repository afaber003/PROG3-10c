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
/*
  Five possible situations
  Item not found (Do nothing or throw exception)
  Removing a leaf (easy)
  Removing a node with only one child - right only
  Removing a node with only one child - left only
  Removing a node with two children

*/
void BSTree::remove(const string& key) {
  //Nodes related to Key
  Node* nodeToDelete = findNode(key, root);
  //Node* keyParent = nodeToDelete->getParent();

  //Nodes related to Key's Successor
  //Node* keySuccessor = findSuccessor(nodeToDelete);
  //Node* SuccessorParent = keySuccessor->getParent();
  //Node* SuccessorChild = keySuccessor->getRightChild();
  
  //Nodes related to Key's Predecessor
  //Node* keyPredecessor = findPredecessor(nodeToDelete);
  //Node* PredecessorParent = keySuccessor->getParent();
  //Node* PredecessorChild = keySuccessor->getLeftChild();

  if (search(nodeToDelete->getData()) == false)
  {
    return;
  }
  //For leaf node
  else if (nodeToDelete->hasChild() == false)
  {
    Node* keyParent = nodeToDelete->getParent();

    nodeToDelete->setParent(nullptr);
    delete nodeToDelete;
    //If the deleted leaf node is a right child
    if (keyParent->getRightChild() == nodeToDelete)
    {
      keyParent->setRightChild(nullptr);
   
    }
    //If the deleted leaf node is a left child
    else if (keyParent->getLeftChild() == nodeToDelete)
    {
      keyParent->setLeftChild(nullptr);
    }
    
    return;
  }
  //If the deleted node has children
  else if (nodeToDelete->hasChild())
  {
    //If the deleted node only has a right child
    if (nodeToDelete->rightChildExists() == true && nodeToDelete->leftChildExists() == false)
    {
      Node* keyParent = nodeToDelete->getParent();
      keyParent->setRightChild(nodeToDelete->getRightChild());
      if (nodeToDelete == root)
      {
        
      }
    }
  }

  

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

/*
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

    if (keySuccessor != root)
    {
      if (root->leftChildExists() && root->getRightChild() == keySuccessor)
      {
        keySuccessor->setLeftChild(root->getLeftChild());
        delete root;
        root = keySuccessor;
        return;
      }
      
      else if (root->getLeftChild() == nullptr && root->getRightChild() == keySuccessor)
      {
        cout << "test";
        //keySuccessor->setParent(nullptr);
        //root->setRightChild(nullptr);
        delete root;
        root = keySuccessor;
        //root->setParent(nullptr);
        return;
      }
      
      
      if (root->leftChildExists() && root->getRightChild() != keySuccessor)
      {
        root->setData(keySuccessor->getData());
        keySuccessor->setParent(nullptr);
        if (keySuccessor->rightChildExists())
        {
          keyParent->setLeftChild(keySuccessor->getRightChild());
        }
        keySuccessor->setLeftChild(root->getLeftChild());
        keySuccessor->setRightChild(keyParent);
        delete root;
        root = keySuccessor;
        return;

      }
      
      
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
*/