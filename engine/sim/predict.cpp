#include "predict.hpp"

#include <algorithm>

namespace lme::sim {

void schedule_pairwise_collisions(World& world, Scheduler& scheduler, Real horizon) {
    const Real relative_max = std::max<Real>(0.0, horizon - world.current_time());
    for (std::size_t i = 0; i < world.packets().size(); ++i) {
        for (std::size_t j = i + 1; j < world.packets().size(); ++j) {
            const Packet& a = world.packets()[i];
            const Packet& b = world.packets()[j];
            if (!a.alive || !b.alive) {
                continue;
            }
            auto result = geom::toi_disk_disk(a.kinematics.position, a.kinematics.velocity, a.kinematics.radius,
                                              b.kinematics.position, b.kinematics.velocity, b.kinematics.radius,
                                              0.0, relative_max);
            if (!result.hit) {
                continue;
            }
            Event event;
            event.time = world.current_time() + result.time;
            event.type = EventType::PacketPacketCollision;
            event.participants[0] = {a.id, a.revision};
            event.participants[1] = {b.id, b.revision};
            event.normal = result.normal;
            scheduler.schedule(event);
        }
    }
}

} // namespace lme::sim
