#include "Task.hpp"

namespace TaskDB
{
Task::Task()
    : enable(true), title(), priority(3), urgency(3), detail(), progress(0), man_hour(0.0)
{
}

const Task &Task::operator=(const Task &other)
{
    this->enable = other.enable;
    this->title = other.title;
    this->detail = other.detail;
    this->priority = other.priority;
    this->urgency = other.urgency;
    this->progress = other.progress;
    this->man_hour = other.man_hour;
    return *this;
}
}; // namespace TaskDB