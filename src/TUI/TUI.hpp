#pragma once
#include "Context.hpp"
#include <map>
#include <memory>

class TUI
{
    std::map<CONTEXT_ID, std::shared_ptr<Context>> contexts_;
    bool is_open_;
    ContextInfo info_;
public:
    TUI();
    ~TUI();
    void update();
    bool is_open() const;
};
