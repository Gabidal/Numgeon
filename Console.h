#ifndef _CONSOLE_H_
#define _CONSOLE_H_

#include <string>

using namespace std;

namespace CONSOLE{

    inline string RESET = "";
    inline string BLACK = "";
    inline string RED = "";
    inline string GREEN = "";
    inline string YELLOW = "";
    inline string BLUE = "";
    inline string MAGENTA = "";
    inline string CYAN = "";
    inline string WHITE = "";

    inline string (*Bold)(string Text);

}

#endif