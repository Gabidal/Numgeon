#ifndef _CONSTRUCT_H_
#define _CONSTRUCT_H_

#include <string>
#include <vector>

#include <iostream>

using namespace std;

class Object;

enum class SIDE{
    TOP,
    BOTTOM,
    LEFT,
    RIGHT,
};

class Tile{
public:
    //Side, <Tile ID, Variation>
    vector<pair<SIDE, pair<int, int>>> Neighbours;

    int ID = 0;

    string Data = "";

};

class Tile_Set{
public:
    //rotations, and og tile
    vector<vector<Tile>> Tiles;

    string Data = "";

    int Data_Width = 0;
    int Data_Height = 0;

    int Tile_Width = 0;

    Tile_Set(string data, int data_height, int data_width, int tile_width){
        Data = data;
        Data_Height = data_height;
        Data_Width = data_width;
        Tile_Width = tile_width;

        if (Data_Width % 2 != 0 || Data_Height % 2 != 0){
            
            cout << "Error: Given string width and height were not even." << endl;

        }

        Convert();
    }

    void Convert();

    string Rotate_Data_Right(string data);

    vector<pair<SIDE, pair<int, int>>> Rotate_Neighbours_To_Right(vector<pair<SIDE, pair<int, int>>> n);
};

class Construct{
public:
    vector<Tile_Set> Tile_Sets;

    //<possible outcomes <tile ID, Variatino>>
    vector<vector<pair<int, int>>> Map;

    Construct(vector<Tile_Set> Data);

    void Wave_Function_Collapse();

    void Transform();

    vector<pair<pair<int, int>, pair<int, int>>>  Get_Surrounding_Neighbours(int X, int Y, Tile_Set* Current_Tile_Set, Tile* Current_Tile);

    static Object* Parse_Char(char Char);
};

#endif