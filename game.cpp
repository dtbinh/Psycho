#include "game.h"

Game::Game()
{
    Board& theboard = Board::Instance();
    cout << "Board created ! With " << theboard.size() << " nodes." << endl;
    playerone = new Player(PLAYERONE);
    playertwo = new Player(PLAYERTWO);

    playerone->setOpponent(playertwo);
    playertwo->setOpponent(playerone);

    playerone->computePossibilities();
    playertwo->computePossibilities();

    minimax = new Minimax();
}

Game::~Game()
{

}

void Game::testMinimax(){
    MyVectorOfTree* tmp = minimax->initParcours(playerone);
    minimax->bestTree(playerone, tmp, time(0));
}
