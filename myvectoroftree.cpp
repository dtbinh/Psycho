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

#include "myvectoroftree.h"
#include <cstdlib>
#include <iostream>

using namespace std;

// Recursively set index of nodes
void setIndex(node* current){
    if(current != NULL){
        if(current->previous != NULL){
            current->index = current->previous->index + 1;
            setIndex(current->next);
        }else{
            current->index = 0;
        }
    }
}

// Recursively free the linkedList nodes
void setFree(node* current){
    if(current != NULL){
        node* tmp = current->next;
        free(current);
        setFree(tmp);
    }
}

MyVectorOfTree::MyVectorOfTree()
{
    node* beginning = new node;
    beginning->data = pT_NULL;
    beginning->next = NULL;
    beginning->previous = NULL;
    beginning->index = 0;
    this->start = beginning;
}

MyVectorOfTree::MyVectorOfTree(Tree* t)
{
    node* beginning = new node;
    beginning->data = t;
    beginning->next = NULL;
    beginning->previous = NULL;
    beginning->index = 0;
    this->start = beginning;
}

MyVectorOfTree::~MyVectorOfTree()
{

}

bool MyVectorOfTree::initTree(){
    setFree(this->start);
    node* beginning = new node;
    beginning->data = pT_NULL;
    beginning->next = NULL;
    beginning->previous = NULL;
    beginning->index = 0;
    this->start = beginning;

    return true;
}

// add a node to the queue of the linkedList, its data is equal to the parameter
bool MyVectorOfTree::addTree(Tree* p){
    if(this->start->data == NULL){
        this->start->data = p;
    }else{
        node* newNode = new node;
        newNode->data = p;
        newNode->next = NULL;
        node* current = this->start;
        while(current->next != NULL){
            current = current->next;
        }
        current->next = newNode;
        newNode->previous = current;
        newNode->index = current->index + 1;
    }
    return true;
}

// add a node in the position i of the linkedList, its data is equal to p
bool MyVectorOfTree::addTree(Tree* p,int i){
    node* newNode = new node;
    newNode->data = p;
    newNode->next = NULL;
    node* current = this->start;
    while(current->next != NULL && current->next->index != i){
        current = current->next;
    }
    newNode->previous = current;
    newNode->index = current->index + 1;
    if(newNode->index == i){
        newNode->next = current->next;
        current->next->previous = newNode;
        setIndex(newNode->next);
    }
    current->next = newNode;

    return true;
}

// find and return the data of the node of index searched, if no nodes have this index return null
Tree* MyVectorOfTree::getTree(int index){
    node* current = this->start;
    while(current->index != index && current->next != NULL){
        current = current->next;
    }
    if(current->index != index){
        return NULL;
    }else{
        return current->data;
    }
}

// Remove the node from the linkedList with data equal to the parameter, assure the integrity of the linkedList
Tree* MyVectorOfTree::removeTree(Tree* p){
    node* current = this->start;
    pTree value;
    while(current->data != p && current->next != NULL){
        current = current->next;
    }
    if(current->data != p){
        return NULL;
    }else{
        current->previous->next = current->next;
        current->next->previous = current->previous;
        setIndex(current->next);
        value = current->data;
        free(current);
        return value;
    }
}

Tree* MyVectorOfTree::removeTree(int i){
    node* current = this->start;
    pTree value;
    while(current->index != i && current->next != NULL){
        current = current->next;
    }
    if(current->index != i){
        return NULL;
    }else{
        current->previous->next = current->next;
        current->next->previous = current->previous;
        setIndex(current->next);
        value = current->data;
        free(current);
        return value;
    }
}


