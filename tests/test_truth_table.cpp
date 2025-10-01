#include <cassert>
#include <vector>

#include "../engine/logic/truth_table_rule.hpp"

int main() {
    using namespace lme::logic;
    TruthTableRule rule({
        {{0, 0}, {1}},
        {{0, 1}, {1}},
        {{1, 0}, {1}},
        {{1, 1}, {0}}
    });

    auto out = rule.evaluate({1, 1});
    assert(out.has_value());
    assert(out->at(0) == 0);

    out = rule.evaluate({0, 1});
    assert(out.has_value());
    assert(out->at(0) == 1);

    out = rule.evaluate({1, 2});
    assert(!out.has_value());

    return 0;
}
