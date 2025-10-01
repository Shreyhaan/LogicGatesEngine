#pragma once

#include <cmath>
#include <cstdint>
#include <functional>
#include <ostream>

namespace lme {

using Real = double;

struct Vec2 {
    Real x{0};
    Real y{0};

    constexpr Vec2() = default;
    constexpr Vec2(Real x_, Real y_) : x(x_), y(y_) {}

    constexpr Vec2 operator+(const Vec2& rhs) const noexcept {
        return {x + rhs.x, y + rhs.y};
    }

    constexpr Vec2 operator-(const Vec2& rhs) const noexcept {
        return {x - rhs.x, y - rhs.y};
    }

    constexpr Vec2 operator*(Real scalar) const noexcept {
        return {x * scalar, y * scalar};
    }

    constexpr Vec2 operator/(Real scalar) const noexcept {
        return {x / scalar, y / scalar};
    }

    Vec2& operator+=(const Vec2& rhs) noexcept {
        x += rhs.x;
        y += rhs.y;
        return *this;
    }

    Vec2& operator-=(const Vec2& rhs) noexcept {
        x -= rhs.x;
        y -= rhs.y;
        return *this;
    }

    Vec2& operator*=(Real scalar) noexcept {
        x *= scalar;
        y *= scalar;
        return *this;
    }

    Vec2& operator/=(Real scalar) noexcept {
        x /= scalar;
        y /= scalar;
        return *this;
    }
};

inline constexpr Vec2 operator*(Real s, const Vec2& v) noexcept {
    return v * s;
}

inline Real dot(const Vec2& a, const Vec2& b) noexcept {
    return a.x * b.x + a.y * b.y;
}

inline Real cross(const Vec2& a, const Vec2& b) noexcept {
    return a.x * b.y - a.y * b.x;
}

inline Real length_sq(const Vec2& v) noexcept {
    return dot(v, v);
}

inline Real length(const Vec2& v) noexcept {
    return std::sqrt(length_sq(v));
}

inline Vec2 normalize(const Vec2& v, Real eps = 1e-12) noexcept {
    Real len = length(v);
    if (len < eps) {
        return {0.0, 0.0};
    }
    return v / len;
}

struct PacketState {
    std::uint32_t bits{0};
};

struct PacketKinematics {
    Vec2 position{0.0, 0.0};
    Vec2 velocity{0.0, 0.0};
    Real radius{0.05};
    Real mass{1.0};
};

} // namespace lme

namespace std {

template <> struct hash<lme::Vec2> {
    std::size_t operator()(const lme::Vec2& v) const noexcept {
        std::size_t hx = std::hash<lme::Real>{}(v.x);
        std::size_t hy = std::hash<lme::Real>{}(v.y);
        return hx ^ (hy + 0x9e3779b9 + (hx << 6) + (hx >> 2));
    }
};

inline std::ostream& operator<<(std::ostream& os, const lme::Vec2& v) {
    os << '(' << v.x << ',' << v.y << ')';
    return os;
}

} // namespace std
