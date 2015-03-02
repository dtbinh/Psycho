#ifndef MYVECTOROFTREE_H
#define MYVECTOROFTREE_H

#include "tree.h"

typedef struct node{
    Tree* data;
    node* next;
    node* previous;
    int index;
}node;

class MyVectorOfTree
{
public:
    MyVectorOfTree();
    MyVectorOfTree(Tree* t);
    ~MyVectorOfTree();

    bool initTree();
    Tree* getTree(int index);
    Tree* removeTree(Tree*);
    Tree* removeTree(int);
    bool addTree(Tree*);
    bool addTree(Tree*, int);

private:
    node* start;
};

#endif // MYVECTOROFTREE_H
