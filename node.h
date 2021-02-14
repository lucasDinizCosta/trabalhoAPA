#ifndef NODE_H_INCLUDED
#define NODE_H_INCLUDED

class Node {

private:
    int start;
    int end;
    Node *left;
    Node *right;
    bool isLeaf;

public:
    Node(int, int);

    Node();

    ~Node();

    Node *getLeft();

    Node *getRight();

    int getStart();

    int getEnd();

    bool getIsLeaf();

    void setLeft(Node *);

    void setRight(Node *);

    void setStart(int);

    void setEnd(int);

    void setIsLeaf(bool);
};

#endif //NODE_H_INCLUDED