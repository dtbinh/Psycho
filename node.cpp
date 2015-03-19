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

#include "node.h"
#include "path.h"


Node::Node(){

}

/**
 * @brief Node::Node constructor of Node class
 * @param id the id of this Node on the board
 * @param marble the Marble contained in this Node (usually NULL)
 * @param special
 * @param deadMarble
 */
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

/**
 * @brief Node::getPath getter of paths attribute
 * @return paths an array of Path
 */
Path** Node::getPath(){
    return this->paths;
}

/**
 * @brief Node::setPath setter of paths attribute
 * @param p an array of Path
 */
void Node::setPath(Path **p){
   this->paths = p;
}

/**
 * @brief Node::addPath add a Path to the paths attribute
 * @param p the Path to add
 */
void Node::addPath(Path *p){
    this->paths[this->currentNbPaths] = p;
    this->currentNbPaths++;
}

/**
 * @brief Node::nbPathsOfNode getter of cuurentNbPaths attribute
 * @return currentNbPaths
 */
int Node::nbPathsOfNode(){
    return this->currentNbPaths;
}

/**
 * @brief Node::isSpecial
 * @return special attribute ( the special Nodes are : 0, 8, 155, 93, 101, 147)
 */
bool Node::isSpecial(){
    return this->special;
}

/**
 * @brief Node::getId getter of id attribute
 * @return id
 */
int Node::getId(){
    return this->id;
}

/**
 * @brief Node::getMarble getter of marble attribute
 * @return marble
 */
Marble* Node::getMarble(){
    return marble;
}

/**
 * @brief Node::setMarble setter of marble attribute
 * @param _marble a Marble
 */
void Node::setMarble(Marble* _marble){
    marble = _marble;
}


