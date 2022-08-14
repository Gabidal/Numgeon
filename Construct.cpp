#include "Construct.h"
#include "Object.h"
#include "Map.h"
#include "Globals.h"

#include <unordered_map>

extern Map* World;

void Tile_Set::Convert(){
    //divides the given string into same proportional sizes (tiles)
    for (int i = 0; i < Data_Height; i += Tile_Width){
        for (int j = 0; j < Data_Width; j += Tile_Width){

            Tile New_Tile;

            for (int X = i; X < i + Tile_Width; X++){
                for (int Y = j; Y < j + Tile_Width; Y++){
                    New_Tile.Data += Data[X * Data_Width + Y];
                }
            }

            New_Tile.ID = Tiles.size();
            Tiles.push_back({New_Tile});
        }
    }
    
    int Tile_Horizontal_Count = Data_Width / Tile_Width;

    for (int X = 0; X < Tile_Horizontal_Count; X++){
        for (int Y = 0; Y < Tile_Horizontal_Count; Y++){

            Tile& Current_Tile = Tiles[X * Tile_Horizontal_Count + Y][0];

            //Check if left side if ok
            if (Y - 1 >= 0){
                Tile& Neighbouring_Tile = Tiles[X * Tile_Horizontal_Count + Y - 1][0];

                Current_Tile.Neighbours.push_back({SIDE::RIGHT, Neighbouring_Tile.ID, Neighbouring_Tile.Variation});
            }
            
            //Check if right side if ok
            if (Y + 1 < Tile_Horizontal_Count){
                Tile& Neighbouring_Tile = Tiles[X * Tile_Horizontal_Count + Y + 1][0];

                Current_Tile.Neighbours.push_back({SIDE::LEFT, Neighbouring_Tile.ID, Neighbouring_Tile.Variation});
            }
            
            //Check if top side if ok
            if (X - 1 >= 0){
                Tile& Neighbouring_Tile = Tiles[(X - 1) * Tile_Horizontal_Count + Y][0];

                Current_Tile.Neighbours.push_back({SIDE::TOP, Neighbouring_Tile.ID, Neighbouring_Tile.Variation});
            }
            
            //Check if bottom side if ok
            if (X + 1 < Tile_Horizontal_Count){
                Tile& Neighbouring_Tile = Tiles[(X + 1) * Tile_Horizontal_Count + Y][0];

                Current_Tile.Neighbours.push_back({SIDE::BOTTOM, Neighbouring_Tile.ID, Neighbouring_Tile.Variation});
            }

        }
    }


    int Og_Tiles_Count = Tiles.size();
    int Square_Side_Count = 3;

    //We are going to add now the rotation tile variants
    for (int i = 0; i < Og_Tiles_Count; i++){

        string Previus_Data = Tiles[i][0].Data;
        
        vector<Neighbour> Previus_Neighbours = Tiles[i][0].Neighbours;
         
        for (int Side = 0; Side < Square_Side_Count; Side++){
            Tile New_Tile;
            //Save the newly rotated data and carry it to next rotation to take it from.
            Previus_Data = New_Tile.Data = Rotate_Data_Right(Previus_Data);
            New_Tile.ID = Tiles.size();
            
            Previus_Neighbours = New_Tile.Neighbours = Rotate_Neighbours_To_Right(Previus_Neighbours);

            //Add the new variatino into the tile set.
            Tiles[i].push_back(New_Tile);
        }
    }
}

vector<Neighbour> Tile_Set::Rotate_Neighbours_To_Right(vector<Neighbour> n){

    vector<Neighbour> Result = n;

    for (int i = 0; i < n.size(); i++){

        switch (n[i].Side){
            case SIDE::TOP:
                Result[i].Side = SIDE::RIGHT;
                break;
            case SIDE::RIGHT:
                Result[i].Side = SIDE::BOTTOM;
                break;
            case SIDE::BOTTOM:
                Result[i].Side = SIDE::LEFT;
                break;
            case SIDE::LEFT:
                Result[i].Side = SIDE::TOP;
                break;
        }

    }

    return Result;
}

//This functino rotates the whole Data that is a square of characters by 90 degrees to the right.
string Tile_Set::Rotate_Data_Right(string data){

    //Rotating --> -->
    string Result = data;

    for (int Data_X = 0; Data_X < Tile_Width; Data_X++){

        for (int Data_Y = 0; Data_Y < Tile_Width; Data_Y++){
            
            Result[Data_X * Tile_Width + Data_Y] = data[(Tile_Width - Data_Y - 1) * Tile_Width + Data_X];

        }
    }

    return Result;
}

