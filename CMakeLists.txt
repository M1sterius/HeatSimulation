cmake_minimum_required(VERSION 3.19)

project(HeatSimulation)

set(CMAKE_CXX_STANDARD 20)

file(GLOB_RECURSE SOURCES "src/*.cpp")
add_executable(HeatSimulation ${SOURCES})

set_target_properties(HeatSimulation PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY_DEBUG "${CMAKE_SOURCE_DIR}/bin/HeatSimulation/Debug"
    RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_SOURCE_DIR}/bin/HeatSimulation/Release"
)

target_compile_definitions(HeatSimulation PRIVATE "SFML_STATIC")

include_directories(
    ${CMAKE_SOURCE_DIR}/dependencies/SFML/include
    ${CMAKE_SOURCE_DIR}/dependencies/glm
)

target_link_directories(HeatSimulation PRIVATE 
    ${CMAKE_SOURCE_DIR}/dependencies/SFML/lib
)

target_link_libraries(HeatSimulation
    sfml-window-s
    sfml-system-s
    opengl32
    freetype
    sfml-graphics-s
    winmm
    gdi32
)
