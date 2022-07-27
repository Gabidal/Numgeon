#ifndef _CONSTRUCT_H_
#define _CONSTRUCT_H_

#include <string>
#include <vector>

using namespace std;

class Object;

class Construct
{
public:
    string Data;    //Constains ascii house data

    int Width;
    int Height;

    Construct(string Data, int Width) : Data(Data), Width(Width), Height(Height){}

    Construct(string Data, int Width, int Height) : Data(Data), Width(Width), Height(Height){}

    void Generate(int X, int Y);

    static Object* Parse_Char(char Char);
};

inline vector<Construct*> CONSTRUCTS = {
    new Construct{
        string(
            "##########"
            "#        #"
            "#        #"
            "#        #"
            "####  ####"
        ),
        10,
        5,
    },

    new Construct{
        string(
            "#"
            "#"
            "#"
            "#"
            "#"
            "#"
            "#"
            "#"
            "#"
            "#"
        ),
        1,
        10,
    },

    new Construct{
        string(
            "##########"
        ),
        10,
        1,
    },

};

#endif