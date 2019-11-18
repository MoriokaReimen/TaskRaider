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
    for(int line = 0; line < SHOW_COLUM; line++) {
        int task_id = (selection_ - selection_ % SHOW_COLUM) + line;
        if(task_id >= Globals::taskdb.size()) break;
        Task task;
        task = Globals::taskdb.queryTask(task_id);

        /*show task_id, task title and detail*/
        if(task_id == selection_) {
            attron(COLOR_PAIR(Globals::SELECT_COLOR));
        } else {
            attron(COLOR_PAIR(Globals::DEFAULT_COLOR));
        }
        mvwprintw(stdscr, line + 2, 0,  "| %05d", task_id);
        mvwprintw(stdscr, line + 2, 10, "| %-18s", task.title.c_str());
        mvwprintw(stdscr, line + 2, 31, "| %-18.18s ",task.detail.c_str());

        /*show task progress with bar*/
        {
            using Globals::COLOR_IDX;
            wmove(stdscr, line + 2, 50);
            wclrtoeol(stdscr);
            mvwprintw(stdscr, line + 2, 50, "| %3d%%", task.progress);
            COLOR_IDX color = task.progress < 30 ? COLOR_IDX::RED_COLOR :
                                       task.progress < 60 ? COLOR_IDX::YELLOW_COLOR :
                                       COLOR_IDX::BLUE_COLOR;
            for(int i = 0; i < task.progress / 5; ++i) {
                attron(COLOR_PAIR(color));
                mvwprintw(stdscr, line + 2, 59 + i, " ");
            }
        }
        {
            attron(COLOR_PAIR(Globals::DEFAULT_COLOR));
            mvwprintw(stdscr, line + 2, 78, "|");
            using Globals::COLOR_IDX;
            COLOR_IDX color = task.priority < 2 ? COLOR_IDX::LOW_COLOR :
                              task.priority < 5 ? COLOR_IDX::MIDDLE_COLOR :
                              COLOR_IDX::HIGH_COLOR;
            attron(COLOR_PAIR(color));
            wprintw(stdscr, " %1d ", task.priority);
            attron(COLOR_PAIR(Globals::DEFAULT_COLOR));
            wprintw(stdscr, "|");
        }
        {
            using Globals::COLOR_IDX;
            COLOR_IDX color = task.urgency < 2 ? COLOR_IDX::LOW_COLOR :
                              task.urgency < 5 ? COLOR_IDX::MIDDLE_COLOR :
                              COLOR_IDX::HIGH_COLOR;
            attron(COLOR_PAIR(color));
            wprintw(stdscr, " %1d ", task.urgency);
            attron(COLOR_PAIR(Globals::DEFAULT_COLOR));
            wprintw(stdscr, "|");
        }
    }
}

int TaskView::get_selection() const
{
    return this->selection_;
}
