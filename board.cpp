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

#include "board.h"
#include "util.h"
#include "marble.h"
#include "player.h"


#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <vector>

using namespace std;

Board Board::m_instance=Board();

Board::Board()
{    
    // Paths loading


    nodes = new Node*[BOARDSIZE];

    for(int i = 0 ; i <= BOARDNODES ; i++){
        // special nodes        
        if(i == 0 || i == 155 || i == 8 || i == 93 || i == 101 || i == 147){
            this->nodes[i] = new Node(i, NULL, true, false);
        }
        // others nodes
        else{
            this->nodes[i] = new Node(i, NULL, false, false);
        }
    }

    if(this->loadPaths(DATA_PATH + "paths.txt")){
        cout << "paths loaded" << endl;
    }
    else{
        cout << "fatal error : path of path file not found" << endl;
        exit(EXIT_FAILURE);
    }

    // setPaths for all the nodes
    /*
    for(int i = 0 ; i < this->getNbPaths() ; i++){
        for(int j = 0 ; j < this->getPath(i)->size ; j++){
            this->nodes[this->getPath(i)->nodes[j]]->addPath(this->getPath(i));
        }
    }
    */

    // nodes for dead marbles
    for(int i = BOARDNODES + 1 ; i <= BOARDSIZE - 1 ; i++){
        this->nodes[i] = new Node(i, NULL, false, true);
    }
    this->firstFreeDeadMarble = BOARDNODES + 1;
}

Board::~Board()
{
    free(nodes);
    free(paths);
}

Board& Board::Instance(){
    return m_instance;
}

/**
 * @brief Board::loadPaths
 * @param file the path to the text file containing the paths of the board (paths.txt)
 * @return true if the file is correctly loaded, false otherwise
 */
bool Board::loadPaths(string file){
    ifstream fichier;
    fichier.open(file.c_str(), ios::in); // opening file in read only
    int * nodeList;

    if(fichier) // success
    {
        string line;
        this->nbPaths = NBPATHS;

        this->paths = new Path*[nbPaths];
        nodeList = new int[MAXPATHSIZE];

        cout << nbPaths << " paths found" << endl;

        while(!fichier.eof()){
            nodeList = new int[MAXPATHSIZE];
            getline(fichier, line);
            string delimiter = " : ";
            string pathId = line.substr(0, line.find(delimiter));
            string rest = line.substr(line.find(delimiter)+3, line.length()); // +3 for the 2 spaces and the :
            int nbNodes;

            nbNodes = Util::split(nodeList, rest, ' ');

            this->paths[atoi(pathId.c_str())] = new Path(atoi(pathId.c_str()), nodeList, nbNodes);
        }

        fichier.close();

        return true;
    }
    else{
        cerr << "Error in file open " << file << endl;
        return false;
    }
}

/**
 * @brief Board::checkDeaths check the possible deaths caused by the last Move
 * @param me the Player that owns the Marble that moved
 * @param dst the Node toward which the Marble moved
 * @return useless
 */
bool Board::checkDeaths(Player * me, Node * dst){
    Marble* tmp;
    // A) CHECK SUICIDE
    if(dst->getMarble()->isCaught()){
        cout << "(" << dst->getId() << ") " << Marble::getNameFromType(dst->getMarble()->getType()) << " suicided !" << endl;
        tmp = dst->getMarble();
        killMarble(dst->getMarble());
        // if psychologist suicided the other player can revive
        if(tmp->getType() == PSYCHOLOGIST){
            Player * p = me->getEnnemy();
            p->askRespawn(dst);
        }
    }
    // B) CHECK KILL
    else{
        if(dst->getMarble()->getType() == DOCTOR || dst->getMarble()->getType() == INFORMER){
            // check paths and check isCatch for all annemys in it
            for(int i = 0 ; i < dst->nbPathsOfNode() ; i++){
                Path * currentPath = dst->getPath()[i];
                for(int j = 0 ; j < currentPath->size ; j++){
                    Marble * currentMarble = currentPath->nodes[j]->getMarble();
                    // if marble on current node check if catch
                    if(currentMarble){
                        if(currentMarble->isCaught()){
                            currentMarble->kill();
                            // If the marble killed was a psychologist the player can revive a marble
                            if(currentMarble->getType()==PSYCHOLOGIST){
                                me->askRespawn(currentPath->nodes[j]);
                            }
                        }
                    }
                }
            }
        }
    }
    return false;
}

bool Board::killMarble(Marble * marbleToKill){
    if(marbleToKill != NULL){
        Node * marbleNode = marbleToKill->getMyNode();
        Node * deadNode = nodes[firstFreeDeadMarble]; // get an empty dead node
        deadNode->setMarble(marbleToKill); // put the marble in it
        marbleNode->setMarble(NULL); // set the previous node marble to null
        deadNode->getMarble()->setMyNode(deadNode);
        cout << "killed " << marbleNode->getId() << " to " << deadNode->getId() << endl;
        firstFreeDeadMarble++ ;
        return true;
    }
    else{
        cout << "No marble to kill !" << endl;
        return false;
    }
}

// move a marble without checking constraints
void Board::forceMove(Node * src, Node * dst){
    dst->setMarble(src->getMarble());
    src->setMarble(NULL);
    dst->getMarble()->setMyNode(dst);
   // cout << "moved " << src->getId() << " to " << dst->getId() << endl;
}


Path* Board::getPath(int i){
    return paths[i];
}

Path** Board::getPaths(){
    return paths;
}

int Board::getNbPaths(){
    return this->nbPaths;
}

Node* Board::getNode(int i){
    return nodes[i];
}

void Board::showPaths(){
    for(int i = 0 ; i < this->getNbPaths() ; i++){
        cout << "Path " << i << endl;
        if(this->getPath(i)->isBorder){
            cout << " IS BORDER" << endl;
        }
        for(int j = 0 ; j < this->getPath(i)->size ; j++){
            cout << this->getPath(i)->nodes[j] << " ";
        }
        cout << endl;
    }
}

int Board::size(){
    return BOARDSIZE;
}

