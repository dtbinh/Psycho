#ifndef MARBLE_H
#define MARBLE_H

#include "player.h"
#include <string>

using namespace std;

#define PSYCHOPATH 0
#define INFORMER 1
#define DOCTOR 2
#define PSYCHOLOGIST 3

#define NB_CROSSING_PATHS 3

class Path;

class Marble
{
public:
    Marble();
    Marble(int nodeId, int type);
    ~Marble();

    void computeAccessibleNodes();
    void setCurrentNode(int nodeId);
    void setOwner(Player*);
    void displayAccessibleNodes();

    int* getAccessibleNodes();
    int getCurrentNode();
    Player* getOwner();
    static string getNameFromType(int t);

    bool isCatch();

    int getType();

private:
    void computeAccessibleNodesForPath(Path*, int marbleId);
    int type;
    int* accessibleNodes; // nodes ids
    int nbComputedNodes;
    bool hadPsychologist;
    bool stuck;
    int myNode; // current node id
    Player* owner;
};

#endif // MARBLE_H
