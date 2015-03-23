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

#include "util.h"
#include "node.h"
#include "marble.h"
#include "path.h"
#include "board.h"


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
    if(this->loadPaths(DATA_PATH + "paths.txt")){
        cout << "paths loaded" << endl;
    }
    else{
        cout << "fatal error : path of path file not found" << endl;
        exit(EXIT_FAILURE);
    }

    nodes = new Node*[BOARDSIZE];

    for(int i = 0 ; i <= BOARDNODES ; i++){
    	bool isSpecialNode = (i == 0 || i == 155 || i == 8 || i == 93 || i == 101 || i == 147);
        this->nodes[i] = new Node(i, NULL, isSpecialNode, false);
    }

    // setPaths for all the nodes
    for(int i = 0 ; i < this->getNbPaths() ; i++){
        for(int j = 0 ; j < this->getPath(i)->getNbNodes() ; j++){
            this->nodes[this->getPath(i)->getNodeId(j)]->addPath(this->getPath(i));
        }
    }

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

	if (!fichier) return false;

	string line;
	// 1st line : number of paths
	getline(fichier, line);

	this->nbPaths = atoi(line.c_str());

	this->paths = (Path**) malloc(sizeof(Path*) * nbPaths);
	nodeList = (int *) malloc(sizeof(int) * MAXPATHSIZE);

	cout << nbPaths << " paths found" << endl;

	while(!fichier.eof()){
		nodeList = (int *) malloc(sizeof(int) * MAXPATHSIZE);
		getline(fichier, line);
		string delimiter = " : ";
		string pathId = line.substr(0, line.find(delimiter));
		string rest = line.substr(line.find(delimiter)+3, line.length()); // +3 for the 2 spaces and the :
		int nbNodes;

		nbNodes = Util::split(nodeList, rest, ' ');

		if(atoi(pathId.c_str()) == 0){
			this->paths[atoi(pathId.c_str())] = new Path(nodeList, nbNodes, true);
		}
		else{
			this->paths[atoi(pathId.c_str())] = new Path(nodeList, nbNodes, false);
		}
	}

	fichier.close();

	return true;
        
}

/**
 * @brief Board::checkDeaths check the possible deaths caused by the last Move
 * @param me the Player that owns the Marble that moved
 * @param dst the Node toward which the Marble moved
 * @return useless
 */
bool Board::checkDeaths(Player * me, Node * dst){
    // A) CHECK SUICIDE
    if(dst->getMarble()->isCatch()){
        cout << "(" << dst->getId() << ") " << Marble::getNameFromType(dst->getMarble()->getType()) << " suicided !" << endl;
        dst->getMarble()->kill();
        // if psychologist suicided the other player can revive
        if(dst->getMarble()->getType() == PSYCHOLOGIST){
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
                for(int j = 0 ; j < currentPath->getNbNodes() ; j++){
                    Marble * currentMarble = this->getNode(currentPath->getNodeId(j))->getMarble();
                    // if marble on current node check if catch
                    if(currentMarble){
                        if(currentMarble->isCatch()){
                            currentMarble->kill();
                            // If the marble killed was a psychologist the player can revive a marble
                            if(currentMarble->getType()==PSYCHOLOGIST){
                                me->askRespawn(this->getNode(currentPath->getNodeId(j)));
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
        Node * marbleNode = nodes[marbleToKill->getMyNode()];
        Node * deadNode = nodes[firstFreeDeadMarble]; // get an empty dead node
        deadNode->setMarble(marbleToKill); // put the marble in it
        marbleNode->setMarble(NULL); // set the previous node marble to null
        deadNode->getMarble()->setMyNode(deadNode->getId());
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
    dst->getMarble()->setMyNode(dst->getId());
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
        if(this->getPath(i)->isTheBorder()){
            cout << " IS BORDER" << endl;
        }
        for(int j = 0 ; j < this->getPath(i)->getNbNodes() ; j++){
            cout << this->getPath(i)->getNodeId(j) << " ";
        }
        cout << endl;
    }
}

int Board::size(){
    return BOARDSIZE;
}

