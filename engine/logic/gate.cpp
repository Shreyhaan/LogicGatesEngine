#include "gate.hpp"

namespace lme::logic {

GateInstance::GateInstance(std::uint32_t gate_id, std::string gate_name, std::vector<GatePort> ports, TruthTableRule rule)
    : id_(gate_id), name_(std::move(gate_name)), ports_(std::move(ports)), rule_(std::move(rule)) {}

const GatePort* GateInstance::find_port(const std::string& port_name) const noexcept {
    for (const auto& port : ports_) {
        if (port.name == port_name) {
            return &port;
        }
    }
    return nullptr;
}

const GatePort* GateInstance::find_port(std::uint32_t port_id) const noexcept {
    for (const auto& port : ports_) {
        if (port.id == port_id) {
            return &port;
        }
    }
    return nullptr;
}

std::optional<std::vector<std::uint32_t>> GateInstance::evaluate(const std::vector<std::uint32_t>& inputs) const {
    return rule_.evaluate(inputs);
}

} // namespace lme::logic
