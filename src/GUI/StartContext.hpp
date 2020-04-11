#pragma once
#include <IContext.hpp>

namespace GUI
{

class StartContext : public IContext
{

public:
    StartContext(sf::RenderWindow &window, std::shared_ptr<TaskDB::TaskDB> task_db);
    ~StartContext() override;
    CONTEXT handleInput(const CONTEXT &context) override;
    CONTEXT draw(const CONTEXT &context) override;
};

}; // namespace GUI