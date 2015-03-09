#ifndef TREE_H
#define TREE_H

#include "util.h"
// Class represent a move from the psychoPath

// Not used : copy of current board instead
class Move{
public:
    Move();
    Move(int from, int to);

    Move* getConsequence();
    void setConsequence();

    Move* transposeMove();
private:
    int fromNode;           // index of the node from which the Marble moved
    int toNode;             // index of the node to which the Marble moved
    Move* consequence;      // a move that result of this move : a captured piece
};


class Tree;
class MyVectorOfTree;

typedef Tree* pTree;

const pTree pT_NULL = 0;

class Tree
{
public:
    Tree();
    ~Tree();
    Tree(pTree father);
    Tree(pTree father, Move* fatherMove);
    Tree(pTree father, char* marblesPosition);

    void setLevel(int _level);
    void setNbSons(int _nbSons);

    int getLevel();
    int getNbSons();

    void displayTree();
    void displayTreeNode();

    void createNextSons(int _nbSons);
    void addSon(pTree son);
    void addSon(pTree son, int);

    void deleteAllSons();

    void pruneTree(int sonToPrune);

    pTree father;
    MyVectorOfTree* sons;

private:
    int value;
    int level;      // Used to find if min or max for minmax algorithm
    int nbSons;     // Used to compute arity and mean arity

    Move* fatherMove;
    char marblesPosition[NB_TOTAL_MARBLE];  // Copy of the board represented by the marbles positions

    void computeLevel();

    void initSons(int _nbSons);
    void deleteSons();
};

#endif // TREE_H
