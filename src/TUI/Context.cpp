#include "Context.hpp"
#include <iostream>

void StartContext::handle_input()
{

}

void StartContext::draw() const
{
    std::cout << "Hello";
}

CONTEXT_ID StartContext::next() const
{
    return START;
}
