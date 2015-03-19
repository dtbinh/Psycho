#include "minimax.h"
#include "tree.h"
#include "marble.h"
#include "board.h"
#include "player.h"


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
        marblePosition[i] > 162;
        marble = Util::getMarbleFromInt(i);
        if(player == marble->getOwner()){
            if(i < 13){
                value--;
            }else{
                value++;
            }
        }else{
            if(i >= 13){
                value--;
            }else{
                value++;
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
