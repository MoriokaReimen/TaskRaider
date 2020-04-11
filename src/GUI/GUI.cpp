#include <GUI.hpp>
#include <chrono>
#include <thread>
#include <cmath>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <StartContext.hpp>
namespace GUI
{
GUI::GUI(TaskDB::TaskDB &task_db)
    : current_context_{START},
      window_(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "TaskRaider")
{
    /* ocnfigure window setting */
    window_.setVerticalSyncEnabled(false);
    window_.setFramerateLimit(static_cast<int>(FPS));
    contexts_[CONTEXT::START] = std::make_shared<StartContext>(window_, task_db);
}

void GUI::loop()
{
    const auto lag = std::chrono::milliseconds(1000 / FPS);
    while (true)
    {
        const auto start_time = std::chrono::high_resolution_clock::now();

        /* handling input and switch contexts */
        current_context_ = contexts_[current_context_]->handleInput();
        if (current_context_ == CONTEXT::CLOSE)
        {
            break;
        }

        /* draw context */
        contexts_[current_context_]->draw();

        /* calculate delta time */
        const auto delta_time = std::chrono::high_resolution_clock::now() - start_time;

        /* adjust FPS */
        const auto end_time = start_time + lag;
        std::this_thread::sleep_until(end_time);
    }
}
}; // namespace GUI