#pragma once
#include <IContext.hpp>

namespace GUI
{

class EditContext : public IContext
{
    CONTEXT next_context_;
public:
    EditContext(sf::RenderWindow &window, TaskDB::TaskDB &task_db);
    ~EditContext() override;
    CONTEXT handleInput() override;
    void draw() override;
};

};