cmake_minimum_required(VERSION 3.30)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(crean)

set(CR_PLATFORM "GLFW" CACHE STRING "Platform")
set_property(CACHE CR_PLATFORM PROPERTY STRINGS GLFW)

set(INCLUDES
        include/crean/core/logger.hpp
        include/crean/core/types.hpp
        include/crean/platform/platform.hpp
        include/crean/platform/window.hpp
)

set(SOURCES
)

if (CR_PLATFORM STREQUAL "GLFW")
    list(APPEND INCLUDES
            include/crean/platform/glfw/glfw.hpp
            include/crean/platform/glfw/glfw_platform.hpp
            include/crean/platform/glfw/glfw_window.hpp
    )

    list(APPEND SOURCES
            src/crean/platform/glfw/glfw.cpp
            src/crean/platform/glfw/glfw_platform.cpp
            src/crean/platform/glfw/glfw_window.cpp
    )
endif ()

add_library(crean STATIC ${SOURCES} ${INCLUDES})
target_include_directories(crean PUBLIC include)

target_compile_definitions(crean PUBLIC CR_ENGINE_ASSETS_DIR="${CMAKE_CURRENT_SOURCE_DIR}/assets")

if (CMAKE_BUILD_TYPE MATCHES Debug)
    target_compile_definitions(crean PUBLIC CR_DEBUG_MODE)
endif ()

add_subdirectory(external/glm)
target_link_libraries(crean PUBLIC glm)
target_compile_definitions(crean PUBLIC GLM_FORCE_DEPTH_ZERO_TO_ONE GLM_ENABLE_EXPERIMENTAL)

add_subdirectory(external/stduuid)
target_link_libraries(crean PUBLIC stduuid)

if (CR_PLATFORM STREQUAL "GLFW")
    add_subdirectory(external/glfw)
    target_link_libraries(crean PUBLIC glfw)
    target_compile_definitions(crean PUBLIC CR_PLATFORM_GLFW)
endif ()

add_subdirectory(games)
