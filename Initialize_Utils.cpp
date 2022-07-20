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
    else{

        CONSOLE::RESET = "\033[0m";
        CONSOLE::BLACK = "\033[30m";
        CONSOLE::RED = "\033[31m";
        CONSOLE::GREEN = "\033[32m";
        CONSOLE::YELLOW = "\033[33m";
        CONSOLE::BLUE = "\033[34m";
        CONSOLE::MAGENTA = "\033[35m";
        CONSOLE::CYAN = "\033[36m";
        CONSOLE::WHITE = "\033[37m";

        CONSOLE::Bold = [](string Text){

            return string("\033[1m") + Text;

        };

    }

}