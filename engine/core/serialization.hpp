#pragma once

#include <istream>
#include <string>

#include "world.hpp"

namespace lme::serialization {

void load_scene_from_stream(std::istream& input, World& world);
void load_scene_from_file(const std::string& path, World& world);

} // namespace lme::serialization
