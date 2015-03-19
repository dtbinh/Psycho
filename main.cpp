/**
    Psychopath - Board Game

    Copyleft  (C) <2008>  <Olivier Perriquet> (Game conception)
    Copyright (C) <2015>  <Robache Alexis, Sévin Léo-Paul> (AI conception and implementation>

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.

*/

#include <iostream>
#include "util.h"
#include "board.h"
#include "player.h"
#include "path.h"
#include "tree.h"
#include "minimax.h"
#include "myvectoroftree.h"
#include "minimax.h";
#include <cstdlib>
#include <ctime>

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



    Minimax* mini = new Minimax();
    MyVectorOfTree* tmp = mini->initParcours(blanc);
    mini->bestTree(blanc, tmp, time(0));



    // PArcourir tableau de char pour deplacer les marbles
    // getmarblefromint(i).setnodeid(char(i))

   Util::updatePositionsTxt(blanc, noir);
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

    //blanc->fillDecisionTree();

    return 0;
}

