#include "Teller.h"
#include "Object.h"

#include <iostream>
#include <thread>
#include <chrono>

using namespace std;

string Declare(Object* o){
    string Result = "";
    Result += Centence_Start[Random(Centence_Start)];
    Result += o->Social.Name;
    Result += " That just appeard!";

    return Result;
}

void Slow_Talk(string text, int speed){
    for (int i = 0; i < text.size(); i++){
        cout << text[i];
        this_thread::sleep_for(chrono::milliseconds(speed));
    }
}

string Generate_Name(Object* o){
    int Name_Length = rand() % (Name_Parts.size() / 2);

    string Result = "";

    for(int i = 0; i < Name_Length; i++){
        if (rand() % 5 == 0 && Result.size() > 0){
            Result += " ";
        }

        Result += Name_Parts[Random(Name_Parts)];
    }

    return Result;
}

