#include "Util.hpp"
#include "Globals.hpp"
#include <ncurses.h>
#include <algorithm>
#include <array>

bool ok_dialogue(const std::string& message)
{
    bool ret = false;
    bool loop = true;
    const std::array<char, 2> YES{'Y', 'y'};
    const std::array<char, 2> NO{'N', 'n'};
    auto win = subwin(stdscr, 10, 30, 10, 10);
    wclear(win);
    wattron(win, COLOR_PAIR(Globals::DEFAULT_COLOR));
    box(win, 0, 0);

    while(loop)
    {
        char input = getch();
        mvwprintw(win, 2, 5, "%20s", message.c_str());
        mvwprintw(win, 3, 10, "Y/N?");

        if(std::any_of(YES.begin(), YES.end(), [&input](char x){return x == input;}))
        { /* received yes for message*/
            ret = true;
            loop = false;
        }else if(std::any_of(NO.begin(), NO.end(), [&input](char x){return x == input;}))
        { /* received no for message*/
            ret = false;
            loop = false;
        }
        wrefresh(win);

    }

    delwin(win);

    return ret;
}
