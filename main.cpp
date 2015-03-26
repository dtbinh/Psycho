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
#include <cstdlib>
#include <ctime>

#include "util.h"
#include "game.h"

using namespace std;

int main()
{
   Game * game = new Game();

   game->testMinimax();

    // PArcourir tableau de char pour deplacer les marbles
    // getmarblefromint(i).setnodeid(char(i))

   //Util::updatePositionsTxt(white, black);
    
    //system("pause");
    cin.get();



    // main play method (if uncomment, also uncomment play() of Player)
    /**
    // boucle de jeu
    string winner;
    while(!white->hasLost() && !black->hasLost()){
        white->play();
        black->computePossibilities();
        white->computePossibilities();
        Util::updatePositionsTxt(white, black);
        if(!white->hasLost() && !black->hasLost()){
            black->play();
            black->computePossibilities();
            white->computePossibilities();
            Util::updatePositionsTxt(white, black);
        }
    }
    if(white->hasLost()){
        winner =  "black";
    }
    else{
        winner = "white";
    }

    cout << winner << " a gagné ! Vive " << winner << " !!!!" << endl;

    Util::updatePositionsTxt(white, black);

    //blanc->fillDecisionTree();
*/
    return 0;
}

