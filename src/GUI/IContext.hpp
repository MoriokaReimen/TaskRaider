#pragma once
#include <TaskDB/TaskDB.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <memory>

namespace GUI
{

enum CONTEXT
{
    START,
    EDIT,
    CLOSE
};

class IContext
{
protected:
    sf::RenderWindow &window_;
    std::shared_ptr<TaskDB::TaskDB> task_db_;

public:
    IContext(sf::RenderWindow &window, std::shared_ptr<TaskDB::TaskDB> task_db)
        : window_(window),
          task_db_(task_db){};
    virtual ~IContext(){};
    virtual CONTEXT handleInput(const CONTEXT &context) = 0;
    virtual CONTEXT draw(const CONTEXT &context) = 0;
};

} // namespace GUI

/* Declaration fo Context siblings */
#include <StartContext.hpp>
#include <EditContext.hpp>