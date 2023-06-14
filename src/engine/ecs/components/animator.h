#pragma once
#include <map>
#include <string>

#include "animation.h"

struct animator
{
    std::map<std::string,animation> animations;
    std::string active{};
};
