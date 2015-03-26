/**
    Psychopath - Board Game

    Copyleft  (C) <2008>  <Olivier Perriquet> (Game conception)
    Copyright (C) <2015>  <Robache Alexis, Sévin Léo-Paul> (AI conception and implementation>

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
class Tree;
typedef Tree* pTree;

class MyVectorOfTree;

const pTree pT_NULL = 0;

class Tree
{
public:
    Tree();
    ~Tree();
    Tree(pTree father);
    Tree(pTree father, Marble ** dispositionPlayerOne, Marble **dispositionPlayerTwo);

    void setLevel(int _level);
    void setNbSons(int _nbSons);
    void setValue(int value);

    int getLevel();
    int getNbSons();
    int getValue();

    void displayTree();
    void displayTreeNode();
    void displayMarbles();

    void createNextSons(int _nbSons);
    void addSon(pTree son);
    void addSon(pTree son, int);

    void deleteAllSons();

    int getMaxValue();
    int getMinValue();

    int *getMarbleDisposition();
    void pruneTree(int sonToPrune);

    Marble** getDispositionFromMarblePosition();

    pTree father;
    MyVectorOfTree* sons;

private:
    int value;      // TODO the value computed by the evaluation algorithm,
    int level;      // The depth of the this Tree ( root at 0)
    int nbSons;     // The number of sons of this Tree, used to compute arity and mean arity

    int* marblesPosition;  // Copy of the board, represented by the Marbles positions

    // each char is the id of the node containing the marble

    void setMarblePositionsWithDisposition(Marble ** dispositionPlayerOne, Marble **dispositionPlayerTwo);

    void computeLevel();

    void initSons(int _nbSons);
    void deleteSons();
};

#endif // TREE_H
