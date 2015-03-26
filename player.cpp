/**
    Psychopath - Board Game

    Copyleft  (C) <2008>  <Olivier Perriquet> (Game conception)
    Copyright (C) <2015>  <Robache Alexis, Sévin Léo-Paul> (AI conception and implementation>

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.

*/

#include "marble.h"
#include "player.h"
#include "node.h"
#include "board.h"
#include "util.h"
#include "path.h"
#include "tree.h"
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <sstream>



/**
 * @brief Player::Player Initialize player
 * @param player Player 0 is human, player 1 is computer
 */
Player::Player(int player)
{
    string file = DATA_PATH + "marbles.txt";
    ifstream fichier;
    fichier.open(file.c_str(), ios::in); // opening file in read only
    Board& boardInstance = Board::Instance();
    whoAmI = player;
    nbMarbles = NBMARBLES;

    if(fichier) // success
    {
        string line;
        int dispId = 0; // id for disposition array
        int currentMarbleData[3]; // Array storing the line read
        nbMarbles = NBMARBLES;

        if(player == PLAYERONE || player == PLAYERTWO){
            this->disposition = new Marble*[nbMarbles];

            // reading marbles
            while(!fichier.eof()){
                // reading line by line
                getline(fichier, line);
                Util::split(currentMarbleData, line, ' ');

                // Check player ID
                if(currentMarbleData[0] == player){
                    disposition[dispId] = new Marble(currentMarbleData[1], currentMarbleData[2], this);
                    boardInstance.getNode(currentMarbleData[1])->setMarble(disposition[dispId]);
                    dispId++;
                }
            }
            for(int i = 0; i < nbMarbles; i++){
                Util::setMarbleInt(i + (player * 13), disposition[i]);
            }
        }
        else{
            cerr << "Error in Player initialization" << endl;
            exit(EXIT_FAILURE);
        }

        for(int i = 0; i < nbMarbles; i++){
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

/*void Player::play(){
    Board& boardInstance = Board::Instance();
    int idSrc;
    int idDst;
    bool correctMove = false;
    // HUMAN PLAYER
    if(this->whoAmI == PLAYERONE){
        while(!correctMove){
            cout << "Player " << this->whoAmI << " : Do a move !" << endl;
            cout << "From ?" << endl;
            cin >> idSrc;
            cout << "To ?" << endl;
            cin >> idDst;
            correctMove = this->move(boardInstance.getNode(idSrc), boardInstance.getNode(idDst));
            if(!correctMove){
                cout << "INCORRECT MOVE, please try again" << endl;
            }
        }

    }
    // AI PLAYER
    else{

    }
}*/

/**
 * @brief Player::getEnnemy get pointer of the other player
 * @return pointer of the other player
 */
Player * Player::getEnnemy(){return this->ennemy;}

/**
 * @brief Player::setEnnemy set pointer of the other player
 * @param p pointer of the other player
 */
void Player::setOpponent(Player * p){this->ennemy = p;}

/**
 * @brief Player::hasLost Check if psychopath is dead
 * @return true if player has lost
 */
bool Player::hasLost(){
    for(int i = 0 ; i < nbMarbles ; i++){
        if(disposition[i]->getType() == PSYCHOPATH){
            if(disposition[i]->isDead()){
                return true;
            }
        }
    }
    return false;
}

/**
 * @brief Player::move Check source node and destination node and do the move if possible.
 * @param src node where the marble is
 * @param dst node where the marble goes
 * @return false if invalid move
 */
bool Player::move(Node * src, Node * dst){
    Board& boardInstance = Board::Instance();
    // 0 if nodes exist
    if(!src || !dst){
        cout << "nodes doesn't exist !" << endl;
        return false;
    }
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
        for(int i = 0 ; i < src->getMarble()->getNbAccessibleNodes(); i++){
            // If dst found then it's correct
            if(correctDestinations[i] == dst->getId()){
                dstNodeIsCorrect = true;
            }
        }
        // 3 if correct, do the move
        if(dstNodeIsCorrect){
            boardInstance.forceMove(src, dst);
            // WHEN MOVED DO THE CHECKS
            boardInstance.checkDeaths(this, dst);
            return true;
        }
        else{
            cout << "Destination node invalid (" << dst->getId() << ")" << endl;
            return false;
        }
    }
    
    cout << "source node invalid (" << src->getId() << ")" << endl;
    return false;
}

/**
 * @brief Player::askRespawn allow player to respawn one of his marbles
 * @param psychologistDeathNode node where the psychologist died
 */
void Player::askRespawn(Node * psychologistDeathNode){
    int choice=0;
    if(this->whoAmI == PLAYERONE){
        cout << "Congrats, you can revive one of your marbles !" << endl;
        cout << "please type the number of the marble you want" << endl;
        cout << "1 - Informer" << endl;
        cout << "2 - Doctor" << endl;
        cout << "3 - Psychologist" << endl;
        cin >> choice;
    }
    else{

    }
    respawnUnit(psychologistDeathNode, choice);
}

/**
 * @brief Player::respawnUnit Move the first dead marble wanted encountered to the old psychologist node
 * @param psychologistDeathNode node where the psychologist died
 * @param marbleWanted ID of marble type wanted
 * @return false if can't
 */
bool Player::respawnUnit(Node * psychologistDeathNode, int marbleWanted){
    Board& boardInstance = Board::Instance();
    // Seek for the marble wanted
    for(int i = BOARDNODES + 1 ; i < BOARDSIZE ; i++){
        Marble * currentMarble = boardInstance.getNode(i)->getMarble();
        if(currentMarble){
            if(currentMarble->getType() == marbleWanted && currentMarble->getOwner() == this){
                cout << "Respawning " << Marble::getNameFromType(currentMarble->getType()) << " to node " << psychologistDeathNode->getId() << endl;
                boardInstance.forceMove(boardInstance.getNode(i), psychologistDeathNode);
                return true;
            }
        }
    }
    cout << "Couldn't respawn " << Marble::getNameFromType(marbleWanted) << endl;
    return false;
}

/**
 * @brief Player::computePossibilities
 * calls computeAccessibleNodes for each marble
 */
void Player::computePossibilities(){
    for(int i = 0 ; i < nbMarbles ; i++){
        disposition[i]->computeAccessibleNodes();
    }
}

/**
 * @brief Player::displayMarbles display all marbles with few informations in console
 */
void Player::displayMarbles(){
   string name;
   for(int i = 0; i < NBMARBLES; i++){
       name = Marble::getNameFromType(disposition[i]->getType());
       cout << "(" << name << ") " << disposition[i]->getMyNode() << endl;
       disposition[i]->displayAccessibleNodes();
   }
}

/**
 * @brief Player::getWhoAmI
 * @return PLAYERONE or PLAYERTWO
 */
int Player::getWhoAmI(){return whoAmI;}

/**
 * @brief Player::getStringMarblesForFile
 * @return string in marbles.txt format to write in currentGame.txt
 */
string Player::getStringMarblesForFile(){
    stringstream sstm;

    // Write player / NodeID / MarbleType
    for(int i = 0 ; i < nbMarbles ; i++){
        sstm << whoAmI << " " << disposition[i]->getMyNode() << " " << disposition[i]->getType() << endl;
    }
    return sstm.str();
}

/**
 * @brief Player::getDisposition
 * @return array of his marbles
 */
Marble** Player::getDisposition(){return this->disposition;}

