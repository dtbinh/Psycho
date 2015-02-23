#include "marble.h"
#include "player.h"
#include "node.h"
#include "board.h"
#include "util.h"
#include <cstdlib>
#include <iostream>
#include <fstream>



Player::Player(int player)
{
    string file = DATA_PATH + "marbles.txt";
    ifstream fichier;
    fichier.open(file.c_str(), ios::in); // opening file in read only

    if(fichier) // success
    {
        string line;
        // 1st line : number of marbles for player one
        getline(fichier, line);
        int playerOneMarbles = atoi(line.c_str());
        int playerTwoMarbles = 0;
        cout << "p1 " << playerOneMarbles << endl;
        int readingFinished = false; // set to true when all marbles have been read

        int dispId = 0; // id for disposition array

        int currentMarbleData[3];
        if(player == PLAYERONE){
            Board& boardInstance = Board::Instance();
            this->disposition = new Marble*[playerOneMarbles];
            while(!fichier.eof() && !readingFinished){
                // reading line by line
                getline(fichier, line);
                int nb = Util::split(currentMarbleData, line, ' ');
                // if only one number, is the playerTwo number of marbles so we stop the reading
                if(nb == 1){
                    readingFinished = true;
                }
                else{
                    disposition[dispId] = new Marble(currentMarbleData[1], currentMarbleData[2]);
                    boardInstance.getNode(currentMarbleData[1])->setMarble(disposition[dispId]);
                    dispId++;
                }
            }
            nbMarbles = playerOneMarbles;
        }
        else if(player == PLAYERTWO){
            // seek number of marbles for player 2
            for(int i = 0 ; i < playerOneMarbles ; i++){
                getline(fichier, line);
            }

            // After player 1 we have the number of marbles for player 2
            getline(fichier, line);
            playerTwoMarbles = atoi(line.c_str());
            cout << "p2 " << playerTwoMarbles << endl;

            Board& boardInstance = Board::Instance();
            this->disposition = new Marble*[playerTwoMarbles];
            while(!fichier.eof() && !readingFinished){
                // reading line by line
                getline(fichier, line);
                int nb = Util::split(currentMarbleData, line, ' ');
                disposition[dispId] = new Marble(currentMarbleData[1], currentMarbleData[2]);
                boardInstance.getNode(currentMarbleData[1])->setMarble(disposition[dispId]);
                dispId++;
            }
            nbMarbles = playerTwoMarbles;
        }
        else{
            // ?
            readingFinished = true;
        }

        for(int i = 0; i < NBMARBLES; i++){
            disposition[i]->setOwner(this);
        }
        fichier.close();
    }
    else{
        cerr << "Error in file open " << file << endl;
    }
}

Player::~Player()
{

}

// Check source node and destination node and do the move if possible. Return false if invalid move
bool Player::move(Node * src, Node * dst){
    // 1) if src node exists
    if(src->getMarble()){
        // if wrong owner
        if(src->getMarble()->getOwner() != this){
            cout << "invalid owner" << endl;
            return false;
        }
        // 2 : check the dst node
        bool dstNodeIsCorrect = false;
        int * correctDestinations = src->getMarble()->getAccessibleNodes();
        //cout << "checking " << src->getMarble()->getNbComputedNodes() << " nodes" << endl;
        for(int i = 0 ; i < src->getMarble()->getNbComputedNodes(); i++){
            // If dst found then it's correct
            if(correctDestinations[i] == dst->getId()){
                dstNodeIsCorrect = true;
            }
        }
        // 3 if correct, do the move
        if(dstNodeIsCorrect){
            dst->setMarble(src->getMarble());
            src->setMarble(NULL);
            dst->getMarble()->setCurrentNode(dst->getId());
            cout << "moved " << src->getId() << " to " << dst->getId() << endl;
        }
        else{
            cout << "Destination node invalid (" << dst->getId() << ")" << endl;
            return false;
        }
    }
    else{
        cout << "source node invalid (" << src->getId() << ")" << endl;
        return false;
    }
}

void Player::computePossibilities(){
    for(int i = 0 ; i < nbMarbles ; i++){
        disposition[i]->computeAccessibleNodes();
    }
}

void Player::displayMarbles(){
   string name;
   for(int i = 0; i < NBMARBLES; i++){
       name = Marble::getNameFromType(disposition[i]->getType());
       cout << "(" << name << ") " << disposition[i]->getCurrentNode() << endl;
       disposition[i]->displayAccessibleNodes();
   }
}


