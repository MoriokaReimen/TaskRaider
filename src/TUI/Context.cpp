#include "Context.hpp"
#include "Globals.hpp"
#include "Util.hpp"
#include <algorithm>
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
        case 's':
            if(ok_dialogue("Save Task Data?")){
                Globals::taskdb.saveFile("sample.toml");
            }
            break;
        default:
            break;
    }
}

void StartContext::draw() const
{
    clear();
    attron(COLOR_PAIR(Globals::DEFAULT_COLOR));
    mvwprintw(stdscr, 0, 0, "| Task ID | Title              | Detail           | Progress                |");
    mvwprintw(stdscr, 1, 0, "|---------|--------------------|------------------|-------------------------|");
    task_view_.draw();
    refresh();
}

ContextInfo StartContext::next() const
{
    switch(last_key_)
    {
        case 'q':
            if(ok_dialogue("Do you want to quit?")){
                if(ok_dialogue("Save Task Data?")){
                    Globals::taskdb.saveFile("sample.toml");
                }
                return ContextInfo{START, END, this->task_view_.get_selection()};
            } else {
                return ContextInfo{START, START, this->task_view_.get_selection()};
            }
            break;
        case 'c':
            return ContextInfo{START, CREATE, this->task_view_.get_selection()};
            break;
        case 'e':
            return ContextInfo{START, EDIT, this->task_view_.get_selection()};
            break;
        default:
            return ContextInfo{START, START, this->task_view_.get_selection()};
            break;
    }

}

/* CreateContext **********************************************************************************/
void CreateContext::on_entry(const ContextInfo& info)
{
}

CreateContext::CreateContext()
    : title_(), detail_(), progress_(0), last_key_(0), selection_(0)
{

}

void CreateContext::handle_input()
{
    last_key_ = getch();
    switch(last_key_)
    {
        case 'k':
            selection_--;
            selection_ = std::clamp(selection_, 0, 2);
            break;
        case 'j':
            selection_++;
            selection_ = std::clamp(selection_, 0, 2);
            break;
        case 'e':
            editTask();
            break;
        case 'l':
            if(selection_ == 2)
            {
                this->progress_ += 10;
                this->progress_= std::clamp(this->progress_, 0, 100);
            }
            break;
        case 'h':
            if(selection_ == 2)
            {
                this->progress_ -= 10;
                this->progress_= std::clamp(this->progress_, 0, 100);
            }
            break;
        default:
            break;
    }
}

void CreateContext::draw() const
{
    clear();
    attron(COLOR_PAIR(Globals::SELECT_COLOR));
    mvwprintw(stdscr, 0, 0, "Now you are Creating New Task:");

    if(selection_ == 0)
    {
        attron(COLOR_PAIR(Globals::SELECT_COLOR));
    } else {
        attron(COLOR_PAIR(Globals::DEFAULT_COLOR));
    }
    mvwprintw(stdscr, 2, 0, "Task TITLE: %s", this->title_.c_str());

    if(selection_ == 1)
    {
        attron(COLOR_PAIR(Globals::SELECT_COLOR));
    } else {
        attron(COLOR_PAIR(Globals::DEFAULT_COLOR));
    }
    mvwprintw(stdscr, 3, 0, "Task DETAIL:%s", this->detail_.c_str());

    if(selection_ == 2)
    {
        attron(COLOR_PAIR(Globals::SELECT_COLOR));
    } else {
        attron(COLOR_PAIR(Globals::DEFAULT_COLOR));
    }
    mvwprintw(stdscr, 5, 0,"Task PROGRESS: %d%%", this->progress_);
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

void CreateContext::on_exit(const ContextInfo& info)
{
    if(info.current != CREATE)
    {
        Task task;
        task.title = this->title_;
        task.detail = this->detail_;
        task.progress = this->progress_;
        Globals::taskdb.registerTask(task);
    }
}

void CreateContext::editTask()
{
    switch(this->selection_)
    {
        case 0:
            this->title_ = line_dialogue("Task Title");;
            break;
        case 1:
            this->detail_ = line_dialogue("Task Detail");;;
            break;
        case 2:
            this->progress_ = int_dialogue("Input Progress", 0, 100);
            break;
    }
}

/* EditContext ************************************************************************************/
EditContext::EditContext()
    : task_id_(0), last_key_(0), selection_(0)
{

}

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

void EditContext::handle_input()
{
    last_key_ = getch();
    switch(last_key_)
    {
        case 'k':
            selection_--;
            selection_ = std::clamp(selection_, 0, 2);
            break;
        case 'j':
            selection_++;
            selection_ = std::clamp(selection_, 0, 2);
            break;
        case 'e':
            editTask();
            break;
        case 'l':
            if(selection_ == 2)
            {
                this->progress_ += 10;
                this->progress_= std::clamp(this->progress_, 0, 100);
            }
            break;
        case 'h':
            if(selection_ == 2)
            {
                this->progress_ -= 10;
                this->progress_= std::clamp(this->progress_, 0, 100);
            }
            break;
        default:
            break;
    }
}

void EditContext::draw() const
{
    clear();
    attron(COLOR_PAIR(Globals::SELECT_COLOR));
    mvwprintw(stdscr, 0, 0, "Now you are editing Task ID: %04d", task_id_);

    if(selection_ == 0)
    {
        attron(COLOR_PAIR(Globals::SELECT_COLOR));
    } else {
        attron(COLOR_PAIR(Globals::DEFAULT_COLOR));
    }
    mvwprintw(stdscr, 2, 0, "Task TITLE: %s", this->title_.c_str());

    if(selection_ == 1)
    {
        attron(COLOR_PAIR(Globals::SELECT_COLOR));
    } else {
        attron(COLOR_PAIR(Globals::DEFAULT_COLOR));
    }
    mvwprintw(stdscr, 3, 0, "Task DETAIL:%s", this->detail_.c_str());

    if(selection_ == 2)
    {
        attron(COLOR_PAIR(Globals::SELECT_COLOR));
    } else {
        attron(COLOR_PAIR(Globals::DEFAULT_COLOR));
    }
    mvwprintw(stdscr, 5, 0,"Task PROGRESS: %d%%", this->progress_);
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

void EditContext::on_exit(const ContextInfo& info)
{
    if(info.current != EDIT)
    {
        Task task;
        task.title = this->title_;
        task.detail = this->detail_;
        task.progress = this->progress_;
        Globals::taskdb.updateTask(this->task_id_, task);
    }
}

void EditContext::editTask()
{
    switch(this->selection_)
    {
        case 0:
            this->title_ = line_dialogue("Task Title");;
            break;
        case 1:
            this->detail_ = line_dialogue("Task Detail");;;
            break;
        case 2:
            this->progress_ = int_dialogue("Input Progress", 0, 100);
            break;
    }
}
