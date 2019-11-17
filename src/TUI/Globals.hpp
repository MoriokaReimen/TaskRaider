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
enum COLOR_IDX {
    DEFAULT_COLOR = 1,
    BORDER_COLOR,
    WARNING_COLOR,
    SELECT_COLOR,
    RED_COLOR,
    YELLOW_COLOR,
    BLUE_COLOR
};
extern const std::array<Color, 7> ALL_COLOR;
}
