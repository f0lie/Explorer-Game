#Change this if you need to target a specific CMake version
cmake_minimum_required(VERSION 3.3)

# Name of project
project(legend_of_the_swamp)

# Set cmake flags
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-Wall -pedantic -Wno-reorder")

# Enable debug symbols by default
# must be done before project() statement
if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug CACHE STRING "Choose the type of build (Debug or Release)" FORCE)
endif ()
# (you can also set it on the command line: -D CMAKE_BUILD_TYPE=Release)


# Define sources and executable
set(EXECUTABLE_NAME "legend_of_the_swamp")
file(GLOB LEGEND_OF_THE_SWAMP_SRC
        "src/include/*.h"
        "src/*.cpp")
file(GLOB LIB_SRC
        "lib/EasyBMP/*.h"
        "lib/EasyBMP/*.cpp")
add_executable(${EXECUTABLE_NAME} ${LEGEND_OF_THE_SWAMP_SRC} ${LIB_SRC})


# Detect and add SFML
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})
#Find any version 2.X of SFML
#See the FindSFML.cmake file for additional details and instructions
if (WIN32)
    find_package(SFML 2 REQUIRED system window graphics audio main)
else ()
    find_package(SFML 2 REQUIRED system window graphics audio)
endif ()
if (SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
    target_link_libraries(${EXECUTABLE_NAME} ${SFML_LIBRARIES})
endif ()


# Install target
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR})
install(TARGETS ${EXECUTABLE_NAME} DESTINATION ${PROJECT_SOURCE_DIR})


# CPack packaging
include(InstallRequiredSystemLibraries)
set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_SOURCE_DIR}/COPYING")
include(CPack)