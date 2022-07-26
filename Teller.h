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

inline vector<string> Centence_Start = {
    "An ",  //name
    " ",     //name
    "Something came from the bush, a ",
    "\"Do i know you?\" says ",
}; 

inline vector<string> Friend_Mistakes = {
    /*Name */" had a brain fart and didnt remember that he was already friends with ",
    " had a dementia moment and forgot he was friends with ",
    " ?? ",
};

inline vector<string> Nonsentical = {
    " iwurbvkjbqrepevbkavbareivaebv ",
    " aaaaaaaaaaaaaaaaaaaaaaaaaaaaa ",
    " reeeeeeeeeeeeeeeeeeeeeeeeeeee ",
    " I lOvE iCeCrEaM!! ",
};

inline vector<string> Good_Bye = {
    " Didn't like vibe check with ",
    " Could not handle ",
};

inline vector<string> Succeeded = {
    " Succeeded to deploy ",
    " Pushed past limit and achieved ",
    " Got past and beyond ",
    " Achieved glimpse of infinity ",
};

inline vector<string> Failed = {
    " Had second toughts about ",
    " Didn't believe in himself ",
};

string Declare(Object* o);
void Slow_Talk(string text, int speed = 100);


#endif