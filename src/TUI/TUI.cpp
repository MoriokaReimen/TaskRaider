#include "TUI.hpp"

TUI::TUI()
    : is_open_(true)
{

}

TUI::~TUI()
{

}

void TUI::update()
{

}

bool TUI::is_open() const
{
    return this->is_open_;
}
