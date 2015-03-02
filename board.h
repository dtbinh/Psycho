#ifndef BOARDS_H
#define BOARDS_H

#include <string>
#include "node.h"

#define BOARDNODES 162
#define BOARDSIZE 190
#define MAXPATHSIZE 50


class Path;
class Marble;

using namespace std;

const string DATA_PATH = "./data/";

class Board
{

private:
    //Board& operator=(const Board&){}
    //Board (const Board&){}

    static Board m_instance; // There is only one instance of the class Board, accessible with Instance()
    Board();
    ~Board();

    Node** nodes; // nodes
    Path** paths; // paths
    int nbPaths; // number of paths (27)
    int firstFreeDeadMarble;

public:
    static Board& Instance();
    int size();
    Node* getNode(int i);

    bool loadPaths(string file);
    Path* getPath(int i);
    Path** getPaths();
    int getNbPaths();

    bool killMarble(Marble * marbleToKill);

    void forceMove(Node * src, Node * dst); // move a marble without checking constraints

    void showPaths();
};

#endif // BOARDS_H
