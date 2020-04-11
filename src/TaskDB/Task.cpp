#include "Task.hpp"

namespace TaskDB
{
Task::Task()
    : title(), priority(3), urgency(3), detail(), progress(0)
{
}

const Task &Task::operator=(const Task &other)
{
    this->title = other.title;
    this->detail = other.detail;
    this->priority = other.priority;
    this->urgency = other.urgency;
    this->progress = other.progress;
    return *this;
}
}; // namespace TaskDB