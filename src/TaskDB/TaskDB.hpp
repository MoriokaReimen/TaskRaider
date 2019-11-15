#pragma once
#include <vector>
#include <string>

struct Task
{
    std::string title;
    std::string detail;
};

class TaskDB
{
    bool is_open_;
public:
    TaskDB();
    ~TaskDB();
    bool openFile(const std::string& file);
    void closeFile();
    bool isOpen() const;
    Task queryTask(const int& id) const;
    bool registerTask(const Task& task);

};

