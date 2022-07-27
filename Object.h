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
    PLAYER,
    DEAD,
};

enum class Behaviour{
    DEFENSIVE,
    PASSIVE,
    FAITHFULL,
    EVIL,
    AGGRESSIVE,
    TROLLER,
    MAD,
    COUNT,
};

enum class STATS{
    REJECTED,
    TOLERABLE,
    MEDIOCRE,
    SATISFYING,
    GUD_SOUP,
    GREAT, //Default
    HANDFUL,
    COUNT,
};

template<typename T>
T Random(){
    return (T)(rand() % (int)T::COUNT);
}

inline int Random(vector<string> names){
    return (int)(rand() % (int)names.size());
}

class Life_System{
public:
    STATS HP;
    STATS DEFENCE;
    STATS STRENGTH;
    STATS MANA;
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
    //                 friend, reputation
    vector<pair<class Object*, int>> Friends;

    Position Birth_Place;

    pair<class Object*, int> Find(Object* o);
};

class Object{
public:
    Position Position;
    Object_Type Type;
    Behaviour Behaviour;
    Life_System Life;
    Social Social;

    Object();

    Object(bool Extern);

    Object(int x, int y);

    Object(Object_Type t);

    static string Get_Color(Object* o);

    static string Get_Color(vector<Object*> o);

    static char Get_Marker(Object* o);

    static char Get_Marker(vector<Object*> o);

    void Charm(Object* o);

    void Turn(vector<Object*>& Enemies, vector<Object*>& Team);

    int AI_Turn(vector<Object*>& Enemies, vector<Object*>& Team);

    void Act(vector<Object*> Enemies, vector<Object*> Team);

    //Target, Action
    pair<int, int> AI_Act(vector<Object*> Enemies, vector<Object*> Team);

    void Sleep();

    void Run(vector<Object*>& Enemies, vector<Object*>& Team);

    bool Physical_Attack(Object* o);
    bool Spell_Attack(Object* o);
    bool Spell_Heal(Object* o);

    bool Over_Use_Magic();

    bool Say_Mad_Word();
};

#endif