#include "Context.hpp"
#include "Globals.hpp"
#include <iostream>
#include <ncurses.h>

StartContext::StartContext()
    : task_view_(), last_key_(0)
{

}

void StartContext::handle_input()
{
    last_key_ = getch();
    switch(last_key_)
    {
        case 'k':
            task_view_.decrement_selection();
            break;
        case 'j':
            task_view_.increment_selection();
            break;
        default:
            break;
    }
}

void StartContext::draw() const
{
    clear();
    attron(COLOR_PAIR(Globals::DEFAULT_COLOR));
    mvwprintw(stdscr, 0, 0, "| Task ID | Title              | Detail             | Progress                |");
    mvwprintw(stdscr, 1, 0, "|---------|--------------------|--------------------|-------------------------|");
    task_view_.draw();
    refresh();
}

CONTEXT_ID StartContext::next() const
{
    switch(last_key_)
    {
        case 'q':
            return END;
            break;
        default:
            return START;
            break;
    }

}
