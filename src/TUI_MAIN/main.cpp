#include <iostream>
#include "Globals.hpp"

int main()
{
    while(Globals::tui.is_open()) {
        Globals::tui.update();
    }

    return 0;
}
