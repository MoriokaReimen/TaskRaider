#include "TUI.hpp"

TUI::TUI()
    : is_open_(true), context_id_(START)
{
    this->contexts_.insert( {START, std::make_shared<StartContext>()});

}

TUI::~TUI()
{
    this->is_open_ = false;

}

void TUI::update()
{
    this->contexts_[this->context_id_]->handle_input();
    this->contexts_[this->context_id_]->draw();
    this->context_id_ = this->contexts_[this->context_id_]->next();
}

bool TUI::is_open() const
{
    return this->is_open_;
}
