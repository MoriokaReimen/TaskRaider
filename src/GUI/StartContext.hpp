#pragma once
#include <IContext.hpp>

namespace GUI
{

class StartContext : public IContext
{
public:
    StartContext(sf::RenderWindow &window, TaskDB::TaskDB &task_db);
    ~StartContext() override;
    CONTEXT handleInput() override;
    void draw() override;
};

};