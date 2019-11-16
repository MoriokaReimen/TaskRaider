#include "TUI.hpp"
#include "Globals.hpp"
#include <ncurses.h>
#include <thread>
#include <chrono>

TUI::TUI()
    : is_open_(true), context_id_(START)
{
    /*Initialize ncurses*/
    initscr(); // Initialize screen
    start_color(); // start color mode
    cbreak(); // get one charcter at once
    nodelay(stdscr, TRUE); // non blocking getch()
    noecho(); // supress echo
    keypad(stdscr, TRUE); // get special keys

    /*Initialize Color pairs*/
    for(auto color : Globals::ALL_COLOR)
    {
        init_pair(color.idx, color.fg, color.bg);
    }

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
    using namespace std::chrono_literals;
    this->contexts_[this->context_id_]->handle_input();
    this->contexts_[this->context_id_]->draw();
    this->context_id_ = this->contexts_[this->context_id_]->next();
    std::this_thread::sleep_for(0.08s);
}

bool TUI::is_open() const
{
    return this->context_id_ != END;
}
