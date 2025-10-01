#include "process.hpp"

namespace lme::sim {

namespace {

void apply_elastic(Packet& a, Packet& b, const Vec2& normal) {
    Vec2 rel = a.kinematics.velocity - b.kinematics.velocity;
    Real rel_normal = dot(rel, normal);
    if (rel_normal >= 0.0) {
        return;
    }
    a.kinematics.velocity -= normal * rel_normal;
    b.kinematics.velocity += normal * rel_normal;
    ++a.revision;
    ++b.revision;
}

} // namespace

bool process_next_event(World& world, Scheduler& scheduler, Real horizon) {
    while (!scheduler.empty()) {
        Event event = scheduler.pop();
        if (!event.valid(world)) {
            continue;
        }
        integrate_to(world, event.time);
        switch (event.type) {
        case EventType::PacketPacketCollision: {
            Packet* a = world.find_packet(event.participants[0].id);
            Packet* b = world.find_packet(event.participants[1].id);
            if (!a || !b) {
                break;
            }
            apply_elastic(*a, *b, event.normal);
            break;
        }
        default:
            break;
        }
        schedule_pairwise_collisions(world, scheduler, horizon);
        return true;
    }
    return false;
}

} // namespace lme::sim
