#include "TUI.hpp"
#include "Globals.hpp"
#include <ncurses.h>
#include <thread>
#include <chrono>
#include <locale>

TUI::TUI()
    : is_open_(true), info_{START, START, 0}
{
    /*use utf8*/
    std::setlocale(LC_ALL, "");
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
    ContextInfo info = this->info_;
    using namespace std::chrono_literals;
    this->contexts_[info.current]->on_entry(this->info_);
    this->contexts_[info.current]->handle_input();
    this->contexts_[info.current]->draw();
    this->info_ = this->contexts_[info.current]->next();
    this->contexts_[info.current]->on_exit(this->info_);
    std::this_thread::sleep_for(0.08s);
}

bool TUI::is_open() const
{
    return this->info_.current != END;
}
