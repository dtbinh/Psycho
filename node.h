#ifndef NODE_H
#define NODE_H

#include "marble.h"

class Path;

class Node
{
private :
    int id; // number of node
    Marble* marble; // marble on the node, null if none
    //Path path; // list of reachable nodes from the node
    bool special; // true if "special" (on border)
    bool deadMarble; // not on board, nodes for dead marbles
    Path * path;

public:
    Node();
    Node(int , Marble* , bool , bool);
    ~Node();
    bool isSpecial();
    int getId();
    Marble* getMarble();
    void setMarble(Marble*);
    Path * getPath();
    void setPath(Path * p);
};

#endif // NODE_H
