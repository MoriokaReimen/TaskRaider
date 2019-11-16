#include "Context.hpp"
#include "Globals.hpp"
#include <iostream>
#include <ncurses.h>

/* StartContext *******************************************************************************/
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

ContextInfo StartContext::next() const
{
    switch(last_key_)
    {
        case 'q':
            return ContextInfo{START, END, 0};
            break;
        case 'c':
            return ContextInfo{START, CREATE, 0};
            break;
        case 'e':
            return ContextInfo{START, EDIT, 0};
            break;
        default:
            return ContextInfo{START, START, 0};
            break;
    }

}

/* CreateContext **********************************************************************************/
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

ContextInfo CreateContext::next() const
{
    switch(last_key_)
    {
        case 'q':
            return ContextInfo{CREATE, START, 0};
            break;
        default:
            return ContextInfo{CREATE, CREATE, 0};
            break;
    }

}

/* EditContext ************************************************************************************/
void EditContext::on_entry(const ContextInfo& info)
{
    if(info.old != EDIT)
    {
        Task task;
        task = Globals::taskdb.queryTask(info.task_id);
        this->task_id_ = info.task_id;
        this->title_ = task.title;
        this->detail_ = task.detail;
        this->progress_ = task.progress;
    }
}

EditContext::EditContext()
    : task_id_(0), last_key_(0)
{

}

void EditContext::handle_input()
{
    last_key_ = getch();
}

void EditContext::draw() const
{
    clear();
    attron(COLOR_PAIR(Globals::SELECT_COLOR));
    mvwprintw(stdscr, 0, 0, "Now you are editing Task ID: %04d", task_id_);
    attron(COLOR_PAIR(Globals::DEFAULT_COLOR));
    mvwprintw(stdscr, 1, 0, "Task TITLE: %s", this->title_.c_str());
    mvwprintw(stdscr, 2, 0, "Task DETAIL:");
    mvwprintw(stdscr, 3, 0, "%s", this->detail_.c_str());
    mvwprintw(stdscr, 30, 0,"Task PROGRESS: %d%%", this->progress_);
    refresh();
}

ContextInfo EditContext::next() const
{
    switch(last_key_)
    {
        case 'q':
            return ContextInfo{EDIT, START, 0};
            break;
        default:
            return ContextInfo{EDIT, EDIT, 0};
            break;
    }

}

