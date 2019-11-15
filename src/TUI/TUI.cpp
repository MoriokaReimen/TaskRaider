#include "TUI.hpp"
#include <ncurses.h>

TUI::TUI()
    : is_open_(true), context_id_(START)
{
    /*Initialize ncurses*/
    initscr(); // Initialize screen
    cbreak(); // get one charcter at once
    noecho(); // supress echo
    keypad(stdscr, TRUE); // get special keys
    /*Initialize Contexts*/
    this->contexts_.insert( {START, std::make_shared<StartContext>()});

}

TUI::~TUI()
{
    endwin();
    this->is_open_ = false;

}

void TUI::update()
{
    this->contexts_[this->context_id_]->handle_input();
    this->contexts_[this->context_id_]->draw();
    this->context_id_ = this->contexts_[this->context_id_]->next();
}

bool TUI::is_open() const
{
    return this->context_id_ != END;
}
