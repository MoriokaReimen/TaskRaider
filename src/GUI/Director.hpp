#pragma once
#include "Builder.hpp"
#include  <nana/gui.hpp>
#include <memory>
#include <vector>

class Director
{
    std::vector<std::shared_ptr<Builder>> builders_;
    std::shared_ptr<nana::form> form_;

public:
    Director();
    std::shared_ptr<nana::form> construct();
};
