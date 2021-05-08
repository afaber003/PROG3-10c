#ifndef NODE_H
#define NODE_H

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

        //Mutators
        void setData(string);
        void setRightChild(Node*);
        void setLeftChild(Node*);
        void setParent(Node*);

    private:
        string data;
        Node* parent;
        Node* leftChild;
        Node* rightChild;

};

#endif