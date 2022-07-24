#ifndef _TELLER_H_
#define _TELLER_H_

#include <string>
#include <vector>

using namespace std;

class Object;

inline string GABE = "Gabe"; 
inline string S1MPLE = "S1mple";

inline vector<string> NAMES = {
    "Crab",
    "Troll",
    "Skeleton",
    S1MPLE,
    "Uncle",
    GABE,
    "Cow"
};

static vector<string> Centence_Start = {
    "An ",  //name
    " ",     //name
    "Something came from the bush, a ",
    "\"Do i know you?\" says ",
}; 

static string Declare(Object* o);


#endif