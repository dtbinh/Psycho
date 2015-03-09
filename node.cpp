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


