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
        case 'c':
            return CREATE;
            break;
        default:
            return START;
            break;
    }

}

CreateContext::CreateContext()
    : last_key_(0)
{

}

void CreateContext::handle_input()
{
    last_key_ = getch();
    switch(last_key_)
    {
        case 'k':
            break;
        case 'j':
            break;
        default:
            break;
    }
}

void CreateContext::draw() const
{
    clear();
    attron(COLOR_PAIR(Globals::DEFAULT_COLOR));
    mvwprintw(stdscr, 0, 0, "Task ID: ");
    mvwprintw(stdscr, 1, 0, "Task TITLE: ");
    mvwprintw(stdscr, 2, 0, "Task DETAIL: ");
    mvwprintw(stdscr, 30, 0,"Task PROGRESS: ");
    refresh();
}

CONTEXT_ID CreateContext::next() const
{
    switch(last_key_)
    {
        case 'q':
            return START;
            break;
        default:
            return CREATE;
            break;
    }

}
