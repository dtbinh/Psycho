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

#ifndef MARBLE_H
#define MARBLE_H

#include "player.h"
#include <string>

using namespace std;

#define PSYCHOPATH 0
#define INFORMER 1
#define DOCTOR 2
#define PSYCHOLOGIST 3

#define NB_CROSSING_PATHS 3

class Path;

class Marble
{
public:
    Marble();
    Marble(int nodeId, int type);
    ~Marble();

    void computeAccessibleNodes();
    void setMyNode(int nodeId);
    void setOwner(Player*);
    void displayAccessibleNodes();

    int* getAccessibleNodes();
    int getMyNode();
    Player* getOwner();
    static string getNameFromType(int t);

    void kill();    

    bool isCatch();

    int getType();
    int getNbComputedNodes();
    bool isDead(); // check if node > 162 (dead)

private:
    void computeAccessibleNodesForPath(Path*, int marbleId);    // Not used anymore
    int type;                                                   // PSYCHOPATH, INFORMER, DOCTOR or PSYCHOLOGIST
    int* accessibleNodes;                                       // an array containning the ids of the Nodes toward which this Marble can move
    int nbComputedNodes;                                        // the number of these Nodes
    bool hadPsychologist;                                       // Not used anymore
    bool stuck;                                                 // Not used anymore
    int myNode;                                                 // the id that currently contains this Marble
    Player* owner;                                              // the owner of this Marble
};

#endif // MARBLE_H
