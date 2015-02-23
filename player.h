#ifndef PLAYER_H
#define PLAYER_H

#define PLAYERONE   1
#define PLAYERTWO   2
#define NBMARBLES   13

class Marble;
class Node;

class Player
{

private:
    Marble** disposition;
    int nbMarbles;
public:
    Player(int);
    ~Player();
    void displayMarbles(); // show marbles in console
    bool move(Node * src, Node * dst); // move a marble. Return false if impossible, true if move done.
    void computePossibilities();
};

#endif // PLAYER_H
