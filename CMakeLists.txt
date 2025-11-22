cmake_minimum_required(VERSION 3.16...3.26)
include(CMakeDependentOption)
include(FetchContent)
include(ExternalProject)

set(CMAKE_BUILD_PLATFORM "default" CACHE STRING "Platform to cross-compile for. Options: android default")

option(OPTION_ENABLE_TRACY "Enable Tracy profiler support" OFF)

message(STATUS "OPTION_ENABLE_TRACY: ${OPTION_ENABLE_TRACY}")

if (CMAKE_BUILD_PLATFORM STREQUAL "win_emscripten")
    message("Platform: win + emscripten")
    set(WIN_EMSCRIPTEN TRUE) 
else()
    set(WIN_EMSCRIPTEN FALSE)
endif()

if (CMAKE_BUILD_PLATFORM STREQUAL "android")
    message("Platform: android")
    set(PLATFORM_ANDROID TRUE)
else()
    set(PLATFORM_ANDROID FALSE)
endif()

#
# Akhenaten
#

set(GAME akhenaten)
project(${GAME} C CXX)
message("C++ compiler is ${CMAKE_CXX_COMPILER_ID}" )

set(GAME_ARCH_64 TRUE)
set(GAME_PROCESSOR_ARCH "x64")

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")
include("${CMAKE_MODULE_PATH}/CMakeRC.cmake")

# Force using zlib from FetchContent, ignore system zlib
# This prevents find_package(ZLIB) from finding system libraries
set(CMAKE_FIND_PACKAGE_PREFER_CONFIG TRUE)

# Dependency versions
set(SDL2_VERSION "2.32.10")
set(SDL2_MIXER_VERSION "2.8.0")
set(CPPTRACE_VERSION "v1.0.4")
set(TRACY_VERSION "v0.10")
set(CURL_VERSION "curl-8_10_1")
set(ZLIB_VERSION "v1.3.1")
set(FREETYPE_VERSION "VER-2-13-3")
set(HARFBUZZ_VERSION "7.3.0")
set(STB_VERSION "5736b15f7ea0ffb08dd38af21067c314d6a3aae9")
set(LIBPNG_VERSION "v1.6.50")
set(IMGUI_VERSION "v1.92.2")

#
# CppTrace
#

if(PLATFORM_ANDROID)
    # no cpptrace for android
else()
    if(CMAKE_BUILD_TYPE STREQUAL "RelWithDebInfo" OR CMAKE_BUILD_TYPE STREQUAL "Debug")
        if (APPLE AND CMAKE_BUILD_TYPE STREQUAL "Debug") # Get meaningful trace on memory access errors etc.
            add_compile_options(-fsanitize=address)
            add_link_options(-fsanitize=address)
        endif()

        add_definitions(-DCPPTRACE_ENABLED=ON)
        add_definitions(-DCPPTRACE_STATIC_DEFINE)

        FetchContent_Declare(
                cpptrace
                GIT_REPOSITORY https://github.com/jeremy-rifkin/cpptrace.git
                GIT_TAG        ${CPPTRACE_VERSION}
        )
        FetchContent_MakeAvailable(cpptrace)

        set(CPPTRACE_LIBRARY cpptrace::cpptrace)
    endif()
endif()

if (MSVC)
    add_compile_options(/wd4244)
    add_compile_options(/MP)
    add_compile_options(/EHsc)
elseif (APPLE)
    set(CMAKE_CXX_FLAGS "-Wno-c++11-narrowing -Wno-deprecated-declarations -Wno-switch --std=c++17 -fno-exceptions -stdlib=libc++ ${CMAKE_CXX_FLAGS}")
elseif(PLATFORM_ANDROID)
    set(CMAKE_CXX_FLAGS "-Wno-c++11-narrowing -fno-exceptions -Wno-switch -Wno-non-pod-varargs --std=c++17 -Wno-constant-conversion ${CMAKE_CXX_FLAGS}")
elseif(WIN_EMSCRIPTEN)
    if(DEFINED ENV{EMSDK})
        set(EMSDK $ENV{EMSDK})
        set(CMAKE_TOOLCHAIN_FILE "$ENV{EMSDK}/upstream/emscripten/cmake/Modules/Platform/Emscripten.cmake" CACHE PATH "toolchain file")
    else()
        message(FATAL_ERROR "Please define EMSDK to Emscripten SDK in system path!")
    endif()
    message("Emscripten SDK: ${EMSDK}")
    set(USE_FLAGS "-sSDL2_MIXER_FORMATS=mp3 -s USE_MPG123=1 -gsource-map")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${USE_FLAGS}")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} \
    ${USE_FLAGS} \
    -sASYNCIFY -sASYNCIFY_STACK_SIZE=32768 \
    -sALLOW_MEMORY_GROWTH -sINITIAL_MEMORY=128mb -sMEMORY_GROWTH_LINEAR_STEP=32mb \
    -sENVIRONMENT=web \
    -sMODULARIZE \
    -sEXPORT_ALL -sEXPORTED_RUNTIME_METHODS=callMain,addRunDependency,removeRunDependency \
    -lidbfs.js")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} \
    -Wno-c++11-narrowing \
    -fno-exceptions \
    -Wno-varargs \
    -Wno-constant-conversion \
    -Wno-non-pod-varargs \
    --std=c++17 \
    ${USE_FLAGS}")
elseif(UNIX)
    set(CMAKE_CXX_FLAGS "-fno-exceptions -static-libgcc --std=c++17 -static-libstdc++ ${CMAKE_CXX_FLAGS}")
else()
    set(CMAKE_CXX_FLAGS "-Wno-c++11-narrowing -fno-exceptions -static-libgcc --std=c++17 -static-libstdc++ ${CMAKE_CXX_FLAGS}")
endif()

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(GAME_WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}/bin_x64")

if(CMAKE_BUILD_TYPE STREQUAL "RelWithDebInfo")
    SET(GAME_BUILD_TYPE "RelWithDebInfo")
elseif(CMAKE_BUILD_TYPE STREQUAL "Release")
    SET(GAME_BUILD_TYPE "Release")
else()
    SET(GAME_BUILD_TYPE "Debug")
endif()

#
# Dependencies and libs
#
if (MSVC OR WIN_EMSCRIPTEN)
    # Unified configuration for MSVC and WIN_EMSCRIPTEN
    set(LOCAL_DEPS_ROOT "${CMAKE_CURRENT_SOURCE_DIR}/_deps")
    
    # Setup SDL2 FetchContent
    if (EXISTS "${LOCAL_DEPS_ROOT}/SDL2-src/CMakeLists.txt")
        set(FETCHCONTENT_SOURCE_DIR_SDL2 "${LOCAL_DEPS_ROOT}/SDL2-src")
        set(FETCHCONTENT_UPDATES_DISCONNECTED_SDL2 TRUE)
    endif()
    
    FetchContent_Declare(
        SDL2
        GIT_REPOSITORY https://github.com/libsdl-org/SDL.git
        GIT_TAG        release-${SDL2_VERSION}
    )
    
    # Configure SDL2 build options - build as static library
    set(SDL_SHARED OFF CACHE BOOL "" FORCE)
    set(SDL_STATIC ON CACHE BOOL "" FORCE)
    set(SDL_STATIC_PIC ON CACHE BOOL "" FORCE)
    set(SDL_TEST OFF CACHE BOOL "" FORCE)
    
    FetchContent_MakeAvailable(SDL2)
    
    # Set SDL2 variables for linking
    set(SDL2_LIBRARY SDL2::SDL2)
    get_target_property(SDL2_INCLUDE_DIR_TEMP SDL2::SDL2 INTERFACE_INCLUDE_DIRECTORIES)
    if(SDL2_INCLUDE_DIR_TEMP)
        list(GET SDL2_INCLUDE_DIR_TEMP 0 SDL2_INCLUDE_DIR)
    else()
        # Fallback: construct from source dir if available
        if(DEFINED SDL2_SOURCE_DIR)
            set(SDL2_INCLUDE_DIR "${SDL2_SOURCE_DIR}/include")
        endif()
    endif()
    set(SDL_EXT_DIR ${CMAKE_CURRENT_SOURCE_DIR}/ext/SDL2)
    
    if (EXISTS "${LOCAL_DEPS_ROOT}/SDL2_mixer-src/CMakeLists.txt")
        set(FETCHCONTENT_SOURCE_DIR_SDL2_MIXER "${LOCAL_DEPS_ROOT}/SDL2_mixer-src")
        set(FETCHCONTENT_UPDATES_DISCONNECTED_SDL2_MIXER TRUE)
    endif()
    
    FetchContent_Declare(
        SDL2_mixer
        GIT_REPOSITORY https://github.com/libsdl-org/SDL_mixer.git
        GIT_TAG        release-${SDL2_MIXER_VERSION}
    )
    
    set(SDL2_SHARED OFF CACHE BOOL "" FORCE)
    set(SDL2MIXER_SAMPLES OFF CACHE BOOL "" FORCE)
    set(SDL2MIXER_VENDORED ON CACHE BOOL "" FORCE)
    set(SDL2MIXER_SHARED OFF CACHE BOOL "" FORCE)
    
    FetchContent_MakeAvailable(SDL2_mixer)
    
    # Set SDL2_mixer variables for linking
    # SDL2_mixer may create different target names depending on version
    if(TARGET SDL2::SDL2_mixer)
        set(SDL2_MIXER_LIBRARY SDL2::SDL2_mixer)
        get_target_property(SDL2_MIXER_INCLUDE_DIR_TEMP SDL2::SDL2_mixer INTERFACE_INCLUDE_DIRECTORIES)
        if(SDL2_MIXER_INCLUDE_DIR_TEMP)
            list(GET SDL2_MIXER_INCLUDE_DIR_TEMP 0 SDL2_MIXER_INCLUDE_DIR)
        endif()
    elseif(TARGET SDL2_mixer::SDL2_mixer)
        set(SDL2_MIXER_LIBRARY SDL2_mixer::SDL2_mixer)
        get_target_property(SDL2_MIXER_INCLUDE_DIR_TEMP SDL2_mixer::SDL2_mixer INTERFACE_INCLUDE_DIRECTORIES)
        if(SDL2_MIXER_INCLUDE_DIR_TEMP)
            list(GET SDL2_MIXER_INCLUDE_DIR_TEMP 0 SDL2_MIXER_INCLUDE_DIR)
        endif()
    elseif(TARGET SDL2_mixer)
        set(SDL2_MIXER_LIBRARY SDL2_mixer)
        get_target_property(SDL2_MIXER_INCLUDE_DIR_TEMP SDL2_mixer INTERFACE_INCLUDE_DIRECTORIES)
        if(SDL2_MIXER_INCLUDE_DIR_TEMP)
            list(GET SDL2_MIXER_INCLUDE_DIR_TEMP 0 SDL2_MIXER_INCLUDE_DIR)
        endif()
    else()
        # Fallback: assume SDL2::SDL2_mixer will be available at link time
        set(SDL2_MIXER_LIBRARY SDL2::SDL2_mixer)
    endif()
    
    # Fallback: use source directory for includes if target properties not available
    if(NOT SDL2_MIXER_INCLUDE_DIR AND DEFINED SDL2_mixer_SOURCE_DIR)
        set(SDL2_MIXER_INCLUDE_DIR "${SDL2_mixer_SOURCE_DIR}/include")
    endif()
