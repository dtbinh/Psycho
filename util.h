#ifndef UTIL_H
#define UTIL_H

#include <string>
#include <cstdlib>

class Player;
using namespace std;

class Util
{
public:
    Util();
    static int split(int * destination, string chaine, char separateur);
    static bool updatePositionsTxt(Player * p1, Player * p2);
    ~Util();
};

#endif // UTIL_H
