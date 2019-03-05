# Project
cmake_minimum_required(VERSION 3.1)
project(RTSGame)

# Source Files
set(SRC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src")
set(LIB_DIR "${CMAKE_CURRENT_SOURCE_DIR}/lib")
set(INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/include")

include_directories(${INCLUDE_DIR})

set(SRC ${SRC_DIR}/main.cpp

        ${INCLUDE_DIR}/engine/camera.h
        ${SRC_DIR}/engine/camera.cpp
        ${INCLUDE_DIR}/engine/window.h
        ${SRC_DIR}/engine/window.cpp
        ${INCLUDE_DIR}/engine/transform.h
        ${INCLUDE_DIR}/engine/resources_manager.h
        ${SRC_DIR}/engine/resources_manager.cpp
        ${INCLUDE_DIR}/engine/shader.h
        ${SRC_DIR}/engine/shader.cpp
        ${INCLUDE_DIR}/engine/texture.h
        ${SRC_DIR}/engine/texture.cpp

        # Dear ImGui Files
        ${INCLUDE_DIR}/imgui/imconfig.h
        ${SRC_DIR}/imgui/imgui_demo.cpp
        ${SRC_DIR}/imgui/imgui_draw.cpp
        ${INCLUDE_DIR}/imgui/imgui_internal.h
        ${SRC_DIR}/imgui/imgui_widgets.cpp
        ${SRC_DIR}/imgui/imgui.cpp
        ${INCLUDE_DIR}/imgui/imgui.h
        ${INCLUDE_DIR}/imgui/imstb_rectpack.h
        ${INCLUDE_DIR}/imgui/imstb_textedit.h
        ${INCLUDE_DIR}/imgui/imstb_truetype.h
        ${SRC_DIR}/imgui/imgui_impl_glfw.cpp
        ${INCLUDE_DIR}/imgui/imgui_impl_glfw.h
        ${SRC_DIR}/imgui/imgui_impl_opengl3.cpp
        ${INCLUDE_DIR}/imgui/imgui_impl_opengl3.h
        
        # STB Image Files
        ${INCLUDE_DIR}/stb_image.h
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