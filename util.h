#ifndef UTIL_H
#define UTIL_H

#include <string>
#include <cstdlib>

using namespace std;

class Util
{
public:
    Util();
    static int split(int * destination, string chaine, char separateur);
    ~Util();
};

#endif // UTIL_H
