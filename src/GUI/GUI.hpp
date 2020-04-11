#pragma once
#include <TaskDB/TaskDB.hpp>
#include <IContext.hpp>
#include <memory>
#include <map>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
namespace GUI
{
inline const int FPS{20}; /* frame per second */
inline const int WINDOW_WIDTH{800};
inline const int WINDOW_HEIGHT{600};
class GUI
{
    std::map<CONTEXT, std::shared_ptr<IContext>> contexts_;
    CONTEXT current_context_;
    sf::RenderWindow window_;

public:
    GUI(std::shared_ptr<TaskDB::TaskDB> task_db);
    void loop();
};

} // namespace GUI