#include "integrate.hpp"

namespace lme::sim {

void integrate_to(World& world, Real target_time) {
    Real dt = target_time - world.current_time();
    if (dt <= 0.0) {
        world.advance_time(target_time);
        return;
    }
    for (auto& packet : world.packets()) {
        if (!packet.alive) {
            continue;
        }
        packet.kinematics.position += packet.kinematics.velocity * dt;
    }
    world.advance_time(target_time);
}

} // namespace lme::sim
