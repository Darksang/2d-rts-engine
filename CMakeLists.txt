# Project
cmake_minimum_required(VERSION 3.1)
project(RTSGame)

# Source Files
set(SRC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src")
set(LIB_DIR "${CMAKE_CURRENT_SOURCE_DIR}/lib")
set(INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/include")

include_directories(${INCLUDE_DIR})

# Add all source files from Box2D
file(GLOB_RECURSE BOX2D ${SRC_DIR}/Box2D/*.cpp)

# Add all source files from ImGui
file(GLOB_RECURSE IMGUI ${SRC_DIR}/imgui/*.cpp)

set(SRC ${SRC_DIR}/main.cpp

        # Engine Files
        ${SRC_DIR}/engine/camera2d.cpp
        ${SRC_DIR}/engine/debug_draw.cpp
        ${SRC_DIR}/engine/engine.cpp
        ${SRC_DIR}/engine/input_state.cpp
        ${SRC_DIR}/engine/shader.cpp
        ${SRC_DIR}/engine/sprite_renderer.cpp
        ${SRC_DIR}/engine/texture.cpp

        ${SRC_DIR}/engine/systems/camera_system.cpp
        ${SRC_DIR}/engine/systems/debug_system.cpp
        ${SRC_DIR}/engine/systems/physics_system.cpp
        ${SRC_DIR}/engine/systems/render_system.cpp

        # Game Files

        # Box2D Files
        ${BOX2D}

        # Dear ImGui Files
        ${IMGUI}
        
        # STB Image Files
        ${SRC_DIR}/stb_image.cpp)

# Executable Definition
add_executable(${PROJECT_NAME} ${SRC})
target_include_directories(${PROJECT_NAME} PRIVATE "${SRC_DIR}" "${INCLUDE_DIR}")
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 11)

# GLFW
set(GLFW_DIR "${LIB_DIR}/glfw")

set(GLFW_BUILD_EXAMPLES OFF CACHE INTERNAL "Build the GLFW example programs")
set(GLFW_BUILD_TESTS OFF CACHE INTERNAL "Build the GLFW test programs")
set(GLFW_BUILD_DOCS OFF CACHE INTERNAL "Build the GLFW documentation")
set(GLFW_INSTALL OFF CACHE INTERNAL "Generate installation target")

add_subdirectory("${GLFW_DIR}")

target_link_libraries(${PROJECT_NAME} "glfw" "${GLFW_LIBRARIES}")
target_include_directories(${PROJECT_NAME} PRIVATE "${GLFW_DIR}/include")
target_compile_definitions(${PROJECT_NAME} PRIVATE "GLFW_INCLUDE_NONE")

# GLAD
set(GLAD_DIR "${LIB_DIR}/glad")

add_library("glad" "${GLAD_DIR}/src/glad.c")

target_include_directories("glad" PRIVATE "${GLAD_DIR}/include")
target_include_directories(${PROJECT_NAME} PRIVATE "${GLAD_DIR}/include")
target_link_libraries(${PROJECT_NAME} "glad" "${CMAKE_DL_LIBS}")