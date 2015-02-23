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
    string victory = ""; // who wins;

    theboard.killMarble(theboard.getNode(34)->getMarble());
    theboard.killMarble(theboard.getNode(34)->getMarble());

    return 0;

}