endif()

# Use Tracy from repository via FetchContent (optional)
set(TRACY_FILES "")
if (OPTION_ENABLE_TRACY)
    set(LOCAL_DEPS_ROOT "${CMAKE_CURRENT_SOURCE_DIR}/_deps")
    if (EXISTS "${LOCAL_DEPS_ROOT}/tracy-src/CMakeLists.txt")
        set(FETCHCONTENT_SOURCE_DIR_TRACY "${LOCAL_DEPS_ROOT}/tracy-src")
        set(FETCHCONTENT_UPDATES_DISCONNECTED_TRACY TRUE)
    endif()

    FetchContent_Declare(
        tracy
        GIT_REPOSITORY https://github.com/wolfpld/tracy.git
        GIT_TAG        ${TRACY_VERSION}
    )

    # Configure Tracy options before FetchContent_MakeAvailable
    # Build Tracy as static library
    set(TRACY_STATIC ON CACHE BOOL "" FORCE)
    option(TRACY_ENABLE "Enable profiling" ON)

    FetchContent_MakeAvailable(tracy)
endif()

if (MSVC)
    set(LOCAL_DEPS_ROOT "${CMAKE_CURRENT_SOURCE_DIR}/_deps")
    if (EXISTS "${LOCAL_DEPS_ROOT}/curl-src/CMakeLists.txt")
        set(FETCHCONTENT_SOURCE_DIR_CURL "${LOCAL_DEPS_ROOT}/curl-src")
        set(FETCHCONTENT_UPDATES_DISCONNECTED_CURL TRUE)
    endif()
    
    FetchContent_Declare(
        curl
        GIT_REPOSITORY https://github.com/curl/curl.git
        GIT_TAG        ${CURL_VERSION}
    )
    
    # Configure curl build options
    set(BUILD_SHARED_LIBS OFF CACHE BOOL "" FORCE)
    set(BUILD_CURL_EXE OFF CACHE BOOL "" FORCE)
    set(CURL_DISABLE_LDAP ON CACHE BOOL "" FORCE)
    set(CURL_DISABLE_LDAPS ON CACHE BOOL "" FORCE)
    set(CURL_DISABLE_TELNET ON CACHE BOOL "" FORCE)
    set(CURL_DISABLE_DICT ON CACHE BOOL "" FORCE)
    set(CURL_DISABLE_FILE ON CACHE BOOL "" FORCE)
    set(CURL_DISABLE_FTP ON CACHE BOOL "" FORCE)
    set(CURL_DISABLE_GOPHER ON CACHE BOOL "" FORCE)
    set(CURL_DISABLE_IMAP ON CACHE BOOL "" FORCE)
    set(CURL_DISABLE_POP3 ON CACHE BOOL "" FORCE)
    set(CURL_DISABLE_RTSP ON CACHE BOOL "" FORCE)
    set(CURL_DISABLE_SMTP ON CACHE BOOL "" FORCE)
    set(CURL_DISABLE_TFTP ON CACHE BOOL "" FORCE)
    set(CURL_USE_SCHANNEL ON CACHE BOOL "" FORCE)  # Use Windows Schannel instead of OpenSSL
    set(CURL_USE_OPENSSL OFF CACHE BOOL "" FORCE)  # Explicitly disable OpenSSL
    set(CURL_CA_BUNDLE "" CACHE STRING "" FORCE)
    set(CURL_CA_PATH "" CACHE STRING "" FORCE)
    
    FetchContent_MakeAvailable(curl)
endif()

if (CMAKE_BUILD_DEPENDENCIES STREQUAL "android")
    set(SDL2_SRC_CHECK_PATH "${SDL2_EXTRACT_PATH}/SDL2-${SDL2_VERSION}/include/SDL.h")
    set(SDL2_SRC_DOWNLOAD_URL "https://github.com/libsdl-org/SDL/releases/download/release-${SDL2_VERSION}/SDL2-${SDL2_VERSION}.zip")
    set(SDL2_SRC_DEP_FILENAME "SDL2-${SDL2_VERSION}.zip")
    set(SDL2_SRC_UNPACK_DIR "SDL2-${SDL2_VERSION}")
    set(SDL2_SRC_TMP_ZIP_PATH "${CMAKE_BINARY_DIR}/tmp/${SDL2_SRC_DEP_FILENAME}")
    set(SDL2_SRC_EXTRACT_PATH "${CMAKE_CURRENT_SOURCE_DIR}/ext/SDL2")
    if (NOT EXISTS "${SDL2_SRC_CHECK_PATH}")
        message("Download SDL2 sources to ${SDL2_SRC_TMP_ZIP_PATH}")
        file(DOWNLOAD "${SDL2_SRC_DOWNLOAD_URL}" "${SDL2_SRC_TMP_ZIP_PATH}")
        message("Unpack SDL2 sources to ${SDL2_SRC_EXTRACT_PATH}")
        execute_process(COMMAND ${CMAKE_COMMAND} -E tar xzf ${SDL2_SRC_TMP_ZIP_PATH} WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/tmp)
        file(COPY ${CMAKE_BINARY_DIR}/tmp/${SDL2_SRC_UNPACK_DIR} DESTINATION ${SDL2_SRC_EXTRACT_PATH})
    endif()

    set(SDL2_MIXER_VERSION "2.8.0")
    set(SDL2_MIXER_SRC_CHECK_PATH "${SDL2_EXTRACT_PATH}/SDL2_mixer-${SDL2_MIXER_VERSION}/mixer.h")
    set(SDL2_MIXER_SRC_DOWNLOAD_URL "https://github.com/libsdl-org/SDL_mixer/archive/refs/tags/release-${SDL2_MIXER_VERSION}.zip")
    set(SDL2_MIXER_SRC_DEP_FILENAME "SDL2_mixer-${SDL2_MIXER_VERSION}.zip")
    set(SDL2_MIXER_SRC_UNPACK_DIR "SDL2_mixer-${SDL2_MIXER_VERSION}")
    set(SDL2_MIXER_SRC_TMP_ZIP_PATH "${CMAKE_BINARY_DIR}/tmp/${SDL2_MIXER_SRC_DEP_FILENAME}")

    if (NOT EXISTS "${SDL2_MIXER_SRC_CHECK_PATH}")
        message("Download SDL2_mixer sources to ${SDL2_MIXER_SRC_TMP_ZIP_PATH}")
        file(DOWNLOAD "${SDL2_MIXER_SRC_DOWNLOAD_URL}" "${SDL2_MIXER_SRC_TMP_ZIP_PATH}")
        message("Unpack SDL2_mixer sources to ${CMAKE_BINARY_DIR}/tmp")
        execute_process(COMMAND ${CMAKE_COMMAND} -E tar xzf ${SDL2_MIXER_SRC_TMP_ZIP_PATH} WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/tmp)
        message("Copy SDL2_mixer sources to ${SDL2_SRC_EXTRACT_PATH}")
        file(RENAME ${CMAKE_BINARY_DIR}/tmp/SDL_mixer-release-${SDL2_MIXER_VERSION} ${CMAKE_BINARY_DIR}/tmp/SDL2_mixer-${SDL2_MIXER_VERSION})
        file(COPY ${CMAKE_BINARY_DIR}/tmp/SDL2_mixer-${SDL2_MIXER_VERSION} DESTINATION ${SDL2_SRC_EXTRACT_PATH})
        set(SDL2_MIXER_SRC_EXTRACT_PATH "${CMAKE_BINARY_DIR}/tmp/SDL2_mixer-${SDL2_MIXER_VERSION}")
        file(COPY ${SDL2_MIXER_SRC_EXTRACT_PATH}/include/SDL_mixer.h DESTINATION ${SDL2_EXTRACT_PATH}/SDL2_mixer-${SDL2_MIXER_VERSION}/include)
    endif()
