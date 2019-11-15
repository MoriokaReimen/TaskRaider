#include "TaskDB.hpp"

TaskDB::TaskDB()
{

}

TaskDB::~TaskDB()
{

}

bool TaskDB::openFile(const std::string& file)
{
    for(int i = 0; i < 100; ++i)
    {
        this->tasks_.push_back({"Sample", "Sample Task", 30});
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
    return this->tasks_[id];
}

int TaskDB::registerTask(const Task& task)
{
    int id;
    try {
        this->tasks_.push_back(task);
        id =  this->tasks_.size();

    } catch(...)
    {
        id = -1;
    }
    return id;
}
