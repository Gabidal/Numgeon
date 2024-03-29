#include <iostream>

#include "Campaing.h"
#include "Map.h"
#include "Globals.h"
#include "Console.h"
#include "Parse_Arguments.h"
#include "Teller.h"
#include "Construct.h"

#include <thread>
#include <chrono>


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
        cout << "4: Tasks              (" << Player->Social.Tasks.size() << ")\n";
        cout << "5: Exit campaing\n";
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
            vector<Object*> actors = World->At(Player->Position.X, Player->Position.Y);

            int Alive = 0;

            for (int i = 0; i < actors.size(); i++){
                if (actors[i]->Type != Object_Type::DEAD){
                    Alive++;
                }
                else{
                    actors.erase(actors.begin() + i--);
                }
            }

            if (Alive <= 1){
                cout << "There is nothing to act upon" << endl;
                continue;
            }

            Act(actors);
        }
        else if (Action == 4){
            Player->Social.List_Tasks(Player);
        }
        else if (Action == 5){
            return;
        }
        else{
            cout << "Invalid deed" << endl;
        }

        if (Action != 1 && Action != 4){
            //Update AI
            Update_World();
        }

    }

    cout << CONSOLE::RED << CONSOLE::Bold("YOU HAVE LOST!") << CONSOLE::RESET << endl;

    Player->Life.HP = STATS::SATISFYING;
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

                if (Player->Position.X + X < 0 || Player->Position.Y + Y < 0 || Player->Position.X + X > MAP_WIDTH || Player->Position.Y + Y > MAP_WIDTH){
                    cout << CONSOLE::BLUE << CONSOLE::Bold(string(1, Object::Get_Marker(Object_Type::WATER))) << CONSOLE::RESET;
                }
                else{
                    vector<Object*> Current_Objects = World->At(Player->Position.X + X, Player->Position.Y + Y);

                    cout << Object::Get_Color(Current_Objects) + Object::Get_Marker(Current_Objects) + CONSOLE::RESET;
                }
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

                Commands.erase(Commands.begin(), Commands.begin() +2);
            }
            else if (Commands[0] == "down"){
                Detect_Collision_X(o, o->Position.X + Amount);
                
                Commands.erase(Commands.begin(), Commands.begin() +2);
            }
            else if (Commands[0] == "left"){
                Detect_Collision_Y(o, o->Position.Y - Amount);

                Commands.erase(Commands.begin(), Commands.begin() +2);
            }
            else if (Commands[0] == "right"){
                Detect_Collision_Y(o, o->Position.Y + Amount);
                
                Commands.erase(Commands.begin(), Commands.begin() +2);
            }
            else{
                cout << "Invalid deed" << endl;

                Commands.erase(Commands.end());
            }

        }

    }

}

void CAMPAING::Act(vector<Object*> Entities){

    //First pronounce that an act has just started.
    cout << LINE << endl;

    //First get the name of the most aggresive entitie
    Object* Starter = nullptr;

    for (auto& i : Entities){
        if (!Starter)
            Starter = i;
        //The more aggresive behaviours are at higher value.
        else if (i->Behaviour > Starter->Behaviour)
            Starter = i;
    }

    //Now we can report who started this act.
    cout << Declare(Starter) << endl;
    cout << LINE << endl;

    Start_Friending(Entities);

    vector<vector<Object*>> Sides;

    //group the Sides by the friends list
    for (auto& i : Entities){
        vector<Object*> Side;

        for (auto& tmp_1 : Sides){
            for (auto& tmp_2 : tmp_1){
                if (i == tmp_2){
                    goto CONTINUE;
                }
            }
        }

        Side = {i};

        for (auto& j : i->Social.Friends){
            //check if his friend is already on another team
            for (auto& tmp_1 : Sides){
                for (auto& tmp_2 : tmp_1){
                    if (i == tmp_2){
                        goto SKIP;
                    }
                }
            }
            Side.push_back(j.first);
            SKIP:;
        }

        Sides.push_back(Side);

        CONTINUE:;
    }

    //Now that the sides are defined, we can start the battle.
    Battle(Sides);

    //Present the victorious side.
    cout << LINE << endl;
    if (Sides.size() > 0){
        cout << CONSOLE::GREEN << "The victorious side is team '" << Sides[0][0]->Social.Name << "'" << CONSOLE::RESET << endl;
    }
    else{
        cout << CONSOLE::MAGENTA << "There are no winners in war." << CONSOLE::RESET << endl;
    }


}

