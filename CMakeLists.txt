cmake_minimum_required(VERSION 3.24)
project(quadbuffer)

set(CMAKE_CXX_STANDARD 23)


# Bibliothèques

find_package(SDL2 CONFIG REQUIRED)
find_package(glslang CONFIG REQUIRED)
find_package(glm CONFIG REQUIRED)
find_package(Vulkan MODULE REQUIRED COMPONENTS glslc)
find_program(glslc_executable NAMES glslc HINTS Vulkan::glslc)

# Includes

include_directories(AFTER SYSTEM "${CMAKE_CURRENT_SOURCE_DIR}/include")

# Shaders Vulkan

set(SHADER_SOURCE_DIR src/vk_shaders)
set(SHADER_BINARY_DIR ${CMAKE_CURRENT_BINARY_DIR}/shaders)

file(GLOB SHADERS
        ${SHADER_SOURCE_DIR}/*.vert
        ${SHADER_SOURCE_DIR}/*.frag
        ${SHADER_SOURCE_DIR}/*.comp
        ${SHADER_SOURCE_DIR}/*.geom
        ${SHADER_SOURCE_DIR}/*.tesc
        ${SHADER_SOURCE_DIR}/*.tese
        ${SHADER_SOURCE_DIR}/*.mesh
        ${SHADER_SOURCE_DIR}/*.task
        ${SHADER_SOURCE_DIR}/*.rgen
        ${SHADER_SOURCE_DIR}/*.rchit
        ${SHADER_SOURCE_DIR}/*.rmiss)

message(STATUS "Shader Source Dir: ${SHADER_SOURCE_DIR}")
message(STATUS "Shader Binary Dir: ${SHADER_BINARY_DIR}")

add_custom_command(
        COMMAND
        ${CMAKE_COMMAND} -E make_directory ${SHADER_BINARY_DIR}
        OUTPUT ${SHADER_BINARY_DIR}
        COMMENT "Creating ${SHADER_BINARY_DIR}"
)

foreach(source IN LISTS SHADERS)
    get_filename_component(FILENAME ${source} NAME)
    add_custom_command(
            COMMAND
            ${glslc_executable}
            #      -MD -MF ${SHADER_BINARY_DIR}/${FILENAME}.d
            -o ${SHADER_BINARY_DIR}/${FILENAME}.spv
            ${source}
            OUTPUT ${SHADER_BINARY_DIR}/${FILENAME}.spv
            DEPENDS ${source} ${SHADER_BINARY_DIR}
            COMMENT "Compiling ${FILENAME}"
    )
    list(APPEND SPV_SHADERS ${SHADER_BINARY_DIR}/${FILENAME}.spv)
endforeach()

add_custom_target(shady ALL DEPENDS ${SPV_SHADERS})

# Tests

file(GLOB STANDALONE_APPS src/standalone/*.cpp)

foreach(FILE ${STANDALONE_APPS})
    cmake_path(GET FILE STEM PROGNAME)
    SET(TGT "standalone-${PROGNAME}")
    add_executable("${TGT}" ${FILE})
    set(VULKAN_LIB_LIST "vulkan-1")
    target_link_libraries("${TGT}" PRIVATE glm::glm)
    target_link_libraries("${TGT}" PRIVATE Vulkan::Vulkan)
    target_link_libraries("${TGT}" PRIVATE SDL2::SDL2main SDL2::SDL2)
    add_dependencies("${TGT}" shady)
    target_include_directories("${TGT}" PUBLIC ${Vulkan_INCLUDE_DIR})
endforeach ()

