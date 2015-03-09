#ifndef UTIL_H
#define UTIL_H

#include <string>
#include <cstdlib>

#define NB_TOTAL_MARBLE 26

class Player;
class Marble;
using namespace std;

class Util
{
public:
    static int split(int * destination, string chaine, char separateur);
    static bool updatePositionsTxt(Player * p1, Player * p2);
    static Marble** intToMarble;
    static Marble* getMarbleFromInt(int index);
    static bool setMarbleInt(int index, Marble* marble);

    static int test;
};

#endif // UTIL_H
