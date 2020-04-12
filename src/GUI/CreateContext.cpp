#include <CreateContext.hpp>
#include <imgui.h>
#include <imgui-SFML.h>
#include <GUI.hpp>
#include <cstring>
#include <Event.hpp>
#include <iostream>
#include <regex>

namespace GUI
{
CreateContext::CreateContext(sf::RenderWindow &window, std::shared_ptr<TaskDB::TaskDB> task_db)
    : IContext(window, task_db)
{
    bus_.listen<SelectTask>([](const SelectTask& select){std::cout << select.id << std::endl;});
}

CreateContext::~CreateContext()
{
}

CONTEXT CreateContext::handleInput(const CONTEXT &context)
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

CONTEXT CreateContext::draw(const CONTEXT &context)
{
    static char task_title[256];
    static char task_detail[1024];
    static int priority = 3;
    static int urgency = 3;
    static int progress = 0;
    static float man_hour = 0.f;

    CONTEXT next_context(context);

    ImGui::SFML::Update(window_, sf::milliseconds(1000 / FPS));
    ImGui::Begin("新規タスク");
    ImGui::SetWindowSize(ImVec2(WINDOW_WIDTH, WINDOW_HEIGHT));
    ImGui::SetWindowPos(ImVec2(0, 0));

    /* Show task tiltle dialogue */
    ImGui::Text("タスク名");
    ImGui::InputText("##タスク名", task_title, sizeof(task_title));

    /* Show Detail Dialogue */
    ImGui::Text("詳細");
    ImGui::InputTextMultiline("##詳細", task_detail, sizeof(task_detail));

    /* Show Priority Dialogue */
    ImGui::Text("重要度");
    ImGui::SliderInt("##重要度", &priority, 1, 5, "%d");
    ImGui::SameLine();
    if (ImGui::SmallButton("-##重要度"))
    {
        priority -= 1;
        priority = std::clamp(priority, 1, 5);
    }
    ImGui::SameLine();
    if (ImGui::SmallButton("+##重要度"))
    {
        priority += 1;
        priority = std::clamp(priority, 1, 5);
    }

    /* Show Urgency Dialogue */
    ImGui::Text("緊急度");
    ImGui::SliderInt("##緊急度", &urgency, 1, 5, "%d");
    ImGui::SameLine();
    if (ImGui::SmallButton("-##緊急度"))
    {
        urgency -= 1;
        urgency = std::clamp(urgency, 1, 5);
    }
    ImGui::SameLine();
    if (ImGui::SmallButton("+##緊急度"))
    {
        urgency += 1;
        urgency = std::clamp(urgency, 1, 5);
    }

    /* Show Progress Dialogue */
    ImGui::Text("進行");
    ImGui::SliderInt("##進行", &progress, 0, 100, "%d%%");
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

    if (ImGui::Button("追加"))
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
        task.man_hour = 0.0;
        task_db_->registerTask(task);
        task_db_->saveFile("data.toml");
        std::memset(task_title, 0, sizeof(task_title));
        std::memset(task_detail, 0, sizeof(task_detail));
        priority = 3;
        urgency = 3;
        progress = 0;
        next_context = CONTEXT::START;
    }
    ImGui::SameLine();
    if (ImGui::Button("キャンセル"))
    {
        std::memset(task_title, 0, sizeof(task_title));
        std::memset(task_detail, 0, sizeof(task_detail));
        priority = 3;
        urgency = 3;
        progress = 0;
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