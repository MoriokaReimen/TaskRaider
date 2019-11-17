#pragma once
#include <vector>
#include <string>

struct Task {
    std::string title;
    std::string detail;
    int priority;
    int urgency;
    int progress;
    Task();
    const Task& operator=(const Task& other);
};

class TaskDB
{
    std::vector<Task> tasks_;
    bool is_open_;
public:
    TaskDB();
    ~TaskDB();
    bool openFile(const std::string& file);
    void closeFile();
    bool saveFile(const std::string& file);
    bool isOpen() const;
    Task queryTask(const int& id) const;
    int registerTask(const Task& task);
    bool updateTask(const int& id, const Task& task);
    int size() const;

};

