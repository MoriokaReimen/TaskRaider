#include <StartContext.hpp>
#include <imgui.h>
#include <imgui-SFML.h>
#include <GUI.hpp>
#include <Event.hpp>

namespace GUI
{
StartContext::StartContext(sf::RenderWindow &window, std::shared_ptr<TaskDB::TaskDB> task_db)
    : IContext(window, task_db)
{
}

StartContext::~StartContext()
{
}

CONTEXT StartContext::handleInput(const CONTEXT &context)
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

CONTEXT StartContext::draw(const CONTEXT &context)
{
    CONTEXT next_context(context);

    ImGui::SFML::Update(window_, sf::milliseconds(1000 / FPS));
    ImGuiWindowFlags window_flags = 0;
    window_flags |= ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize;  
    ImGui::Begin("タスク一覧", nullptr, window_flags);
    ImGui::SetWindowSize(ImVec2(WINDOW_WIDTH, WINDOW_HEIGHT));
    ImGui::SetWindowPos(ImVec2(0, 0));

    /* List All tasks in db */
    ImGui::Columns(5);
    ImGui::Separator();
    ImGui::Text("タスク名");
    ImGui::NextColumn();
    ImGui::Text("優先度");
    ImGui::NextColumn();
    ImGui::Text("緊急性");
    ImGui::NextColumn();
    ImGui::Text("進行");
    ImGui::NextColumn();
    ImGui::NextColumn();
    ImGui::Separator();
    for (int i = 0; i < task_db_->size(); i++)
    {
        TaskDB::Task task = task_db_->queryTask(i);
        if(!task.enable) continue; /* skip disabled task */
        ImGui::Text("%s", task.title.c_str());
        ImGui::NextColumn();
        ImGui::Text("%d", task.priority);
        ImGui::NextColumn();
        ImGui::Text("%d", task.urgency);
        ImGui::NextColumn();
        ImGui::ProgressBar(task.progress / 100.f);
        ImGui::Text("総工数: %4.1f 時間", task.man_hour);
        ImGui::NextColumn();
        ImGui::PushID(i);
        if(ImGui::Button("詳細"))
        {
            SelectTask select{i};
            bus_.notify(select);
            next_context = CONTEXT::EDIT;
        }

        if(ImGui::Button("無効化"))
        {
            task.enable = false;
            task_db_->updateTask(i, task);
            task_db_->saveFile("data.toml");
        }
        ImGui::PopID();
        ImGui::NextColumn();
        ImGui::Separator();
    }
    ImGui::Columns(1);

    if (ImGui::Button("新規タスク"))
    {
        next_context = CONTEXT::CREATE;
    }
    ImGui::SameLine();
    if (ImGui::Button("メール文面生成"))
    {
        bus_.notify(GenerateMail());
        next_context = CONTEXT::PREVIEW;
    }

    ImGui::End();

    window_.clear();
    ImGui::SFML::Render(window_);
    window_.display();

    return next_context;
}

} // namespace GUI