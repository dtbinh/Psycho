/**
    Psychopath - Board Game

    Copyright (C) <2015>  <Olivier Perriquet>

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



// set human to true if human, false if AI
/**
 * @brief Player::Player constructor of Player class, use a text file to load its Marble positions
 * @param player the Integer representation of the Player (cf. Player.h file)
 * @param human the boolean that indicate if the Player is human or AI
 */
Player::Player(int player, bool human)
{
    this->isHuman = human;
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
            whoAmI = PLAYERONE;
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
            for(int i = 0; i < nbMarbles; i++){
                Util::setMarbleInt(i, disposition[i]);
            }
        }
        else if(player == PLAYERTWO){
            whoAmI = PLAYERTWO;
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
                Util::split(currentMarbleData, line, ' ');
                disposition[dispId] = new Marble(currentMarbleData[1], currentMarbleData[2]);
                boardInstance.getNode(currentMarbleData[1])->setMarble(disposition[dispId]);
                dispId++;
            }
            nbMarbles = playerTwoMarbles;
            for(int i = 0; i < nbMarbles; i++){
                Util::setMarbleInt(i+13, disposition[i]);
            }
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

/**
 * @brief Player::play if this Player is human, will ask a move from this Player via the terminal
 * TODO the AI Player
 */
void Player::play(){
    Board& boardInstance = Board::Instance();
    int idSrc;
    int idDst;
    bool correctMove = false;
    // HUMAN PLAYER
    if(this->isHuman){
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
}

/**
 * @brief Player::getEnnemy getter of ennemy attribute
 * @return the Player, opponent of this Player of this game
 */
Player * Player::getEnnemy(){
    return this->ennemy;
}

/**
 * @brief Player::setEnnemy setter of ennemy attribute
 * @param p the Player, opponent of this Player of this game
 */
void Player::setEnnemy(Player * p){
    this->ennemy = p;
}

/**
 * @brief Player::hasLost Check if PSYCHOPATH is dead
 * @return true if this Player's PSYCHOPATH is dead
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
 * @brief Player::move Check source Node and destination Node and do the move if possible
 * @param src the Node that contains the Marble this Player wants to move
 * @param dst the Node where this Player wants to move the Marble contained in src
 * @return false if this move is invalid : comments in code express the reasons of this invalidity
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
        for(int i = 0 ; i < src->getMarble()->getNbComputedNodes(); i++){
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
    else{
        cout << "source node invalid (" << src->getId() << ")" << endl;
        return false;
    }
    return false;
}

/**
 * @brief Player::askRespawn ask this player if he wants to respawn one of its Marbles (called when this Player kills a opponent's PSYCHOLOGIST
 * @param psychologistDeathNode the Node that contained the dead PSYCHOLOGIST
 */
void Player::askRespawn(Node * psychologistDeathNode){
    int choice=0;
    if(this->isHuman){
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

// Move the first dead marble wanted encountered to the old psychologist node
// return false if can't
/**
 * @brief Player::respawnUnit move the first dead marble wanted encountered to the old PSYCHOLOGIST's Node
 * @param psychologistDeathNode the Node that contained the dead PSYCHOLOGIST
 * @param marbleWanted an integer that represent the type of Marble wanted (cf. Marble.h file)
 * @return false if no Marble of this Type is available
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
 * @brief Player::computePossibilities compute all the possible action this Player can take according to this game's rules
 * side effect of this method : call each of this Player's Marble's computeAccessibleNodes() method
 */
void Player::computePossibilities(){
    for(int i = 0 ; i < nbMarbles ; i++){
        disposition[i]->computeAccessibleNodes();
    }
}

/**
 * @brief Player::displayMarbles for debug purpose only
 * side effect of this method : display this Player's Marbles,
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
 * @return the integer that represent this Player status : 1 if PLAYERONE, 2 if PLAYERTWO
 */
int Player::getWhoAmI(){
    return whoAmI;
}

// affiche au format des fichiers txt de marbles
/**
 * @brief Player::getStringMarblesForFile create a string to the format of text files containing the Marbles information
 * @return the string representation of this Player's Marble
 */
string Player::getStringMarblesForFile(){
    stringstream sstm;
    // 1) nbMarbles
    sstm << nbMarbles << endl;
    // 2) Write player / NodeID / MarbleType
    for(int i = 0 ; i < nbMarbles ; i++){
        sstm << whoAmI << " " << disposition[i]->getMyNode() << " " << disposition[i]->getType() << endl;
    }


    return sstm.str();
}

void Player::fillDecisionTree(){
    this->displayMarbles();

    Tree* root = new Tree();
    root->createNextSons(0);
    Tree* son;
    Marble* currentMarble;
    for(int i = 0; i < this->nbMarbles; i++){
        currentMarble = this->disposition[i];
        for(int j = 0; j < currentMarble->getNbComputedNodes(); j++){
            son = new Tree(root, new Move(currentMarble->getMyNode(), currentMarble->getAccessibleNodes()[j]));
            root->addSon(son);
        }
    }

    root->displayTree();
}
