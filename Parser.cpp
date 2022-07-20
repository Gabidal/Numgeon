#include "Parse_Arguments.h"
#include <vector>
#include <string> 

#include <iostream>
#include <functional>

#include "Globals.h"
#include "Object.h"
#include "Map.h"

using namespace std;


void PARSE_ARGUMENTS::Parse_OS(int Count, char** args){
    //change the char** into vector strings
    std::vector<std::string> Arguments;

    for(int i = 0; i < Count; i++){
        Arguments.push_back(args[i]);
    }

    //check if the OS is windows or linux
    for (auto arg : Arguments){
        if (arg == "linux"){
            OS = "linux";
        }
        else if (arg == "win"){
            OS = "win";
        }
    }
}

Position* PARSE_ARGUMENTS::Parse_String_To_Position(string text){
    while (text.size() < 2){
        cout << "Too short, grant me a longer one: ";
        cin >> text;
    }

    int Inter_Section = text.size() / 2;

    string X_String = "";
    string Y_String = "";

    X_String.insert(X_String.end(), text.begin(), text.begin() + Inter_Section);
    Y_String.insert(Y_String.end(), text.begin() + Inter_Section, text.end());

    int X = hash<string>{}(X_String) % MAP_WIDTH;
    int Y = hash<string>{}(Y_String) % MAP_WIDTH;

    return new Position{X, Y};
}