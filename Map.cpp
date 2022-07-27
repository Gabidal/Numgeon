#include "Map.h"
#include "Globals.h"

Map::Map(){

    int Entity_Count = 1000;
    Objects.resize(Entity_Count);

    for(int i = 0; i < Entity_Count; i++){
        Objects[i] = new Object();
        Objects[i]->Position.X = rand() % MAP_WIDTH;
        Objects[i]->Position.Y = rand() % MAP_WIDTH;
    }

}

vector<Object*> Map::At(int X, int Y){

    vector<Object*> Return_Objects;

    for(int i = 0; i < Objects.size(); i++){
        if(Objects[i]->Position.X == X && Objects[i]->Position.Y == Y){
            Return_Objects.push_back(Objects[i]);
        }
    }

    return Return_Objects;
}