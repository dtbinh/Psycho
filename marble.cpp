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
}

Marble::~Marble()
{
    delete [] accessibleNodes;
}


/**
 * @brief Marble::getAccessibleNodes
 * @return the array that contains the id of all the nodes accessible from this Marble
 * Use condition : the array returned by this method is updated by the computeAccessibleNodes method
 * if a Marble's position have changed it is advisable to call computeAccessibleNodes before calling this method
 */
int* Marble::getAccessibleNodes(){
    return accessibleNodes;
}

/**
 * @brief Marble::getMyNode
 * @return the Node'id that contains this Marble
 */
int Marble::getMyNode(){
    return myNode;
}

/**
 * @brief Marble::setMyNode
 * @param nodeId integer representation of the Node that contains this Marble
 */
void Marble::setMyNode(int nodeId){
    myNode = nodeId;
}

/**
 * @brief Marble::setOwner
 * @param owner, reference to the Player that owns this Marble
 */
void Marble::setOwner(Player* owner){
    this->owner = owner;
}

/**
 * @brief Marble::getOwner
 * @return the reference to the Player that owns this Marble
 */
Player* Marble::getOwner(){
    return this->owner;
}

/**
 * @brief Marble::getType
 * @return an Integer that represent the type of this Marble, Types defined in Marble.h file
 */
int Marble::getType(){
    return type;
}

int Marble::getNbComputedNodes(){
    return nbComputedNodes;
}

/**
 * @brief Marble::isDead
 * @return true if this Marble is dead (outside of the visible board), false otherwise
 */
bool Marble::isDead(){
    return myNode > 162;
}

/**
 * @brief Marble::getNameFromType return the string representation of the parameter
 * @param integer t represent a type of Marble, different types are defined in Marble.h file
 * @return
 */
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
 * @brief Marble::computeAccessibleNodes Compute the nodes accessible by this marble
 * browse throught all the paths of this Marble's Node
 * side effect of this method : fill a static array (accessibleNodes) with the nodes accessible
 * side effect of this method : set the value of an integer (nbComputedNodes) to the number of nodes accessible
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


                // The border is special
                if(!currentPath->isTheBorder()){
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
                        }else{
                            marbleEncountered = true;                       // Marble can't "Jump" above other marbles
                        }
                    }

                    marbleEncountered = false;
                    //Browse the begining of the Path
                    for(int k = j-1; k >=0 ; k--){
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
                }else{
                    for(int k = j+1; k != j; k = (k+1) % currentPath->getNbNodes() ){
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
                        }else{
                            marbleEncountered = true;                       // Marble can't "Jump" above other marbles
                        }
                    }

                    marbleEncountered = false;
                    //Browse the begining of the Path
                    for(int k = j-1; k != j ; k = k==0 ? currentPath->getNbNodes() - 1 : k-1){
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
            }
            // This Marble cannot move, no need to search other Paths
            if(this->stuck){
                break;
            }
        }
    }
}

/**
 * @brief Marble::isCatch this method browse throught all the paths of this marble's node
 * If this marble is surrounded by two DOCTOR and watched by an INFORMER on another path it is captured
 * @return true if the marble, on which isCatch is called, is captured. false otherwise
 */
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

                if(!currentPath->isTheBorder()){

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
                    }

                }else{

                    for(int k = j+1; k != j; k = (k+1)%currentPath->getNbNodes() ){
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

                        if(!doctorAfter && !surrounded && boardInstance.getNode(currentPath->getNodeId(k))->isSpecial()){
                            specialNodeBeforeDoctor++;
                        }

                    }

                    //Browse the begining of the Path
                    for(int k = j-1; k !=j ; k = (k == 0) ? currentPath->getNbNodes()-1 : k-1){
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

                        if(!doctorBefore && !surrounded && boardInstance.getNode(currentPath->getNodeId(k))->isSpecial()){
                            specialNodeBeforeDoctor++;
                        }
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
            cout << surroundedOnPath[i] << " , " << watchedOnPath[i] << endl;
            if(surroundedOnPath[i] != watchedOnPath[j]){
                cout << Marble::getNameFromType(this->getType()) << " captured" << endl;
                return true;
            }
        }
    }

    return false;
}

/**
 * @brief Marble::kill
 * side effect of this method : call to Board::killMarble() method
 */
void Marble::kill(){
    Board& boardInstance = Board::Instance();
    boardInstance.killMarble(this);
}

/**
 * @brief Marble::displayAccessibleNodes debug method, useless otherwise
 * display the accessibleNodes
 */
void Marble::displayAccessibleNodes(){
    cout << nbComputedNodes << " Nodes" << endl;
    for(int i = 0; i < nbComputedNodes; i++){
        cout << "   |" << endl;
        cout << "   _" << accessibleNodes[i] << endl;
    }
}


/**
 * @brief Marble::computeAccessibleNodesForPath Not used anymore, Kept for possible debug
 * @param p the Path to browse to add Nodes'id to accessibleNodes
 * @param marbleId the index in Path p where this Marble is located
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

