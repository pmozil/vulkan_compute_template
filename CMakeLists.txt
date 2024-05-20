cmake_minimum_required(VERSION 3.20)
set(PROJ_NAME integrate_parallel_vulkan)
project(${PROJ_NAME} C CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

##########################################################
# User configurable options of the template
##########################################################
# Note: symbols like WARNINGS_AS_ERRORS in configuration are intentionally variables
# and not CMake options --using options creates too many problems for students.

#! It is a good practice to set "WARNINGS_AS_ERRORS" ON,
#  but sometimes it creates too much trouble, so default is OFF.
set(WARNINGS_AS_ERRORS ON)

#! Select appropriate sanitizers.
#  Definitely enable sanitizers while developing.
#  Disable it for the production builds and before submitting for grading.
#  Only one of the Memory (MSAN), Address (ASAN), or Thread (TSan)
#  sanitizers is applicable at the time -- the first defined.

#! UndefinedBehaviorSanitizer (UBSan).
#  Info: https://clang.llvm.org/docs/UndefinedBehaviorSanitizer.html
set(ENABLE_UBSan OFF)
#! AddressSanitizer -- detects use after free or after scope exit,
#  memory overflows and leaks.
#  Info: https://github.com/google/sanitizers/wiki/AddressSanitizer
set(ENABLE_ASAN OFF)
#! ThreadSanitizer -- detects data races.
#  Info: https://clang.llvm.org/docs/ThreadSanitizer.html
set(ENABLE_TSan OFF)
#! MemorySanitizer -- detects uninitialized memory reads
#  Info: https://github.com/google/sanitizers/wiki/MemorySanitizer
set(ENABLE_MSAN OFF)

#! Be default -- build release version if not specified otherwise.
if (NOT CMAKE_BUILD_TYPE)
	set(CMAKE_BUILD_TYPE Release)
endif ()

# Warnings as errors should be imported here -- do not move this line
include(cmake/CompilerWarnings.cmake)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
SET(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS})

find_package(Vulkan REQUIRED)

IF (NOT Vulkan_FOUND)
    message(FATAL_ERROR Could not find Vulkan library!)
ELSE()
    message(STATUS ${Vulkan_LIBRARY})
ENDIF()

find_program(Vulkan_GLSC_VALIDATOR
	NAMES glslc
	HINTS ENV VULKAN_SDK 
    PATH_SUFFIXES bin
)

if (NOT Vulkan_GLSC_VALIDATOR)
    message(FATAL_ERROR "glslc not found!")
endif()

# file(GLOB HEADERS ${CMAKE_SOURCE_DIR}/include/*.h ${CMAKE_SOURCE_DIR}/include/*/*.h)
# include_directories(${CMAKE_SOURCE_DIR}/include)
# include_directories(${CMAKE_SOURCE_DIR}/include/vulkan_base)

# Compile the dependencies

file(GLOB VK_BASE_SRC 
    ${CMAKE_SOURCE_DIR}/src/vulkan_base/*.cpp)

add_library(vk_base ${VK_BASE_SRC})
target_include_directories(vk_base PUBLIC ${CMAKE_SOURCE_DIR}/include)
target_include_directories(vk_base PUBLIC ${CMAKE_SOURCE_DIR}/include/vulkan_base)
target_link_libraries(vk_base PUBLIC Vulkan::Vulkan)

# Complie the application
file(GLOB MAIN_SRC
    ${CMAKE_SOURCE_DIR}/src/main.cpp  
    ${CMAKE_SOURCE_DIR}/src/parse_file.cpp  
    ${CMAKE_SOURCE_DIR}/src/simple_compute_pipeline.cpp)

# set(APP_SOURCE_FILES ${SOURCE_FILES} CACHE INTERNAL STRINGS)
add_executable(${PROJECT_NAME} ${MAIN_SRC})
target_include_directories(${PROJECT_NAME} 
    PUBLIC ${CMAKE_SOURCE_DIR}/include)
target_include_directories(${PROJECT_NAME} 
    PUBLIC ${CMAKE_SOURCE_DIR}/include/vulkan_base)
target_link_libraries(${PROJECT_NAME} PUBLIC vk_base)

# Compile shaders
file(MAKE_DIRECTORY ${PROJECT_BINARY_DIR}/shaders)
set(GLSL_SOURCE_FILES
    "${CMAKE_SOURCE_DIR}/shaders/func1.comp"
    "${CMAKE_SOURCE_DIR}/shaders/func2.comp"
    "${CMAKE_SOURCE_DIR}/shaders/func3.comp"
    "${CMAKE_SOURCE_DIR}/shaders/compute.comp")

foreach(GLSL ${GLSL_SOURCE_FILES})
  get_filename_component(FILE_NAME ${GLSL} NAME)
  set(SPIRV ${PROJECT_BINARY_DIR}/shaders/${FILE_NAME}.spv)
  add_custom_command(
    OUTPUT ${SPIRV}
    COMMAND ${CMAKE_COMMAND} -E make_directory "${PROJECT_BINARY_DIR}/shaders/"
    COMMAND ${Vulkan_GLSC_VALIDATOR} ${GLSL} -o ${SPIRV} --target-env=vulkan1.3 -O
    DEPENDS ${GLSL})
  list(APPEND SPIRV_BINARY_FILES ${SPIRV})
endforeach(GLSL)

add_custom_target(
    Shaders 
    DEPENDS ${SPIRV_BINARY_FILES}
    )

add_dependencies(${PROJ_NAME} Shaders)

# Define ALL_TARGETS variable to use in PVS and Sanitizers
set(ALL_TARGETS ${PROJ_NAME} vk_base)

# Include CMake setup
include(cmake/main-config.cmake)
