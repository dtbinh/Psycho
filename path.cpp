#include "path.h"

Path::Path(int * t, int nbNodes, bool isBorder){
    this->path = t;
    this->nbNodes = nbNodes;
    this->isBorder = isBorder;
}

Path::Path()
{

}

Path::~Path()
{

}

int Path::getNbNodes(){
    return nbNodes;
}

int Path::getNodeId(int i){
    return path[i];
}

bool Path::isTheBorder(){
    return isBorder;
}
