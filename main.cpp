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

        blanc->computePossibilities();
        noir->computePossibilities();


        cout << "Tentative de cout valide : 34 vers 14" << endl;
        if(blanc->move(theboard.getNode(34), theboard.getNode(14))){
            cout << "34 vers 14 reussi. Verification" << endl;
            blanc->displayMarbles();
            cout << "Mais qu'y a t il dans le 34 ? Rien attendu : " << theboard.getNode(34)->getMarble() << endl;
        }
        else{
            cout << "dafuq" << endl;
        }

        cout << "Tentative de cout foireux : 64 vers 96" << endl;
        if(noir->move(theboard.getNode(64), theboard.getNode(96))){
            cout << "c'est pas normal" << endl;
        }
        else{
            cout << "ON BOUGE PAS NON MAIS" << endl;
        }

        cout << "Tentative de cout foireux : 120 vers 54" << endl;
        if(blanc->move(theboard.getNode(120), theboard.getNode(54))){
            cout << "c'est pas normal" << endl;
        }
        else{
            cout << "ON BOUGE PAS NON MAIS" << endl;
        }

        cout << "Tentative de cout foireux : 132 vers 131 mais pas le bon joueur" << endl;
        if(noir->move(theboard.getNode(120), theboard.getNode(54))){
            cout << "c'est pas normal" << endl;
        }
        else{
            cout << "ON BOUGE PAS NON MAIS" << endl;
        }


        cout << "end" << endl;                
        return 0;

}

