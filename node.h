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

#ifndef NODE_H
#define NODE_H

#include "marble.h"

class Path;

class Node
{
private :
    int id;                             // id of this Node,
    Marble* marble;                     // Marble contained in this Node, NULL if none
    bool special;                       // true if "special" (on border)
    bool deadMarble;                    // not on board, Nodes for dead Marbles
    Path** paths;                       // the different Paths that contains this Node
    int currentNbPaths;                 // number of Path that contains this Node

public:
    Node();
    Node(int , Marble* , bool , bool);
    ~Node();
    bool isSpecial();
    int getId();
    Marble* getMarble();
    void setMarble(Marble*);
    Path** getPath();
    void setPath(Path** p);
    void addPath(Path* p);
    int nbPathsOfNode();
};

#endif // NODE_H
