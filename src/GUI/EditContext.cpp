#include <EditContext.hpp>
#include <imgui.h>
#include <imgui-SFML.h>
#include <GUI.hpp>
#include <cstring>
#include <Event.hpp>
#include <iostream>

namespace GUI
{
EditContext::EditContext(sf::RenderWindow &window, std::shared_ptr<TaskDB::TaskDB> task_db)
    : IContext(window, task_db),
      select_id_(-1)
{
    bus_.listen<SelectTask>(std::bind(&EditContext::set_select, this, std::placeholders::_1));
}

EditContext::~EditContext()
{
}

void EditContext::set_select(const SelectTask &select)
{
    select_id_ = select.id;
    auto task = task_db_->queryTask(select_id_);
    std::memset(task_title, 0, sizeof(task_title));
    std::memset(task_detail, 0, sizeof(task_detail));
    std::memmove(task_title, task.title.c_str(), task.title.size());
    std::memmove(task_detail, task.detail.c_str(), task.detail.size());
    priority = task.priority;
    urgency = task.urgency;
    progress = task.progress;
    man_hour = task.man_hour;
}

CONTEXT EditContext::handleInput(const CONTEXT &context)
{
    CONTEXT next_context(context);
    sf::Event event;
    while (window_.pollEvent(event))
    {
        /* Handle ImGui Events */
        ImGui::SFML::ProcessEvent(event);

        /* Handle other Events */
        switch (event.type)
        {
        case sf::Event::Closed:
            window_.close();
            next_context = CONTEXT::CLOSE;
            break;
        default:
            break;
        }
    }

    /* this block might be redundant */
    if (!window_.isOpen())
    {
        next_context = CONTEXT::CLOSE;
    }

    return next_context;
}

CONTEXT EditContext::draw(const CONTEXT &context)
{
    CONTEXT next_context(context);

    ImGui::SFML::Update(window_, sf::milliseconds(1000 / FPS));
    ImGuiWindowFlags window_flags = 0;
    window_flags |= ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize;  
    ImGui::Begin("タスク詳細", nullptr, window_flags);
    ImGui::SetWindowSize(ImVec2(WINDOW_WIDTH, WINDOW_HEIGHT));
    ImGui::SetWindowPos(ImVec2(0, 0));

    /* Show task tiltle dialogue */
    ImGui::Text("タスク名");
    ImGui::InputText("##Editタスク名", task_title, sizeof(task_title));

    /* Show Detail Dialogue */
    ImGui::Text("詳細");
    ImGui::InputTextMultiline("##Edit詳細", task_detail, sizeof(task_detail));

    /* Show Priority Dialogue */
    ImGui::Text("重要度");
    ImGui::SliderInt("##Edit重要度", &priority, 1, 5, "%d");
    ImGui::SameLine();
    if (ImGui::SmallButton("-##Edit重要度"))
    {
        priority -= 1;
        priority = std::clamp(priority, 1, 5);
    }
    ImGui::SameLine();
    if (ImGui::SmallButton("+##Edit重要度"))
    {
        priority += 1;
        priority = std::clamp(priority, 1, 5);
    }

    /* Show Urgency Dialogue */
    ImGui::Text("緊急度");
    ImGui::SliderInt("##Edit緊急度", &urgency, 1, 5, "%d");
    ImGui::SameLine();
    if (ImGui::SmallButton("-##Edit緊急度"))
    {
        urgency -= 1;
        urgency = std::clamp(urgency, 1, 5);
    }
    ImGui::SameLine();
    if (ImGui::SmallButton("+##Edit緊急度"))
    {
        urgency += 1;
        urgency = std::clamp(urgency, 1, 5);
    }

    /* Show Man Hour */
    ImGui::Text("総工数");
    ImGui::Text("%4.1f 時間", man_hour);
    ImGui::SameLine();
    if (ImGui::SmallButton("-##Edit総工数"))
    {
        man_hour -= 0.5;
    }
    ImGui::SameLine();
    if (ImGui::SmallButton("+##Edit総工数"))
    {
        man_hour += 0.5;
    }

    /* Show Progress Dialogue */
    ImGui::Text("進行");
    ImGui::SliderInt("##Edit進行", &progress, 0, 100, "%d%%");
    ImGui::SameLine();
    if (ImGui::SmallButton("-"))
    {
        progress -= 10;
        progress = (progress / 10) * 10;
        progress = std::clamp(progress, 0, 100);
    }
    ImGui::SameLine();
    if (ImGui::SmallButton("+"))
    {
        progress += 10;
        progress = (progress / 10) * 10;
        progress = std::clamp(progress, 0, 100);
    }

    if (ImGui::Button("保存##Edit"))
    {
        TaskDB::Task task;
        task.enable = true;
        task.title = std::string(task_title);
        task.title.erase(task.title.find_last_not_of(" \r\n\f\v"));
        task.detail = std::string(task_detail);
        task.detail.erase(task.detail.find_last_not_of(" \r\n\f\v"));
        task.priority = priority;
        task.urgency = urgency;
        task.progress = progress;
        task.man_hour = man_hour;
        if(!task.title.empty())
        {
            task_db_->updateTask(select_id_, task);
        }
        task_db_->saveFile("data.toml");
        std::memset(task_title, 0, sizeof(task_title));
        std::memset(task_detail, 0, sizeof(task_detail));
        std::memcpy(task_title, task.title.c_str(), task.title.size());
        std::memcpy(task_detail, task.detail.c_str(), task.detail.size());
        priority = 3;
        urgency = 3;
        progress = 0;
        man_hour = 0;
        next_context = CONTEXT::START;
    }
    ImGui::SameLine();
    if (ImGui::Button("キャンセル##Edit"))
    {
        std::memset(task_title, 0, sizeof(task_title));
        std::memset(task_detail, 0, sizeof(task_detail));
        priority = 3;
        urgency = 3;
        progress = 0;
        man_hour = 0;
        std::memset(task_title, 0, sizeof(task_title));
        next_context = CONTEXT::START;
    }
    ImGui::End();

    window_.clear();
    ImGui::SFML::Render(window_);
    window_.display();

    return next_context;
}

} // namespace GUI