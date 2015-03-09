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
    string vainqueur;


    blanc->setEnnemy(noir);
    noir->setEnnemy(blanc);

    noir->computePossibilities();
    blanc->computePossibilities();

    noir->fillDecisionTree();
    blanc->fillDecisionTree();

   /* Util::updatePositionsTxt(blanc, noir);
    system("pause");
    // boucle de jeu
    while(!blanc->hasLost() && !noir->hasLost()){
        blanc->play();
        noir->computePossibilities();
        blanc->computePossibilities();
        Util::updatePositionsTxt(blanc, noir);
        if(!blanc->hasLost() && !noir->hasLost()){
            noir->play();
            noir->computePossibilities();
            blanc->computePossibilities();
            Util::updatePositionsTxt(blanc, noir);
        }
    }
    if(blanc->hasLost()){
        vainqueur =  "noir";
    }
    else{
        vainqueur = "blanc";
    }

    cout << vainqueur << " a gagné ! Vive " << vainqueur << " !!!!" << endl;

    Util::updatePositionsTxt(blanc, noir);

    blanc->fillDecisionTree();*/

    return 0;
}

