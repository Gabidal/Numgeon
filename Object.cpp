#include "Object.h"
#include "Console.h"
#include "Parse_Arguments.h"
#include "Globals.h"
#include "Teller.h"

#include <iostream>
#include <map>

using namespace std;

extern Object* Player;

string Life_System::Get_Stats(STATS sta){

    switch (sta){
        case STATS::HANDFUL:
            return "Handful";
        case STATS::GREAT:
            return "Great";
        case STATS::GUD_SOUP:
            return "Gud Soup";
        case STATS::SATISFYING:
            return "Satisfying";
        case STATS::MEDIOCRE:
            return "Mediocre";
        case STATS::TOLERABLE:
            return "Tolerable";
        case STATS::REJECTED:
            return "Rejected";
        default:
            return "_@$NULL$#_";
    }

}

void Life_System::Report(){

    string Result = "";

    Result += CONSOLE::RED    + "HP: "  +       CONSOLE::Bold(Get_Stats(HP))      + CONSOLE::RESET + "\n"; 
    Result += CONSOLE::BLUE   + "DEF: " +       CONSOLE::Bold(Get_Stats(DEFENCE)) + CONSOLE::RESET + "\n"; 
    Result += CONSOLE::YELLOW + "STE: " +       CONSOLE::Bold(Get_Stats(STRENGTH))  + CONSOLE::RESET + "\n";
    Result += CONSOLE::YELLOW + "MAN: " +       CONSOLE::Bold(Get_Stats(MANA))  + CONSOLE::RESET + "\n";
    Result += CONSOLE::CYAN   + "SPE: " +       CONSOLE::Bold(Get_Stats(SPEED))   + CONSOLE::RESET + "\n"; 
    Result += CONSOLE::WHITE  + "STA: " +       CONSOLE::Bold(Get_Stats(STAMINA)) + CONSOLE::RESET + "\n"; 
    Result += CONSOLE::MAGENTA+ "IQ: "  +       CONSOLE::Bold(Get_Stats(IQ))      + CONSOLE::RESET + "\n"; 

    cout << Result << endl; 
}

Life_System::Life_System(){

    HP = Random<STATS>();
    DEFENCE = Random<STATS>();
    STRENGTH = Random<STATS>();
    MANA = Random<STATS>();
    SPEED = Random<STATS>();
    STAMINA = Random<STATS>();
    IQ = Random<STATS>();

}

pair<Object*, int> Social::Find(Object* o){
    for (auto& i : Friends){
        if (i.first == o){
            return i;
        }
    }

    return {nullptr, -1};
}

Object::Object(){

    Type = Random<Object_Type>();
    Behaviour = Random<enum class Behaviour>();
    Life = Life_System();

    Social.Name = NAMES[Random(NAMES)];

    Social.Birth_Place.X = rand() % MAP_WIDTH;
    Social.Birth_Place.Y = rand() % MAP_WIDTH;

}

Object::Object(bool Extern) : Object(){
    string tmp;

    //check if the object is going to be handled by a player or a computer
    if (Extern){
        cout << "Who thou to rule mine destiny? ";
        cin >> Social.Name;

        cout << "\nWhat are thy hobbies? ";
        cin >> tmp;

        cout << "\nI see, thou are a homeles man trying to get thy life back together." << endl;

        cout << "\nDoth thou  hast friends? ";
        cin >> tmp;

        cout << "\nI see, that thou are maidenles" << endl;

        tmp = "";

        cout << "\nOne moe question, whence hath thou born? ";
        cin >> tmp;

        Social.Birth_Place = *PARSE_ARGUMENTS::Parse_String_To_Position(tmp);
        Position = Social.Birth_Place;

        cout << "\nI until are from the '" << Social.Birth_Place.X << ", " << Social.Birth_Place.Y << "'\n";
        cout << LINE << endl;

        Type = Object_Type::PLAYER;
    }

}

Object::Object(int x, int y) : Object() {
    Position.X = x;
    Position.Y = y;
}

string Object::Get_Color(Object* o){
    if (o){
        if (o->Behaviour == Behaviour::PASSIVE){
            return CONSOLE::GREEN;
        }
        else if (o->Behaviour == Behaviour::AGGRESSIVE){
            return CONSOLE::RED;
        }
        else if (o->Behaviour == Behaviour::DEFENSIVE){
            return CONSOLE::BLUE;
        }
        else if (o->Behaviour == Behaviour::FAITHFULL){
            return CONSOLE::MAGENTA;
        }
        else if (o->Behaviour == Behaviour::EVIL){
            return CONSOLE::BLACK;
        }
        else if (o->Behaviour == Behaviour::TROLLER){
            return CONSOLE::CYAN;
        }
    }

    return CONSOLE::WHITE;
}

