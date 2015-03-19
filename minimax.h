#ifndef MINIMAX_H
#define MINIMAX_H

class Player;

class Tree;
class Minimax
{
public:
    Minimax();
    ~Minimax();

    int eval(char* marblePosition, Player* player);
    char *getMoveFrom(Tree* root);

    Tree* fillDecisionTree(Tree*, int);
};

#endif // MINIMAX_H
