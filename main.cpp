#include <iostream>
#include "board.h"
#include "player.h"
#include "path.h"
#include <cstdlib>

using namespace std;

int main()
{
    Board& theboard = Board::Instance();

    cout << "Board created ! With " << theboard.size() << " nodes." << endl;

    Player* blanc = new Player(PLAYERONE);
    Player* noir = new Player(PLAYERTWO);

   /* cout << "=== Joueur 1 ===" << endl;
    blanc->displayMarbles();
    cout << "=== Joueur 2 ===" << endl;
    noir ->displayMarbles();*/

    blanc->computePossibilities();
    noir->computePossibilities();


    cout << endl << endl << "[blanc] Allons capturer le psycho d'en face (76) !" << endl;


    blanc->move(theboard.getNode(34), theboard.getNode(29)); // informer
    blanc->computePossibilities();
    noir->computePossibilities();
    blanc->move(theboard.getNode(29), theboard.getNode(73)); // informer
    blanc->computePossibilities();
    noir->computePossibilities();
    blanc->move(theboard.getNode(120), theboard.getNode(114)); // doctor
    blanc->computePossibilities();
    noir->computePossibilities();
    blanc->move(theboard.getNode(114), theboard.getNode(105)); // doctor
    blanc->computePossibilities();
    noir->computePossibilities();

    cout << theboard.getNode(76)->getMarble()->isCatch() << endl;

    cout << "end" << endl;
    return 0;

}

