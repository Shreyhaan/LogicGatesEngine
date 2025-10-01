#pragma once

#include <cstdint>
#include <optional>
#include <string>
#include <utility>
#include <vector>

#include "truth_table_rule.hpp"
#include "../core/types.hpp"

namespace lme::logic {

struct GatePort {
    std::uint32_t id{0};
    std::string name;
    lme::Vec2 position;
    lme::Vec2 direction{1.0, 0.0};
    lme::Real radius{0.05};
};

class GateInstance {
public:
    GateInstance() = default;
    GateInstance(std::uint32_t gate_id, std::string gate_name, std::vector<GatePort> ports, TruthTableRule rule);

    std::uint32_t id() const noexcept { return id_; }
    const std::string& name() const noexcept { return name_; }

    const std::vector<GatePort>& ports() const noexcept { return ports_; }
    const GatePort* find_port(const std::string& port_name) const noexcept;
    const GatePort* find_port(std::uint32_t port_id) const noexcept;

    std::optional<std::vector<std::uint32_t>> evaluate(const std::vector<std::uint32_t>& inputs) const;

private:
    std::uint32_t id_{0};
    std::string name_;
    std::vector<GatePort> ports_;
    TruthTableRule rule_;
};

} // namespace lme::logic
