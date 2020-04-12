#pragma once
#include <string>
#include <vector>

namespace TaskDB
{
struct Task
{
    bool enable;
    std::string title;
    std::string detail;
    int priority;
    int urgency;
    int progress;
    float man_hour;
    Task();
    const Task &operator=(const Task &other);
};

} // namespace TaskDB