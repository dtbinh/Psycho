#include "util.h"
#include <iostream>

Util::Util()
{

}

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

Util::~Util()
{

}

