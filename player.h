#ifndef PLAYER_H
#define PLAYER_H

#define PLAYERONE   1
#define PLAYERTWO   2
#define NBMARBLES   13

class Marble;

class Player
{

private:
    Marble** disposition;
public:
    Player(int);
    ~Player();
    void displayMarbles();
};

#endif // PLAYER_H
