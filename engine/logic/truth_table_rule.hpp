#pragma once

#include <cstdint>
#include <optional>
#include <string>
#include <unordered_map>
#include <vector>

namespace lme::logic {

struct TruthTableRow {
    std::vector<std::uint32_t> inputs;
    std::vector<std::uint32_t> outputs;
};

class TruthTableRule {
public:
    TruthTableRule() = default;
    explicit TruthTableRule(std::vector<TruthTableRow> rows);

    std::optional<std::vector<std::uint32_t>> evaluate(const std::vector<std::uint32_t>& inputs) const;

    const std::vector<TruthTableRow>& rows() const noexcept { return rows_; }

private:
    using Key = std::vector<std::uint32_t>;
    struct KeyHash {
        std::size_t operator()(const Key& key) const noexcept;
    };

    std::vector<TruthTableRow> rows_;
    std::unordered_map<Key, std::size_t, KeyHash> index_;
};

} // namespace lme::logic
