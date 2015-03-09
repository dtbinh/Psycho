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

#include "marble.h"
#include "path.h"
#include "board.h"
#include <cstdlib>
#include <iostream>

using namespace std;

Marble::Marble(){

}

Marble::Marble(int nodeId, int type)
{
    this->myNode = nodeId;
    this->type = type;
    this->hadPsychologist = false;
    this->stuck = false;
    //this->owner = owner;
}

Marble::~Marble()
{

}

int Marble::getCurrentNode(){
    return myNode;
}

int* Marble::getAccessibleNodes(){
    return accessibleNodes;
}

void Marble::setCurrentNode(int nodeId){
    myNode = nodeId;
}

void Marble::setOwner(Player* owner){
    this->owner = owner;
}

Player* Marble::getOwner(){
    return this->owner;
}

int Marble::getType(){
    return type;
}

int Marble::getNbComputedNodes(){
    return nbComputedNodes;
}

// Return true if marble is dead
bool Marble::isDead(){
    return myNode > 162;
}

string Marble::getNameFromType(int t){
    switch(t){
    case PSYCHOPATH :
        return "Psychopath";
    case INFORMER:
        return "Informer";
    case DOCTOR:
        return "Doctor";
    case PSYCHOLOGIST:
        return "Psychologist";
    default:
        return "unknown";
    }
    return "unknown";
}


/**
 * Compute the nodes accessible by this marble
 * @brief Marble::computeAccessibleNodes
 */
void Marble::computeAccessibleNodes(){

    // Declaration block
    Board& boardInstance = Board::Instance();
    this->accessibleNodes = new int[boardInstance.size()];
    nbComputedNodes = 0;
    bool alreadyStuckByPsychologist = false;                                        // A Psychologist is locking a path
    bool stuckByPsychologist = false;                                               // A Psychologist is locking the current path
    bool savedByPsychologist = false;                                               // A Psychologist is unlocking the current path if needed be
    bool marbleEncountered = false;                                                 // A Marble have been encountered, no more accessible nodes in this direction of the path
    int startAccessibleNodes;                                                       // Number of accessible nodes before the current path

    stuck = false;                                                                  // This marble cannot move

    Path* currentPath;                                                              // Used to gain computation time and space in the code
    Marble* currentMarble;                                                          // Same
    Path** paths = boardInstance.getNode(this->myNode)->getPath();                  // Same
    int nbPath = boardInstance.getNode(this->myNode)->nbPathsOfNode();              // Same


    /* browse throught all the paths
     * if this marble is in a path
     * add all the nodes of that path to the accessible nodes of this marble (exception commented)
     */
    for(int i = 0; i < nbPath; i++){
        currentPath = paths[i];
        stuckByPsychologist = false;
        savedByPsychologist = false;
        startAccessibleNodes = this->nbComputedNodes;
        for(int j = 0 ; currentPath != NULL && j < currentPath->getNbNodes(); j++){
            // The currentPath contains this Marble
            if(currentPath->getNodeId(j) == myNode){

                marbleEncountered = false;
                // Browse the rest of the Path
                for(int k = j+1; k < currentPath->getNbNodes(); k++){
                    currentMarble = boardInstance.getNode(currentPath->getNodeId(k))->getMarble();
                    // There is no Marble in that node and no Marble encountered, so that node is added to the accessibleNodes
                    if(currentMarble == NULL){
                        if(!marbleEncountered){
                            accessibleNodes[nbComputedNodes] = currentPath->getNodeId(k);
                            nbComputedNodes++;
                        }
                        // There is a Marble in that node
                    }else if(currentMarble->getType() == PSYCHOLOGIST){
                        if(currentMarble->getOwner() != this->owner){
                            stuckByPsychologist = true;                 // There is a Psychologist locking this path
                        }else{
                            savedByPsychologist = true;                 // There is a Psychologist unlocking this path
                        }
                        continue;                                       // Marbles can "Jump" above a Psychologist
                    }else{
                        marbleEncountered = true;                       // Marble can't "Jump" above other marbles
                    }
                }

                marbleEncountered = false;
                //Browse the begining of the Path
                for(int k = j-1; k >=0 ; k--){
                    currentMarble = boardInstance.getNode(currentPath->getNodeId(k))->getMarble();
                    currentMarble = boardInstance.getNode(currentPath->getNodeId(k))->getMarble();
                    // There is no Marble in that node and no Marble encountered, so that node is added to the accessibleNodes
                    if(currentMarble == NULL){
                        if(!marbleEncountered){
                            accessibleNodes[nbComputedNodes] = currentPath->getNodeId(k);
                            nbComputedNodes++;
                        }
                        // There is a Marble in that node
                    }else if(currentMarble->getType() == PSYCHOLOGIST){
                        if(currentMarble->getOwner() != this->owner){
                            stuckByPsychologist = true;                 // There is a Psychologist locking this path
                        }else{
                            savedByPsychologist = true;                 // There is a Psychologist unlocking this path
                        }
                        continue;                                       // Marbles can "Jump" above a Psychologist
                    }else{
                        marbleEncountered = true;                       // Marble can't "Jump" above other marbles
                    }
                }
                // A Psychologist is blocking this Path
                if(stuckByPsychologist && !savedByPsychologist){
                    // An other Path was locked too, so the marble is stuck
                    if(alreadyStuckByPsychologist){
                        this->stuck = true;
                        nbComputedNodes = 0;
                    }else{
                        // Only the nodes of this Path are accessible because of a Psychologist
                        accessibleNodes = &(accessibleNodes[startAccessibleNodes]);
                        nbComputedNodes = nbComputedNodes - startAccessibleNodes;
                        alreadyStuckByPsychologist = true;
                    }
                }
            }
            // This Marble cannot move, no need to search other Paths
            if(this->stuck){
                break;
            }
        }
    }
}

