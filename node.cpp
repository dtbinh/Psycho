#include "node.h"
#include "path.h"


Node::Node(){

}

Node::Node(int id, Marble* marble, bool special = false, bool deadMarble = false)
{
    this->id = id;
    this->marble = marble;
    this->special = special;
    this->deadMarble = deadMarble;
    this->paths = new Path*[NB_CROSSING_PATHS];
    this->currentNbPaths = 0;
}

Node::~Node()
{

}

Path** Node::getPath(){
    return this->paths;
}

void Node::setPath(Path **p){
   this->paths = p;
}

void Node::addPath(Path *p){
    this->paths[this->currentNbPaths] = p;
    this->currentNbPaths++;
}

int Node::nbPathsOfNode(){
    return this->currentNbPaths;
}

bool Node::isSpecial(){
    return this->special;
}

int Node::getId(){
    return this->id;
}

Marble* Node::getMarble(){
    return marble;
}

void Node::setMarble(Marble* _marble){
    marble = _marble;
}


