#include "collision_ccd.hpp"

#include <cmath>
#include <limits>

namespace lme::geom {

TOIResult toi_disk_disk(const Vec2& x1, const Vec2& v1, Real r1,
                        const Vec2& x2, const Vec2& v2, Real r2,
                        Real t_min, Real t_max, Real eps) {
    Vec2 p = x2 - x1;
    Vec2 w = v2 - v1;
    Real R = r1 + r2;
    Real a = dot(w, w);
    Real b = 2.0 * dot(p, w);
    Real c = dot(p, p) - R * R;

    if (c <= 0.0) {
        return {true, t_min + eps, normalize(p)};
    }

    if (a < eps) {
        return {false, 0.0, {0.0, 0.0}};
    }

    Real disc = b * b - 4.0 * a * c;
    if (disc < 0.0) {
        return {false, 0.0, {0.0, 0.0}};
    }

    Real sqrt_disc = std::sqrt(disc);
    Real t0 = (-b - sqrt_disc) / (2.0 * a);
    Real t1 = (-b + sqrt_disc) / (2.0 * a);

    Real t = std::numeric_limits<Real>::infinity();
    if (t0 >= t_min) {
        t = t0;
    } else if (t1 >= t_min) {
        t = t1;
    }

    if (!(t < t_max)) {
        return {false, 0.0, {0.0, 0.0}};
    }

    Vec2 normal = normalize(p + w * t);
    if (length(normal) < eps) {
        normal = {0.0, 1.0};
    }

    return {true, t, normal};
}

} // namespace lme::geom
