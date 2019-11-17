#pragma once

#include <string>

bool ok_dialogue(const std::string& message);
std::string line_dialogue(const std::string& message);
int int_dialogue(const std::string& message, const int& min, const int& max);

