#include "TaskDB.hpp"

Task::Task()
    : title(), detail(), progress(0)
{

}

const Task& Task::operator=(const Task& other)
{
    this->title = other.title;
    this->detail = other.detail;
    this->progress = other.progress;
    return *this;
}

TaskDB::TaskDB()
{
    this->openFile("");

}

TaskDB::~TaskDB()
{

}

bool TaskDB::openFile(const std::string& file)
{
    for(int i = 0; i < 100; ++i)
    {
        Task task;
        task.title = "Sample";
        task.detail = "Sample";
        task.progress = 33;
        this->tasks_.emplace_back(task);
    }
    this->is_open_ = true;

    return true;
}

void TaskDB::closeFile()
{
    this->is_open_ = false;

}

bool TaskDB::isOpen() const
{
    return this->is_open_;
}

Task TaskDB::queryTask(const int& id) const
{
    Task task;
    try {
        task = this->tasks_[id];
    } catch(...)
    {
    }

    return task;
}

int TaskDB::registerTask(const Task& task)
{
    int id;
    try {
        this->tasks_.push_back(task);
        id =  this->tasks_.size() - 1;

    } catch(...)
    {
        id = -1;
    }
    return id;
}

int TaskDB::size() const
{
    return this->tasks_.size();
}
