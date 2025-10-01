#include "renderer.hpp"

#include <iomanip>

namespace lme::viewer {

void Renderer::draw(const World& world) const {
    std::cout << std::fixed << std::setprecision(3);
    std::cout << "t=" << world.current_time() << " packets=" << world.packets().size() << '\n';
    for (const auto& packet : world.packets()) {
        if (!packet.alive) {
            continue;
        }
        std::cout << "  id=" << packet.id
                  << " pos=" << packet.kinematics.position
                  << " vel=" << packet.kinematics.velocity
                  << " state=" << packet.state.bits
                  << '\n';
    }
    std::cout.flush();
}

} // namespace lme::viewer
