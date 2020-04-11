#include <GUI.hpp>
#include <chrono>
#include <thread>
#include <cmath>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <imgui.h>
#include <imgui-SFML.h>
#include <ResourceManager.hpp>

namespace GUI
{
GUI::GUI(TaskDB::TaskDB &task_db)
    : current_context_{START},
      window_(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "TaskRaider")
{
    /* ocnfigure window setting */
    window_.setVerticalSyncEnabled(false);
    window_.setFramerateLimit(static_cast<int>(FPS));

    /* Initialize Resource */
    resource.loadFont("./resource/font/ipag.ttf", "ipag");
    resource.loadFont("./resource/font/ipagp.ttf", "ipagp");
    resource.loadFont("./resource/font/ipam.ttf", "ipam");
    resource.loadFont("./resource/font/ipamp.ttf", "ipamp");

    /* Initialize Contexts */
    contexts_[CONTEXT::START] = std::make_shared<StartContext>(window_, task_db);
    contexts_[CONTEXT::EDIT] = std::make_shared<EditContext>(window_, task_db);

    /* Initialize ImGui */
    ImGui::SFML::Init(window_);
    auto io = ImGui::GetIO();
    io.Fonts->Clear();
    io.Fonts->AddFontFromFileTTF("./resource/font/ipam.ttf", 20.f, nullptr, io.Fonts->GetGlyphRangesJapanese());
    io.Fonts->AddFontFromFileTTF("./resource/font/ipamp.ttf", 20.f, nullptr, io.Fonts->GetGlyphRangesJapanese());
    io.Fonts->AddFontFromFileTTF("./resource/font/ipag.ttf", 20.f, nullptr, io.Fonts->GetGlyphRangesJapanese());
    io.Fonts->AddFontFromFileTTF("./resource/font/ipagp.ttf", 20.f, nullptr, io.Fonts->GetGlyphRangesJapanese());
    ImGui::SFML::UpdateFontTexture();
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