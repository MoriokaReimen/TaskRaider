#include "TaskView.hpp"
#include "Globals.hpp"
#include "ncurses.h"

#include <algorithm>

TaskView::TaskView() : selection_(0)
{

}

int TaskView::increment_selection()
{
    selection_++;
    selection_ = std::clamp(selection_, 0, Globals::taskdb.size() - 1);
    return selection_;
}

int TaskView::decrement_selection()
{
    selection_--;
    selection_ = std::clamp(selection_, 0, Globals::taskdb.size() - 1);
    return selection_;

}

void TaskView::draw() const
{
    for(int line = 0; line < SHOW_COLUM; line++)
    {
        int task_id = (selection_ - selection_ % SHOW_COLUM) + line;
        if(task_id >= Globals::taskdb.size()) break;
        Task task;
        task = Globals::taskdb.queryTask(task_id);

        /*show task_id, task title and detail*/
        if(task_id == selection_)
        {
            attron(COLOR_PAIR(Globals::SELECT_COLOR));
        } else
        {
            attron(COLOR_PAIR(Globals::DEFAULT_COLOR));
        }
        mvwprintw(stdscr, line + 2, 0,  "| %05d", task_id);
        mvwprintw(stdscr, line + 2, 10, "| %-18s", task.title.c_str());
        mvwprintw(stdscr, line + 2, 31, "| %-18.18s ",task.detail.c_str());

        /*show task progress with bar*/
        using Globals::COLOR_IDX;
        wmove(stdscr, line + 2, 50);
        wclrtoeol(stdscr);
        mvwprintw(stdscr, line + 2, 50, "| %3d%%", task.progress);
        Globals::COLOR_IDX color = task.progress < 30 ? COLOR_IDX::RED_COLOR :
                                   task.progress < 60 ? COLOR_IDX::YELLOW_COLOR :
                                   COLOR_IDX::BLUE_COLOR;
        for(int i = 0; i < task.progress / 10; ++i)
        {
            attron(COLOR_PAIR(color));
            mvwprintw(stdscr, line + 2, 59 + i, " ");
        }
    }
}

int TaskView::get_selection() const
{
     return this->selection_;
}
