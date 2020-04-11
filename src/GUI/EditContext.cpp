#include <EditContext.hpp>
#include <imgui.h>
#include <imgui-SFML.h>
#include <GUI.hpp>

namespace GUI
{
EditContext::EditContext(sf::RenderWindow &window, TaskDB::TaskDB &task_db)
    : IContext(window, task_db)
{
}

EditContext::~EditContext()
{
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
    ImGui::Begin("新規タスク");
    if (ImGui::Button("追加"))
    {
        next_context = CONTEXT::START;
    }
    ImGui::End();

    window_.clear();
    ImGui::SFML::Render(window_);
    window_.display();

    return next_context;
}

}; // namespace GUI