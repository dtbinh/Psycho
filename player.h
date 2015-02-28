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
    bool isHuman;
public:
    Player(int, bool);
    ~Player();
    void displayMarbles(); // show marbles in console
    string getStringMarblesForFile();
    bool move(Node * src, Node * dst); // move a marble. Return false if impossible, true if move done.    
    void computePossibilities();

    bool respawnUnit(Node * psychologistDeathNode, int marbleWanted);

    int getWhoAmI();

    // Check if psychopath is dead
    bool hasLost();

    // if human ask to play, else AI plays (doing a move)
    void play();
};

#endif // PLAYER_H
