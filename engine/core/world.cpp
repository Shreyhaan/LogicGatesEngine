#include "world.hpp"

#include <algorithm>

namespace lme {

Packet& World::spawn_packet(const PacketKinematics& kinematics, PacketState state) {
    Packet packet;
    packet.id = next_packet_id_++;
    packet.kinematics = kinematics;
    packet.state = state;
    packet.alive = true;
    packet.revision = 1;
    packets_.push_back(packet);
    return packets_.back();
}

Packet* World::find_packet(std::uint32_t id) noexcept {
    auto it = std::find_if(packets_.begin(), packets_.end(), [id](const Packet& p) { return p.id == id; });
    return it == packets_.end() ? nullptr : &*it;
}

const Packet* World::find_packet(std::uint32_t id) const noexcept {
    auto it = std::find_if(packets_.begin(), packets_.end(), [id](const Packet& p) { return p.id == id; });
    return it == packets_.end() ? nullptr : &*it;
}

std::uint64_t World::packet_revision(std::uint32_t id) const noexcept {
    if (const Packet* packet = find_packet(id)) {
        return packet->revision;
    }
    return 0;
}

void World::remove_packet(std::uint32_t id) {
    auto it = std::remove_if(packets_.begin(), packets_.end(), [id](const Packet& p) { return p.id == id; });
    packets_.erase(it, packets_.end());
}

void World::advance_time(Real t) {
    current_time_ = t;
}

void World::clear() {
    next_packet_id_ = 1;
    packets_.clear();
    segments_.clear();
    gates_.clear();
    emitters_ = logic::EmitterRegistry{};
    current_time_ = 0.0;
}

} // namespace lme
