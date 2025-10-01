#pragma once

#include <optional>

#include "../core/types.hpp"

namespace lme::geom {

struct TOIResult {
    bool hit{false};
    Real time{0.0};
    Vec2 normal{0.0, 1.0};
};

TOIResult toi_disk_disk(const Vec2& x1, const Vec2& v1, Real r1,
                        const Vec2& x2, const Vec2& v2, Real r2,
                        Real t_min, Real t_max, Real eps = 1e-9);

} // namespace lme::geom
