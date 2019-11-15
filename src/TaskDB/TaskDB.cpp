#include "TaskDB.hpp"

TaskDB::TaskDB()
{

}

TaskDB::~TaskDB()
{

}

bool TaskDB::openFile(const std::string& file)
{
    this->is_open_ = true;
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
    return {"Eat Lunch", "Don't skip meal"};

}

bool TaskDB::registerTask(const Task& task)
{
    return true;
}
