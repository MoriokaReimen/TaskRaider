#pragma once
#include <IContext.hpp>

namespace GUI
{

class CreateContext : public IContext
{

public:
    CreateContext(sf::RenderWindow &window, std::shared_ptr<TaskDB::TaskDB> task_db);
    ~CreateContext() override;
    CONTEXT handleInput(const CONTEXT &context) override;
    CONTEXT draw(const CONTEXT &context) override;
};

} // namespace GUI