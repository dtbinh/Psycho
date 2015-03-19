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

#include "minimax.h"
#include "tree.h"
#include "marble.h"
#include "board.h"
#include "player.h"
#include "myvectoroftree.h"


//Cnut et johnson minimax algorithmique


Minimax::Minimax()
{

}

Minimax::~Minimax()
{

}


int Minimax::eval(char *marblePosition, Player* player){
    Marble* marble;
    int value = 0;
    for(int i = 0; i < NB_TOTAL_MARBLE; i++){
        if(marblePosition[i] > 162){
            marble = Util::getMarbleFromInt(i);
            if(player == marble->getOwner()){
                value -= 1;
            }else{
                value += 1;
            }
        }
    }
    return value;
}

/*
Tree* Minimax::fillDecisionTree(Tree * tree, int depth){
    Board& boardInstance = Board::Instance();
    // If first call, initialize the tree
    if(tree == NULL){
        tree = new Tree();
        tree->createNextSons(0);
        Tree* son;
        Marble* currentMarble;
        for(int i = 0; i < this->nbMarbles; i++){
            tree->setMarblePositionsWithDisposition(this->disposition, this->nbMarbles);

            currentMarble = this->disposition[i];
            for(int j = 0; j < currentMarble->getNbComputedNodes(); j++){
                son = new Tree(tree);
                // do the move
                currentMarble->getOwner()->move(boardInstance.getNode(currentMarble->getMyNode()),boardInstance.getNode(currentMarble->getAccessibleNodes()[j]));
                // get the new disposition and add it to the son
                son->setMarblePositionsWithDisposition(this->disposition, this->nbMarbles);
                tree->addSon(son);
                if(depth > 0){
                    this->fillDecisionTree(son, depth - 1);
                }
            }
        }
    }
    else{
        // For each son
        // get the disposition of father


        // create his son with new disposition


    }
    return tree;
}

*/

MyVectorOfTree* Minimax::initParcours(Player* player){
    MyVectorOfTree* list = new MyVectorOfTree();
    Tree* root = new Tree();
    if(player->getWhoAmI() == PLAYERONE){
        root->setMarblePositionsWithDisposition(player->getDisposition(), player->getEnnemy()->getDisposition());
    }else{
        root->setMarblePositionsWithDisposition(player->getEnnemy()->getDisposition(), player->getDisposition());
    }
    list->addTree(root);
    root->setLevel(0);

    this->bestSon = root;
    this->bestValue = this->eval(root->getMarbleDisposition(), player);

    return list;
}

Tree* Minimax::bestTree(Player *player, MyVectorOfTree* list, time_t timeout){
    Board& boardInstance = Board::Instance();
    int* accessibleNodes;
    int sonValue;
    Tree* sonTree;

    Marble* currentMarble;
    Marble** allMarbles;
    Marble** playerMarbles;
    Tree* currentTree;

    while(!list->isEmpty() && timeout+60 > time(0)){
        currentTree = list->removeTree(0);

        allMarbles = currentTree->getDispositionFromMarblePosition();
        for(int i = 0; i < NB_TOTAL_MARBLE; i++){
            boardInstance.getNode(allMarbles[i]->getMyNode())->setMarble(allMarbles[i]);
        }
        if((currentTree->getLevel()) %2 == 0){
            player->computePossibilities();
            playerMarbles = player->getDisposition();
        }else{
            player->getEnnemy()->computePossibilities();
            playerMarbles = player->getEnnemy()->getDisposition();
        }


        for(int i = 0; i < NBMARBLES; i++){

            currentMarble = playerMarbles[i];
            accessibleNodes = currentMarble->getAccessibleNodes();
            for(int j = 0; j < currentMarble->getNbComputedNodes(); j++){
                player->move(boardInstance.getNode(currentMarble->getMyNode()), boardInstance.getNode(accessibleNodes[j]));
                sonTree = new Tree(currentTree);
                sonTree->setLevel(currentTree->getLevel()+1);
                if(player->getWhoAmI() == PLAYERONE){
                    sonTree->setMarblePositionsWithDisposition(player->getDisposition(), player->getEnnemy()->getDisposition());
                }else{
                    sonTree->setMarblePositionsWithDisposition(player->getEnnemy()->getDisposition(), player->getDisposition());
                }
                sonValue = this->eval(sonTree->getMarbleDisposition(), player);
                if(sonValue > this->bestValue){
                    this->bestValue = sonValue;
                    this->bestSon = sonTree;
                }
                list->addTree(sonTree);

                allMarbles = currentTree->getDispositionFromMarblePosition();
                for(int i = 0; i < NB_TOTAL_MARBLE; i++){
                    boardInstance.getNode(allMarbles[i]->getMyNode())->setMarble(allMarbles[i]);
                }
                if((currentTree->getLevel()) %2 == 0){
                    player->computePossibilities();
                }else{
                    player->getEnnemy()->computePossibilities();
                }
            }
        }
    }

    return this->bestSon;
}
