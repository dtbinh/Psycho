#ifndef PATH_H
#define PATH_H



class Path
{
private :
    int * path; // A path is a list of nodes ids
    int nbNodes; // number of nodes

public:
    Path();
    Path(int * t, int nbNodes);
    ~Path();
    int getNodeId(int);
    int getNbNodes();
};

#endif // PATH_H
