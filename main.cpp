#include <iostream>
#include "board.h"
#include "player.h"
#include <cstdlib>

using namespace std;

int main()
{
    Board& theboard = Board::Instance();
        Player* blanc = new Player(PLAYERONE);
        Player* noir = new Player(PLAYERTWO);

        cout << "Board created ! With " << theboard.size() << " nodes." << endl;

        cout << "=== Joueur 1 ==="     << endl;

        blanc->displayMarbles();

        cout << "=== Joueur 2 ===" << endl;

        noir ->displayMarbles();

        return 0;

}

