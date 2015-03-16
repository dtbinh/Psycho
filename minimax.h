#ifndef MINIMAX_H
#define MINIMAX_H

class Tree;
class Minimax
{
public:
    Minimax();
    ~Minimax();

    static int eval(char* marblePosition);
    char *getMoveFrom(Tree* root);
};

#endif // MINIMAX_H
