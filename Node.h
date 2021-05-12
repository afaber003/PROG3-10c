#ifndef NODE_H
#define NODE_H
#include <string>

using namespace std;

class Node {
   public:
    // Constructors
    Node();
    Node(string);

    //Accessors
    string getData();
    Node* getLeftChild();
    Node* getRightChild();
    Node* getParent();
    bool hasChild();
    bool leftChildExists();
    bool rightChildExists();
    int getCount();
    Node* findNode(const string&);

    //Mutators
    void setData(string);
    void setRightChild(Node*);
    void setLeftChild(Node*);
    void setParent(Node*);
    void setCount(int);
    void increaseCount();
    void decreaseCount();

   private:
    string data;
    Node* parent;
    Node* leftChild;
    Node* rightChild;
    int count;
};

#endif