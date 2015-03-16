#include "minimax.h"
#include "tree.h"

Minimax::Minimax()
{

}

Minimax::~Minimax()
{

}

char* Minimax::getMoveFrom(Tree* root, int depth){

    int best = root->getMaxValue();
    return root->getDispositionFromValue(best);
}

int Minimax::eval(char *marblePosition){
    //TODO real evaluation function
    int* rdm;
    return (int) rdm;
}
