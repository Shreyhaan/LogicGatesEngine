#include "determinism.hpp"

namespace lme::sim {

std::uint64_t hash_world_state(const World& world) {
    std::uint64_t hash = 1469598103934665603ULL;
    for (const auto& packet : world.packets()) {
        const auto mix = [&](std::uint64_t value) {
            hash ^= value + 0x9e3779b97f4a7c15ULL + (hash << 6) + (hash >> 2);
        };
        mix(static_cast<std::uint64_t>(packet.id));
        mix(static_cast<std::uint64_t>(packet.state.bits));
        mix(static_cast<std::uint64_t>(packet.revision));
        mix(static_cast<std::uint64_t>(packet.alive));
        mix(static_cast<std::uint64_t>(packet.kinematics.radius * 1e6));
        mix(static_cast<std::uint64_t>(packet.kinematics.mass * 1e6));
        mix(static_cast<std::uint64_t>(packet.kinematics.position.x * 1e6));
        mix(static_cast<std::uint64_t>(packet.kinematics.position.y * 1e6));
        mix(static_cast<std::uint64_t>(packet.kinematics.velocity.x * 1e6));
        mix(static_cast<std::uint64_t>(packet.kinematics.velocity.y * 1e6));
    }
    return hash;
}

} // namespace lme::sim
