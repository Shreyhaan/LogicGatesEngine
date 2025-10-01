#include "truth_table_rule.hpp"

#include <stdexcept>
#include <utility>

namespace lme::logic {

TruthTableRule::TruthTableRule(std::vector<TruthTableRow> rows)
    : rows_(std::move(rows)) {
    for (std::size_t i = 0; i < rows_.size(); ++i) {
        const auto& key = rows_[i].inputs;
        if (!index_.emplace(key, i).second) {
            throw std::runtime_error("Duplicate row in truth table");
        }
    }
}

std::optional<std::vector<std::uint32_t>> TruthTableRule::evaluate(const std::vector<std::uint32_t>& inputs) const {
    auto it = index_.find(inputs);
    if (it == index_.end()) {
        return std::nullopt;
    }
    return rows_[it->second].outputs;
}

std::size_t TruthTableRule::KeyHash::operator()(const Key& key) const noexcept {
    std::size_t result = 0xcbf29ce484222325ULL;
    for (std::uint32_t value : key) {
        result ^= static_cast<std::size_t>(value) + 0x9e3779b97f4a7c15ULL + (result << 6) + (result >> 2);
    }
    return result;
}

} // namespace lme::logic
