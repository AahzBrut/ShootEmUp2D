cmake_minimum_required(VERSION 4.2)
project(ShootEmUp2D)

set(CMAKE_TLS_VERIFY FALSE)
set(CMAKE_CXX_STANDARD 20)
set(BUILD_SHARED_LIBS OFF)
add_compile_definitions(FLECS_CPP_NO_AUTO_REGISTRATION)

include(FetchContent)
file(GLOB_RECURSE MY_SOURCES CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)

FetchContent_Declare(
        raylib
        GIT_REPOSITORY https://github.com/raysan5/raylib.git
        GIT_TAG 6.0
        GIT_SHALLOW TRUE
        GIT_PROGRESS TRUE
)

FetchContent_Declare(
        flecs
        GIT_REPOSITORY https://github.com/SanderMertens/flecs.git
        GIT_TAG v4.1.5
        GIT_SHALLOW TRUE
        GIT_PROGRESS TRUE
)

FetchContent_MakeAvailable(raylib flecs)

add_executable(${CMAKE_PROJECT_NAME})
target_sources(${CMAKE_PROJECT_NAME} PRIVATE ${MY_SOURCES})

target_link_options(${CMAKE_PROJECT_NAME} PRIVATE -static-libgcc -static-libstdc++ -static)
target_link_options(${CMAKE_PROJECT_NAME} PRIVATE -mwindows)

target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE raylib flecs_static)
target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE src)

add_custom_command(TARGET ${CMAKE_PROJECT_NAME} POST_BUILD COMMAND
        ${CMAKE_COMMAND} -E copy_directory_if_different
        "${CMAKE_CURRENT_LIST_DIR}/assets" "${CMAKE_CURRENT_BINARY_DIR}/assets")