#pragma once

#include "integrate.hpp"
#include "predict.hpp"

namespace lme::sim {

bool process_next_event(World& world, Scheduler& scheduler, Real horizon);

} // namespace lme::sim
