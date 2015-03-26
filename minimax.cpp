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
#include "marble.h"
#include "game.h"

Minimax::Minimax()
{

}

Minimax::~Minimax()
{

}


int Minimax::eval(int *marblePosition, Player* player){
    Marble* marble;
    int value = 0;
    for(int i = 0; i < NB_TOTAL_MARBLE; i++){
        if(marblePosition[i] > DEADLIMIT){
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

void Minimax::displayTreeStatus(Tree* T){
    cout << "\t\t[" << T->getLevel() << "] [" << T->getValue() << "] [" << this->bestSon->treeSize << "]        \r";
}

MyVectorOfTree* Minimax::initParcours(Player* player){
    MyVectorOfTree* list = new MyVectorOfTree();
    Tree* root;
    if(player->getWhoAmI() == PLAYERONE){
        root = new Tree(NULL, player->getDisposition(), player->getEnnemy()->getDisposition());
    }else{
        root = new Tree(NULL, player->getEnnemy()->getDisposition(), player->getDisposition());
    }
    list->addTree(root);
    root->setLevel(0);

    this->bestSon = root;
    this->bestValue = this->eval(root->getMarbleDisposition(), player);

    return list;
}

// Changer list en Tree
Tree* Minimax::bestTree(Player *player, MyVectorOfTree* list, time_t timeout){
    Board& boardInstance = Board::Instance();
    int* accessibleNodes;
    Tree* sonTree;
    int treeCpt = 0;

    Marble* currentMarble;
    Marble** allMarbles;
    Marble** playerMarbles;
    Tree* currentTree;

    while(!list->isEmpty() && timeout+TIMEOUT > time(0)){
        currentTree = list->getTree(treeCpt);
        currentTree->createNextSons(0);

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
            for(int j = 0; j < currentMarble->getNbAccessibleNodes(); j++){
                if(currentTree->getLevel() %2 == 0){
                    player->move(boardInstance.getNode(currentMarble->getMyNode()), boardInstance.getNode(accessibleNodes[j]));
                }else{
                    player->getEnnemy()->move(boardInstance.getNode(currentMarble->getMyNode()), boardInstance.getNode(accessibleNodes[j]));
                }
                if(player->getWhoAmI() == PLAYERONE){
                    sonTree = new Tree(currentTree, player->getDisposition(), player->getEnnemy()->getDisposition());
                }else{
                    sonTree = new Tree(currentTree, player->getEnnemy()->getDisposition(), player->getDisposition());
                }
                sonTree->setLevel(currentTree->getLevel()+1);
                sonTree->setValue(this->eval(sonTree->getMarbleDisposition(), player));
                if(sonTree->getValue() > this->bestValue){
                    this->bestValue = sonTree->getValue();
                    this->bestSon = sonTree;
                }
                list->addTree(sonTree);
                currentTree->addSon(sonTree);

                if(player->getWhoAmI() == PLAYERONE){
                    Util::updatePositionsTxt(player, player->getEnnemy());
                }else{
                    Util::updatePositionsTxt(player->getEnnemy(), player);
                }

                allMarbles = currentTree->getDispositionFromMarblePosition();
                // reset board
                for(int i = 0; i < boardInstance.size(); i++){
                    boardInstance.getNode(i)->setMarble(NULL);
                }
                // set the marbles
                for(int i = 0; i < NB_TOTAL_MARBLE; i++){
                    boardInstance.getNode(allMarbles[i]->getMyNode())->setMarble(allMarbles[i]);
                }

                //cin.get();

		        this->bestSon->treeSize++;
    			this->displayTreeStatus(sonTree);
            }
        }
        treeCpt++;
    }

    return this->bestSon;
}
