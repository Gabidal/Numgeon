#include <iostream>

#include "Campaing.h"
#include "Map.h"
#include "Globals.h"
#include "Console.h"
#include "Parse_Arguments.h"


extern Map* World;
extern Object* Player;
extern bool Keep_Going;

void CAMPAING::Campaing(){

    while (Player->Life.HP != STATS::REJECTED){

        cout << LINE << endl;
        cout << "What shall thou doth?\n";
        Player->Life.Report();

        string tmp = "";
        cout << "1: Map\n";
        cout << "2: Move\n";
        cout << "3: Act\n";
        cout << "4: Exit campaing\n";
        cout << ": ";
        cin >> tmp;
        cout << endl;

        
        int Action;
        
        try{
            Action = stoi(tmp);
        } 
        catch (...){
            cout << "Invalid deed" << endl;
            continue;
        }

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

        //Update AI
        Update_World();

    }

}

void CAMPAING::Draw_Map(){

    for (int X = -(RENDER_DISTANCE + 1); X <= RENDER_DISTANCE; X++){
        if (X == -RENDER_DISTANCE){
            cout << CONSOLE::WHITE << X << CONSOLE::RESET;
        }
        else if (X == RENDER_DISTANCE){

            cout << " " + CONSOLE::WHITE << X << CONSOLE::RESET;

        }
        else if (X != -(RENDER_DISTANCE + 1)){
            cout << "   ";
        }

        for (int Y = -(RENDER_DISTANCE + 1); Y <= RENDER_DISTANCE; Y++){
            if (Y == -RENDER_DISTANCE && X == -(RENDER_DISTANCE + 1)){
                cout << CONSOLE::WHITE << Y << CONSOLE::RESET;
            }
            else if (Y == RENDER_DISTANCE && X == -(RENDER_DISTANCE + 1)){

                cout << CONSOLE::WHITE << Y << CONSOLE::RESET;

            }

            if (X == -(RENDER_DISTANCE + 1)){
                cout << " ";
            }


            if (X != -(RENDER_DISTANCE + 1) && Y !=  -(RENDER_DISTANCE + 1)){
                Object* Current_Object = World->At(Player->Position.X - X, Player->Position.Y - Y);
                cout << Object::Get_Color(Current_Object) + Object::Get_Marker(Current_Object) + CONSOLE::RESET;
            }

            cout << " ";
        }
        cout << endl;
    }
}

void CAMPAING::Move(Object* o){

    vector<string> Commands;

    if (o == Player){
        cout << LINE << endl;

        cout << "Where doth thou desire to move?" << endl;
        cout << CONSOLE::BLUE << CONSOLE::Bold("Syntax: up 10") << CONSOLE::RESET << endl;
        cout << ": " << endl;

        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    
        string tmp;
        getline(cin, tmp);
        
        Commands = PARSE_ARGUMENTS::Cut(tmp);
    }

    while (Commands.size() > 0){

        if (Commands.size() > 1){

            int Amount = stoi(Commands[1]);

            if (Commands[0] == "up"){
                Detect_Collision_X(o, o->Position.X - Amount);

                Commands.erase(Commands.end() - 2, Commands.end());
            }
            else if (Commands[0] == "down"){
                Detect_Collision_X(o, o->Position.X + Amount);
                
                Commands.erase(Commands.end() - 2, Commands.end());
            }
            else if (Commands[0] == "left"){
                Detect_Collision_X(o, o->Position.Y - Amount);

                Commands.erase(Commands.end() - 2, Commands.end());
            }
            else if (Commands[0] == "right"){
                Detect_Collision_X(o, o->Position.Y - Amount);
                
                Commands.erase(Commands.end() - 2, Commands.end());
            }
            else{
                cout << "Invalid deed" << endl;

                Commands.erase(Commands.end());
            }

        }

    }

}

void CAMPAING::Act(Object* o){



}

int Sign(int X){
    return (X > 0) - (X < 0);
}

void CAMPAING::Detect_Collision_X(Object* o, int X){
    int Direction = Sign(X - o->Position.X);

    for (int Current_X = o->Position.X; Current_X != X; Current_X += Direction){

        Object* tmp = World->At(Current_X, o->Position.Y);

        if (tmp && tmp->Type == Object_Type::WALL){
            return;
        }

        o->Position.X = Current_X;
    }
}

void CAMPAING::Detect_Collision_Y(Object* o, int Y){
    int Direction = Sign(Y - o->Position.Y);

    for (int Current_Y = o->Position.Y; Current_Y != Y; Current_Y += Direction){

        Object* tmp = World->At(o->Position.X, Current_Y);

        if (tmp && tmp->Type == Object_Type::WALL){
            return;
        }

        o->Position.Y = Current_Y;
    }
}

void CAMPAING::Update_World(){
    for (int X = -RENDER_DISTANCE * 2; X <= RENDER_DISTANCE * 2; X++){
        for (int Y = -RENDER_DISTANCE * 2; Y <= RENDER_DISTANCE * 2; Y++){
            Object* tmp = World->At(X, Y);
            if (tmp){

                if (tmp->Behaviour == Behaviour::AGGRESSIVE){

                    //First get the distance to the player.
                    int Distance_X = tmp->Position.X - Player->Position.X;
                    int Distance_Y = tmp->Position.Y - Player->Position.Y;

                    Detect_Collision_X(tmp, tmp->Position.X + Distance_X);
                    Detect_Collision_Y(tmp, tmp->Position.Y + Distance_Y);

                }

            }
        }
    }
}