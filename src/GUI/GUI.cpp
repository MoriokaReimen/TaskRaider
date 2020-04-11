#include <GUI.hpp>
#include <chrono>
#include <thread>
#include <cmath>

namespace GUI
{
GUI::GUI(TaskDB::TaskDB &task_db)
    : current_context_{START}
{
}

void GUI::loop()
{
    const auto lag = std::chrono::milliseconds(static_cast<int>(1.0 / FPS * 1000.0));
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