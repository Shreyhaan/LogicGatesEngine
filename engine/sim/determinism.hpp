#pragma once

#include <cstdint>
#include <vector>

#include "../core/world.hpp"

namespace lme::sim {

std::uint64_t hash_world_state(const World& world);

} // namespace lme::sim
