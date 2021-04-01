cmake_minimum_required(VERSION 3.17)
project(anotherengine)

set(CMAKE_CXX_STANDARD 14)

add_executable(anotherengine
        src/Engine.cpp
        src/Engine.h
        src/window/Window.cpp
        src/window/Window.h
        src/gl/buffer.cpp
        src/gl/buffer.h
        src/util/Timer.cpp
        src/util/Timer.h src/scene/Scene.cpp src/scene/Scene.h src/gl/shader.cpp src/gl/shader.h)

# find_package(OpenGL REQUIRED)
# list(APPEND INCLUDE_DIRS ${OPENGL_INCLUDE_DIR})
# target_link_libraries(DoubleShift ${OPENGL_gl_LIBRARY})

# Load GLFW (Window/Context Library)
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

add_subdirectory(lib/glfw)
target_link_libraries(anotherengine glfw)
list(APPEND INCLUDE_DIRS "${PROJECT_SOURCE_DIR}/lib/glfw/include")

# Load GLAD (Modern OpenGL Loader)
add_subdirectory(lib/glad)
target_link_libraries(anotherengine glad)

# Load STB headers
list(APPEND INCLUDE_DIRS "${PROJECT_SOURCE_DIR}/lib/stb")

# Load GLM (Math Library)
list(APPEND INCLUDE_DIRS "${PROJECT_SOURCE_DIR}/lib/glm")

# Include directories
target_include_directories(anotherengine PUBLIC "${PROJECT_BINARY_DIR}" ${INCLUDE_DIRS})