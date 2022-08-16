#ifndef _MAP_H_
#define _MAP_H_

#include "Object.h"

class Map{
public:
    vector<Object*> Objects;

    vector<string> Family_Tree;

    vector<Object*> At(int X, int Y);

    void Populate();
};

#endif