#include "Context.hpp"
#include "Globals.hpp"
#include <iostream>
#include <ncurses.h>

void StartContext::handle_input()
{
    last_key_ = getch();

}

void StartContext::draw() const
{
    attron(COLOR_PAIR(Globals::DEFAULT_COLOR));
    mvwprintw(stdscr, 0, 0, "| Task Title          | priority | Importance | Progress                |");
    mvwprintw(stdscr, 1, 0, "|---------------------|----------|------------|-------------------------|");
    refresh();
}

CONTEXT_ID StartContext::next() const
{
    switch(last_key_)
    {
        case 'q':
            return END;
        default:
            return START;
    }
}
