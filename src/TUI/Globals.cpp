#include "Globals.hpp"
#include "ncurses.h"

namespace Globals
{
TaskDB taskdb;

const std::array<Color, 10> ALL_COLOR{
    Color{DEFAULT_COLOR,  COLOR_GREEN,    COLOR_BLACK},
    Color{BORDER_COLOR,   COLOR_WHITE,    COLOR_BLACK},
    Color{WARNING_COLOR,  COLOR_RED,      COLOR_BLACK},
    Color{SELECT_COLOR,   COLOR_BLACK,    COLOR_GREEN},
    Color{RED_COLOR,      COLOR_RED,      COLOR_RED},
    Color{YELLOW_COLOR,   COLOR_YELLOW,   COLOR_YELLOW},
    Color{BLUE_COLOR,     COLOR_BLUE,     COLOR_BLUE},
    Color{HIGH_COLOR,     COLOR_RED,      COLOR_BLACK},
    Color{MIDDLE_COLOR,   COLOR_YELLOW,   COLOR_BLACK},
    Color{LOW_COLOR,      COLOR_BLUE,     COLOR_BLACK}
};
}
