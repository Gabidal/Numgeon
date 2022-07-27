#include "Construct.h"
#include "Object.h"
#include "Map.h"
#include "Globals.h"

extern Map* World;

void Construct::Generate(int X, int Y){

    for (int x = 0; x < Height; x++){
        for (int y = 0; y < Width; y++){
            Object* Tile = Parse_Char(Data[x * Width + y]);

            if (Tile == nullptr)
                continue;

            Tile->Position.X = X + x;
            Tile->Position.Y = Y + y;

            World->Objects.push_back(Tile);
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