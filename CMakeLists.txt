cmake_minimum_required(VERSION 3.0.0)

set(PROJECT_NAME Attractors)
project(${PROJECT_NAME} VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDART 17)
set(CMAKE_MODULE_PATH /usr/lib/cmake)
set(CMAKE_EXPORT_COMPILE_COMMANDS 1)

add_executable( ${PROJECT_NAME} 
    src/main.cpp

    src/core/Camera/Camera.cpp

    src/core/Objects/Geometry2D.cpp

    src/core/Renderer/ShaderProgram.cpp

    src/core/Renderer/Window.cpp

    src/Scene/Scene.cpp
)

include_directories(src/core)
include_directories(src)

# include glad
add_subdirectory(external/glad)
target_link_libraries(${PROJECT_NAME} glad)

# include glfw
add_subdirectory(external/glfw)
target_link_libraries(${PROJECT_NAME} glfw)

# include glm
find_package(glm REQUIRED)
if(NOT GLM_FOUND)
    message(Error "GLM not found")
endif(NOT GLM_FOUND)
