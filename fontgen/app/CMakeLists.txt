cmake_minimum_required(VERSION 3.11)
include(FetchContent)

project(app)

set(CMAKE_CXX_STANDARD 20)

add_executable(ank_font_generator ank_font_generator.cpp)
target_link_libraries(ank_font_generator fgen)

# Add fgen library with its dependencies to a folder
set_target_properties(fgen PROPERTIES FOLDER "fgen")
# Get all the dependencies of "fgen"
get_target_property(dependencies fgen INTERFACE_LINK_LIBRARIES)
# Iterate over the dependencies and put them in "fgen" folder
foreach(dependency ${dependencies})
    set_target_properties(${dependency} PROPERTIES FOLDER "fgen")
endforeach()

# Copy resources to build directory
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/fonts DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
