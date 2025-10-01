#include <algorithm>
#include <exception>
#include <iostream>

#include "input.hpp"
#include "renderer.hpp"

#include "../engine/core/serialization.hpp"
#include "../engine/sim/process.hpp"

int main(int argc, char** argv) {
    try {
        auto options = lme::viewer::parse_arguments(argc, argv);
        lme::World world;
        lme::serialization::load_scene_from_file(options.scene_path, world);

        lme::Scheduler scheduler;
        lme::viewer::Renderer renderer;

        const lme::Real end_time = world.current_time() + options.duration;
        lme::sim::schedule_pairwise_collisions(world, scheduler, world.current_time() + options.horizon);

        while (world.current_time() < end_time) {
            if (!lme::sim::process_next_event(world, scheduler, world.current_time() + options.horizon)) {
                lme::Real next_time = std::min(end_time, world.current_time() + options.idle_step);
                lme::sim::integrate_to(world, next_time);
                lme::sim::schedule_pairwise_collisions(world, scheduler, world.current_time() + options.horizon);
            }
            renderer.draw(world);
        }

        return 0;
    } catch (const std::exception& ex) {
        std::cerr << "viewer error: " << ex.what() << '\n';
        return 1;
    }
}
