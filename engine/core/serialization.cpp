#include "serialization.hpp"

#include <fstream>
#include <stdexcept>

#include "../../third_party/nlohmann_json.hpp"

using nlohmann::json;

namespace lme::serialization {
namespace {

Vec2 parse_vec2(const json& value) {
    if (!value.is_array() || value.size() != 2) {
        throw std::runtime_error("Expected array[2] for vec2");
    }
    return Vec2{value.at(0).get<Real>(), value.at(1).get<Real>()};
}

logic::GatePort parse_port(const json& j) {
    logic::GatePort port;
    port.id = j.at("id").get<std::uint32_t>();
    port.name = j.at("name").get<std::string>();
    port.position = parse_vec2(j.at("pos"));
    if (j.contains("dir")) {
        port.direction = parse_vec2(j.at("dir"));
    }
    if (j.contains("radius")) {
        port.radius = j.at("radius").get<Real>();
    }
    return port;
}

logic::TruthTableRule parse_truth_table(const json& rule_json) {
    std::vector<logic::TruthTableRow> rows;
    for (const auto& row_json : rule_json.at("table")) {
        logic::TruthTableRow row;
        row.inputs = row_json.at("in").get<std::vector<std::uint32_t>>();
        std::vector<std::uint32_t> outputs;
        for (const auto& out_json : row_json.at("outs")) {
            outputs.push_back(out_json.at("state").get<std::uint32_t>());
        }
        row.outputs = std::move(outputs);
        rows.push_back(std::move(row));
    }
    return logic::TruthTableRule{std::move(rows)};
}

void parse_packets(const json& packets_json, World& world) {
    for (const auto& packet_json : packets_json) {
        PacketKinematics kinematics;
        kinematics.position = parse_vec2(packet_json.at("pos"));
        kinematics.velocity = parse_vec2(packet_json.at("vel"));
        if (packet_json.contains("radius")) {
            kinematics.radius = packet_json.at("radius").get<Real>();
        }
        if (packet_json.contains("mass")) {
            kinematics.mass = packet_json.at("mass").get<Real>();
        }
        PacketState state;
        state.bits = packet_json.at("state").get<std::uint32_t>();
        world.spawn_packet(kinematics, state);
    }
}

void parse_segments(const json& colliders_json, World& world) {
    for (const auto& collider_json : colliders_json) {
        if (collider_json.at("type").get<std::string>() != "segment") {
            continue;
        }
        StaticSegment segment;
        segment.id = collider_json.at("id").get<std::uint32_t>();
        segment.a = parse_vec2(collider_json.at("a"));
        segment.b = parse_vec2(collider_json.at("b"));
        world.segments().push_back(segment);
    }
}

void parse_gates(const json& gates_json, World& world) {
    for (const auto& gate_json : gates_json) {
        std::uint32_t id = gate_json.at("id").get<std::uint32_t>();
        std::string name = gate_json.at("name").get<std::string>();
        std::vector<logic::GatePort> ports;
        for (const auto& port_json : gate_json.at("ports")) {
            ports.push_back(parse_port(port_json));
        }
        logic::TruthTableRule rule;
        if (gate_json.contains("rule")) {
            rule = parse_truth_table(gate_json.at("rule"));
        }
        world.gates().emplace_back(id, std::move(name), std::move(ports), std::move(rule));
    }
}

void parse_emitters(const json& emitters_json, World& world) {
    for (const auto& emitter_json : emitters_json) {
        logic::Emitter emitter;
        emitter.id = emitter_json.at("id").get<std::uint32_t>();
        emitter.port_id = emitter_json.at("port").get<std::uint32_t>();
        if (emitter_json.contains("period")) {
            emitter.period = emitter_json.at("period").get<Real>();
        }
        if (emitter_json.contains("state")) {
            emitter.state = emitter_json.at("state").get<std::uint32_t>();
        }
        if (emitter_json.contains("speed")) {
            emitter.speed = emitter_json.at("speed").get<Real>();
        }
        if (emitter_json.contains("phase")) {
            emitter.phase = emitter_json.at("phase").get<Real>();
        }
        world.emitters().add(emitter);
    }
}

} // namespace

void load_scene_from_stream(std::istream& input, World& world) {
    json data;
    input >> data;
    world.clear();
    if (data.contains("packets")) {
        parse_packets(data.at("packets"), world);
    }
    if (data.contains("colliders")) {
        parse_segments(data.at("colliders"), world);
    }
    if (data.contains("gates")) {
        parse_gates(data.at("gates"), world);
    }
    if (data.contains("emitters")) {
        parse_emitters(data.at("emitters"), world);
    }
}

void load_scene_from_file(const std::string& path, World& world) {
    std::ifstream file(path);
    if (!file) {
        throw std::runtime_error("Failed to open scene file: " + path);
    }
    load_scene_from_stream(file, world);
}

} // namespace lme::serialization
