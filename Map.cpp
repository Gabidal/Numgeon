#include "Map.h"
#include "Globals.h"

vector<Object*> Map::At(int X, int Y){

    vector<Object*> Return_Objects;

    for(int i = 0; i < Objects.size(); i++){
        if(Objects[i]->Position.X == X && Objects[i]->Position.Y == Y){
            Return_Objects.push_back(Objects[i]);
        }
    }

    return Return_Objects;
}