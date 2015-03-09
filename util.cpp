#include "util.h"
#include "board.h"
#include "marble.h"
#include "player.h"
#include <iostream>
#include <fstream>

using namespace std;

Marble** Util::intToMarble = new Marble*[NB_TOTAL_MARBLE];
int Util::test = 0;

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
    Util::test++;
    if(index >= NB_TOTAL_MARBLE){
        return NULL;
    }else{
        return Util::intToMarble[index];
    }
}

bool Util::setMarbleInt(int index, Marble *marble){
    if(index >= NB_TOTAL_MARBLE){
        return false;
    }else{
        Util::intToMarble[index] = marble;
        return true;
    }
}

