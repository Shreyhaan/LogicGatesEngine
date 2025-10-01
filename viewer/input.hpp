#pragma once

#include <string>

#include "../engine/core/types.hpp"

namespace lme::viewer {

struct ViewerOptions {
    std::string scene_path;
    lme::Real duration{5.0};
    lme::Real horizon{5.0};
    lme::Real idle_step{0.1};
};

ViewerOptions parse_arguments(int argc, char** argv);

} // namespace lme::viewer
