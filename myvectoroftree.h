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

#ifndef MYVECTOROFTREE_H
#define MYVECTOROFTREE_H

#include "tree.h"

// the C structure that is used to implement this Vector
typedef struct node{
    Tree* data;
    node* next;
    node* previous;
    int index;
}node;

class MyVectorOfTree
{
public:
    MyVectorOfTree();
    MyVectorOfTree(Tree* t);
    ~MyVectorOfTree();

    bool initTree();
    Tree* getTree(int index);
    Tree* removeTree(Tree*);
    Tree* removeTree(int);
    bool addTree(Tree*);
    bool addTree(Tree*, int);

    int getIndexFromValue(Tree*);

    bool isEmpty();

    int size();

private:
    node* start;                // the first node of this Vector
};

#endif // MYVECTOROFTREE_H
