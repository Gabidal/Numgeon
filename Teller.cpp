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



