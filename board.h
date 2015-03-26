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

#ifndef BOARDS_H
#define BOARDS_H

#include <string>
#include "path.h"
#include "node.h"

#define BOARDNODES 162
#define BOARDSIZE 190
#define MAXPATHSIZE 50
#define NBPATHS 27

class Marble;
class Player;
using namespace std;

const string DATA_PATH = "./data/";

class Board
{

private:
    //Board& operator=(const Board&){}
    //Board (const Board&){}

    static Board m_instance; // There is only one instance of the class Board, accessible with Instance()
    Board();
    ~Board();

    Node** nodes; // nodes
    Path** paths; // paths
    int nbPaths; // number of paths (27)
    int firstFreeDeadMarble;

public:
    static Board& Instance();
    int size();
    Node* getNode(int i);

    bool loadPaths(string file);
    Path* getPath(int i);
    Path** getPaths();
    int getNbPaths();

    bool checkDeaths(Player * me, Node * dst); // check suicides and kills and do respawns and kills

    bool killMarble(Marble * marbleToKill);

    void forceMove(Node * src, Node * dst); // move a marble without checking constraints

    void showPaths();
};

#endif // BOARDS_H