bool Marble::isCatch(){
    Board& boardInstance = Board::Instance();
    int surroundedOnPath[NB_CROSSING_PATHS];
    int surroundedOnIndex = 0;
    int watchedOnPath[NB_CROSSING_PATHS];
    int watchedOnIndex = 0;
    int specialNodeBeforeDoctor;

    bool surrounded;                                                                // This Marble is surrounded by Doctors
    bool watched;                                                                   // This Marble is watched by an Informer
    bool doctorAfter;
    bool doctorBefore;

    Path* currentPath;                                                              // Used to gain computation time and space in the code
    Marble* currentMarble;                                                          // Same
    Path** paths = boardInstance.getNode(this->myNode)->getPath();                  // Same
    int nbPath = boardInstance.getNode(this->myNode)->nbPathsOfNode();              // Same

    for(int i = 0; i < nbPath; i++){
        currentPath = paths[i];
        doctorAfter = false;
        doctorBefore = false;
        surrounded = false;
        watched = false;
        specialNodeBeforeDoctor = 0;
        for(int j = 0 ; currentPath != NULL && j < currentPath->getNbNodes(); j++){
            // The currentPath contains this Marble
            if(currentPath->getNodeId(j) == this->myNode){
                //Browse the rest of the Path
                for(int k = j+1; k < currentPath->getNbNodes(); k++){
                    currentMarble = boardInstance.getNode(currentPath->getNodeId(k))->getMarble();

                    //The current Node contains an opponent's Marble
                    if(currentMarble != NULL && currentMarble->owner != this->owner){

                        if(currentMarble->getType() == DOCTOR && doctorBefore && !surrounded){
                            surrounded = true;
                        }else if(currentMarble->getType() == DOCTOR){
                            doctorAfter = true;
                        }

                        if(currentMarble->getType() == INFORMER && !watched){
                            watched = true;
                        }
                    }

                    if(currentPath->isTheBorder() && !doctorAfter && boardInstance.getNode(currentPath->getNodeId(k))->isSpecial()){
                        specialNodeBeforeDoctor++;
                    }

                }

                //Browse the begining of the Path
                for(int k = j-1; k >=0 ; k--){
                    currentMarble = boardInstance.getNode(currentPath->getNodeId(k))->getMarble();

                    if(currentMarble != NULL && currentMarble->owner != this->owner){

                        if(currentMarble->getType() == DOCTOR && doctorAfter && !surrounded){
                            surrounded = true;
                        }else if(currentMarble->getType() == DOCTOR){
                            doctorBefore = true;
                        }

                        if(currentMarble->getType() == INFORMER && !watched){
                            watched = true;
                        }
                    }

                    if(currentPath->isTheBorder() && !doctorBefore && boardInstance.getNode(currentPath->getNodeId(k))->isSpecial()){
                        specialNodeBeforeDoctor++;
                    }

                }

                if(specialNodeBeforeDoctor > 1){
                    surrounded = false;
                }

                if(surrounded){
                    surroundedOnPath[surroundedOnIndex] = i;
                    surroundedOnIndex++;
                }

                if(watched){
                    watchedOnPath[watchedOnIndex] = i;
                    watchedOnIndex++;
                }
            }
        }
    }
    for(int i = 0; i < surroundedOnIndex; i++){
        for(int j = 0; j < watchedOnIndex; j++){
            if(surroundedOnPath[i] != watchedOnPath[j]){
                cout << Marble::getNameFromType(this->getType()) << " captured" << endl;
                return true;
            }
        }
    }

    return false;
}

void Marble::kill(){
    Board& boardInstance = Board::Instance();
    boardInstance.killMarble(this);
}

void Marble::displayAccessibleNodes(){
    cout << nbComputedNodes << " Nodes" << endl;
    for(int i = 0; i < nbComputedNodes; i++){
        cout << "   |" << endl;
        cout << "   _" << accessibleNodes[i] << endl;
    }
}


/**
 * Not used anymore, Kept for possible debug
 * @brief Marble::computeAccessibleNodesForPath
 * @param p
 * @param marbleId
 */
void Marble::computeAccessibleNodesForPath(Path *p, int marbleId){
    Board& boardInstance = Board::Instance();
    int startAccessibleNodes = nbComputedNodes;
    bool havePsychologist = false;

    for(int i = marbleId + 1; i < p->getNbNodes(); i++){
        if(boardInstance.getNode(p->getNodeId(i))->getMarble() == NULL){
            accessibleNodes[nbComputedNodes] = p->getNodeId(i);
            nbComputedNodes++;
        }else if(boardInstance.getNode(p->getNodeId(i))->getMarble()->getType() == PSYCHOLOGIST){
            havePsychologist = true;
            continue;
        }else{
            break;
        }
    }

    for(int i = marbleId - 1; i >= 0; i--){
        if(boardInstance.getNode(p->getNodeId(i))->getMarble() == NULL){
            accessibleNodes[nbComputedNodes] = p->getNodeId(i);
            nbComputedNodes++;
        }else if(boardInstance.getNode(p->getNodeId(i))->getMarble()->getType() == PSYCHOLOGIST){
            havePsychologist = true;
            continue;
        }else{
            break;
        }
    }

    if(havePsychologist && hadPsychologist){
        stuck = true;
    }else if(havePsychologist){
        accessibleNodes = accessibleNodes + sizeof(int) * startAccessibleNodes;
        nbComputedNodes = nbComputedNodes - startAccessibleNodes;
        hadPsychologist = true;
    }

}

