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

#ifndef MINIMAX_H
#define MINIMAX_H

#include<ctime>
#include <iostream>

class Player;
class MyVectorOfTree;

class Tree;
class Minimax
{
public:
    Minimax();
    ~Minimax();

    int eval(char* marblePosition, Player* player);
    char *getMoveFrom(Tree* root);

    Tree* fillDecisionTree(Tree*, int);
    void treeStatus(int level, int value, int maxValue, int bestTreeIndex);
    Tree* bestTree(Player *player, MyVectorOfTree* list, time_t timeout);
    MyVectorOfTree* initParcours(Player *player);

private:
    int bestValue;
    Tree* bestSon;

};

#endif // MINIMAX_H
