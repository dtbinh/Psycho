#include <iostream>
#include "util.h"
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

    Util::updatePositionsTxt(blanc, noir);
    system("pause");

    noir->computePossibilities();
    blanc->computePossibilities();
    blanc->move(theboard.getNode(44), theboard.getNode(22));
    blanc->computePossibilities();
    noir->computePossibilities();
    Util::updatePositionsTxt(blanc, noir);
    system("pause");
    noir->move(theboard.getNode(64), theboard.getNode(31));
    noir->computePossibilities();
    blanc->computePossibilities();
    Util::updatePositionsTxt(blanc, noir);
    system("pause");
    noir->move(theboard.getNode(31), theboard.getNode(33));
    noir->computePossibilities();
    blanc->computePossibilities();
    Util::updatePositionsTxt(blanc, noir);
    system("pause");
    // joueur noir essaye de res son doc

    noir->respawnUnit(theboard.getNode(51), DOCTOR);

    Util::updatePositionsTxt(blanc, noir);


    return 0;
}

