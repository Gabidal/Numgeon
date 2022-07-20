#ifndef _MAP_H_
#define _MAP_H_

#include "Object.h"

class Map{
public:
    vector<Object> Objects;

    Map();

    Object* At(int X, int Y);
};

#endif