#include "TUI.hpp"
#include "Globals.hpp"
#include <ncurses.h>
#include <thread>
#include <chrono>

TUI::TUI()
    : is_open_(true), info_{START, START, 0}
{
    /*Initialize ncurses*/
    initscr(); // Initialize screen
    start_color(); // start color mode
    cbreak(); // get one charcter at once
    curs_set(0); // hide cursor
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
    this->contexts_.insert( {CREATE, std::make_shared<CreateContext>()});
    this->contexts_.insert( {EDIT, std::make_shared<EditContext>()});

}

TUI::~TUI()
{
    endwin();
    this->is_open_ = false;

}

void TUI::update()
{
    using namespace std::chrono_literals;
    this->contexts_[this->info_.current]->on_entry(this->info_);
    this->contexts_[this->info_.current]->handle_input();
    this->contexts_[this->info_.current]->draw();
    this->info_ = this->contexts_[this->info_.current]->next();
    std::this_thread::sleep_for(0.08s);
}

bool TUI::is_open() const
{
    return this->info_.current != END;
}