endif()

set(PREBUILT_LIBS_INTERMEDIATE_DIR "${CMAKE_BINARY_DIR}/prebuilt_libs" CACHE PATH "Directory for prebuilt libraries")
set(PREBUILT_LIBS_DIR "${CMAKE_BINARY_DIR}/libs")

set(LOCAL_DEPS_ROOT "${CMAKE_CURRENT_SOURCE_DIR}/_deps")
if (EXISTS "${LOCAL_DEPS_ROOT}/zlib-src/CMakeLists.txt")
    set(FETCHCONTENT_SOURCE_DIR_ZLIB "${LOCAL_DEPS_ROOT}/zlib-src")
    set(FETCHCONTENT_UPDATES_DISCONNECTED_ZLIB TRUE)
endif()

#
#zlib section begin
#

FetchContent_Declare(
    zlib
    GIT_REPOSITORY https://github.com/madler/zlib
    GIT_TAG ${ZLIB_VERSION}
)

FetchContent_GetProperties(zlib)
if(NOT zlib_POPULATED)
    FetchContent_Populate(zlib)
endif()

set(ZLIB_SOURCE_DIR "${zlib_SOURCE_DIR}")
set(ZLIB_BUILD_BASE_DIR "${PREBUILT_LIBS_INTERMEDIATE_DIR}/zlib")
set(ZLIB_BUILD_DIR "${ZLIB_BUILD_BASE_DIR}/build")
set(ZLIB_INSTALL_DIR "${CMAKE_BINARY_DIR}/libs/zlib")
set(ZLIB_BUILD_CONFIG ${CMAKE_BUILD_TYPE})

# Create build directory in prebuild_libs/zlib
file(MAKE_DIRECTORY ${ZLIB_BUILD_BASE_DIR})
file(MAKE_DIRECTORY ${ZLIB_BUILD_DIR})
file(MAKE_DIRECTORY ${ZLIB_INSTALL_DIR})

# Prepare variables for BuildZlib.cmake
set(ZLIB_BUILD_SCRIPT "${CMAKE_SOURCE_DIR}/cmake/BuildZlib.cmake")

# Build zlib using execute_process (runs during configuration phase)
message(STATUS "Building zlib static library...")
execute_process(
    COMMAND ${CMAKE_COMMAND} 
        -DZLIB_VERSION=${ZLIB_VERSION}
        -DZLIB_SOURCE_DIR=${ZLIB_SOURCE_DIR}
        -DZLIB_BUILD_DIR=${ZLIB_BUILD_DIR}
        -DZLIB_INSTALL_DIR=${ZLIB_INSTALL_DIR}
        -DZLIB_BUILD_CONFIG=${ZLIB_BUILD_CONFIG}
        -DZLIB_IS_MSVC=${MSVC}
        -P ${ZLIB_BUILD_SCRIPT}
    WORKING_DIRECTORY ${ZLIB_BUILD_BASE_DIR}
    RESULT_VARIABLE ZLIB_BUILD_RESULT
)

# Set ZLIB library path - use absolute path to avoid issues with find_package
if(MSVC)
    if(CMAKE_BUILD_TYPE STREQUAL "Debug" OR NOT CMAKE_BUILD_TYPE)
        set(ZLIB_LIBRARY "${ZLIB_INSTALL_DIR}/zlibstaticd.lib")
    else()
        set(ZLIB_LIBRARY "${ZLIB_INSTALL_DIR}/zlibstatic.lib")
    endif()
else()
    set(ZLIB_LIBRARY "${ZLIB_INSTALL_DIR}/libzlibstatic.a")
endif()   

# Convert to absolute path to ensure correct linking
get_filename_component(ZLIB_LIBRARY "${ZLIB_LIBRARY}" ABSOLUTE)

set(ZLIB_INCLUDE_DIR "${ZLIB_INSTALL_DIR}/include" CACHE PATH "Path to zlib include directory" FORCE)
set(ZLIB_ROOT "${ZLIB_INSTALL_DIR}" CACHE PATH "Path to zlib installation" FORCE)
set(ZLIB_FOUND TRUE CACHE BOOL "Whether zlib was found" FORCE)

# Set ZLIB_LIBRARIES for compatibility with find_package(ZLIB)
set(ZLIB_LIBRARIES "${ZLIB_LIBRARY}" CACHE FILEPATH "Path to zlib library" FORCE)

#
# zlib section end
#

#
# freetype section begin (must be before harfbuzz for harfbuzz to use freetype)
#

set(LOCAL_DEPS_ROOT "${CMAKE_CURRENT_SOURCE_DIR}/_deps")
if (EXISTS "${LOCAL_DEPS_ROOT}/freetype-src/CMakeLists.txt")
    set(FETCHCONTENT_SOURCE_DIR_FREETYPE "${LOCAL_DEPS_ROOT}/freetype-src")
    set(FETCHCONTENT_UPDATES_DISCONNECTED_FREETYPE TRUE)
endif()

# Configure freetype build options before FetchContent_MakeAvailable
# First build freetype without harfbuzz
set(BUILD_SHARED_LIBS OFF CACHE BOOL "" FORCE)
set(FT_DISABLE_ZLIB OFF CACHE BOOL "" FORCE)
set(FT_REQUIRE_ZLIB ON CACHE BOOL "" FORCE)
set(FT_REQUIRE_HARFBUZZ OFF CACHE BOOL "" FORCE)  # Build freetype first without harfbuzz

FetchContent_Declare(
    freetype
    GIT_REPOSITORY https://github.com/freetype/freetype.git
    GIT_TAG        ${FREETYPE_VERSION}
)

FetchContent_MakeAvailable(freetype)
set(FREETYPE_SOURCE_DIR "${freetype_SOURCE_DIR}")
set(FREETYPE_LIBRARY freetype)
set(FREETYPE_INCLUDE_DIR "${FREETYPE_SOURCE_DIR}/include")
set(FREETYPE_INCLUDE_DIRS "${FREETYPE_INCLUDE_DIR}" CACHE INTERNAL "Path to freetype include directory" FORCE)

set(FREETYPE_ROOT "${FREETYPE_SOURCE_DIR}" CACHE INTERNAL "Path to freetype source" FORCE)
set(FREETYPE_FOUND TRUE CACHE INTERNAL "Whether freetype was found" FORCE)

#
# freetype section end
#

#
# harfbuzz section begin
#

set(LOCAL_DEPS_ROOT "${CMAKE_CURRENT_SOURCE_DIR}/_deps")
if (EXISTS "${LOCAL_DEPS_ROOT}/harfbuzz-src/CMakeLists.txt")
    set(FETCHCONTENT_SOURCE_DIR_HARFBUZZ "${LOCAL_DEPS_ROOT}/harfbuzz-src")
    set(FETCHCONTENT_UPDATES_DISCONNECTED_HARFBUZZ TRUE)
endif()

# Configure harfbuzz build options before FetchContent_MakeAvailable
set(HB_BUILD_SUBSET OFF CACHE BOOL "" FORCE)
set(BUILD_SHARED_LIBS OFF CACHE BOOL "" FORCE)
# Set freetype variables for harfbuzz to find
set(Freetype_ROOT ${FREETYPE_SOURCE_DIR} CACHE PATH "" FORCE)
set(Freetype_INCLUDE_DIR ${FREETYPE_INCLUDE_DIRS} CACHE PATH "" FORCE)
set(Freetype_INCLUDE_DIRS ${FREETYPE_INCLUDE_DIRS} CACHE PATH "" FORCE)
set(Freetype_LIBRARY ${FREETYPE_LIBRARY} CACHE STRING "" FORCE)
# Add freetype to CMAKE_PREFIX_PATH so harfbuzz can find it via find_package
set(CMAKE_PREFIX_PATH "${FREETYPE_ROOT};${CMAKE_PREFIX_PATH}" CACHE PATH "" FORCE)

