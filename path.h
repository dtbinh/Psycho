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
