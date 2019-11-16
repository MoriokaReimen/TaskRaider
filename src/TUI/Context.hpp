#pragma once
#include "TaskView.hpp"

enum CONTEXT_ID
{
    START,
    END
};

class Context
{

public:
    virtual ~Context() {};
    virtual void handle_input() = 0;
    virtual void draw() const = 0;
    virtual CONTEXT_ID next() const = 0;
};

class StartContext : public Context
{
    TaskView task_view_;
    int last_key_;
public:
    StartContext();
    void handle_input() override;
    void draw() const override;
    CONTEXT_ID next()const override;
};
