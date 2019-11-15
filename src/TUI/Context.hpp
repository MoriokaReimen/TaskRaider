#pragma once

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
public:
    void handle_input() override;
    void draw() const override;
    CONTEXT_ID next()const override;
};