//This function starts from the 0, 0 coordinates and generates upto World_Width, World_Height
void Construct::Wave_Function_Collapse(){

    int Tile_Set_ID = 0;

    Tile_Set* Current_Set = &Tile_Sets[Tile_Set_ID];

    int Cell_Count_Horizontal = MAP_WIDTH / Current_Set->Tile_Width;

    Map.resize(pow(Cell_Count_Horizontal, 2));

    for (int X = 0; X < Cell_Count_Horizontal; X++){
        for (int Y = 0; Y < Cell_Count_Horizontal; Y++){
            //first we are going to populate the whole map with random noise.
            int Tile_ID = rand() % Current_Set->Tiles.size();
            int Tile_Variation = rand() % Current_Set->Tiles[Tile_ID].size();

            //Get the tile by id and variation
            Tile Tile = Current_Set->Tiles[Tile_ID][Tile_Variation];

            //Now populate the top, bottom right and left sides of these coordinates of this tile with its respectfull neighbour data.
            for (auto& i : Get_Surrounding_Neighbours(X, Y, Current_Set, &Tile)){
                
                Map[i.second.first * Cell_Count_Horizontal + i.second.second].push_back({i.first.ID, i.first.Variation});

            }
        }
    }

    //now that the map has been populated we can start the wave collaps part of the function.
    for (auto& i : Map){
        //This index has already collapsed.
        if (i.size() == 1)
            continue;
        	
        int Most_ID = 0;
        unordered_map<int, int> Most_Tile = {{0, 0}};

        for (auto& j : i){
            if (Most_Tile.find(j.first) != Most_Tile.end()){
                Most_Tile[j.first] += j.second;

                if (Most_Tile[Most_ID] < Most_Tile[j.first])
                    Most_ID = j.first;
            }
            else{
                Most_Tile[j.first] = j.second;

                if (Most_Tile[Most_ID] < Most_Tile[j.first])
                    Most_ID = j.first;
            }
        }

        //now that we know what tile to collapse into, we need to know what tile variation is the most likely to collapse.
        unordered_map<int, int> Most_Variation;
        int Most_Variation_ID = 0;

        for (auto& j : i){
            if (j.first != Most_ID)
                continue;

            if (Most_Variation.find(j.second) != Most_Variation.end()){
                Most_Variation[j.second] += j.second;

                if (Most_Variation[Most_Variation_ID] < Most_Variation[j.second])
                    Most_Variation_ID = j.second;
            }
            else{
                Most_Variation[j.second] = j.second;
                
                if (Most_Tile[Most_ID] < Most_Tile[j.first])
                    Most_ID = j.first;
            }
        }
        
        i.clear();

        i.push_back({Most_ID, Most_Variation_ID});
    }

}

void Construct::Transform(){

    int Tile_Set_ID = 0;

    Tile_Set* Current_Set = &Tile_Sets[Tile_Set_ID];

    int Chunk_Horizontal_Count = MAP_WIDTH / Current_Set->Tile_Width;

    for (int X = 0; X < Chunk_Horizontal_Count; X++){
        for (int Y = 0; Y < Chunk_Horizontal_Count; Y++){

            pair<int, int> Variation_Tile = Map[X * (Chunk_Horizontal_Count) + Y][0];

            Tile* Current_Tile = &Current_Set->Tiles[Variation_Tile.first][Variation_Tile.second];
            
            for (int Relative_X = 0; Relative_X < Current_Set->Tile_Width; Relative_X++){
                for (int Relative_Y = 0; Relative_Y < Current_Set->Tile_Width; Relative_Y++){

                    Object* Entity = Parse_Char(Current_Tile->Data[Relative_X * Current_Set->Tile_Width + Relative_Y]);

                    if (Entity){
                        //Chunk index_x * chunk_width + inside chunk index_x
                        Entity->Position.X = X * Current_Set->Tile_Width + Relative_X;
                        Entity->Position.Y = Y * Current_Set->Tile_Width + Relative_Y;

                        World->Objects.push_back(Entity);

                    }
                }
            }
        }
    }
}

Object* Construct::Parse_Char(char Char){

    if (Char == '#'){
        Object* tmp = new Object(Object_Type::WALL);
        tmp->Behaviour = Behaviour::COUNT;
        return tmp;
    }
    return nullptr;
}

//This function checks the compability of the tile set neighbours and the map location restrictinos to get the best neighbour set.
vector<pair<Neighbour, pair<int, int>>> Construct::Get_Surrounding_Neighbours(int X, int Y, Tile_Set* Current_Tile_Set, Tile* Current_Tile){
    //{{neighbour x, y}, {map x, y}}
    vector<pair<Neighbour, pair<int, int>>>  Result;

    int Cell_Width_Count = MAP_WIDTH / Current_Tile_Set->Tile_Width;

    vector<pair<SIDE, pair<int, int>>> Fitted_Sides;

    //Check if left side if ok
    if (Y - 1 >= 0){
        Fitted_Sides.push_back({SIDE::LEFT, {X, Y -1}});
    }
    
    //Check if right side if ok
    if (Y + 1 < Cell_Width_Count){
        Fitted_Sides.push_back({SIDE::RIGHT, {X, Y + 1}});
    }
    
    //Check if top side if ok
    if (X - 1 >= 0){
        Fitted_Sides.push_back({SIDE::TOP, {X - 1, Y}});
    }
    
    //Check if bottom side if ok
    if (X + 1 < Cell_Width_Count){
        Fitted_Sides.push_back({SIDE::BOTTOM, {X + 1, Y}});
    }
    
    for (auto& i : Fitted_Sides){
        for (auto& j : Current_Tile->Neighbours){
            if (i.first == j.Side){
                Result.push_back({j, {i.second.first, i.second.second}});
            }
        }
    }

    return Result;
}


Construct::Construct(vector<Tile_Set> Data){
    Tile_Sets = Data;

    Wave_Function_Collapse();

    Transform();
}