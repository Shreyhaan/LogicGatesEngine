#pragma once

#include "../core/scheduler.hpp"
#include "../core/world.hpp"
#include "../geom/collision_ccd.hpp"

namespace lme::sim {

void schedule_pairwise_collisions(World& world, Scheduler& scheduler, Real horizon);

} // namespace lme::sim
