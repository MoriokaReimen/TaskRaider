#pragma once
#include  <nana/gui.hpp>
#include  <nana/gui/widgets/textbox.hpp>
#include <memory>

class Builder
{
protected:
    std::shared_ptr<nana::form> form_;

public:
    Builder(std::shared_ptr<nana::form> form): form_{form} {};
    Builder(const Builder& other) = delete;
    const Builder& operator=(const Builder& other) = delete;
    virtual void build() = 0;
};

class LabelBuilder : public Builder
{

    nana::textbox txt;
public:
    LabelBuilder(std::shared_ptr<nana::form> form)
        : Builder{form}, txt{*form, nana::rectangle{50, 50, 50, 50}}{};
    void build() override;
};
