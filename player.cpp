#include "marble.h"
#include "player.h"
#include "board.h"
#include <cstdlib>



Player::Player(int player)
{
    if(player == PLAYERONE){
        Board& boardInstance = Board::Instance();
        this->disposition = new Marble*[NBMARBLES];
        disposition[0] = new Marble(56, PSYCHOPATH);
        boardInstance.getNode(56)->setMarble(disposition[0]);
        disposition[1] = new Marble(45, PSYCHOLOGIST);
        boardInstance.getNode(45)->setMarble(disposition[1]);
        disposition[2] = new Marble(121, PSYCHOLOGIST);
        boardInstance.getNode(121)->setMarble(disposition[2]);
        disposition[3] = new Marble(34, INFORMER);
        boardInstance.getNode(34)->setMarble(disposition[3]);
        disposition[4] = new Marble(35, INFORMER);
        boardInstance.getNode(35)->setMarble(disposition[4]);
        disposition[5] = new Marble(132, INFORMER);
        boardInstance.getNode(132)->setMarble(disposition[5]);
        disposition[6] = new Marble(133, INFORMER);
        boardInstance.getNode(133)->setMarble(disposition[6]);
        disposition[7] = new Marble(44, DOCTOR);
        boardInstance.getNode(44)->setMarble(disposition[7]);
        disposition[8] = new Marble(46, DOCTOR);
        boardInstance.getNode(46)->setMarble(disposition[8]);
        disposition[9] = new Marble(55, DOCTOR);
        boardInstance.getNode(55)->setMarble(disposition[9]);
        disposition[10] = new Marble(57, DOCTOR);
        boardInstance.getNode(57)->setMarble(disposition[10]);
        disposition[11] = new Marble(120, DOCTOR);
        boardInstance.getNode(120)->setMarble(disposition[11]);
        disposition[12] = new Marble(122, DOCTOR);
        boardInstance.getNode(122)->setMarble(disposition[12]);
    }else if(player == PLAYERTWO){
        Board& boardInstance = Board::Instance();
        this->disposition = new Marble*[NBMARBLES];
        disposition[0] = new Marble(76, PSYCHOPATH);
        boardInstance.getNode(76)->setMarble(disposition[0]);
        disposition[1] = new Marble(75, PSYCHOLOGIST);
        boardInstance.getNode(75)->setMarble(disposition[1]);
        disposition[2] = new Marble(77, PSYCHOLOGIST);
        boardInstance.getNode(77)->setMarble(disposition[2]);
        disposition[3] = new Marble(85, INFORMER);
        boardInstance.getNode(85)->setMarble(disposition[3]);
        disposition[4] = new Marble(74, INFORMER);
        boardInstance.getNode(74)->setMarble(disposition[4]);
        disposition[5] = new Marble(89, INFORMER);
        boardInstance.getNode(89)->setMarble(disposition[5]);
        disposition[6] = new Marble(78, INFORMER);
        boardInstance.getNode(78)->setMarble(disposition[6]);
        disposition[7] = new Marble(86, DOCTOR);
        boardInstance.getNode(86)->setMarble(disposition[7]);
        disposition[8] = new Marble(64, DOCTOR);
        boardInstance.getNode(64)->setMarble(disposition[8]);
        disposition[9] = new Marble(87, DOCTOR);
        boardInstance.getNode(87)->setMarble(disposition[9]);
        disposition[10] = new Marble(65, DOCTOR);
        boardInstance.getNode(65)->setMarble(disposition[10]);
        disposition[11] = new Marble(88, DOCTOR);
        boardInstance.getNode(88)->setMarble(disposition[11]);
        disposition[12] = new Marble(66, DOCTOR);
        boardInstance.getNode(66)->setMarble(disposition[12]);
    }else{

    }

    for(int i = 0; i < NBMARBLES; i++){
        disposition[i]->setOwner(this);
    }

    for(int i = 0; i < NBMARBLES; i++){
        disposition[i]->computeAccessibleNodes();
    }
}

Player::~Player()
{

}

void Player::displayMarbles(){
   string name;
   for(int i = 0; i < NBMARBLES; i++){
       name = Marble::getNameFromType(disposition[i]->getType());
       cout << "(" << name << ") " << disposition[i]->getCurrentNode() << endl;
       disposition[i]->displayAccessibleNodes();
   }
}