void CAMPAING::Battle(vector<vector<Object*>> Sides){

    bool Continue = true;

    while (Continue){
        //await orders to continue if there are stll participants left.
        Continue = false;


        for (int Team_A = 0; Team_A < Sides.size(); Team_A++){
            for (int Team_B = 0; Team_B < Sides.size(); Team_B++){
                if (Team_A == Team_B)
                    continue;

                //If there are still figthers, then continue the battle.
                Continue = true;

                cout << LINE << endl;
                cout << "Team '" << Sides[Team_A][0]->Social.Name << "' against team '" << Sides[Team_B][0]->Social.Name << "'" << endl;
                
                this_thread::sleep_for(chrono::milliseconds(TURN_SLEEP_TIME));

                Compete(Sides[Team_A], Sides[Team_B]);

                for (int a = 0; a < Sides[Team_A].size(); a++){
                    if (Sides[Team_A][a]->Life.HP == STATS::REJECTED){
                        Sides[Team_A][a]->Type = Object_Type::DEAD;
                        Sides[Team_A].erase(Sides[Team_A].begin() + a--);
                    }
                }

                if (Sides[Team_A].size() == 0){
                    Sides.erase(Sides.begin() + Team_A);

                    if (Team_A <= Team_B){
                        Team_B = max(--Team_B, 0);
                    }
                    
                    Team_A = max(--Team_A, 0);
                }

                for (int b = 0; b < Sides[Team_B].size(); b++){
                    if (Sides[Team_B][b]->Life.HP == STATS::REJECTED){
                        Sides[Team_B][b]->Type = Object_Type::DEAD;
                        Sides[Team_B].erase(Sides[Team_B].begin() + b--);
                    }
                }

                if (Sides[Team_B].size() == 0){
                    Sides.erase(Sides.begin() + Team_B);

                    if (Team_B <= Team_A){
                        Team_A = max(--Team_A, 0);
                    }

                    Team_B = max(--Team_B, 0);
                }

            }
        }
    }
}

void CAMPAING::Compete(vector<Object*>& A, vector<Object*>& B){
    for (int i = 0; i < A.size(); i++){
        cout << LINE << endl;
        cout << "It's " << A[i]->Social.Name << " turn." << endl;
    
        this_thread::sleep_for(chrono::milliseconds(TURN_SLEEP_TIME));

        A[i]->Turn(B, A);
    }
}

void CAMPAING::Start_Friending(vector<Object*> Entities){

    for (auto& A : Entities){
        
        this_thread::sleep_for(chrono::milliseconds(TURN_SLEEP_TIME));

        for (auto& B : Entities){
            if (A == B && A->Behaviour != Behaviour::MAD)
                continue;    //skip self friending. Unless mad.

            A->Charm(B);

        }
    }

}

int Sign(int X){
    return (X > 0) - (X < 0);
}

void CAMPAING::Detect_Collision_X(Object* o, int X){
    int Direction = Sign(X - o->Position.X);

    for (int Current_X = o->Position.X; Current_X != X;){
        vector<Object*> tiles = World->At(Current_X + Direction, o->Position.Y);

        //need to check only the first tile, since cant go ontop of another wall.
        if (tiles.size() > 0 && tiles[0]->Type == Object_Type::WALL){
            return;
        }

        Current_X += Direction;
        o->Position.X = Current_X;
    }
}

void CAMPAING::Detect_Collision_Y(Object* o, int Y){
    int Direction = Sign(Y - o->Position.Y);

    for (int Current_Y = o->Position.Y; Current_Y != Y;){
        vector<Object*> tiles = World->At(o->Position.X, Current_Y + Direction);

        //need to check only the first tile, since cant go ontop of another wall.
        if (tiles.size() > 0 && tiles[0]->Type == Object_Type::WALL){
            return;
        }

        Current_Y += Direction;
        o->Position.Y = Current_Y;
    }
}

void CAMPAING::Update_World(){
    for (int X = -RENDER_DISTANCE * 2; X <= RENDER_DISTANCE * 2; X++){
        for (int Y = -RENDER_DISTANCE * 2; Y <= RENDER_DISTANCE * 2; Y++){

            int Absolute_X = Player->Position.X + X;
            int Absolute_Y = Player->Position.Y + Y;

            vector<Object*> Results = World->At(Absolute_X, Absolute_Y);

            int Alive = 0;

            for (auto& o : Results){
                if (o->Type != Object_Type::DEAD){
                    Alive++;
                }

                if (o->Type == Object_Type::ENTITY || o->Type == Object_Type::PLAYER){
                    if (rand() % Task_Probability == 0){
                        Task* task = new Task(o);
                        o->Social.Tasks.push_back(task);
                    }
                }
            }

            if (Absolute_X == Player->Position.X && Absolute_Y == Player->Position.Y && Alive > 1){
                Act(Results);
            }
            else for (auto& tmp : Results){
                if ((tmp->Behaviour == Behaviour::AGGRESSIVE ||
                    tmp->Behaviour == Behaviour::MAD ||
                    tmp->Behaviour == Behaviour::TROLLER ||
                    tmp->Behaviour == Behaviour::EVIL
                    ) && tmp->Type != Object_Type::DEAD && tmp->Type == Object_Type::ENTITY){

                    //First get the distance to the player.
                    int Distance_X = Player->Position.X - tmp->Position.X;
                    int Distance_Y = Player->Position.Y - tmp->Position.Y;

                    Detect_Collision_X(tmp, tmp->Position.X + Distance_X);
                    Detect_Collision_Y(tmp, tmp->Position.Y + Distance_Y);

                }
            }
        }
    }
}