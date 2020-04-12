#pragma once
#include <IContext.hpp>
#include <Event.hpp>

namespace GUI
{

class EditContext : public IContext
{
    char task_title[256];
    char task_detail[4096];
    int priority = 3;
    int urgency = 3;
    int progress = 0;
    int select_id_;
    float man_hour;
    void set_select(const SelectTask& select);
public:
    EditContext(sf::RenderWindow &window, std::shared_ptr<TaskDB::TaskDB> task_db);
    ~EditContext() override;
    CONTEXT handleInput(const CONTEXT &context) override;
    CONTEXT draw(const CONTEXT &context) override;
};

} // namespace GUI