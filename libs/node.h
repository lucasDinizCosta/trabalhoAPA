#ifndef NODE_H_INCLUDED
#define NODE_H_INCLUDED

class Node {

private:
    int start;
    int end;
    Node *left;
    Node *right;
    Node *father;
    bool isLeaf;
    bool isRoot;
    int level;

public:
    Node(int, int, bool);

    Node(int, int, Node*);

    Node();

    ~Node();

    Node *getLeft();

    Node *getRight();

    Node *getFather();

    int getStart();

    int getEnd();

    int getLevel();

    bool getIsLeaf();

    bool getIsRoot();

    void setLeft(Node *);

    void setRight(Node *);

    void setFather(Node *);

    void setStart(int);

    void setEnd(int);

    void setLevel(int);

    void setIsLeaf(bool);

    void setIsRoot(bool);
};

#endif //NODE_H_INCLUDED