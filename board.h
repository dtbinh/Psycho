#ifndef BOARDS_H
#define BOARDS_H

#include <iostream>
#include <string>
#include "node.h"

#define BOARDSIZE 190
#define MAXPATHSIZE 50

class Path;

using namespace std;

const string DATA_PATH = "../psychocpp/data/";

class Board
{


private:
    //Board& operator=(const Board&){}
    //Board (const Board&){}

    static Board m_instance;
    Board();
    ~Board();

    Node** nodes;
    Path** paths;
    int nbPaths;

public:
    static Board& Instance();
    int size();
    Node* getNode(int i);

    bool loadPaths(string file);
    Path* getPath(int i);
    Path** getPaths();
    int getNbPaths();
};

#endif // BOARDS_H
