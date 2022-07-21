#include "Object.h"
#include "Console.h"
#include "Parse_Arguments.h"
#include "Globals.h"

#include <iostream>

using namespace std;

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
    Result += CONSOLE::YELLOW + "ATC: " +       CONSOLE::Bold(Get_Stats(ATTACK))  + CONSOLE::RESET + "\n";
    Result += CONSOLE::CYAN   + "SPE: " +       CONSOLE::Bold(Get_Stats(SPEED))   + CONSOLE::RESET + "\n"; 
    Result += CONSOLE::WHITE  + "STA: " +       CONSOLE::Bold(Get_Stats(STAMINA)) + CONSOLE::RESET + "\n"; 
    Result += CONSOLE::MAGENTA+ "IQ: "  +       CONSOLE::Bold(Get_Stats(IQ))      + CONSOLE::RESET + "\n"; 

    cout << Result << endl; 
}

Life_System::Life_System(){

    HP = Random<STATS>();
    DEFENCE = Random<STATS>();
    ATTACK = Random<STATS>();
    SPEED = Random<STATS>();
    STAMINA = Random<STATS>();
    IQ = Random<STATS>();

}

Object::Object(){

    Type = Random<Object_Type>();
    Behaviour = Random<enum class Behaviour>();
    Life = Life_System();

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

char Object::Get_Marker(Object* o){
    if (o){
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

