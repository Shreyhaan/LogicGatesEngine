#include <cassert>

#include "../engine/geom/collision_ccd.hpp"

int main() {
    using namespace lme;
    using namespace lme::geom;

    Vec2 x1{-1.0, 0.0};
    Vec2 v1{1.0, 0.0};
    Vec2 x2{1.0, 0.0};
    Vec2 v2{-1.0, 0.0};
    auto result = toi_disk_disk(x1, v1, 0.5, x2, v2, 0.5, 0.0, 10.0);
    assert(result.hit);
    assert(result.time > 0.4 && result.time < 0.6);

    Vec2 x3{-1.0, 0.0};
    Vec2 v3{-1.0, 0.0};
    result = toi_disk_disk(x1, v3, 0.5, x2, v2, 0.5, 0.0, 10.0);
    assert(!result.hit);

    return 0;
}
