#include "marble.h"
#include "path.h"
#include "board.h"
#include <cstdlib>

Marble::Marble(){

}

Marble::Marble(int nodeId, int type)
{
    this->currentNode = nodeId;
    this->type = type;
    this->hadPsychologist = false;
    this->stuck = false;
    this->owner = owner;
}

Marble::~Marble()
{

}

int Marble::getCurrentNode(){
    return currentNode;
}

int* Marble::getAccessibleNodes(){
    return accessibleNodes;
}

void Marble::setCurrentNode(int nodeId){
    currentNode = nodeId;
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
    nbNodesComputed = 0;
    bool alreadyStuckByPsychologist = false;                    // A Psychologist is locking a path
    bool stuckByPsychologist = false;                           // A Psychologist is locking the current path
    bool savedByPsychologist = false;                           // A Psychologist is unlocking the current path if needed be
    int startAccessibleNodes;                                   // Number of accessible nodes before the current path

    stuck = false;                                              // This marble cannot move
    Path* currentPath;                                          // Used to gain computation time and space in the code
    Marble* currentMarble;                                      // Same
    Path** paths = boardInstance.getPaths();                    // Same
    int nbPath = boardInstance.getNbPaths();                    // Same


    /* browse throught all the paths
     * if this marble is in a path
     * add all the nodes of that path to the accessible nodes of this marble (exception commented)
     */
    for(int i = 0; i < nbPath; i++){
        currentPath = paths[i];
        stuckByPsychologist = false;
        savedByPsychologist = false;
        startAccessibleNodes = this->nbNodesComputed;
        for(int j = 0 ; currentPath != NULL && j < currentPath->getNbNodes(); j++){
            // Ther currentPath contains this Marble
            if(currentPath->getNodeId(j) == currentNode){
                // Browse the rest of the Path
                for(int k = j; k < currentPath->getNbNodes(); k++){
                    currentMarble = boardInstance.getNode(currentPath->getNodeId(k))->getMarble();
                    // There is no Marble in that node, so that node is added to the accessibleNodes
                    if(currentMarble == NULL){
                        accessibleNodes[nbNodesComputed] = currentPath->getNodeId(k);
                        nbNodesComputed++;
                    // There is a Marble in that node
                    }else if(currentMarble->getType() == PSYCHOLOGIST){
                        if(currentMarble->getOwner() != this->owner){
                            stuckByPsychologist = true;                 // There is a Psychologist locking this path
                        }else{
                            savedByPsychologist = true;                  // There is a Psychologist unlocking this path
                        }
                        continue;                                       // Marbles can "Jump" above a Psychologist
                    }else{
                        break;                                          // Marble can't "Jump" above other marbles
                    }
                }

                //Browse the begining of the Path
                for(int k = 0; k < j; k++){
                    currentMarble = boardInstance.getNode(currentPath->getNodeId(k))->getMarble();
                    if(currentMarble == NULL){
                        accessibleNodes[nbNodesComputed] = currentPath->getNodeId(k);
                        nbNodesComputed++;
                    }else if(currentMarble->getType() == PSYCHOLOGIST){
                        if(currentMarble->getOwner() != this->owner){
                            stuckByPsychologist = true;
                        }else{
                            savedByPsychologist = true;
                        }
                        continue;
                    }else{
                        break;
                    }
                }
                // A Psychologist is blocking this Path
                if(stuckByPsychologist && !savedByPsychologist){
                    // An other Path was locked too, so the marble is stuck
                    if(alreadyStuckByPsychologist){
                        this->stuck = true;
                        nbNodesComputed = 0;
                    }else{
                        // Only the nodes of this Path are accessible because of a Psychologist
                        accessibleNodes = &(accessibleNodes[startAccessibleNodes]);
                        nbNodesComputed = nbNodesComputed - startAccessibleNodes;
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

/**
 * Not used anymore, Kept for possible debug
 * @brief Marble::computeAccessibleNodesForPath
 * @param p
 * @param marbleId
 */
void Marble::computeAccessibleNodesForPath(Path *p, int marbleId){
    Board& boardInstance = Board::Instance();
    int startAccessibleNodes = nbNodesComputed;
    bool havePsychologist = false;

    for(int i = marbleId + 1; i < p->getNbNodes(); i++){
        if(boardInstance.getNode(p->getNodeId(i))->getMarble() == NULL){
            accessibleNodes[nbNodesComputed] = p->getNodeId(i);
            nbNodesComputed++;
        }else if(boardInstance.getNode(p->getNodeId(i))->getMarble()->getType() == PSYCHOLOGIST){
            havePsychologist = true;
            continue;
        }else{
            break;
        }
    }

    for(int i = marbleId - 1; i >= 0; i--){
        if(boardInstance.getNode(p->getNodeId(i))->getMarble() == NULL){
            accessibleNodes[nbNodesComputed] = p->getNodeId(i);
            nbNodesComputed++;
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
        nbNodesComputed = nbNodesComputed - startAccessibleNodes;
        hadPsychologist = true;
    }

}

