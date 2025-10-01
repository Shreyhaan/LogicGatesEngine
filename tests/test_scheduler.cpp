#include <cassert>

#include "../engine/core/scheduler.hpp"
#include "../engine/core/world.hpp"

int main() {
    lme::World world;
    lme::PacketKinematics kin;
    kin.position = {-1.0, 0.0};
    kin.velocity = {1.0, 0.0};
    lme::PacketState state{1};
    auto& p = world.spawn_packet(kin, state);

    lme::Scheduler scheduler;
    lme::Event a;
    a.time = 1.0;
    a.participants[0] = {p.id, p.revision};
    scheduler.schedule(a);

    lme::Event b;
    b.time = 0.5;
    b.participants[0] = {p.id, p.revision};
    scheduler.schedule(b);

    assert(!scheduler.empty());
    auto ev = scheduler.pop();
    assert(ev.time == 0.5);

    ++world.find_packet(p.id)->revision;
    lme::Event c;
    c.time = 0.25;
    c.participants[0] = {p.id, p.revision};
    scheduler.schedule(c);

    while (!scheduler.empty()) {
        auto next = scheduler.pop();
        if (!next.valid(world)) {
            continue;
        }
        assert(next.time == 0.25);
        break;
    }

    return 0;
}
