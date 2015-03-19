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

#include "util.h"
#include "board.h"
#include "marble.h"
#include "player.h"
#include <iostream>
#include <fstream>

using namespace std;

Marble** Util::intToMarble = new Marble*[NB_TOTAL_MARBLE];

int Util::split(int * destination, string chaine, char separateur)
{
    string::size_type stTemp = chaine.find(separateur);
    int i = 0;

    while(stTemp != string::npos)
    {
        destination[i] = atoi(chaine.substr(0, stTemp).c_str());
        chaine = chaine.substr(stTemp + 1);
        stTemp = chaine.find(separateur);
        i++;
    }

    destination[i] = atoi(chaine.c_str());

    return i+1;
}

bool Util::updatePositionsTxt(Player * p1, Player * p2){
    ofstream myfile;
    string filePath = DATA_PATH + "currentGame.txt";
    myfile.open(filePath.c_str(), ios::out);
      if (myfile.is_open())
      {
        // Writing player one marbles
        myfile << p1->getStringMarblesForFile();
        myfile << p2->getStringMarblesForFile();
        // Writing player two marbles
        myfile.close();
      }
      else cout << "Unable to open file";
    return false;
}

Marble* Util::getMarbleFromInt(int index){
    if(index >= NB_TOTAL_MARBLE){
        return NULL;
    }else{
        return Util::intToMarble[index];
    }
}

bool Util::setMarbleInt(int index, Marble* marble){
    if(index >= NB_TOTAL_MARBLE){
        return false;
    }else{
        Util::intToMarble[index] = marble;
        return true;
    }
}

