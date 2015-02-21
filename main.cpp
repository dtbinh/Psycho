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

        cout << "Board" << endl;

        for(int i = 0 ; i < theboard.getNbPaths() ; i++){
            cout << "Path " << i << endl;
            for(int j = 0 ; j < theboard.getPath(i)->getNbNodes() ; j++){
                cout << theboard.getPath(i)->getNodeId(j) << " ";
            }
            cout << endl;
        }

        cout << "=== Joueur 1 ==="     << endl;

        blanc->displayMarbles();

        cout << "=== Joueur 2 ===" << endl;

        noir ->displayMarbles();

        cout << "end" << endl;

        return 0;

}

