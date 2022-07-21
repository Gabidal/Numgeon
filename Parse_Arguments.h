#ifndef _PARSE_ARGUMENTS_H_
#define _PARSE_ARGUMENTS_H_

#include <string> 
#include <vector>

using namespace std;

class Position;

namespace PARSE_ARGUMENTS{
    void Parse_OS(int Count, char** args);
    Position* Parse_String_To_Position(string text);
    vector<string> Cut(string raw);
}

#endif