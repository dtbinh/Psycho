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

#ifndef PLAYER_H
#define PLAYER_H

#define PLAYERONE   1
#define PLAYERTWO   2
#define NBMARBLES   13

#include <string>

using namespace std;

class Marble;
class Node;
class Tree;

class Player
{

private:
    Marble** disposition;
    int nbMarbles;
    int whoAmI;
    bool isHuman;
    Player * ennemy;
public:
    Player(int, bool);
    ~Player();
    void displayMarbles(); // show marbles in console
    string getStringMarblesForFile();
    bool move(Node * src, Node * dst); // move a marble. Return false if impossible, true if move done.    
    void computePossibilities();

    void askRespawn(Node * psychologistDeathNode);
    bool respawnUnit(Node * psychologistDeathNode, int marbleWanted);

    Player * getEnnemy();
    void setEnnemy(Player * p);

    Tree * fillDecisionTree(Tree * tree, int depth);

    int getWhoAmI();

    // Check if psychopath is dead
    bool hasLost();

    // if human ask to play, else AI plays (doing a move)
    void play();
};

#endif // PLAYER_H
