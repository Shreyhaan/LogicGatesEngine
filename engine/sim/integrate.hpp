#pragma once

#include "../core/world.hpp"

namespace lme::sim {

void integrate_to(World& world, Real target_time);

} // namespace lme::sim
