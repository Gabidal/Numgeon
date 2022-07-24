#ifndef _OBJECT_H_
#define _OBJECT_H_

#include <string>
#include <vector>

using namespace std;

enum class Object_Type{
    ENTITY,
    WALL,
    AIR,
    WATER,
    ITEM,
    COUNT,
};

enum class Behaviour{
    DEFENSIVE,
    PASSIVE,
    FAITHFULL,
    EVIL,
    AGGRESSIVE,
    TROLLER,
    COUNT,
};

enum class STATS{
    HANDFUL,
    GREAT, //Default
    GUD_SOUP,
    SATISFYING,
    MEDIOCRE,
    TOLERABLE,
    REJECTED,
    COUNT,
};

template<typename T>
T Random(){
    return (T)(rand() % (int)T::COUNT);
}

int Random(vector<string> names){
    return (int)(rand() % (int)names.size());
}

class Life_System{
public:
    STATS HP;
    STATS DEFENCE;
    STATS ATTACK;
    STATS SPEED;
    STATS STAMINA;
    STATS IQ;

    Life_System();

    string Get_Stats(STATS sta);

    void Report();
};

class Position{
public:
    int X = 0;
    int Y = 0;

};

class Social{
public:
    string Name = "";
    string Hobby = "";
    vector<class Object*> Friends;

    Position Birth_Place;
};

class Object{
public:
    Object_Type Type;
    Behaviour Behaviour;
    Life_System Life;
    Social Social;
    Position Position;

    Object();

    Object(bool Extern);

    Object(int x, int y);

    static string Get_Color(Object* o);

    static string Get_Color(vector<Object*> o);

    static char Get_Marker(Object* o);

    static char Get_Marker(vector<Object*> o);
};

#endif