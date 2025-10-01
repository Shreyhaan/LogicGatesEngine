#include "scheduler.hpp"

#include "world.hpp"

namespace lme {

bool Event::valid(const World& world) const {
    for (const auto& participant : participants) {
        if (participant.id == 0) {
            continue;
        }
        if (world.packet_revision(participant.id) != participant.revision) {
            return false;
        }
    }
    return true;
}

Scheduler::Scheduler() = default;

void Scheduler::schedule(Event event) {
    if (event.serial == 0) {
        event.serial = serial_counter_++;
    }
    queue_.push(event);
}

Event Scheduler::pop() {
    Event top_event = queue_.top();
    queue_.pop();
    return top_event;
}

void Scheduler::clear() {
    queue_ = decltype(queue_){};
    serial_counter_ = 1;
}

bool Scheduler::Compare::operator()(const Event& lhs, const Event& rhs) const noexcept {
    if (lhs.time != rhs.time) {
        return lhs.time > rhs.time;
    }
    if (lhs.type != rhs.type) {
        return static_cast<int>(lhs.type) > static_cast<int>(rhs.type);
    }
    return lhs.serial > rhs.serial;
}

} // namespace lme
