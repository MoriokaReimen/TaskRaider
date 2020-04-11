#pragma once
#include <string>

namespace TaskDB
{
struct Task
{
    std::string title;
    std::string detail;
    int priority;
    int urgency;
    int progress;
    Task();
    const Task &operator=(const Task &other);
};

}; // namespace TaskDB