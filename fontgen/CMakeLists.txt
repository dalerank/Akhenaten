cmake_minimum_required(VERSION 3.11)
include(FetchContent)

FetchContent_Declare(
    freetype
    GIT_REPOSITORY https://github.com/freetype/freetype.git
    GIT_TAG        VER-2-13-3
)
FetchContent_Declare(
    harfbuzz
    GIT_REPOSITORY https://github.com/harfbuzz/harfbuzz.git
    GIT_TAG        7.3.0
)
FetchContent_Declare(
    stb
    GIT_REPOSITORY https://github.com/nothings/stb.git
    GIT_TAG        5736b15f7ea0ffb08dd38af21067c314d6a3aae9
)

project(fgen)

set(CMAKE_CXX_STANDARD 20)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT trex)

file(GLOB_RECURSE SOURCES "fgen/*.cpp" "fgen/*.hpp")
add_library(fgen STATIC ${SOURCES})
target_include_directories(fgen PUBLIC fgen/)
target_link_libraries(fgen freetype harfbuzz)

####################
### Dependencies ###
####################

# FreeType
FetchContent_MakeAvailable(freetype)
target_include_directories(fgen PRIVATE ${freetype_SOURCE_DIR}/src)

# HarfBuzz
set(HB_BUILD_SUBSET OFF CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(harfbuzz)

# stb
FetchContent_MakeAvailable(stb)
target_include_directories(fgen PRIVATE ${stb_SOURCE_DIR})

###### BUILD_APP ###
add_subdirectory(app)