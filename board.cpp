#include "node.h"
#include "marble.h"
#include "path.h"
#include "board.h"


#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <vector>

using namespace std;

Board Board::m_instance=Board();

Board::Board()
{    
    // Paths loading
    if(this->loadPaths(DATA_PATH + "paths.txt")){
        cout << "paths loaded" << endl;
    }
    else{
        cout << "fatal error : path of path file not found" << endl;
        exit(EXIT_FAILURE);
    }

    nodes = (Node**)malloc(sizeof(Node*) * BOARDSIZE);

    for(int i = 0 ; i <= 162 ; i++){
        // special nodes        
        if(i == 0 || i == 155 || i == 8 || i == 93 || i == 101 || i == 147){
            this->nodes[i] = new Node(i, NULL, true, false);
        }
        // others nodes
        else{
            this->nodes[i] = new Node(i, NULL, false, false);
        }
    }

    // nodes for dead marbles
    for(int i = 163 ; i <= BOARDSIZE - 1 ; i++){
        this->nodes[i] = new Node(i, NULL, false, true);
    }
}

Board::~Board()
{
    free(nodes);
    free(paths);
}

Board& Board::Instance(){
    return m_instance;
}

int split(int * destination, string chaine, char separateur)
{
    string::size_type stTemp = chaine.find(separateur);
    int i = 0;

    while(stTemp != string::npos)
    {
        destination[i] = atoi(chaine.substr(0, stTemp).c_str());
        chaine = chaine.substr(stTemp + 1);
        stTemp = chaine.find(separateur);
        i++;
    }

    destination[i] = atoi(chaine.c_str());

    return i+1;
}

bool Board::loadPaths(string file){
    ifstream fichier;
    fichier.open(file.c_str(), ios::in); // opening file in read only
    int * nodeList;

    if(fichier) // success
    {
        string line;
        // 1st line : number of path
        getline(fichier, line);

        this->nbPaths = atoi(line.c_str());

        this->paths = (Path**) malloc(sizeof(Path*) * nbPaths);
        nodeList = (int *) malloc(sizeof(int) * MAXPATHSIZE);

        cout << nbPaths << " paths found" << endl;

        while(!fichier.eof()){
            nodeList = (int *) malloc(sizeof(int) * MAXPATHSIZE);
            getline(fichier, line);
            string delimiter = " : ";
            string pathId = line.substr(0, line.find(delimiter));
            string rest = line.substr(line.find(delimiter)+3, line.length()); // +3 for the 2 spaces and the :
            int nbNodes;

            nbNodes = split(nodeList, rest, ' ');

            this->paths[atoi(pathId.c_str())] = new Path(nodeList, nbNodes);
        }

        fichier.close();

        return true;
    }
    else{
        cerr << "Error in file open" << endl;
        return false;
    }
}

Path* Board::getPath(int i){
    return paths[i];
}

Path** Board::getPaths(){
    return paths;
}

int Board::getNbPaths(){
    return this->nbPaths;
}

Node* Board::getNode(int i){
    return nodes[i];
}

int Board::size(){
    return BOARDSIZE;
}

