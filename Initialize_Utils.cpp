#include "Initialize_Utils.h"
#include "Globals.h"
#include "Console.h"


void INITIALIZE_UTILS::INIT(){

    if (OS == "win"){

        CONSOLE::RESET = "";
        CONSOLE::BLACK = "";
        CONSOLE::RED = "";
        CONSOLE::GREEN = "";
        CONSOLE::YELLOW = "";
        CONSOLE::BLUE = "";
        CONSOLE::MAGENTA = "";
        CONSOLE::CYAN = "";
        CONSOLE::WHITE = "";

    }
    else if (OS == "linux"){

        CONSOLE::RESET = "\e[0m";
        CONSOLE::BLACK = "\e[30m";
        CONSOLE::RED = "\e[31m";
        CONSOLE::GREEN = "\e[32m";
        CONSOLE::YELLOW = "\e[33m";
        CONSOLE::BLUE = "\e[34m";
        CONSOLE::MAGENTA = "\e[35m";
        CONSOLE::CYAN = "\e[36m";
        CONSOLE::WHITE = "\e[37m";

        CONSOLE::Bold = [](string Text){

            return string("\e[1m") + "\e" + Text;

        };

    }

}