#pragma once

#include <array>
#include <cstdint>
#include <queue>
#include <vector>

#include "types.hpp"

namespace lme {

class World;

enum class EventType {
    PacketPacketCollision = 0,
    PacketStaticCollision = 1,
    PacketPortHit = 2,
    EmitPacket = 3,
    KillPacket = 4
};

struct EventParticipant {
    std::uint32_t id{0};
    std::uint64_t revision{0};
};

struct Event {
    Real time{0.0};
    EventType type{EventType::PacketPacketCollision};
    std::array<EventParticipant, 2> participants{};
    std::uint64_t serial{0};
    Vec2 normal{0.0, 1.0};

    bool valid(const World& world) const;
};

class Scheduler {
public:
    Scheduler();

    void schedule(Event event);
    bool empty() const noexcept { return queue_.empty(); }
    const Event& top() const { return queue_.top(); }
    Event pop();
    void clear();
    std::size_t size() const noexcept { return queue_.size(); }

private:
    struct Compare {
        bool operator()(const Event& lhs, const Event& rhs) const noexcept;
    };

    std::priority_queue<Event, std::vector<Event>, Compare> queue_;
    std::uint64_t serial_counter_{1};
};

} // namespace lme
