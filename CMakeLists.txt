cmake_minimum_required(VERSION 3.20)
project(game_engine)

set(CMAKE_CXX_STANDARD 20)

# Create executable
add_executable(game_engine
        src/main.cpp
        includes/glad/glad.c
        src/core/engine.cpp
        src/core/engine.h
        src/core/Logger.h
        src/core/Window.cpp
        src/core/Window.h
        src/core/Vertex.h
        src/core/Shader.cpp
        src/core/Shader.h
        src/core/Mesh.h
        src/core/Texture.h
        src/math/Transform.h
        src/core/RenderableObject.cpp
        src/core/RenderableObject.h
        src/core/Material.h
        src/primitives/Square.h
        src/math/Transform.cpp
        src/primitives/Primitives.h
        src/core/Camera.cpp
        src/core/Camera.h
        src/primitives/Sphere.h
)

include(FetchContent)

FetchContent_Declare(
        glm
        GIT_REPOSITORY	https://github.com/g-truc/glm.git
        GIT_TAG 	0af55ccecd98d4e5a8d1fad7de25ba429d60e863 #refs/tags/1.0.1
)

FetchContent_MakeAvailable(glm)

# Include your headers
target_include_directories(game_engine PRIVATE
        ${CMAKE_SOURCE_DIR}/includes
)

# Tell CMake where glfw3.lib is
target_link_directories(game_engine PRIVATE
        ${CMAKE_SOURCE_DIR}/lib
)

# Link libraries
target_link_libraries(game_engine PRIVATE
        glfw3
        opengl32
        glm::glm
)

file(GLOB_RECURSE ASSET_FILES "${CMAKE_SOURCE_DIR}/src/assets/*")

add_custom_target(copy_assets ALL
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/src/assets
        $<TARGET_FILE_DIR:game_engine>/assets
        DEPENDS ${ASSET_FILES}
        COMMENT "Copying assets..."
)

add_dependencies(game_engine copy_assets)

