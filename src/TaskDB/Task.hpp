#pragma once
#include <string>
#include <vector>

namespace TaskDB
{
struct Task
{
    std::string title;
    std::string detail;
    int priority;
    int urgency;
    int progress;
    std::vector<int> children;
    Task();
    const Task &operator=(const Task &other);
};

}; // namespace TaskDB