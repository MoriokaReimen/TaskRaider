#pragma once
#include <TaskDB/TaskDB.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

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
    TaskDB::TaskDB &task_db_;
    sf::RenderWindow &window_;

public:
    IContext(sf::RenderWindow &window, TaskDB::TaskDB &task_db)
        : window_(window),
          task_db_(task_db){};
    virtual ~IContext(){};
    virtual CONTEXT handleInput(const CONTEXT &context) = 0;
    virtual CONTEXT draw(const CONTEXT &context) = 0;
};

}; // namespace GUI

/* Declaration fo Context siblings */
#include <StartContext.hpp>
#include <EditContext.hpp>