#pragma once
#include <IContext.hpp>
#include <string>

namespace GUI
{
struct GenerateMail;
class PreviewContext : public IContext
{
    std::string mail_;
    void generate_mail(const GenerateMail& _);
public:
    PreviewContext(sf::RenderWindow &window, std::shared_ptr<TaskDB::TaskDB> task_db);
    ~PreviewContext() override;
    CONTEXT handleInput(const CONTEXT &context) override;
    CONTEXT draw(const CONTEXT &context) override;
};

} // namespace GUI