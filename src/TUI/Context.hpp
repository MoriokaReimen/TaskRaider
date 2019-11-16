#pragma once
#include "TaskView.hpp"
#include <string>

enum CONTEXT_ID
{
    START,
    CREATE,
    EDIT,
    END
};

struct ContextInfo
{
    CONTEXT_ID old;
    CONTEXT_ID current;
    int task_id;
};

class Context
{

public:
    virtual ~Context() {};
    virtual void on_entry(const ContextInfo& info) {};
    virtual void on_exit(const ContextInfo& info) {};
    virtual void handle_input() = 0;
    virtual void draw() const = 0;
    virtual ContextInfo next() const = 0;
};

class StartContext : public Context
{
    TaskView task_view_;
    int last_key_;
public:
    StartContext();
    void handle_input() override;
    void draw() const override;
    ContextInfo next()const override;
};

class CreateContext : public Context
{
    int last_key_;
public:
    CreateContext();
    void handle_input() override;
    void draw() const override;
    ContextInfo next()const override;
};

class EditContext : public Context
{
    int task_id_;
    std::string title_;
    std::string detail_;
    int progress_;
    int last_key_;
public:
    EditContext();
    virtual void on_entry(const ContextInfo& info) override;
    virtual void on_exit(const ContextInfo& info) override;
    void handle_input() override;
    void draw() const override;
    ContextInfo next()const override;
};
