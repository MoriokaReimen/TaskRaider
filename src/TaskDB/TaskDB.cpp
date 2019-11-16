#include "TaskDB.hpp"
#include "toml.hpp"
#include <fstream>

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
    try {
        const auto data = toml::parse("sample.toml");
        const auto tasks = toml::find<std::vector<toml::table>>(data, "TASK");

        for(const auto& data : tasks)
        {
            Task temp;
            temp.title = data.at("title").as_string();
            temp.detail = data.at("detail").as_string();
            temp.progress = data.at("progress").as_integer();
            this->tasks_.emplace_back(temp);
        }
        this->is_open_ = true;
    } catch(...)
    {
        this->is_open_ = false;
    }

    return this->is_open_;
}

bool TaskDB::saveFile(const std::string& file)
{
    bool ret;
    toml::array out_data;
    try {
        for(const auto& data : this->tasks_)
        {
            toml::table temp{
                {"title", data.title},
                {"detail", data.detail},
                {"progress", data.progress},
            };
            out_data.push_back(temp);
        }
        toml::value write_data(out_data);
        std::ofstream ofs(file);
        ofs << write_data;
        ofs.close();
        ret = true;
    } catch(...)
    {
        ret = false;
    }

    return ret;

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
