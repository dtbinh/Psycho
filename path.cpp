#include "path.h"

Path::Path(int * t, int nbNodes){
    this->path = t;
    this->nbNodes = nbNodes;
}

Path::Path()
{

}

Path::~Path()
{

}

Path::getNbNodes(){
    return nbNodes;
}

Path::getNodeId(int i){
    return path[i];
}
