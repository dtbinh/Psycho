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
}

Node::~Node()
{

}

Path * Node::getPath(){
    return path;
}

void Node::setPath(Path * p){
    path = p;
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


