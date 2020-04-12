#include <PreviewContext.hpp>
#include <imgui.h>
#include <imgui-SFML.h>
#include <GUI.hpp>
#include <cstring>
#include <Event.hpp>
#include <iostream>

namespace GUI
{
PreviewContext::PreviewContext(sf::RenderWindow &window, std::shared_ptr<TaskDB::TaskDB> task_db)
    : IContext(window, task_db)
{
    bus_.listen<GenerateMail>(std::bind(&PreviewContext::generate_mail, this, std::placeholders::_1));
}

PreviewContext::~PreviewContext()
{
}

void PreviewContext::generate_mail(const GenerateMail& _)
{
    this->mail_ = task_db_->render();
}

CONTEXT PreviewContext::handleInput(const CONTEXT &context)
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

CONTEXT PreviewContext::draw(const CONTEXT &context)
{
    static char mail[8192] = {0};
    CONTEXT next_context(context);

    ImGui::SFML::Update(window_, sf::milliseconds(1000 / FPS));
    ImGui::Begin("メールプレビュー");
    std::memmove(mail, this->mail_.c_str(), this->mail_.size());
    ImGui::InputTextMultiline("##文面", mail, sizeof(mail));

    if (ImGui::Button("戻る"))
    {
        next_context = CONTEXT::START;
    }
    ImGui::End();

    window_.clear();
    ImGui::SFML::Render(window_);
    window_.display();

    return next_context;
}

} // namespace GUI