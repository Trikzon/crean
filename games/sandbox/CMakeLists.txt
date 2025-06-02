cmake_minimum_required(VERSION 3.30)

set(SOURCES
        src/main.cpp
)

add_executable(sandbox ${SOURCES})

target_compile_definitions(crean PUBLIC CR_GAME_ASSETS_DIR="${CMAKE_CURRENT_SOURCE_DIR}/assets")

target_link_libraries(sandbox PRIVATE crean)
