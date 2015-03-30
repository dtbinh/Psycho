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
#include "player.h"
#include "board.h"
#include <cstdlib>
#include <iostream>

using namespace std;

Marble::Marble(){

}

Marble::Marble(Node *nodeId, int type, Player* owner)
{
    this->myNode = nodeId;
    this->type = type;
    this->owner = owner;
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
Node** Marble::getAccessibleNodes(){return accessibleNodes;}

/**
 * @brief Marble::getMyNode
 * @return the Node'id that contains this Marble
 */
Node *Marble::getMyNode(){return myNode;}

/**
 * @brief Marble::setMyNode
 * @param nodeId integer representation of the Node that contains this Marble
 */
void Marble::setMyNode(Node* nodeId){myNode = nodeId;}

/**
 * @brief Marble::setOwner
 * @param owner, reference to the Player that owns this Marble
 */
void Marble::setOwner(Player* owner){this->owner = owner;}

/**
 * @brief Marble::getOwner
 * @return the reference to the Player that owns this Marble
 */
Player* Marble::getOwner(){return this->owner;}

/**
 * @brief Marble::getType
 * @return an Integer that represent the type of this Marble, Types defined in Marble.h file
 */
int Marble::getType(){return type;}

/**
 * @brief Marble::getNbAccessibleNodes
 * @return the number of Nodes accessible by this marble
 */
int Marble::getNbAccessibleNodes(){return nbComputedNodes;}

/**
 * @brief Marble::isDead
 * @return true if this Marble is dead (outside of the visible board), false otherwise
 */
bool Marble::isDead(){return myNode->getId() > DEADLIMIT;}

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
    this->accessibleNodes = new Node*[boardInstance.size()];
    this->nbComputedNodes = 0;
    bool alreadyStuckByPsychologist = false;                                        // A Psychologist is locking a path
    bool stuckByPsychologist = false;                                               // A Psychologist is locking the current path
    bool stuck = false;                                                             // This marble cannot move
    int startAccessibleNodes;                                                       // Number of accessible nodes before the current path

    Path* currentPath;                                                              // Used to gain computation time and space in the code
    Path** paths = this->myNode->getPath();                  // Same
    int nbPath = this->myNode->nbPathsOfNode();              // Same


    /* browse throught all the Paths of this Marble's Node
     * add all the nodes of that path to the accessible nodes of this marble (exception commented)
     */
    for(int i = 0; i < nbPath; i++){
        currentPath = paths[i];
        stuckByPsychologist = false;
        startAccessibleNodes = this->nbComputedNodes;
        for(int j = 0 ; currentPath != NULL && j < currentPath->size; j++){
            // The currentPath contains this Marble
            if(currentPath->nodes[j] == myNode){
                stuckByPsychologist = computePath(currentPath, j);

                if(stuckByPsychologist){
                    // An other Path was locked too, so the marble is stuck
                    if(alreadyStuckByPsychologist){
                        stuck = true;
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
    }

}

/**
 * @brief Marble::isCatch this method browse throught all the paths of this marble's node
 * If this marble is surrounded by two DOCTOR and watched by an INFORMER on another path it is captured
 * @return true if the marble, on which isCatch is called, is captured. false otherwise
 */
bool Marble::isCaught(){

    Board& boardInstance = Board::Instance();
    int surroundedOnPath[NB_CROSSING_PATHS];
    int surroundedOnPathNb = 0;
    int watchedOnPath[NB_CROSSING_PATHS];
    int watchedOnPathNb = 0;
    int specialNodeBeforeDoctor;

    bool surrounded;                                                                // This Marble is surrounded by Doctors
    bool watched;                                                                   // This Marble is watched by an Informer
    bool doctorAfter;
    bool doctorBefore;

    Path* currentPath;                                                              // Used to gain computation time and space in the code
    Marble* currentMarble;                                                          // Same
    Path** paths = this->myNode->getPath();                  // Same
    int nbPath = this->myNode->nbPathsOfNode();              // Same

    for(int i = 0; i < nbPath; i++){
        currentPath = paths[i];
        doctorAfter = false;
        doctorBefore = false;
        surrounded = false;
        watched = false;
        specialNodeBeforeDoctor = 0;
        for(int j = 0 ; currentPath != NULL && j < currentPath->size; j++){
            // The currentPath contains this Marble
            if(currentPath->nodes[j] == this->myNode){

                if(!currentPath->isBorder){

                    //Browse the rest of the Path
                    for(int k = j+1; k < currentPath->size; k++){
                        currentMarble = currentPath->nodes[k]->getMarble();

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

                        currentMarble = currentPath->nodes[k]->getMarble();

                        if(currentMarble != NULL && currentMarble->owner != this->owner){
                            if(currentMarble->getType() == DOCTOR && doctorAfter && !surrounded) surrounded = true;
                            else if(currentMarble->getType() == DOCTOR) doctorBefore = true;
                            if(currentMarble->getType() == INFORMER && !watched) watched = true;
                        }
                    }

                }else{

                    for(int k = (j+1) % currentPath->size; k != j; k = (k+1)%currentPath->size ){
                        currentMarble = currentPath->nodes[k]->getMarble();

                        //The current Node contains an opponent's Marble
                        if(currentMarble != NULL && currentMarble->owner != this->owner){
                            if(currentMarble->getType() == DOCTOR && doctorBefore && !surrounded) surrounded = true;
                            else if(currentMarble->getType() == DOCTOR) doctorAfter = true;
                            if(currentMarble->getType() == INFORMER && !watched) watched = true;
                        }

                        if(!doctorAfter && !surrounded && currentPath->nodes[k]->isSpecial()) specialNodeBeforeDoctor++;

                    }

                    //Browse the begining of the Path
                    for(int k = (j == 0) ? currentPath->size -1 : j-1; k !=j ; k = (k == 0) ? currentPath->size -1 : k-1){
                        currentMarble = currentPath->nodes[k]->getMarble();

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

                        if(!doctorBefore && !surrounded && currentPath->nodes[k]->isSpecial()){
                            specialNodeBeforeDoctor++;
                        }
                    }
                }

                if(specialNodeBeforeDoctor > 1) surrounded = false;
                if(surrounded) surroundedOnPath[surroundedOnPathNb++] = i;
                if(watched) watchedOnPath[watchedOnPathNb++] = i;
                
            }
        }
    }

    for(int i = 0; i < surroundedOnPathNb; i++){
        for(int j = 0; j < watchedOnPathNb; j++){
            if(surroundedOnPath[i] != watchedOnPath[j]){
                return true;
            }
        }
    }

    return false;
}

bool Marble::computePath(Path* p, int index){
    Board& boardInstance = Board::Instance();
    bool marbleEncountered = false;
    bool enemyPsychologist = false;
    bool allyPsychologist = false;

    if(p->isBorder){
        for(int i = index == 0 ? p->size -1 : index-1; i != index; i = i == 0 ? p->size-1 : i-1){
            allyPsychologist = treatNode(p->nodes[i]->getMarble(), &marbleEncountered, &enemyPsychologist, p->nodes[i]) || allyPsychologist;
        }
        marbleEncountered = false;
        for(int i = index+1 % p->size; i != index; i = (++i % p->size)){
            allyPsychologist = treatNode(p->nodes[i]->getMarble(), &marbleEncountered, &enemyPsychologist, p->nodes[i]) || allyPsychologist;
        }

    }else{
        for(int i = index - 1; i >= 0; i--){
            allyPsychologist = treatNode(p->nodes[i]->getMarble(), &marbleEncountered, &enemyPsychologist, p->nodes[i]) || allyPsychologist;
        }
        marbleEncountered = false;
        for(int i = index+1; i < p->size; i++){
            allyPsychologist = treatNode(p->nodes[i]->getMarble(), &marbleEncountered, &enemyPsychologist, p->nodes[i]) || allyPsychologist;
        }
    }

    return enemyPsychologist && !allyPsychologist;

}

bool Marble::treatNode(Marble* currentMarble, bool* marbleEncountered, bool* stuckByPsychologist, Node* node){
    if(currentMarble == NULL){
        if(!(*marbleEncountered)) accessibleNodes[nbComputedNodes++] = node;
    }else if(currentMarble->getType() == PSYCHOLOGIST){
        if(currentMarble->getOwner() != this->owner){
            *stuckByPsychologist = true;                    // There is a Psychologist locking this path
        }else{
            return true;                                   // There is a Psychologist unlocking this path
        }
    }else{
        *marbleEncountered = true;                          // Marble can't "Jump" above other marbles
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
