#ifndef GAME_H
#define GAME_H

#include "board.h"
#include "player.h"
#include "minimax.h"

class Game
{
public:
    Game(); // Constructor
    ~Game();

    void testMinimax();

private:
    Minimax * minimax;
    Player * playerone;
    Player * playertwo;
};

#endif // GAME_H
