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

#ifndef PATH_H
#define PATH_H



class Path
{
private :
    int * path; // A path is a list of nodes ids
    int nbNodes; // number of nodes
    bool isBorder;

public:
    Path();
    Path(int * t, int nbNodes, bool isBorder);
    ~Path();
    int getNodeId(int);
    int getNbNodes();
    bool isTheBorder();
};

#endif // PATH_H
