#pragma once
#include <TaskDB/TaskDB.hpp>
#include <IContext.hpp>
#include <memory>
#include <map>

namespace GUI
{
inline const double FPS{20.0}; /* frame per second */

class GUI
{
    std::map<CONTEXT, std::shared_ptr<IContext>> contexts_;
    CONTEXT current_context_;

public:
    GUI(TaskDB::TaskDB &task_db);
    void loop();
};

}; // namespace GUI