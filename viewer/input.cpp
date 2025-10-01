#include "input.hpp"

#include <cstdlib>
#include <iostream>
#include <stdexcept>

namespace lme::viewer {

ViewerOptions parse_arguments(int argc, char** argv) {
    ViewerOptions options;
    if (argc < 2) {
        throw std::runtime_error("Usage: viewer <scene.json> [duration] [horizon] [idle_step]");
    }
    options.scene_path = argv[1];
    if (argc > 2) {
        options.duration = std::atof(argv[2]);
    }
    if (argc > 3) {
        options.horizon = std::atof(argv[3]);
    }
    if (argc > 4) {
        options.idle_step = std::atof(argv[4]);
    }
    if (options.horizon <= 0.0) {
        options.horizon = 1.0;
    }
    if (options.idle_step <= 0.0) {
        options.idle_step = 0.1;
    }
    return options;
}

} // namespace lme::viewer
