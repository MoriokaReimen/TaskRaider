#pragma once
#include <IContext.hpp>

namespace GUI
{

class EditContext : public IContext
{

public:
    EditContext(sf::RenderWindow &window, std::shared_ptr<TaskDB::TaskDB> task_db);
    ~EditContext() override;
    CONTEXT handleInput(const CONTEXT &context) override;
    CONTEXT draw(const CONTEXT &context) override;
};

} // namespace GUI