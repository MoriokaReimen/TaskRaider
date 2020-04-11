#include <StartContext.hpp>
#include <imgui.h>
#include <imgui-SFML.h>
#include <GUI.hpp>

namespace GUI
{
StartContext::StartContext(sf::RenderWindow &window, TaskDB::TaskDB &task_db)
    : IContext(window, task_db)
{
}

StartContext::~StartContext()
{
}

CONTEXT StartContext::handleInput()
{
    CONTEXT next_context{CONTEXT::START};
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

void StartContext::draw()
{
    ImGui::SFML::Update(window_, sf::milliseconds(1000/FPS));
    ImGui::Begin("Test");
    ImGui::Button("Press Me");
    ImGui::End();

    window_.clear();
    ImGui::SFML::Render(window_);
    window_.display();
}

}; // namespace GUI