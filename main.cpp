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
    Player* blanc = new Player(PLAYERONE, true);
    Player* noir = new Player(PLAYERTWO, true);

    Util::updatePositionsTxt(blanc, noir);
    system("pause");

    while(!blanc->hasLost() && !noir->hasLost()){
        noir->computePossibilities();
        blanc->computePossibilities();
        blanc->play();
        Util::updatePositionsTxt(blanc, noir);
        noir->computePossibilities();
        blanc->computePossibilities();
        // check if someone wins (white suicided or white win)
        if(!blanc->hasLost() && !noir->hasLost()){
            noir->play();
            Util::updatePositionsTxt(blanc, noir);
        }
    }
    string victory;
    if(blanc->hasLost()) victory = "black";
    else victory = "white";

    cout << "Game is over, and " << victory << " wins !" << endl;

    return 0;
}

