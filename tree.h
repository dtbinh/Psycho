/**
    Psychopath - Board Game

    Copyright (C) <2015>  <Olivier Perriquet>

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.

*/

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

    char* getDispositionFromValue(int value);
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
    void displayMarbles();

    void createNextSons(int _nbSons);
    void addSon(pTree son);
    void addSon(pTree son, int);

    void deleteAllSons();

    int getMaxValue();

    int getMinValue();

    void setMarblePositionsWithDisposition(Marble ** disposition, int sizeOfDisposition);

    void pruneTree(int sonToPrune);

    pTree father;
    MyVectorOfTree* sons;

private:
    int value;      // TODO the value computed by the evaluation algorithm,
    int level;      // The depth of the this Tree ( root at 0)
    int nbSons;     // The number of sons of this Tree, used to compute arity and mean arity

    Move* fatherMove;                       // Not used anymore
    char marblesPosition[NB_TOTAL_MARBLE];  // Copy of the board, represented by the Marbles positions

    // each char is the id of the node containing the marble


    void computeLevel();

    void initSons(int _nbSons);
    void deleteSons();
};

#endif // TREE_H