FetchContent_Declare(
    harfbuzz
    GIT_REPOSITORY https://github.com/harfbuzz/harfbuzz.git
    GIT_TAG        ${HARFBUZZ_VERSION}
)

FetchContent_MakeAvailable(harfbuzz)

# Set harfbuzz variables for linking
set(HARFBUZZ_SOURCE_DIR "${harfbuzz_SOURCE_DIR}")
if(TARGET harfbuzz::harfbuzz)
    set(HARFBUZZ_LIBRARY harfbuzz::harfbuzz)
    get_target_property(HARFBUZZ_INCLUDE_DIR_TEMP harfbuzz::harfbuzz INTERFACE_INCLUDE_DIRECTORIES)
    if(HARFBUZZ_INCLUDE_DIR_TEMP)
        list(GET HARFBUZZ_INCLUDE_DIR_TEMP 0 HARFBUZZ_INCLUDE_DIR)
    else()
        set(HARFBUZZ_INCLUDE_DIR "${HARFBUZZ_SOURCE_DIR}/src")
    endif()
else()
    # Fallback
    set(HARFBUZZ_LIBRARY harfbuzz)
    set(HARFBUZZ_INCLUDE_DIR "${HARFBUZZ_SOURCE_DIR}/src")
endif()

set(HARFBUZZ_INCLUDE_DIRS "${HARFBUZZ_INCLUDE_DIR}" CACHE INTERNAL "Path to harfbuzz include directory" FORCE)
set(HARFBUZZ_ROOT "${HARFBUZZ_SOURCE_DIR}" CACHE INTERNAL "Path to harfbuzz source" FORCE)
set(HarfBuzz_ROOT "${HARFBUZZ_SOURCE_DIR}" CACHE INTERNAL "Path to harfbuzz source (alternative name)" FORCE)
set(HARFBUZZ_FOUND TRUE CACHE INTERNAL "Whether harfbuzz was found" FORCE)

#
# harfbuzz section end
#

FetchContent_Declare(
    stb
    GIT_REPOSITORY https://github.com/nothings/stb.git
    GIT_TAG        ${STB_VERSION}
)
FetchContent_MakeAvailable(stb)

set(LOCAL_DEPS_ROOT "${CMAKE_CURRENT_SOURCE_DIR}/_deps")
if (EXISTS "${LOCAL_DEPS_ROOT}/imgui-src/CMakeLists.txt")
    set(FETCHCONTENT_SOURCE_DIR_IMGUI "${LOCAL_DEPS_ROOT}/imgui-src")
    set(FETCHCONTENT_UPDATES_DISCONNECTED_IMGUI TRUE)
endif()

FetchContent_Declare(
    imgui
    GIT_REPOSITORY https://github.com/ocornut/imgui.git
    GIT_TAG        ${IMGUI_VERSION}
)
FetchContent_MakeAvailable(imgui)

if (PLATFORM_ANDROID)
    set(PROJECT_VERSION_MAJOR 0)
    set(PROJECT_VERSION_MINOR 2)
    set(PROJECT_VERSION_PATCH 2)
    set(IS_RELEASE_VERSION FALSE)
    set(VERSION_REVISION "")
endif()

if (PLATFORM_ANDROID OR WIN_EMSCRIPTEN OR APPLE)
else()
    add_subdirectory(ext/gpupixel)
endif()

