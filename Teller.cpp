#include "Teller.h"
#include "Object.h"

string Declare(Object* o){
    string Result = "";
    Result += Centence_Start[Random(Centence_Start)];
    Result += o->Social.Name;
    Result += " That just appeard!";

    return Result;
}