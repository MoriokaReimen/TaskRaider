#include "TaskDB.hpp"
#include "toml.hpp"
#include <fstream>
#include <Jinja2CppLight.h>

namespace TaskDB
{
TaskDB::TaskDB()
{
    this->openFile("");
}

TaskDB::~TaskDB()
{
}

bool TaskDB::openFile(const std::string &file)
{
    try
    {
        const auto data = toml::parse(file);
        const auto tasks = toml::find<std::vector<toml::table>>(data, "TASK");

        for (const auto &data : tasks)
        {
            Task temp;
            temp.enable = data.at("enable").as_boolean();
            temp.title = data.at("title").as_string();
            temp.detail = data.at("detail").as_string();
            temp.priority = data.at("priority").as_integer();
            temp.urgency = data.at("urgency").as_integer();
            temp.progress = data.at("progress").as_integer();
            temp.man_hour = data.at("man_hour").as_floating();
            this->tasks_.emplace_back(temp);
        }
        this->mail_head_ = toml::find<std::string>(data, "MAIL_HEAD");
        this->mail_body_ = toml::find<std::string>(data, "MAIL_BODY");
        this->mail_foot_ = toml::find<std::string>(data, "MAIL_FOOT");
        this->is_open_ = true;
    }
    catch (...)
    {
        this->is_open_ = false;
    }

    return this->is_open_;
}

bool TaskDB::saveFile(const std::string &file)
{
    bool ret;
    toml::array out_data;
    try
    {
        for (const auto &data : this->tasks_)
        {
            toml::table temp{
                {"enable", data.enable},
                {"title", data.title},
                {"detail", data.detail},
                {"priority", data.priority},
                {"urgency", data.urgency},
                {"progress", data.progress},
                {"man_hour", data.man_hour},
            };
            out_data.push_back(temp);
        }
        toml::value write_data{{"TASK", out_data},
                               {"MAIL_HEAD", this->mail_head_},
                               {"MAIL_BODY", this->mail_body_},
                               {"MAIL_FOOT", this->mail_foot_}};
        std::ofstream ofs(file);
        ofs << write_data;
        ofs.close();
        ret = true;
    }
    catch (...)
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

Task TaskDB::queryTask(const int &id) const
{
    Task task;
    try
    {
        task = this->tasks_[id];
    }
    catch (...)
    {
    }

    return task;
}

int TaskDB::registerTask(const Task &task)
{
    int id;
    try
    {
        this->tasks_.push_back(task);
        id = this->tasks_.size() - 1;
    }
    catch (...)
    {
        id = -1;
    }
    return id;
}

bool TaskDB::updateTask(const int &id, const Task &task)
{
    bool ret;
    try
    {
        this->tasks_[id] = task;
        ret = true;
    }
    catch (...)
    {
        ret = false;
    }
    return ret;
}

int TaskDB::size() const
{
    return this->tasks_.size();
}

std::string TaskDB::render() const
{
    std::stringstream ss;
    ss << this->mail_head_;
    for (int i = 0; i < this->size(); i++)
    {
        const Task task = this->queryTask(i);
        if(!task.enable) continue; /* skip disabled task */
        Jinja2CppLight::Template jinja(this->mail_body_);
        jinja.setValue("id", i+1);
        jinja.setValue("enable", task.enable);
        jinja.setValue("title", task.title);
        jinja.setValue("detail", task.detail);
        jinja.setValue("priority", task.priority);
        jinja.setValue("urgency", task.urgency);
        jinja.setValue("progress", task.progress);
        jinja.setValue("man_hour", task.man_hour);
        ss << jinja.render();
    }
    ss << this->mail_foot_;

    return ss.str();
}
}; // namespace TaskDB