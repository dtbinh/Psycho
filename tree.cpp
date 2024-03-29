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

#include "tree.h"
#include "marble.h"
#include "node.h"
#include "myvectoroftree.h"
#include "board.h"
#include <iostream>
#include <cstdio>
#include <cstdlib>

using namespace std;

/**
 * @brief Tree::Tree constructor void of Tree class
 */
Tree::Tree()
{
    level = 0;
    nbSons = 0;
    treeSize = 0;
    father = pT_NULL;
    sons = new MyVectorOfTree();
    value = -1;
    marblesPosition = new int[NB_TOTAL_MARBLE];
}

/**
 * @brief Tree::Tree constructor of Tree class
 * @param father the Tree object father of this Tree
 */
Tree::Tree(pTree father){
    level = 0;
    nbSons = 0;
    treeSize = 0;
    this->father = father;
    sons = new MyVectorOfTree();
    value = -1;
    marblesPosition = new int[NB_TOTAL_MARBLE];
}

Tree::Tree(pTree father, Marble **dispositionPlayerOne, Marble **dispositionPlayerTwo){
    level = 0;
    nbSons = 0;
    treeSize = 0;
    this->father = father;
    sons = new MyVectorOfTree();
    value = -1;
    marblesPosition = new int[NB_TOTAL_MARBLE];
    this->setMarblePositionsWithDisposition(dispositionPlayerOne, dispositionPlayerTwo);
}

Tree::~Tree()
{
    deleteAllSons();
}

/**
 * @brief Tree::setLevel setter of level attribute
 * @param _level integer
 */
void Tree::setLevel(int _level){
    level = _level;
}

/**
 * @brief Tree::getLevel getter of level attribute
 * @return integer level
 */
int Tree::getLevel(){
    return level;
}

/**
 * @brief Tree::computeLevel compute this Tree's level from this father's level
 * Calls computeLevel of all the sons of this Tree
 */
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

/**
 * @brief Tree::setNbSons setter of nbSons attribute
 * @param _nbSons number of sons of this Tree
 */
void Tree::setNbSons(int _nbSons){
    nbSons = _nbSons;
}

/**
 * @brief Tree::getNbSons getter of nbSons attribute
 * @return integer nbSons, the number of sons of this Tree
 */
int Tree::getNbSons(){
    return nbSons;
}

void Tree::setValue(int value){
    this->value = value;
}

int Tree::getValue(){
    return this->value;
}

/**
 * @brief Barre only used to display the Tree
 * @param c the character displayed nbChar times
 * @param nbChar the number of time the character c will be displayed
 */
void Barre(char c, int nbChar){
    for(int i = 0; i < nbChar; i++){
        cout << c;
    }
}

/**
 * @brief Tree::displayTreeNode only used to display thr Tree
 * displays all the informations of this node
 */
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

void Tree::displayMarbles(){
    for(int i = 0 ; i < NB_TOTAL_MARBLE/2 ; i++){
        cout << marblesPosition[i] << " ; ";
    }
    cout << endl;
}

/**
 * @brief Tree::displayTree only used to display the Tree
 * display this Tree's Node, calls this method on all this Trees sons
 */
void Tree::displayTree(){
    displayTreeNode();
    for(int i = 0; i < nbSons; i++){
        pTree currentSon= sons->getTree(i);
        if(currentSon != NULL){
            currentSon->displayTree();
        }
    }
}

/**
 * @brief Tree::initSons initialise MyVectorOfTree
 * @param _nbSons the number of sons of this Tree (not used anymore)
 */
void Tree::initSons(int _nbSons){
    if(sons != NULL){
        deleteAllSons();
    }
    nbSons = _nbSons;
    sons = new MyVectorOfTree(new Tree());
}

/**
 * @brief Tree::deleteAllSons TODO check of this method does not break MyVectorOfTree
 */
void Tree::deleteAllSons(){
    for(int i = 0; i < nbSons; i++){
        delete sons->getTree(i);
    }
    deleteSons();
}

/**
 * @brief Tree::deleteSons
 */
void Tree::deleteSons(){
    if(sons != NULL){
        free(sons);
    }
    nbSons = 0;
    sons = NULL;
}

/**
 * @brief Tree::createNextSons create _nbSons new sons to this Tree
 * @param _nbSons
 */
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

/**
 * @brief Tree::addSon add the Tree son at index sonToAdd to MyVectorOfTree
 * @param son the Tree to add
 * @param sonToAdd the place to add the Tree son
 */
void Tree::addSon(pTree son,int sonToAdd){
    nbSons++;
    son->father = this;
    son->computeLevel();
    sons->addTree(son, sonToAdd);
}

/**
 * @brief Tree::addSon add the Tree son to the queue of MyVectorOfTree
 * @param son the Tree to add
 */
void Tree::addSon(pTree son){
    nbSons++;
    son->father = this;
    son->computeLevel();
    sons->addTree(son);
}

// Seek vertically the max value of all sons
/**
 * @brief Tree::getMaxValue search the Tree for the maximum value of the sons
 * set the value of this Tree to the maximum value of this Tree's sons
 * @return an integer, value of this Tree
 */
int Tree::getMaxValue(){

    int sonValue = -1;
    for(int i = 0; i < nbSons; i++){
        sonValue = sons->getTree(i)->getMinValue();
        if(value < sonValue){
            value = sonValue;
        }
    }
    return this->value;
}

/**
 * @brief Tree::getMinValue search the Tree for the minimum vaue of the snons
 * set the value of this Tree to the minimum value of this Tree's sons
 * @return an integer, value of this Tree
 */
int Tree::getMinValue(){

    int sonValue = INT_MAX;
    for(int i = 0; i < nbSons; i++){
        sonValue = sons->getTree(i)->getMaxValue();

        if(value > sonValue){
            value = sonValue;
        }
    }
    return this->value;
}


void Tree::setMarblePositionsWithDisposition(Marble ** dispositionPlayerOne, Marble** dispositionPlayerTwo){
    for(int i = 0 ; i < NB_TOTAL_MARBLE / 2 ; i++){
        this->marblesPosition[i] = dispositionPlayerOne[i]->getMyNode()->getId();
    }
    for(int i = 0; i < NB_TOTAL_MARBLE / 2; i++){
        this->marblesPosition[i+(NB_TOTAL_MARBLE / 2)] = dispositionPlayerTwo[i]->getMyNode()->getId();
    }
}


Marble** Tree::getDispositionFromMarblePosition(){

    Marble** allMarbles = new Marble*[NB_TOTAL_MARBLE];
    for(int i = 0 ; i < NB_TOTAL_MARBLE; i++){
        allMarbles[i] = Util::getMarbleFromInt(i);
        allMarbles[i]->setMyNode(Board::Instance().getNode(this->marblesPosition[i]));
    }
    return allMarbles;
}

int* Tree::getMarbleDisposition(){
    return this->marblesPosition;
}

/**
 * @brief Tree::pruneTree prune the subTree of index sonToPrune and rearange the sons to leave no empty space in the array
 * @param sonToPrune the index of the son to prune
 */
void Tree::pruneTree(int sonToPrune){
    pTree test = sons->removeTree(sonToPrune);
    if(test != NULL){
        nbSons--;
    }
}
