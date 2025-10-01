cmake_minimum_required(VERSION 3.16)
project(LogicMatterEngine LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_library(engine
    engine/core/types.cpp
    engine/core/world.cpp
    engine/core/scheduler.cpp
    engine/core/serialization.cpp
    engine/geom/collision_ccd.cpp
    engine/logic/truth_table_rule.cpp
    engine/logic/gate.cpp
    engine/logic/emitters.cpp
    engine/sim/predict.cpp
    engine/sim/process.cpp
    engine/sim/integrate.cpp
    engine/sim/determinism.cpp
)

target_include_directories(engine PUBLIC engine third_party)

add_executable(viewer
    viewer/main.cpp
    viewer/renderer.cpp
    viewer/input.cpp
)

target_link_libraries(viewer PRIVATE engine)

add_executable(test_toi tests/test_toi.cpp)
target_link_libraries(test_toi PRIVATE engine)

add_executable(test_scheduler tests/test_scheduler.cpp)
target_link_libraries(test_scheduler PRIVATE engine)

add_executable(test_truth_table tests/test_truth_table.cpp)
target_link_libraries(test_truth_table PRIVATE engine)

enable_testing()
add_test(NAME toi COMMAND test_toi)
add_test(NAME scheduler COMMAND test_scheduler)
add_test(NAME truth_table COMMAND test_truth_table)
