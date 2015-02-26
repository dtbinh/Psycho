#ifndef PLAYER_H
#define PLAYER_H

#define PLAYERONE   1
#define PLAYERTWO   2
#define NBMARBLES   13

#include <string>

using namespace std;

class Marble;
class Node;

class Player
{

private:
    Marble** disposition;
    int nbMarbles;
    int whoAmI;
public:
    Player(int);
    ~Player();
    void displayMarbles(); // show marbles in console
    string getStringMarblesForFile();
    bool move(Node * src, Node * dst); // move a marble. Return false if impossible, true if move done.    
    void computePossibilities();

    bool respawnUnit(Node * psychologistDeathNode, int marbleWanted);

    int getWhoAmI();
};

#endif // PLAYER_H
