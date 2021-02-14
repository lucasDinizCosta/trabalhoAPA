#include "node.h"
#include <iostream>
#include <string>
#include <sstream>

using namespace std;

Node::Node(int st, int e)
{
    start = st;
    end = e;
    left = NULL;
    right = NULL;
    isLeaf = true;
}

Node::Node()
{
    start = -1;
    end = -1;
    left = NULL;
    right = NULL;
    isLeaf = true;
}

Node::~Node(){};

Node* Node::getLeft()
{
    return left;
}

Node* Node::getRight()
{
    return right;
}

int Node::getStart()
{
    return start;
}

int Node::getEnd()
{
    return end;
}

bool Node::getIsLeaf()
{
    return isLeaf;
}

void Node::setLeft(Node *l)
{
    left = l;
}

void Node::setRight(Node *r)
{
    right = r;
}

void Node::setStart(int s)
{
    start = s;
}

void Node::setEnd(int e)
{
    end = e;
}

void Node::setIsLeaf(bool il)
{
    isLeaf = il;
}
