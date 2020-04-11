#include <EditContext.hpp>
#include <imgui.h>
#include <imgui-SFML.h>
#include <GUI.hpp>

namespace GUI
{
EditContext::EditContext(sf::RenderWindow &window, TaskDB::TaskDB &task_db)
    : IContext(window, task_db),
      next_context_(EDIT)
{
}

EditContext::~EditContext()
{
}

CONTEXT EditContext::handleInput()
{
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
            next_context_ = CONTEXT::CLOSE;
            break;
        default:
            break;
        }
    }

    /* this block might be redundant */
    if (!window_.isOpen())
    {
        next_context_ = CONTEXT::CLOSE;
    }
    return next_context_;
}

void EditContext::draw()
{

    ImGui::SFML::Update(window_, sf::milliseconds(1000 / FPS));
    ImGui::Begin("Test");
    ImGui::Button("Press Me");
    ImGui::End();

    window_.clear();
    ImGui::SFML::Render(window_);
    window_.display();
}

}; // namespace GUI