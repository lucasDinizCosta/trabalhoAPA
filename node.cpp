#include "libs/node.h"
#include <iostream>
#include <string>
#include <sstream>

using namespace std;


Node::Node(int st, int e, bool _isRoot)
{   
    isRoot = _isRoot;
    level = 0;
    start = st;
    end = e;
    left = NULL;
    right = NULL;
    father = NULL;
    isLeaf = true;
    
}

Node::Node(int st, int e, Node* _father)
{   
    isRoot = false;
    father = _father;
    level = father->getLevel() + 1;
    start = st;
    end = e;
    left = NULL;
    right = NULL;
    
    isLeaf = true;
    
}

Node::Node()
{
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

Node* Node::getFather()
{
    return father;
}

int Node::getStart()
{
    return start;
}

int Node::getEnd()
{
    return end;
}

int Node::getLevel()
{
    return level;
}

bool Node::getIsLeaf()
{
    return isLeaf;
}

bool Node::getIsRoot()
{
    return isRoot;
}

void Node::setLeft(Node *l)
{
    left = l;
}

void Node::setRight(Node *r)
{
    right = r;
}

void Node::setFather(Node *r)
{
    father = r;
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

void Node::setIsRoot(bool il)
{
    isLeaf = il;
}

void Node::setLevel(int lv)
{
    level = lv;
}