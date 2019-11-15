#include "Context.hpp"
#include <iostream>
#include <ncurses.h>

void StartContext::handle_input()
{

}

void StartContext::draw() const
{
    mvaddstr(10, 20, "hello");
    refresh();
}

CONTEXT_ID StartContext::next() const
{
    return START;
}