file(GLOB PLATFORM_FILES ${PROJECT_SOURCE_DIR}/src/platform/*.cpp)
file(GLOB CONFIG_FILES ${PROJECT_SOURCE_DIR}/src/config/*.cpp)
file(GLOB CONTENT_FILES ${PROJECT_SOURCE_DIR}/src/content/*.cpp)
file(GLOB CORE_FILES ${PROJECT_SOURCE_DIR}/src/core/*.cpp)
file(GLOB CORE_ENCODING_FILES ${PROJECT_SOURCE_DIR}/src/core/encoding/*.cpp)
file(GLOB BUILDING_FILES ${PROJECT_SOURCE_DIR}/src/building/*.cpp)
file(GLOB BUILDING_CONSTRUCTION_FILES ${PROJECT_SOURCE_DIR}/src/building/construction/*.cpp)
file(GLOB CITY_FILES ${PROJECT_SOURCE_DIR}/src/city/*.cpp)
file(GLOB EMPIRE_FILES ${PROJECT_SOURCE_DIR}/src/empire/*.cpp)
file(GLOB FIGURE_FILES ${PROJECT_SOURCE_DIR}/src/figure/*.cpp)
file(GLOB FIGURETYPE_FILES ${PROJECT_SOURCE_DIR}/src/figuretype/*.cpp)
file(GLOB GAME_FILES ${PROJECT_SOURCE_DIR}/src/game/*.cpp)
file(GLOB TUTORIAL_FILES ${PROJECT_SOURCE_DIR}/src/tutorial/*.cpp)
file(GLOB INPUT_FILES ${PROJECT_SOURCE_DIR}/src/input/*.cpp)
file(GLOB GRID_FILES ${PROJECT_SOURCE_DIR}/src/grid/*.cpp)
file(GLOB GRID_ROUTING_FILES ${PROJECT_SOURCE_DIR}/src/grid/routing/*.cpp)
file(GLOB SCENARIO_FILES ${PROJECT_SOURCE_DIR}/src/scenario/*.cpp)
file(GLOB GRAPHICS_ELEMENTS_FILES ${PROJECT_SOURCE_DIR}/src/graphics/elements/*.cpp)
file(GLOB GRAPHICS_VIEW_FILES ${PROJECT_SOURCE_DIR}/src/graphics/view/*.cpp)
file(GLOB GRAPHICS_FONTGEN_FILES ${PROJECT_SOURCE_DIR}/src/graphics/fontgen/*.cpp)
file(GLOB SOUND_FILES ${PROJECT_SOURCE_DIR}/src/sound/*.cpp)
file(GLOB WIDGET_FILES ${PROJECT_SOURCE_DIR}/src/widget/*.cpp)
file(GLOB WIDGET_CITY_FILES ${PROJECT_SOURCE_DIR}/src/widget/city/*.cpp)
file(GLOB OVERLAYS_FILES ${PROJECT_SOURCE_DIR}/src/overlays/*.cpp)
file(GLOB WIDGET_SIDEBAR_FILES ${PROJECT_SOURCE_DIR}/src/widget/sidebar/*.cpp)
file(GLOB WINDOW_ADVISOR_FILES ${PROJECT_SOURCE_DIR}/src/window/advisor/*.cpp)
file(GLOB WINDOW_FILES ${PROJECT_SOURCE_DIR}/src/window/*.cpp)
file(GLOB WINDOW_EDITOR_FILES ${PROJECT_SOURCE_DIR}/src/window/editor/*.cpp)
file(GLOB WINDOW_BUILDING_FILES ${PROJECT_SOURCE_DIR}/src/window/building/*.cpp)
file(GLOB DEV_FILES ${PROJECT_SOURCE_DIR}/src/dev/*.cpp)
file(GLOB EDITOR_FILES ${PROJECT_SOURCE_DIR}/src/editor/*.cpp)
file(GLOB TRANSLATION_FILES ${PROJECT_SOURCE_DIR}/src/translation/*.cpp)
# imgui files from FetchContent (directly in project, not as separate library)
set(IMGUI_FILES
    ${imgui_SOURCE_DIR}/imgui.cpp
    ${imgui_SOURCE_DIR}/imgui_draw.cpp
    ${imgui_SOURCE_DIR}/imgui_tables.cpp
    ${imgui_SOURCE_DIR}/imgui_widgets.cpp
    ${imgui_SOURCE_DIR}/backends/imgui_impl_sdl2.cpp
    ${imgui_SOURCE_DIR}/backends/imgui_impl_sdlrenderer2.cpp
    ${imgui_SOURCE_DIR}/misc/cpp/imgui_stdlib.cpp
)
file(GLOB GRAPHICS_FILES ${PROJECT_SOURCE_DIR}/src/graphics/*.cpp)
file(GLOB IO_FILES ${PROJECT_SOURCE_DIR}/src/io/*.cpp)
file(GLOB IO_CONFIG_FILES ${PROJECT_SOURCE_DIR}/src/io/config/*.cpp)
file(GLOB IO_GAMEFILES_FILES ${PROJECT_SOURCE_DIR}/src/io/gamefiles/*.cpp)
file(GLOB IO_GAMESTATE_FILES ${PROJECT_SOURCE_DIR}/src/io/gamestate/*.cpp)
file(GLOB IO_IMAGEPAKS_FILES ${PROJECT_SOURCE_DIR}/src/io/imagepaks/*.cpp)
file(GLOB IO_PLAYERDATA_FILES ${PROJECT_SOURCE_DIR}/src/io/playerdata/*.cpp)
file(GLOB RESOURCE_FILES ${PROJECT_SOURCE_DIR}/src/resource/*.cpp)
file(GLOB JS_FILES ${PROJECT_SOURCE_DIR}/src/js/*.cpp)
file(GLOB SCRIPTS_FILES ${PROJECT_SOURCE_DIR}/src/scripts/*.cpp)
file(GLOB LZMA_FILES ${PROJECT_SOURCE_DIR}/src/lzma/*.c)
file(GLOB BZIP_FILES ${PROJECT_SOURCE_DIR}/src/bzip/*.c)
file(GLOB LAME_FILES ${PROJECT_SOURCE_DIR}/src/lame/libmp3lame/*.c)
file(GLOB MUJS_FILES ${PROJECT_SOURCE_DIR}/src/mujs/*.c)

if (PLATFORM_ANDROID)
    add_definitions(-DANDROID_BUILD=ON)
    file(GLOB ANDROID_BACKEND_FILES ${PROJECT_SOURCE_DIR}/src/platform/android/*.cpp)
    set(PLATFORM_FILES ${PLATFORM_FILES} ${ANDROID_BACKEND_FILES})

    set(CMAKE_CXX_FLAGS "-Wno-format-security ${CMAKE_CXX_FLAGS}")
endif()

# Find revision ID and hash of the sourcetree
execute_process(
    COMMAND git rev-list --count --all
    WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}"
    OUTPUT_VARIABLE GAME_BUILD_NUMBER
    OUTPUT_STRIP_TRAILING_WHITESPACE
    ERROR_QUIET
)

add_definitions(-DGAME_BUILD_NUMBER=${GAME_BUILD_NUMBER})
message("GAME_BUILD_NUMBER now is ${GAME_BUILD_NUMBER}")

if(MSVC)
    file(GLOB CORE_HEADERS ${PROJECT_SOURCE_DIR}/src/core/*.h)
    file(GLOB IO_HEADERS ${PROJECT_SOURCE_DIR}/src/io/*.h)
    file(GLOB PLATFORM_HEADERS ${PROJECT_SOURCE_DIR}/src/platform/*.h)
    file(GLOB BUILDING_HEADERS ${PROJECT_SOURCE_DIR}/src/building/*.h)
    file(GLOB BUILDING_CONSTRUCTION_HEADERS ${PROJECT_SOURCE_DIR}/src/building/construction/*.h)
    file(GLOB CITY_HEADERS ${PROJECT_SOURCE_DIR}/src/city/*.h)
    file(GLOB EMPIRE_HEADERS ${PROJECT_SOURCE_DIR}/src/empire/*.h)
    file(GLOB FIGURE_HEADERS ${PROJECT_SOURCE_DIR}/src/figure/*.h)
    file(GLOB FIGURETYPE_HEADERS ${PROJECT_SOURCE_DIR}/src/figuretype/*.h)
    file(GLOB GAME_HEADERS ${PROJECT_SOURCE_DIR}/src/game/*.h)
    file(GLOB INPUT_HEADERS ${PROJECT_SOURCE_DIR}/src/input/*.h)
    file(GLOB GRID_HEADERS ${PROJECT_SOURCE_DIR}/src/grid/*.h)
    file(GLOB GRID_ROUTING_HEADERS ${PROJECT_SOURCE_DIR}/src/grid/routing/*.h)
    file(GLOB SCENARIO_HEADERS ${PROJECT_SOURCE_DIR}/src/scenario/*.h)
    file(GLOB GRAPHICS_ELEMENTS_HEADERS ${PROJECT_SOURCE_DIR}/src/graphics/elements/*.h)
    file(GLOB GRAPHICS_VIEW_HEADERS ${PROJECT_SOURCE_DIR}/src/graphics/view/*.h)
    file(GLOB SOUND_HEADERS ${PROJECT_SOURCE_DIR}/src/sound/*.h)
    file(GLOB WIDGET_HEADERS ${PROJECT_SOURCE_DIR}/src/widget/*.h)
    file(GLOB WIDGET_CITY_HEADERS ${PROJECT_SOURCE_DIR}/src/widget/city/*.h)
    file(GLOB OVERLAYS_HEADERS ${PROJECT_SOURCE_DIR}/src/overlays/*.h)
    file(GLOB WIDGET_SIDEBAR_HEADERS ${PROJECT_SOURCE_DIR}/src/widget/sidebar/*.h)
    file(GLOB WINDOW_ADVISOR_HEADERS ${PROJECT_SOURCE_DIR}/src/window/advisor/*.h)
    file(GLOB WINDOW_HEADERS ${PROJECT_SOURCE_DIR}/src/window/*.h)
    file(GLOB WINDOW_BUILDING_HEADERS ${PROJECT_SOURCE_DIR}/src/window/building/*.h)
    file(GLOB DEV_HEADERS ${PROJECT_SOURCE_DIR}/src/dev/*.h)
    file(GLOB EDITOR_HEADERS ${PROJECT_SOURCE_DIR}/src/editor/*.h)
    file(GLOB TRANSLATION_HEADERS ${PROJECT_SOURCE_DIR}/src/translation/*.h)

    source_group("core" FILES ${CORE_FILES})
    source_group("core/encoding" FILES ${CORE_ENCODING_FILES})
    source_group("platform" FILES ${PLATFORM_FILES} )
    source_group("building" FILES ${BUILDING_FILES})
    source_group("building/construction" FILES ${BUILDING_CONSTRUCTION_FILES})
    source_group("city" FILES ${CITY_FILES})
    source_group("empire" FILES ${EMPIRE_FILES})
    source_group("figure" FILES ${FIGURE_FILES})
    source_group("figuretype" FILES ${FIGURETYPE_FILES})
    source_group("game" FILES ${GAME_FILES})
    source_group("tutorial" FILES ${TUTORIAL_FILES})
    source_group("input" FILES ${INPUT_FILES})
    source_group("grid" FILES ${GRID_FILES})
    source_group("grid/routing" FILES ${GRID_ROUTING_FILES})
    source_group("scenario" FILES ${SCENARIO_FILES})
    source_group("graphics/view" FILES ${GRAPHICS_VIEW_FILES})
    source_group("graphics/elements" FILES ${GRAPHICS_ELEMENTS_FILES})
    source_group("sound" FILES ${SOUND_FILES})
    source_group("widgets" FILES ${WIDGET_FILES})
    source_group("widgets/city" FILES ${WIDGET_CITY_FILES})
    source_group("overlays" FILES ${OVERLAYS_FILES})
    source_group("widgets/sidebar" FILES ${WIDGET_SIDEBAR_FILES})
    source_group("window" FILES ${WINDOW_FILES})
    source_group("window/advisors" FILES ${WINDOW_ADVISOR_FILES})
    source_group("window/editor" FILES ${WINDOW_EDITOR_FILES})
    source_group("window/building" FILES ${WINDOW_BUILDING_FILES})
    source_group("advisor" FILES ${ADVISOR_FILES})
    source_group("dev" FILES ${DEV_FILES})
    source_group("editor" FILES ${EDITOR_FILES})
    source_group("translation" FILES ${TRANSLATION_FILES})
    source_group("io" FILES ${IO_FILES} {IO_HEADERS})
    source_group("io/gamefiles" FILES ${IO_GAMEFILES_FILES})
    source_group("content" FILES ${CONTENT_FILES})
    source_group("config" FILES ${CONFIG_FILES})
    source_group("resource" FILES ${RESOURCE_FILES} ${SCRIPTS_FILES})
    source_group("graphics" FILES ${GRAPHICS_FILES})
    source_group("fontgen" FILE ${GRAPHICS_FONTGEN_FILES})
    source_group("js" FILES ${JS_FILES})
    source_group("lzma" FILES ${LZMA_FILES})
    source_group("bzip" FILES ${BZIP_FILES})
    source_group("lame" FILES ${LAME_FILES})
endif()

set(MACOSX_FILES "")
if(APPLE)
    set(MACOSX_FILES ${PROJECT_SOURCE_DIR}/res/akhenaten.icns)
endif()

set(SOURCE_FILES
    ${PLATFORM_FILES}
    ${CONTENT_FILES}
    ${CONFIG_FILES}
    ${CORE_FILES} ${CORE_HEADERS}
    ${IO_FILES} ${IO_HEADERS}
    ${IO_CONFIG_FILES}
    ${IO_GAMEFILES_FILES}
    ${IO_GAMESTATE_FILES}
    ${IO_IMAGEPAKS_FILES}
    ${IO_PLAYERDATA_FILES}
    ${BUILDING_FILES}
    ${CITY_FILES}
    ${EMPIRE_FILES}
    ${FIGURE_FILES}
    ${FIGURETYPE_FILES}
    ${GAME_FILES}
    ${TUTORIAL_FILES}
    ${INPUT_FILES}
    ${GRID_FILES}
    ${SCENARIO_FILES}
    ${GRAPHICS_FILES}
    ${GRAPHICS_FONTGEN_FILES}
    ${SOUND_FILES}
    ${WIDGET_FILES}
    ${WINDOW_FILES}
    ${DEV_FILES}
    ${EDITOR_FILES}
    ${TRANSLATION_FILES}
    ${ADVISOR_FILES}
    ${WINDOW_BUILDING_FILES}
    ${WINDOW_EDITOR_FILES}
    ${WINDOW_ADVISOR_FILES}
    ${WIDGET_SIDEBAR_FILES}
    ${OVERLAYS_FILES}
    ${WIDGET_CITY_FILES}
    ${GRAPHICS_VIEW_FILES}
    ${GRAPHICS_ELEMENTS_FILES}
    ${BUILDING_CONSTRUCTION_FILES}
    ${CORE_ENCODING_FILES}
    ${GRID_FILES}
    ${GRID_ROUTING_FILES}
    ${IMGUI_FILES}
    ${RC_FILES}
    ${TRACY_FILES}
    ${RESOURCE_FILES}
    ${JS_FILES}
    ${SCRIPTS_FILES}
    ${LZMA_FILES}
    ${BZIP_FILES}
    ${LAME_FILES}
    ${MUJS_FILES}
    ${MACOSX_FILES}
    ${CPPTRACE_FILES}
)

set(SCRIPTS_FOLDER ${PROJECT_SOURCE_DIR}/src/scripts)

file(GLOB SCRIPT_FILES ${SCRIPTS_FOLDER}/*.js)
cmrc_add_resource_library(
    resources
    ALIAS akhenaten::rc
    NAMESPACE akhenaten

    ${SCRIPT_FILES}
    ${PROJECT_SOURCE_DIR}/res/akhenaten_72.png
    ${PROJECT_SOURCE_DIR}/res/patreon_48.png
)

if (!APPLE)
    set_source_files_properties(${SOURCE_FILES} PROPERTIES LANGUAGE CXX)
endif()

if (PLATFORM_ANDROID)
    find_package(SDL2 REQUIRED CONFIG)
    set(SDL2_LIBRARY SDL2::SDL2)
    set(SDL2_MIXER_LIBRARY SDL2::SDL2_mixer)
elseif (MSVC OR WIN_EMSCRIPTEN)
    # do nothing
else()
    find_package(SDL2 REQUIRED)
    find_package(SDL2_mixer REQUIRED)
endif()

if (PLATFORM_ANDROID)
    add_library(${GAME} SHARED ${SDL2_ANDROID_HOOK} ${SOURCE_FILES})
else()
    add_executable(${GAME} ${SOURCE_FILES})
endif()

if(LAME_FILES)
    set_source_files_properties(${LAME_FILES} PROPERTIES
        COMPILE_DEFINITIONS "HAVE_CONFIG_H=ON;CPU_IS_LITTLE_ENDIAN=1;PACKAGE_NAME=\\\"Ozy\\\";PACKAGE_VERSION=\\\"static\\\";HAVE_MPGLIB=ON"
    )
    if(NOT MSVC)
        set_source_files_properties(${LAME_FILES} PROPERTIES COMPILE_FLAGS "-Wno-absolute-value")
    endif()
endif()

if (MSVC)
    add_compile_definitions(_CRT_SECURE_NO_WARNINGS)
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /ignore:4098")
endif()

if(APPLE)
    add_custom_command(OUTPUT ${PROJECT_SOURCE_DIR}/res/akhenaten.icns
        COMMAND mkdir -p akhenaten.iconset
        COMMAND sips -z 16 16    akhenaten_256.png --out akhenaten.iconset/icon_16x16.png
        COMMAND sips -z 32 32    akhenaten_256.png --out akhenaten.iconset/icon_16x16@2x.png
        COMMAND sips -z 32 32    akhenaten_256.png --out akhenaten.iconset/icon_32x32.png
        COMMAND sips -z 64 64    akhenaten_256.png --out akhenaten.iconset/icon_32x32@2x.png
        COMMAND sips -z 128 128  akhenaten_256.png --out akhenaten.iconset/icon_128x128.png
        COMMAND sips -z 256 256  akhenaten_256.png --out akhenaten.iconset/icon_128x128@2x.png
        COMMAND sips -z 256 256  akhenaten_256.png --out akhenaten.iconset/icon_256x256.png
        COMMAND iconutil -c icns akhenaten.iconset
        COMMAND rm -R akhenaten.iconset
        WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/res)

    set_source_files_properties(${PROJECT_SOURCE_DIR}/res/akhenaten.icns PROPERTIES
        MACOSX_PACKAGE_LOCATION "Resources")

    set(MACOSX_BUNDLE_GUI_IDENTIFIER "mt.dalerank.akhenaten")
    set(MACOSX_BUNDLE_BUNDLE_NAME ${PROJECT_NAME})
    set(CMAKE_OSX_DEPLOYMENT_TARGET "10.15" CACHE STRING "Minimum OS X deployment version" FORCE)
    set(MACOSX_BUNDLE_ICON_FILE "akhenaten.icns")
    set(MACOSX_BUNDLE_BUNDLE_VERSION "0.2.1 ${GAME_BUILD_NUMBER}")
    set(MACOSX_BUNDLE_LONG_VERSION_STRING ${MACOSX_BUNDLE_BUNDLE_VERSION})
    set(MACOSX_BUNDLE_SHORT_VERSION_STRING ${MACOSX_BUNDLE_BUNDLE_VERSION})

    set_target_properties(${GAME} PROPERTIES
        MACOSX_BUNDLE TRUE
        MACOSX_BUNDLE_INFO_PLIST "${PROJECT_SOURCE_DIR}/res/macos/Info.plist")

    set(DIRS "")
    set(LIBS "")

    string(REGEX REPLACE ";.*$" "" SDL2_LIB_DIR "${SDL2_LIBRARY}")
    if(EXISTS "${SDL2_LIB_DIR}/Versions/A/Frameworks")
        list(APPEND DIRS "${SDL2_LIB_DIR}/Versions/A/Frameworks")
    endif()

    if(EXISTS "${SDL2_MIXER_LIBRARY}/Versions/A/Frameworks")
        list(APPEND DIRS "${SDL2_MIXER_LIBRARY}/Versions/A/Frameworks")
    endif()

    install(TARGETS ${GAME}
        BUNDLE DESTINATION .
        RUNTIME DESTINATION bin)
    
    install(CODE "
        include(BundleUtilities)
        fixup_bundle(\"\${CMAKE_INSTALL_PREFIX}/${PROJECT_NAME}.app\" \"${LIBS}\" \"${DIRS}\")
    ")

    set(codesignCommand "codesign --verbose=4 --force --deep --options=runtime --timestamp=none --sign -")
    set(codesignCommandWithEntitlements "${codesignCommand} --entitlements \"${PROJECT_SOURCE_DIR}/res/macos/Entitlements.plist\"")
    install(CODE "
        execute_process(COMMAND
            ${codesignCommandWithEntitlements} \"\${CMAKE_INSTALL_PREFIX}/${PROJECT_NAME}.app/Contents/MacOS/${PROJECT_NAME}\"
        )
    ")
endif()

include_directories(${SDL2_INCLUDE_DIR})
include_directories(${SDL2_MIXER_INCLUDE_DIR})
include_directories(${PROJECT_SOURCE_DIR}/src/mujs)
include_directories(${CMRC_INCLUDE_DIR})
include_directories(${PROJECT_SOURCE_DIR}/src/lame/include)

if (PLATFORM_ANDROID OR WIN_EMSCRIPTEN OR APPLE)
    # no filters on android
    set(GPUPIXEL_LIBRARY "")
else()
    include_directories(${GPUPIXEL_INCLUDE_DIR})
endif()

include_directories(ext)
include_directories(src)
include_directories(${imgui_SOURCE_DIR})
include_directories(${imgui_SOURCE_DIR}/backends)
include_directories(${imgui_SOURCE_DIR}/misc/cpp)
include_directories(${HARFBUZZ_INCLUDE_DIRS})
include_directories(ext/gpupixel/utils)

if(MSVC)
    include_directories(ext/bugtrap)
    set_target_properties(${GAME} PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY "${GAME_WORKING_DIRECTORY}")
endif()

if (UNIX AND NOT APPLE AND (CMAKE_COMPILER_IS_GNUCC OR CMAKE_C_COMPILER_ID STREQUAL "Clang"))
    target_link_libraries(${GAME} m)
endif()

message(STATUS "zlib: Linked statically with prebuilt library from ${ZLIB_INSTALL_DIR}")

# Link harfbuzz - freetype will be linked later, but harfbuzz needs it for hb_ft_* functions
target_link_libraries(${GAME} ${HARFBUZZ_LIBRARY})
target_include_directories(${GAME} PRIVATE ${HARFBUZZ_INCLUDE_DIRS})
message(STATUS "harfbuzz: Linked via FetchContent from ${HARFBUZZ_SOURCE_DIR}")

set(ZLIB_ROOT ${ZLIB_ROOT} CACHE PATH "" FORCE)
set(CMAKE_PREFIX_PATH "${ZLIB_ROOT};${CMAKE_PREFIX_PATH}" CACHE PATH "" FORCE)

#
# libpng section begin
#

set(LOCAL_DEPS_ROOT "${CMAKE_CURRENT_SOURCE_DIR}/_deps")
if (EXISTS "${LOCAL_DEPS_ROOT}/libpng-src/CMakeLists.txt")
    set(FETCHCONTENT_SOURCE_DIR_LIBPNG "${LOCAL_DEPS_ROOT}/libpng-src")
    set(FETCHCONTENT_UPDATES_DISCONNECTED_LIBPNG TRUE)
endif()

# Configure libpng build options before FetchContent_MakeAvailable
set(BUILD_SHARED_LIBS OFF CACHE BOOL "" FORCE)
set(PNG_SHARED OFF CACHE BOOL "" FORCE)
set(PNG_STATIC ON CACHE BOOL "" FORCE)
set(PNG_TESTS OFF CACHE BOOL "" FORCE)
set(PNG_USE_FIND_PACKAGE_ZLIB ON CACHE BOOL "" FORCE)

FetchContent_Declare(
    libpng
    GIT_REPOSITORY https://github.com/pnggroup/libpng.git
    GIT_TAG ${LIBPNG_VERSION}
)

FetchContent_MakeAvailable(libpng)

# Set libpng variables for linking
set(LIBPNG_SOURCE_DIR "${libpng_SOURCE_DIR}")
if(TARGET png_static)
    set(LIBPNG_LIBRARY png_static)
    get_target_property(LIBPNG_INCLUDE_DIR_TEMP png_static INTERFACE_INCLUDE_DIRECTORIES)
    if(LIBPNG_INCLUDE_DIR_TEMP)
        list(GET LIBPNG_INCLUDE_DIR_TEMP 0 LIBPNG_INCLUDE_DIR)
    else()
        set(LIBPNG_INCLUDE_DIR "${LIBPNG_SOURCE_DIR}")
    endif()
elseif(TARGET png)
    set(LIBPNG_LIBRARY png)
    get_target_property(LIBPNG_INCLUDE_DIR_TEMP png INTERFACE_INCLUDE_DIRECTORIES)
    if(LIBPNG_INCLUDE_DIR_TEMP)
        list(GET LIBPNG_INCLUDE_DIR_TEMP 0 LIBPNG_INCLUDE_DIR)
    else()
        set(LIBPNG_INCLUDE_DIR "${LIBPNG_SOURCE_DIR}")
    endif()
else()
    # Fallback
    set(LIBPNG_LIBRARY png)
    set(LIBPNG_INCLUDE_DIR "${LIBPNG_SOURCE_DIR}")
endif()

set(PNG_INCLUDE_DIRS "${LIBPNG_INCLUDE_DIR}" CACHE PATH "Path to libpng include directories" FORCE)
set(PNG_FOUND TRUE CACHE BOOL "Whether libpng was found" FORCE)

#
# libpng section end
#

target_link_libraries(${GAME} ${LIBPNG_LIBRARY})
target_include_directories(${GAME} PRIVATE ${LIBPNG_INCLUDE_DIR})
message(STATUS "libpng: Linked via FetchContent from ${LIBPNG_SOURCE_DIR}")

target_link_libraries(${GAME} ${FREETYPE_LIBRARY})
target_include_directories(${GAME} PRIVATE ${FREETYPE_INCLUDE_DIRS})
message(STATUS "freetype: Linked via FetchContent from ${FREETYPE_SOURCE_DIR}")

target_link_libraries (${GAME}
                        ${SDL2_LIBRARY}
                        $<IF:$<TARGET_EXISTS:SDL2::SDL2_mixer>,SDL2::SDL2_mixer,
                            $<IF:$<TARGET_EXISTS:SDL2_mixer::SDL2_mixer>,SDL2_mixer::SDL2_mixer,
                                $<IF:$<TARGET_EXISTS:SDL2_mixer>,SDL2_mixer,${SDL2_MIXER_LIBRARY}>>>
                        $<IF:$<TARGET_EXISTS:SDL2::SDL2main>,SDL2::SDL2main,>
                        ${CPPTRACE_LIBRARY}
                        ${GPUPIXEL_LIBRARY} 
                        ${ZLIB_LIBRARY}
                        akhenaten::rc
                        $<IF:$<TARGET_EXISTS:Tracy::TracyClient>,Tracy::TracyClient,>)

if(MSVC)
    target_link_libraries(${GAME} "winmm" "imagehlp" "shlwapi")
    
    set(LIBVPX_DEPS_ROOT "${CMAKE_BINARY_DIR}/_deps")
    set(LIBVPX_INSTALL_DIR "${LIBVPX_DEPS_ROOT}/libvpx")
    set(LIBVPX_LIB_DIR "${LIBVPX_INSTALL_DIR}/lib")
    set(LIBVPX_INCLUDE_DIR "${LIBVPX_INSTALL_DIR}/include")
    
    message(STATUS "libvpx: Checking for pre-built installation...")
    set(LIBVPX_FOUND FALSE)
    
    # Check for existing installation
    if(EXISTS "${LIBVPX_LIB_DIR}/libvpx.lib" AND EXISTS "${LIBVPX_INCLUDE_DIR}/vpx/vpx_encoder.h")
        message(STATUS "libvpx: Found pre-built installation")
        message(STATUS "libvpx: Installation directory: ${LIBVPX_INSTALL_DIR}")
        set(LIBVPX_FOUND TRUE)
    endif()
    
    # Download pre-built library if not found
    if(NOT LIBVPX_FOUND)
        message(STATUS "libvpx: Pre-built installation not found, downloading...")
        
        # Determine architecture
        if(CMAKE_SIZEOF_VOID_P EQUAL 8)
            set(LIBVPX_ARCH "x64")
        else()
            set(LIBVPX_ARCH "x86")
        endif()
        
        set(LIBVPX_VERSION "1.15.1")
        set(LIBVPX_ZIP_FILE "${LIBVPX_DEPS_ROOT}/libvpx-v${LIBVPX_VERSION}-msvc.zip")
        
        file(MAKE_DIRECTORY ${LIBVPX_DEPS_ROOT})
        message(STATUS "libvpx: Dependencies directory: ${LIBVPX_DEPS_ROOT}")
        
        if(NOT EXISTS "${LIBVPX_ZIP_FILE}")
            message(STATUS "libvpx: Archive not found, starting download...")
            message(STATUS "libvpx: Target archive: ${LIBVPX_ZIP_FILE}")
            
            set(DOWNLOAD_URLS
                "https://github.com/ShiftMediaProject/libvpx/releases/download/v1.15.1/libvpx_v1.15.1_msvc17.zip"
            )
            
            set(DOWNLOAD_SUCCESS FALSE)
            set(URL_INDEX 0)
            foreach(DOWNLOAD_URL ${DOWNLOAD_URLS})
                math(EXPR URL_INDEX "${URL_INDEX} + 1")
                message(STATUS "libvpx: [${URL_INDEX}] Attempting download from: ${DOWNLOAD_URL}")
                
                file(DOWNLOAD 
                    ${DOWNLOAD_URL} 
                    ${LIBVPX_ZIP_FILE}
                    SHOW_PROGRESS
                    STATUS DOWNLOAD_STATUS
                    TLS_VERIFY ON
                )
                list(GET DOWNLOAD_STATUS 0 STATUS_CODE)
                if(STATUS_CODE EQUAL 0)
                    file(SIZE ${LIBVPX_ZIP_FILE} FILE_SIZE)
                    if(FILE_SIZE GREATER 0)
                        math(EXPR FILE_SIZE_MB "${FILE_SIZE} / 1048576")
                        message(STATUS "libvpx: Download successful!")
                        message(STATUS "libvpx: File size: ${FILE_SIZE} bytes (${FILE_SIZE_MB} MB)")
                        set(DOWNLOAD_SUCCESS TRUE)
                        break()
                    else()
                        message(WARNING "libvpx: Downloaded file is empty, removing...")
                        file(REMOVE ${LIBVPX_ZIP_FILE})
                    endif()
                else()
                    list(GET DOWNLOAD_STATUS 1 ERROR_MESSAGE)
                    message(WARNING "libvpx: Download failed: ${ERROR_MESSAGE}")
                    if(EXISTS "${LIBVPX_ZIP_FILE}")
                        file(REMOVE ${LIBVPX_ZIP_FILE})
                    endif()
                endif()
            endforeach()
            
            if(NOT DOWNLOAD_SUCCESS)
                message(FATAL_ERROR "libvpx: Failed to download from all sources.\n"
                    "Please download libvpx manually and extract to: ${LIBVPX_INSTALL_DIR}\n"
                    "Or install via vcpkg: vcpkg install libvpx:x64-windows")
            endif()
        else()
            file(SIZE ${LIBVPX_ZIP_FILE} FILE_SIZE)
            math(EXPR FILE_SIZE_MB "${FILE_SIZE} / 1048576")
            message(STATUS "libvpx: Archive already exists: ${LIBVPX_ZIP_FILE}")
            message(STATUS "libvpx: Archive size: ${FILE_SIZE} bytes (${FILE_SIZE_MB} MB)")
        endif()
        
        # Extract ZIP file
        message(STATUS "libvpx: Starting extraction process...")
        message(STATUS "libvpx: Source archive: ${LIBVPX_ZIP_FILE}")
        message(STATUS "libvpx: Target directory: ${LIBVPX_INSTALL_DIR}")
        
        set(LIBVPX_EXTRACT_TEMP "${LIBVPX_DEPS_ROOT}/libvpx-temp")
        file(MAKE_DIRECTORY ${LIBVPX_EXTRACT_TEMP})
        
        execute_process(
            COMMAND ${CMAKE_COMMAND} -E tar xf ${LIBVPX_ZIP_FILE}
            WORKING_DIRECTORY ${LIBVPX_EXTRACT_TEMP}
            RESULT_VARIABLE EXTRACT_RESULT
            OUTPUT_QUIET
            ERROR_QUIET
        )
        
        if(NOT EXTRACT_RESULT EQUAL 0)
            message(FATAL_ERROR "libvpx: Extraction failed with exit code ${EXTRACT_RESULT}.\n"
                "Please extract manually: ${LIBVPX_ZIP_FILE} to ${LIBVPX_INSTALL_DIR}")
        endif()
        
        message(STATUS "libvpx: Archive extracted successfully")
        
        # Move extracted files to install directory
        file(GLOB EXTRACTED_DIRS "${LIBVPX_EXTRACT_TEMP}/*")
        list(LENGTH EXTRACTED_DIRS EXTRACTED_COUNT)
        
        if(EXTRACTED_COUNT EQUAL 1)
            list(GET EXTRACTED_DIRS 0 EXTRACTED_ROOT)
            file(MAKE_DIRECTORY ${LIBVPX_INSTALL_DIR})
            file(GLOB EXTRACTED_CONTENTS "${EXTRACTED_ROOT}/*")
            foreach(ITEM ${EXTRACTED_CONTENTS})
                get_filename_component(ITEM_NAME ${ITEM} NAME)
                set(TARGET_PATH "${LIBVPX_INSTALL_DIR}/${ITEM_NAME}")
                if(EXISTS ${TARGET_PATH})
                    file(REMOVE_RECURSE ${TARGET_PATH})
                endif()
                file(RENAME ${ITEM} ${TARGET_PATH})
            endforeach()
        else()
            file(MAKE_DIRECTORY ${LIBVPX_INSTALL_DIR})
            file(GLOB EXTRACTED_CONTENTS "${LIBVPX_EXTRACT_TEMP}/*")
            foreach(ITEM ${EXTRACTED_CONTENTS})
                get_filename_component(ITEM_NAME ${ITEM} NAME)
                set(TARGET_PATH "${LIBVPX_INSTALL_DIR}/${ITEM_NAME}")
                if(EXISTS ${TARGET_PATH})
                    file(REMOVE_RECURSE ${TARGET_PATH})
                endif()
                file(RENAME ${ITEM} ${TARGET_PATH})
            endforeach()
        endif()
        
        file(REMOVE_RECURSE ${LIBVPX_EXTRACT_TEMP})
        message(STATUS "libvpx: Extraction completed")
        
        # Find lib and include directories
        file(GLOB_RECURSE VPX_LIB "${LIBVPX_INSTALL_DIR}/*/libvpx.lib")
        file(GLOB_RECURSE VPX_HEADER "${LIBVPX_INSTALL_DIR}/*/vpx/vpx_encoder.h")
        
        if(VPX_LIB)
            list(GET VPX_LIB 0 VPX_LIB_FILE)
            get_filename_component(FOUND_LIB_DIR ${VPX_LIB_FILE} DIRECTORY)
            set(LIBVPX_LIB_DIR ${FOUND_LIB_DIR})
            message(STATUS "libvpx: Library directory found: ${LIBVPX_LIB_DIR}")
        endif()
        
        if(VPX_HEADER)
            list(GET VPX_HEADER 0 VPX_HEADER_FILE)
            get_filename_component(FOUND_INCLUDE_DIR ${VPX_HEADER_FILE} DIRECTORY)
            get_filename_component(FOUND_INCLUDE_DIR ${FOUND_INCLUDE_DIR} DIRECTORY)
            set(LIBVPX_INCLUDE_DIR ${FOUND_INCLUDE_DIR})
            message(STATUS "libvpx: Include directory found: ${LIBVPX_INCLUDE_DIR}")
        endif()
        
        # Verify installation
        if(EXISTS "${LIBVPX_LIB_DIR}/libvpx.lib")
            if(EXISTS "${LIBVPX_INCLUDE_DIR}/vpx/vpx_encoder.h")
                set(LIBVPX_FOUND TRUE)
                message(STATUS "libvpx: Installation verified successfully")
            endif()
        endif()
    endif()
    
    # Link libvpx if found
    if(LIBVPX_FOUND)
        target_link_libraries(${GAME} "${LIBVPX_LIB_DIR}/libvpx.lib")
        target_include_directories(${GAME} PRIVATE ${LIBVPX_INCLUDE_DIR})
        message(STATUS "libvpx: Linked from ${LIBVPX_INSTALL_DIR}")
    else()
        message(FATAL_ERROR "libvpx: Installation failed or incomplete.\n"
            "Library or headers not found after download and extraction.")
    endif()
    target_link_libraries(${GAME} ${CMAKE_SOURCE_DIR}/ext/bugtrap/BugTrap-x64.lib)
    
    if(TARGET CURL::libcurl)
        target_link_libraries(${GAME} CURL::libcurl)
    else()
        if(TARGET libcurl)
            target_link_libraries(${GAME} libcurl)
        else()
            message(WARNING "CURL::libcurl target not found, curl may not be built correctly")
        endif()
    endif()
      
    # harfbuzz and freetype are static libraries, no need to copy DLL
endif()

if (PLATFORM_ANDROID)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -DPNG_ARM_NEON_OPT=0 -D_BSD_SOURCE")
    find_library(log-lib log)
    find_library(android-lib android)
    target_link_libraries(${GAME} ${log-lib} ${android-lib})
endif()

if(NOT APPLE)
    install(TARGETS ${GAME} RUNTIME DESTINATION bin)
endif()

if(UNIX AND NOT APPLE)
    install(FILES "res/akhenaten.desktop" DESTINATION "share/applications" RENAME "com.github.dalerank.akhenaten.desktop")
    install(FILES "res/akhenaten_256.png" DESTINATION "share/icons/hicolor/256x256/apps" RENAME "com.github.dalerank.akhenaten.png")
    install(FILES "res/metainfo.xml"      DESTINATION "share/metainfo" RENAME "com.github.dalerank.akhenaten.metainfo.xml")
endif()

if (MSVC)
    set(BINARY_FILES "${CMAKE_BINARY_DIR}/${GAME_BUILD_TYPE}/${GAME}.exe" "${CMAKE_BINARY_DIR}/${GAME_BUILD_TYPE}/${GAME}.pdb")
    foreach( file_i ${BINARY_FILES})
        add_custom_command(
            TARGET ${GAME}
            POST_BUILD
            COMMAND ${CMAKE_COMMAND}
            ARGS -E copy ${file_i} "${GAME_WORKING_DIRECTORY}"
        )
    endforeach( file_i )

    set(DATA_FILES "${CMAKE_SOURCE_DIR}/data/pharaoh_custom_pack.sgx" "${CMAKE_SOURCE_DIR}/data/pharaoh_fonts_pack.sgx")
    add_custom_command(
        OUTPUT 
        ${GAME_WORKING_DIRECTORY}/Data    
        COMMAND ${CMAKE_COMMAND} 
        -E make_directory ${GAME_WORKING_DIRECTORY}/Data
    )
    set(BINARY_FILES_DIRECTORY "${GAME_WORKING_DIRECTORY}/Data")
    foreach( file_i ${DATA_FILES})
        add_custom_command(
            TARGET ${GAME}
            POST_BUILD
            COMMAND ${CMAKE_COMMAND}
            ARGS -E copy ${file_i} "${BINARY_FILES_DIRECTORY}"
        )
    endforeach( file_i )
endif()
