#pragma once

#include <cstdint>
#include <vector>

#include "../core/types.hpp"

namespace lme::logic {

struct Emitter {
    std::uint32_t id{0};
    std::uint32_t port_id{0};
    lme::Real period{1.0};
    std::uint32_t state{0};
    lme::Real speed{1.0};
    lme::Real phase{0.0};
};

class EmitterRegistry {
public:
    const std::vector<Emitter>& emitters() const noexcept { return emitters_; }
    void add(Emitter emitter) { emitters_.push_back(std::move(emitter)); }

private:
    std::vector<Emitter> emitters_;
};

} // namespace lme::logic
