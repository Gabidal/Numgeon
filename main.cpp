#include <iostream>

#include "Parse_Arguments.h"
#include "Map.h"
#include "Campaing.h"

Object* Player;
bool Keep_Going = true;
Map* World;

void Lobby(){

    while (Keep_Going){

        cout << "What thy desire?\n";
        cout << "1: Campaing\n";
        cout << "2: Shop\n";
        cout << "3: Online\n";
        cout << "4: Cmd\n";
        cout << "5: Exit\n";
        cout << endl;

        string Answer = "";

        cin >> Answer;

        int tmp = stoi(Answer);

        if (tmp == 1){
            CAMPAING::Campaing();
        }
        else if (tmp == 2){
            
        }
        else if (tmp == 3){
            
        }
        else if (tmp == 4){
            
        }
        else if (tmp == 5){
            Keep_Going = false;
        }

    }


}

int main(int Argument_Count, char** Arguments){
    PARSE_ARGUMENTS::Parse_OS(Argument_Count, Arguments);
    World = new Map();

    *World->At(Player->Position.X, Player->Position.Y) = new Object(true);

    //Set the player to point into the map
    Player = World->At(Player->Position.X, Player->Position.Y);

    Lobby();

    return 0;

}