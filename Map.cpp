#include "Map.h"
#include "Globals.h"

Map::Map(){

    int Entity_Count = 100;

    Objects.resize(Entity_Count);

    for(int i = 0; i < Entity_Count; i++){
        Objects[i].Position.X = rand() % MAP_WIDTH;
        Objects[i].Position.Y = rand() % MAP_WIDTH;
    }
}

Object* Map::At(int X, int Y){
    for (auto& i : Objects){
        if (i.Position.X == X && i.Position.Y == Y){
            return &i;
        }
    }
    return nullptr;
}