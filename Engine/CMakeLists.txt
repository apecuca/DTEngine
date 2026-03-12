cmake_minimum_required(VERSION 3.31.7)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(Engine LANGUAGES C CXX)

file(GLOB_RECURSE ENGINE_SOURCES
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
)

add_library(Engine STATIC ${ENGINE_SOURCES})

find_package(glfw3 CONFIG REQUIRED)
find_package(glad CONFIG REQUIRED)
find_package(glm CONFIG REQUIRED)
find_package(Stb REQUIRED)

target_include_directories(Engine
    PUBLIC
        "${CMAKE_CURRENT_SOURCE_DIR}/include"
        "${Stb_INCLUDE_DIR}"
    PRIVATE
        "${CMAKE_CURRENT_SOURCE_DIR}/src"
        "${CMAKE_CURRENT_SOURCE_DIR}/include/Engine"
)

target_link_libraries(Engine 
    PRIVATE
        glad::glad
        glfw
        glm::glm
)

# ---- resources ----

set(RESOURCES_SOURCE "${CMAKE_CURRENT_SOURCE_DIR}/resources")
set(RESOURCES_DEST "$<TARGET_FILE_DIR:Engine>/resources")

add_custom_target(copy_resources ALL
    COMMAND ${CMAKE_COMMAND} -E remove_directory ${RESOURCES_DEST}
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${RESOURCES_SOURCE} ${RESOURCES_DEST}
    COMMENT "Refreshing resources folder"
)

add_dependencies(copy_resources Engine)