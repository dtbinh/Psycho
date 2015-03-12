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

#include "tree.h"
#include "myvectoroftree.h"
#include <iostream>
#include <cstdio>
#include <cstdlib>

using namespace std;

Move::Move(int from, int to){
    this->fromNode = from;
    this->toNode = to;
    this->consequence = NULL;
}

Tree::Tree()
{
    level = 0;
    nbSons = 0;
    father = pT_NULL;
    fatherMove = NULL;
    sons = NULL;
    value = -1;
}

Tree::Tree(pTree father){
    level = 0;
    nbSons = 0;
    this->father = father;
    fatherMove = NULL;
    sons = NULL;
    value = -1;
}

Tree::Tree(pTree father, Move *fatherMove){
    level = 0;
    nbSons = 0;
    this->father = father;
    this->fatherMove = fatherMove;
    sons = NULL;
    value = -1;
}

Tree::~Tree()
{
    deleteAllSons();
}

void Tree::setLevel(int _level){
    level = _level;
}

int Tree::getLevel(){
    return level;
}

void Tree::computeLevel(){
    if(father != pT_NULL){
        level = father->getLevel()+1;
    }else{
        level = 0;
    }
    for(int i = 0; i < nbSons; i++){
        pTree currentSon = sons->getTree(i);
        if(currentSon != NULL){
            currentSon->computeLevel();
        }
    }
}

void Tree::setNbSons(int _nbSons){
    nbSons = _nbSons;
}

int Tree::getNbSons(){
    return nbSons;
}

void Barre(char c, int nbChar){
    for(int i = 0; i < nbChar; i++){
        cout << c;
    }
}

void Tree::displayTreeNode(){
    Barre('\t', level);
    cout << "+ Tree (" << this << ") : " << endl;
    Barre('\t', level);
    cout << "  - level = " << level << endl;
    Barre('\t', level);
    cout << "  - nbSons = " << nbSons << endl;
    Barre('\t', level);
    cout << "  - Father = " << father << endl;
    Barre('\t', level);
    cout << "  - Sons[" << nbSons  << "] = { ";
    for(int i=0; i<nbSons; i++) {
        if(i>0) {
            cout << ", ";
        }
        cout << sons->getTree(i);
    }
    cout << " }" << endl;
    cout << endl;
}

void Tree::displayTree(){
    displayTreeNode();
    for(int i = 0; i < nbSons; i++){
        pTree currentSon= sons->getTree(i);
        if(currentSon != NULL){
            currentSon->displayTree();
        }
    }
}

void Tree::initSons(int _nbSons){
    if(sons != NULL){
        deleteAllSons();
    }
    nbSons = _nbSons;
    sons = new MyVectorOfTree(new Tree());
}

void Tree::deleteAllSons(){
    for(int i = 0; i < nbSons; i++){
        delete sons->getTree(i);
    }
    deleteSons();
}


void Tree::deleteSons(){
    if(sons != NULL){
        free(sons);
    }
    nbSons = 0;
    sons = NULL;
}

void Tree::createNextSons(int _nbSons){
    Tree* son;
    sons = new MyVectorOfTree();
    for(int i = 0; i < _nbSons; i++){
        son = new Tree();
        son->father = this;
        son->computeLevel();
        sons->addTree(son);
    }
    this->nbSons = _nbSons;
}

void Tree::addSon(pTree son,int sonToAdd){
    nbSons++;
    son->father = this;
    son->computeLevel();
    sons->addTree(son, sonToAdd);
}

void Tree::addSon(pTree son){
    nbSons++;
    son->father = this;
    son->computeLevel();
    sons->addTree(son);
}

// Seek vertically the max value of all sons
int Tree::getMaxValue(){
    int sonValue;
    for(int i = 0 ; i < nbSons ; i++){
        sonValue = sons->getTree(i)->getMaxValue();
        // seek max
        if(value < sonValue){
            value = sonValue;
        }
    }
    return value;
}

/**
 * @brief Tree::pruneTree
 * Prune the subTree of index sonToPrune and rearange the sons to leave no empty space in the array
 * @param sonToPrune the index of the son to prune
 */
void Tree::pruneTree(int sonToPrune){
    pTree test = sons->removeTree(sonToPrune);
    if(test != NULL){
        nbSons--;
    }
}
