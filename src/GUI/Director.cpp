#include "Director.hpp"
#include "Builder.hpp"
#include <memory>

Director::Director()
    : form_(std::make_shared<nana::form>())
{
    builders_.push_back(std::make_shared<LabelBuilder>(form_));
}

std::shared_ptr<nana::form> Director::construct()
{
    for(auto& builder : builders_)
    {
        builder->build();
    }

    return form_;
}


