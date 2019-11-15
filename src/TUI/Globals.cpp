#include "Globals.hpp"
#include "ncurses.h"

namespace Globals
{
    TaskDB taskdb;

    const std::array<Color, 3> ALL_COLOR{
        Color{DEFAULT_COLOR, COLOR_GREEN, COLOR_BLACK},
        Color{BORDER_COLOR, COLOR_WHITE, COLOR_BLACK},
        Color{WARNING_COLOR, COLOR_RED,   COLOR_BLACK}
    };
}
