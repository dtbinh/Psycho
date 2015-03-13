/**
    Psychopath - Board Game

    Copyright (C) <2015>  <Olivier Perriquet>

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


    static Marble** intToMarble;                            // an array of Marbles, constant array once initialised (by setMarbleInt() method)
    static Marble* getMarbleFromInt(int index);
    static bool setMarbleInt(int index, Marble* marble);
};

#endif // UTIL_H
