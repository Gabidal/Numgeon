#include <iostream>

#include "Campaing.h"
#include "Map.h"
#include "Globals.h"
#include "Console.h"


extern Map* World;
extern Object* Player;
extern bool Keep_Going;

void CAMPAING::Campaing(){

    while (Player->Life.HP != STATS::REJECTED){

        cout << "What shall thou doth?";
        Player->Life.Report();

        string tmp = "";
        cout << "1: Map\n";
        cout << "2: Move\n";
        cout << "3: Act\n";
        cout << "4: Exit campaing\n";
        cout << ": ";
        cin >> tmp;
        cout << endl;

        int Action = stoi(tmp);

        if (Action == 1){
            Draw_Map();
        }
        else if (Action == 2){
            Move(Player);
        }
        else if (Action == 3){
            Act(Player);
        }
        else if (Action == 4){
            return;
        }
        else{
            cout << "Invalid deed" << endl;
        }
    }

}

void CAMPAING::Draw_Map(){

    for (int X = Player->Position.X -(RENDER_DISTANCE + 1); X < Player->Position.X + RENDER_DISTANCE; X++){

        for (int Y = Player->Position.Y -(RENDER_DISTANCE + 1); Y < Player->Position.Y + RENDER_DISTANCE; Y++){

            if (Y == -(RENDER_DISTANCE + 1)){
                cout << CONSOLE::BLACK << X << CONSOLE::RESET;
            }
            if (X == -(RENDER_DISTANCE + 1)){
                cout << CONSOLE::BLACK << Y << CONSOLE::RESET;
            }
            if (X != -(RENDER_DISTANCE + 1) && Y != -(RENDER_DISTANCE + 1)){
                Object* Current_Object = World->At(X, Y);
                cout << Object::Get_Color(Current_Object) + Object::Get_Marker(Current_Object) + CONSOLE::RESET;
            }
        }
        cout << endl;
    }
}

void CAMPAING::Move(Object* o){



}

void CAMPAING::Act(Object* o){



}
