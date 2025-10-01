#pragma once

#include <iostream>

#include "../engine/core/world.hpp"

namespace lme::viewer {

class Renderer {
public:
    void draw(const World& world) const;
};

} // namespace lme::viewer
