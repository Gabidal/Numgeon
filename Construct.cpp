#include "Construct.h"
#include "Object.h"
#include "Map.h"
#include "Globals.h"

extern Map* World;

void Construct::Generate(int X, int Y){

    for (int x = 0; x < Height; x++){
        for (int y = 0; y < Width; y++){
            Object* Tile = new Object(Parse_Char(Data[x * Width + y]));

            if (Tile->Type == Object_Type::AIR)
                continue;

            if (Tile->Type == Object_Type::COUNT)
                break;

            Tile->Position.X = X + x;
            Tile->Position.Y = Y + y;

            World->Objects.push_back(Tile);
        }
    }
    
}


Object Construct::Parse_Char(char Char){

    if (Char == '#'){
        Object tmp = Object(Object_Type::WALL);
        tmp.Behaviour = Behaviour::COUNT;
        return tmp;
    }
    else if (Char == ' '){
        return Object(Object_Type::AIR);
    }
    else 
        return Object(Object_Type::COUNT);

}