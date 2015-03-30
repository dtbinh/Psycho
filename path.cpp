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

#include "path.h"

/**
 * @brief Path::Path constructor of Path class
 * @param t the array of int, the Nodes ids contained in this Path
 * @param nbNodes the number of Node ids contained in this Path
 * @param isBorder a boolean
 */
Path::Path(int * t, int nbNodes, bool isBorder){
    this->path = t;
    this->size = nbNodes;
    this->isBorder = isBorder;
}

Path::Path()
{

}

Path::~Path()
{

}

/**
 * @brief Path::getNbNodes getter of nbNodes attribute
 * @return nbNodes
 */
int Path::getNbNodes(){
    return size;
}

/**
 * @brief Path::getNodeId find the Node id at index i in path attribute and return it
 * @param i the index of the Node id searched in path attribute
 * @return the Node id at index i
 */
int Path::getNodeId(int i){
    return path[i];
}

/**
 * @brief Path::isTheBorder
 * @return true if this Path is the Border, false otherwise
 */
bool Path::isTheBorder(){
    return isBorder;
}