string Object::Get_Color(vector<Object*> o){
    if (o.size() == 0)
        return CONSOLE::WHITE;

    //        color, count
    map<int, int> Average;

    for (auto& i : o){

        if (Average.find((int)i->Behaviour) != Average.end()){
            Average[(int)i->Behaviour]++;
        }
        else{
            Average[(int)i->Behaviour] = 1;
        }

    }

    //now return the color that has the most count
    int Max = 0;
    ::Behaviour Color;

    for (auto& i : Average){
        if (i.second > Max){
            Max = i.second;
            Color = (::Behaviour)i.first;
        }
    }

    Object tmp;
    tmp.Behaviour = Color;

    return Get_Color(&tmp);
}

char Object::Get_Marker(Object* o){
    if (o){
        if (o->Type == Object_Type::PLAYER){
            return '^';
        }
        if (o->Type == Object_Type::ENTITY){
            return '@';
        }
        else if (o->Type == Object_Type::WALL){
            return '#';
        }
        else if (o->Type == Object_Type::AIR){
            return ' ';
        }
        else if (o->Type == Object_Type::WATER){
            return '~';
        }
        else if (o->Type == Object_Type::ITEM){
            return '?';
        }
    }
    return ' ';
}

char Object::Get_Marker(vector<Object*> o){
    if (o.size() == 0){
        return ' ';
    }
    else if (o.size() == 1){
        return Get_Marker(o[0]);
    }

    return (char)*to_string(o.size()).begin();
}

void Object::Charm(Object* o){
    //first check if this is already be friended with the object o.
    pair<Object*, int> Friend_Status = Social.Find(o);

    if (Friend_Status.second == 0){

        cout <<  Social.Name << Good_Bye[Random(Good_Bye)] << o->Social.Name << endl;

        for (int i = 0; i < Social.Friends.size(); i++){
            if (Social.Friends[i].first == 0){
                Social.Friends.erase(Social.Friends.begin() + i);
            }
        }

    }

    if (Friend_Status.first != nullptr){
        cout << Social.Name << Friend_Mistakes[Random(Friend_Mistakes)] << o->Social.Name << endl;

        return;
    }


    if (Behaviour == Behaviour::MAD){
        Slow_Talk(Social.Name + "Said" + Nonsentical[Random(Nonsentical)] + "to " + o->Social.Name + ".");
    }

    //Calculate the birth place position difference between the two entities
    int Distance = sqrt(pow(Social.Birth_Place.X - o->Social.Birth_Place.X, 2) + pow(Social.Birth_Place.Y - o->Social.Birth_Place.Y, 2));

    if (Distance >= MAP_WIDTH / 2){

        cout << Social.Name << " Tried to befriend " << o->Social.Name << " but to no vail" << endl;

        return;
    }
    else{

        cout << Social.Name << " Befriended " << o->Social.Name << endl;

        Social.Friends.push_back({o, 1});
    }

}

void Object::Turn(vector<Object*> Enemies, vector<Object*> Team){

    if (this == Player){
        cout << "What are thou going to try?" << endl;

        int Act_Index = 1;
        if (Behaviour != Behaviour::AGGRESSIVE && Behaviour != Behaviour::MAD){
            cout << Act_Index++ << ": Skip\n";
        }
        cout << Act_Index++ << ": Act\n";
        cout << Act_Index++ << ": Open Inventory\n";
        cout << Act_Index++ << ": Run\n";

        string Answer = "";

        cin >> Answer;

        if (Act_Index == 5){
            if (stoi(Answer) == 1){
                //Skip
            }
            else if (stoi(Answer) == 2){
                Act(Enemies, Team);
            }
            else if (stoi(Answer) == 3){
                //Open Inventory
            }
            else if (stoi(Answer) == 4){
                //Run
            }
        }
        else if (Act_Index == 4){
            if (stoi(Answer) == 1){
                Act(Enemies, Team);
            }
            else if (stoi(Answer) == 2){
                //Open Inventory
            }
            else if (stoi(Answer) == 3){
                //Run
            }
        }

    }
    else{
        int Choice = rand() % 4;

        if (Choice == 0){
            //Skip
        }
        else if (Choice == 1){
            Act(Enemies, Team);
        }
        else if (Choice == 2){
            //Open Inventory
        }
        else if (Choice == 3){
            //Run
        }
    }
}

