#pragma once

#include <cstdint>
#include <optional>
#include <unordered_map>
#include <vector>

#include "types.hpp"
#include "../logic/gate.hpp"
#include "../logic/emitters.hpp"

namespace lme {

struct Packet {
    std::uint32_t id{0};
    PacketKinematics kinematics;
    PacketState state;
    bool alive{true};
    std::uint64_t revision{0};
};

struct StaticSegment {
    std::uint32_t id{0};
    Vec2 a;
    Vec2 b;
};

class World {
public:
    Packet& spawn_packet(const PacketKinematics& kinematics, PacketState state);
    Packet* find_packet(std::uint32_t id) noexcept;
    const Packet* find_packet(std::uint32_t id) const noexcept;

    std::uint64_t packet_revision(std::uint32_t id) const noexcept;

    void remove_packet(std::uint32_t id);

    const std::vector<Packet>& packets() const noexcept { return packets_; }
    std::vector<Packet>& packets() noexcept { return packets_; }

    const std::vector<StaticSegment>& segments() const noexcept { return segments_; }
    std::vector<StaticSegment>& segments() noexcept { return segments_; }

    const std::vector<logic::GateInstance>& gates() const noexcept { return gates_; }
    std::vector<logic::GateInstance>& gates() noexcept { return gates_; }

    const logic::EmitterRegistry& emitters() const noexcept { return emitters_; }
    logic::EmitterRegistry& emitters() noexcept { return emitters_; }

    Real current_time() const noexcept { return current_time_; }
    void advance_time(Real t);

    void clear();

private:
    std::uint32_t next_packet_id_{1};
    std::vector<Packet> packets_;
    std::vector<StaticSegment> segments_;
    std::vector<logic::GateInstance> gates_;
    logic::EmitterRegistry emitters_;
    Real current_time_{0.0};
};

} // namespace lme
