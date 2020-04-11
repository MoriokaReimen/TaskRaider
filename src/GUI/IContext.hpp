#pragma once
#include <TaskDB/TaskDB.hpp>

namespace GUI
{

enum CONTEXT
{
    START,
    EDIT,
    CLOSE
};

class IContext
{
    TaskDB::TaskDB& task_db_;
public:
    IContext(TaskDB::TaskDB& task_db): task_db_(task_db) {};
    virtual ~IContext() {};
    virtual CONTEXT handleInput() = 0;
    virtual void draw() = 0;
};

};