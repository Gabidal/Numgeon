#include <iostream>

#include "Parse_Arguments.h"
#include "Map.h"
#include "Campaing.h"
#include "Initialize_Utils.h"
#include "Globals.h"
#include "Teller.h"
#include "Construct.h"

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

        int tmp;
        
        try{
            tmp = stoi(Answer);
        }
        catch(...){
            cout << "Invalid deed" << endl;
            continue;
        }

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

        cout << LINE << endl;

    }
}

int main(int Argument_Count, char** Arguments){
    srand(time(NULL));

    PARSE_ARGUMENTS::Parse_OS(Argument_Count, Arguments);
    INITIALIZE_UTILS::INIT();
    World = new Map();

    Player = new Object(true);

    World->Objects.push_back(Player);

    //Set the player to point into the map
    Player = World->Objects[World->Objects.size() - 1];

    World->Populate();

    Lobby();

    return 0;

}