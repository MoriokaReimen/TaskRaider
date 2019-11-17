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

    while(loop) {
        char input = getch();
        mvwprintw(win, 2, 5, "%20s", message.c_str());
        mvwprintw(win, 3, 10, "Y/N?");

        if(std::any_of(YES.begin(), YES.end(), [&input](char x) {
        return x == input;
    })) {
            /* received yes for message*/
            ret = true;
            loop = false;
        } else if(std::any_of(NO.begin(), NO.end(), [&input](char x) {
        return x == input;
    })) {
            /* received no for message*/
            ret = false;
            loop = false;
        }
        wrefresh(win);

    }

    delwin(win);

    return ret;
}

std::string line_dialogue(const std::string& message)
{
    char buff[512];
    auto win = subwin(stdscr, 6, 60, 10, 5);
    wclear(win);
    wattron(win, COLOR_PAIR(Globals::DEFAULT_COLOR));
    box(win, 0, 0);

    wattron(win, COLOR_PAIR(Globals::SELECT_COLOR));
    mvwprintw(win, 2, 3, "%-20s", message.c_str());
    mvwprintw(win, 3, 3, "Input line of String");
    wattron(win, COLOR_PAIR(Globals::DEFAULT_COLOR));
    wmove(win, 4, 3);
    echo();
    curs_set(1); // hide cursor
    wrefresh(win);

    wgetnstr(win, buff, 512);

    delwin(win);

    noecho();
    curs_set(0); // hide cursor

    return std::string(buff);
}

int int_dialogue(const std::string& message, const int& min, const int& max)
{
    bool loop = true;
    int ret = min;
    char buff[512];
    auto win = subwin(stdscr, 6, 60, 10, 5);

    while(loop) {
        wclear(win);
        wattron(win, COLOR_PAIR(Globals::DEFAULT_COLOR));
        box(win, 0, 0);
        wattron(win, COLOR_PAIR(Globals::SELECT_COLOR));
        mvwprintw(win, 2, 3, "%-20s", message.c_str());
        mvwprintw(win, 3, 3, "Input value from %5d to %5d", min, max);
        wattron(win, COLOR_PAIR(Globals::DEFAULT_COLOR));
        wmove(win, 4, 3);
        echo();
        curs_set(1); // hide cursor
        wrefresh(win);

        wgetnstr(win, buff, 512);
        try {
            std::string num(buff);
            ret  = std::stoi(num);
            ret = std::clamp(ret, min, max);
            loop = false;

        } catch(...) {
            // do nothing just retry

        }
    }

    delwin(win);

    noecho();
    curs_set(0); // hide cursor

    return ret;
}
