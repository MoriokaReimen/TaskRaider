#include "Context.hpp"
#include <iostream>
#include <ncurses.h>

void StartContext::handle_input()
{
    last_key_ = getch();

}

void StartContext::draw() const
{
    mvaddstr(10, 20, "hello");
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