void Object::Act(vector<Object*> Enemies, vector<Object*> Team){

    int Choise = 0;
    Object* Target = nullptr;

    if (this == Player){
        cout << LINE << endl;
        cout << "Enemies: \n";

        int Index = 0;
        for (auto& E : Enemies){
            cout << Index++ << Get_Color(E) << ": " << E->Social.Name << CONSOLE::RESET << endl;
        }

        cout << endl;
        cout << "Teamates: \n";

        for (auto& T : Team){
            cout << Index++ << Get_Color(T) << ": " << T->Social.Name << CONSOLE::RESET << endl;
        }

        cout << LINE << endl;
        cout << "Select target: ";

        string Answer = "";
        cin >> Answer;

        if (stoi(Answer) > Enemies.size() - 1){
            Target = Team[stoi(Answer) - (Enemies.size())];
        }
        else{
            Target = Enemies[stoi(Answer)];
        }

        TRY_AGAIN_PLAYER:;

        Life.Report();

        cout << CONSOLE::RED << "1: Physical Attack\n" << CONSOLE::RESET;
        cout << CONSOLE::MAGENTA << "2: Spell Attack\n" << CONSOLE::RESET;
        cout << CONSOLE::GREEN << "3: Spell Heal\n" << CONSOLE::RESET;

        
        cin >> Answer;
        Choise = stoi(Answer);

        if (Choise == 1){
            if (Physical_Attack(Target) == false)
                goto TRY_AGAIN_PLAYER;

            cout << Social.Name << " Used violence and harmed " << Target->Social.Name << " because of it." << endl; 
        }
        else if (Choise == 2){
            if (Spell_Attack(Target) == false)
                goto TRY_AGAIN_PLAYER;
                
            cout << Social.Name << " Used magic to harm " << Target->Social.Name << endl; 
        }
        else if (Choise == 3){
            if (Spell_Heal(Target) == false)
                goto TRY_AGAIN_PLAYER;
                
            cout << Social.Name << " Used magic to heal  " << Target->Social.Name << endl; 
        }
    }
    else{
        TRY_AGAIN_BOT:;

        Choise = rand() % 4;

        Target = Enemies[rand() % Enemies.size()];

        if (Choise == 1){
            if (Physical_Attack(Target) == false)
                goto TRY_AGAIN_BOT;

            cout << Social.Name << " Used violence and harmed " << Target->Social.Name << " because of it." << endl; 
        }
        else if (Choise == 2){
            if (Spell_Attack(Target) == false)
                goto TRY_AGAIN_BOT;
                
            cout << Social.Name << " Used magic to harm " << Target->Social.Name << endl; 
        }
        else if (Choise == 3){
            if (Spell_Heal(Target) == false)
                goto TRY_AGAIN_BOT;
                
            cout << Social.Name << " Used magic to heal  " << Target->Social.Name << endl; 
        }
    }

}

bool Object::Physical_Attack(Object* o){
    o->Life.HP = (STATS)((int)o->Life.HP - ((int)Life.STRENGTH / ((int)STATS::COUNT / 2) / ((int)o->Life.DEFENCE + 1)));

    return true;
}

bool Object::Spell_Attack(Object* o){
    int HP = (int)o->Life.HP;

    int Mana = (int)Life.MANA;

    if (Mana - (int)Life.STRENGTH <= 0 && Mana != 0){
        if (Over_Use_Magic() == false){
            return false;
        }
    }
    else{
        Mana -= (int)Life.STRENGTH;
    }

    HP -= ((int)Life.STRENGTH / ((int)STATS::COUNT / 2) / ((int)o->Life.DEFENCE + 1));

    o->Life.HP = (STATS)HP;

    Life.MANA = (STATS)Mana;

    return true;
}

bool Object::Spell_Heal(Object* o){
    int HP = (int)o->Life.HP;

    int Mana = (int)Life.MANA;

    if (Mana - (int)Life.STRENGTH <= 0 && Mana != 0){
        if (Over_Use_Magic() == false){
            return false;
        }
    }
    else{
        Mana -= (int)Life.STRENGTH;
    }

    HP += ((int)Life.STRENGTH / ((int)STATS::COUNT / 2));

    o->Life.HP = (STATS)HP;

    Life.MANA = (STATS)Mana;

    return true;
}

bool Object::Over_Use_Magic(){
    bool Try_Use = false;

    if (this == Player){
        cout << CONSOLE::YELLOW;
        Slow_Talk("Thou dont hast enough mana. Using this spell shall greatly cripple thy performance.");
        cout << CONSOLE::RESET << endl;

        cout << "1: Use\n";
        cout << "2: Don't\n";

        string Answer = "";
        cin >> Answer;
        

        if (stoi(Answer) == 1){
            Try_Use = true;
        }
        else{
            return false;
        }

    }
    else{
        //AI
    }


    int Probability_Of_Success = (int)Life.IQ + (int)Life.MANA * 10;

    int Success = rand() % 100;

    if (Probability_Of_Success >= Success){
        cout << Social.Name << Succeeded[Random(Succeeded)] << "the attack spell" << endl;
        
    }

    //Mana = empty
    Life.MANA = (STATS)(STATS::REJECTED);
    //sacrifice stamina and HP.
    Life.HP = (STATS)((int)Life.HP - 1);
    Life.STAMINA = (STATS)((int)Life.STAMINA / 2);
    
    //experience new thing.
    Life.IQ = (STATS)((int)Life.IQ + 1);
}
