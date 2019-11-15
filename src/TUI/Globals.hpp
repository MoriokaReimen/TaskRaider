#pragma once
#include "TaskDB/TaskDB.hpp"
#include <array>

namespace Globals
{
    extern TaskDB taskdb;
    struct Color {
        int idx;
        int fg;
        int bg;
    };
    enum COLOR_IDX
    {
        DEFAULT_COLOR = 1,
        BORDER_COLOR,
        WARNING_COLOR
    };
    extern const std::array<Color, 3> ALL_COLOR;
}
