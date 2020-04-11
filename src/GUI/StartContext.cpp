#include <StartContext.hpp>

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
}

}; // namespace GUI