#include "Map.h"
#include "Globals.h"
#include "Construct.h"

vector<Object*> Map::At(int X, int Y){

    vector<Object*> Return_Objects;

    for(int i = 0; i < Objects.size(); i++){
        if(Objects[i]->Position.X == X && Objects[i]->Position.Y == Y){
            Return_Objects.push_back(Objects[i]);
        }
    }

    return Return_Objects;
}

void Map::Populate(){

    cout << "Loading...                 [Generating Map]" << endl;

    Construct C({{
        "#      #"
        "#      #"
        "#      #"
        "#      #"
        "        "
        "########"
        "        "
        "########",
        8, 8, 2
    },
    });

    cout << "Loading...                 [Populating Map]\n" << endl;


    for (int X = 0; X < MAP_WIDTH; X++){
        for (int Y = 0; Y < MAP_WIDTH; Y++){
            if (At(X, Y).size() != 0)
                continue;

            if ((rand() % Spawn_Probability) == 1){
                //If this is true, then there is no walls that this entity can accidentally spawn into.
                Object* o = new Object();
                o->Position.X = X;
                o->Position.Y = Y;

                Objects.push_back(o);
            }
        }
    }

}

