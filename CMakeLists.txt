cmake_minimum_required(VERSION 3.16...3.26)
include(CMakeDependentOption)

set(CMAKE_BUILD_PLATFORM "default" CACHE STRING "Platform to cross-compile for. Options: android default")

option(OPTION_SYSTEM_LIBPNG "Use the system libpng" OFF)
option(OPTION_BUILD_LIBPNG "Build libpng from source" OFF)
message(STATUS "OPTION_SYSTEM_LIBPNG: ${OPTION_SYSTEM_LIBPNG}")
message(STATUS "OPTION_BUILD_LIBPNG: ${OPTION_BUILD_LIBPNG}")

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
project(${GAME} CXX)
message("C++ compiler is ${CMAKE_CXX_COMPILER_ID}" )

if(CMAKE_SIZEOF_VOID_P EQUAL 8)
  set(GAME_ARCH_64 TRUE)
  set(GAME_PROCESSOR_ARCH "x64")
else()
  set(GAME_ARCH_64 FALSE)
  set(GAME_PROCESSOR_ARCH "x86")
endif(CMAKE_SIZEOF_VOID_P EQUAL 8)

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")
include("${CMAKE_MODULE_PATH}/CMakeRC.cmake")

#
# CppTrace
#

if(PLATFORM_ANDROID)
    # no cpptrace for android, baa...
else()
    if(CMAKE_BUILD_TYPE STREQUAL "RelWithDebInfo" OR CMAKE_BUILD_TYPE STREQUAL "Debug")
        if (APPLE AND CMAKE_BUILD_TYPE STREQUAL "Debug") # Get meaningful trace on memory access errors etc.
            add_compile_options(-fsanitize=address)
            add_link_options(-fsanitize=address)
        endif()

        add_definitions(-DCPPTRACE_ENABLED=ON)
        add_definitions(-DCPPTRACE_STATIC_DEFINE)

        include(FetchContent)
        FetchContent_Declare(
                cpptrace
                GIT_REPOSITORY https://github.com/jeremy-rifkin/cpptrace.git
                GIT_TAG        v1.0.4 # <HASH or TAG>
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
    set(USE_FLAGS "--use-port=sdl2 --use-port=sdl2_mixer -sSDL2_MIXER_FORMATS=mp3 -s USE_MPG123=1 -gsource-map")
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

set(SDL2_VERSION "2.32.10")
set(SDL2_MIXER_VERSION "2.8.1")
set(OPENSSL_VERSION "3.0.17")

set(SDL2_EXTRACT_PATH "${CMAKE_CURRENT_SOURCE_DIR}/ext/SDL2")
set(OPENSSL_EXTRACT_PATH "${CMAKE_CURRENT_SOURCE_DIR}/ext/openssl")
set(TRACY_EXT_PATH "${CMAKE_CURRENT_SOURCE_DIR}/ext/tracy")

#
# Dependencies and libs
#
if (MSVC OR WIN_EMSCRIPTEN)
    set(SDL_EXT_DIR ${CMAKE_CURRENT_SOURCE_DIR}/ext/SDL2)
    set(SDL2_CHECK_PATH "${SDL2_EXTRACT_PATH}/include/SDL.h")
    if(NOT EXISTS "${SDL2_CHECK_PATH}")
        set(SDL2_DEP_FILENAME "SDL2-devel-${SDL2_VERSION}-VC.zip")
        set(SDL2_UNPACK_DIR "SDL2-${SDL2_VERSION}")
        set(SDL2_DOWNLOAD_URL "http://libsdl.org/release/${SDL2_DEP_FILENAME}")
        set(SDL2_TMP_ZIP_PATH "${CMAKE_BINARY_DIR}/tmp/${SDL2_DEP_FILENAME}")
        message("Download SDL2 to ${SDL2_TMP_ZIP_PATH}")
        
        if (NOT EXISTS "${SDL2_TMP_ZIP_PATH}")
            file(DOWNLOAD "${SDL2_DOWNLOAD_URL}" "${SDL2_TMP_ZIP_PATH}")
        endif()
        
        message("Unpack SDL2 to ${SDL2_EXTRACT_PATH}")
        execute_process(COMMAND ${CMAKE_COMMAND} -E tar xzf ${SDL2_TMP_ZIP_PATH} WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/tmp)
        file(COPY ${CMAKE_BINARY_DIR}/tmp/${SDL2_UNPACK_DIR}/include DESTINATION ${SDL2_EXTRACT_PATH})
        file(COPY ${CMAKE_BINARY_DIR}/tmp/${SDL2_UNPACK_DIR}/lib DESTINATION ${SDL2_EXTRACT_PATH})
    endif()

    set(SDL2_MIXER_DEP_FILENAME "SDL2_mixer-devel-${SDL2_MIXER_VERSION}-VC.zip")
    set(SDL2_MIXER_DOWNLOAD_URL "https://libsdl.org/projects/SDL_mixer/release/${SDL2_MIXER_DEP_FILENAME}")
    set(SDL2_MIXER_UNPACK_DIR "SDL2_mixer-${SDL2_MIXER_VERSION}")
    set(SDL2_MIXER_CHECK_PATH "${SDL2_EXTRACT_PATH}/include/SDL_mixer.h")
    set(SDL2_MIXER_TMP_ZIP_PATH "${CMAKE_BINARY_DIR}/tmp/${SDL2_MIXER_DEP_FILENAME}")
    if (NOT EXISTS "${SDL2_MIXER_CHECK_PATH}")
        message("Download SDL2_mixer to ${SDL2_MIXER_TMP_ZIP_PATH}")

        if (NOT EXISTS "${SDL2_MIXER_TMP_ZIP_PATH}")
            file(DOWNLOAD "${SDL2_MIXER_DOWNLOAD_URL}" "${SDL2_MIXER_TMP_ZIP_PATH}")
        endif()

        message("Unpack SDL2_mixer to ${SDL2_EXTRACT_PATH}")
        execute_process(COMMAND ${CMAKE_COMMAND} -E tar xzf ${SDL2_MIXER_TMP_ZIP_PATH} WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/tmp)
        file(COPY ${CMAKE_BINARY_DIR}/tmp/${SDL2_MIXER_UNPACK_DIR}/include DESTINATION ${SDL2_EXTRACT_PATH})
        file(COPY ${CMAKE_BINARY_DIR}/tmp/${SDL2_MIXER_UNPACK_DIR}/lib DESTINATION ${SDL2_EXTRACT_PATH})
    endif()

    set(OPENSSL_CHECK_PATH "${OPENSSL_EXTRACT_PATH}/include/openssl/ssl.h")
    message("Check ssl.h exist at ${OPENSSL_CHECK_PATH}")
    if(NOT EXISTS "${OPENSSL_CHECK_PATH}")
        set(OPENSSL_DEP_FILENAME "openssl-${OPENSSL_VERSION}.zip")
        set(OPENSSL_UNPACK_DIR "openssl-${OPENSSL_VERSION}")
        set(OPENSSL_DOWNLOAD_URL "https://download.firedaemon.com/FireDaemon-OpenSSL/${OPENSSL_DEP_FILENAME}")
        set(OPENSSL_TMP_ZIP_PATH "${CMAKE_BINARY_DIR}/tmp/${OPENSSL_DEP_FILENAME}")
        message("Download openssl to ${OPENSSL_TMP_ZIP_PATH}")
        file(DOWNLOAD "${OPENSSL_DOWNLOAD_URL}" "${OPENSSL_TMP_ZIP_PATH}")
        message("Unpack openssl to ${OPENSSL_EXTRACT_PATH}")
        execute_process(COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_BINARY_DIR}/tmp/${OPENSSL_UNPACK_DIR})
        execute_process(COMMAND ${CMAKE_COMMAND} -E tar xzf ${OPENSSL_TMP_ZIP_PATH} WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/tmp/${OPENSSL_UNPACK_DIR})

        execute_process(COMMAND ${CMAKE_COMMAND} -E make_directory ${OPENSSL_EXTRACT_PATH})
        file(COPY ${CMAKE_BINARY_DIR}/tmp/${OPENSSL_UNPACK_DIR}/openssl-3.0/x64/lib DESTINATION ${OPENSSL_EXTRACT_PATH})
        file(COPY ${CMAKE_BINARY_DIR}/tmp/${OPENSSL_UNPACK_DIR}/openssl-3.0/x64/bin DESTINATION ${OPENSSL_EXTRACT_PATH})
        file(COPY ${CMAKE_BINARY_DIR}/tmp/${OPENSSL_UNPACK_DIR}/openssl-3.0/x64/include DESTINATION ${OPENSSL_EXTRACT_PATH})
    endif()

    file(GLOB SDL2_DLL_PUBLIC_DLL "${SDL2_EXTRACT_PATH}/lib/${GAME_PROCESSOR_ARCH}/*.dll")
    file(COPY ${SDL2_DLL_PUBLIC_DLL} DESTINATION ${GAME_WORKING_DIRECTORY})

    file(GLOB OPENSSL_DLL_PUBLIC_DLL "${OPENSSL_EXTRACT_PATH}/bin/*.dll")
    file(COPY ${OPENSSL_DLL_PUBLIC_DLL} DESTINATION ${GAME_WORKING_DIRECTORY})

    set(SDL_FFMPEG_DIR ${CMAKE_CURRENT_SOURCE_DIR}/ext/ffmpeg)
    file(GLOB FFMPEG_PUBLIC_DLL "${SDL_FFMPEG_DIR}/bin/*.dll")
    file(COPY ${FFMPEG_PUBLIC_DLL} DESTINATION ${GAME_WORKING_DIRECTORY})
    set(BUGTRAP_DIR ${CMAKE_CURRENT_SOURCE_DIR}/ext/bugtrap)
    set(BUGTRAP_DLL "${BUGTRAP_DIR}/BugTrap-x64.dll")
    file(COPY ${BUGTRAP_DLL} DESTINATION ${GAME_WORKING_DIRECTORY})
    file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/update_binary_windows.cmd DESTINATION ${GAME_WORKING_DIRECTORY})
endif()

set(TRACY_CHECK_PATH "${TRACY_EXT_PATH}/public/TracyClient.cpp")
if (EXISTS "${TRACY_CHECK_PATH}")
    add_definitions(-DTRACY_ENABLE=ON)
    set(TRACY_FILES ${PROJECT_SOURCE_DIR}/ext/tracy/public/TracyClient.cpp)
    include_directories(${PROJECT_SOURCE_DIR}/ext/tracy/public/)
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

if (PLATFORM_ANDROID)
    set(PROJECT_VERSION_MAJOR 0)
    set(PROJECT_VERSION_MINOR 2)
    set(PROJECT_VERSION_PATCH 2)
    set(IS_RELEASE_VERSION FALSE)
    set(VERSION_REVISION "")
endif()

add_subdirectory(ext/expat)
add_subdirectory(ext/mujs)
add_subdirectory(ext/lame)
add_subdirectory(ext/lzma)
add_subdirectory(ext/bzip)
add_subdirectory(ext/aes)

if (PLATFORM_ANDROID OR WIN_EMSCRIPTEN OR APPLE)
   # no filters on android
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
file(GLOB IMGUI_FILES ${PROJECT_SOURCE_DIR}/ext/imgui/*.cpp)
file(GLOB IMGUI_CPP_FILES ${PROJECT_SOURCE_DIR}/ext/imgui/misc/cpp/*.cpp)
file(GLOB IMGUI_BACKEND_FILES ${PROJECT_SOURCE_DIR}/ext/imgui/backends/*.cpp)
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

if (PLATFORM_ANDROID)
    add_definitions(-DANDROID_BUILD=ON)
    file(GLOB ANDROID_BACKEND_FILES ${PROJECT_SOURCE_DIR}/src/platform/android/*.cpp)
    set(PLATFORM_FILES ${PLATFORM_FILES} ${ANDROID_BACKEND_FILES})

    set(CMAKE_CXX_FLAGS "-Wno-format-security ${CMAKE_CXX_FLAGS}")
    # set(SDL2_ANDROID_HOOK ${SDL_EXT_DIR}/src/main/android/SDL_android_main.c)
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

set(IMGUI_FILES ${IMGUI_FILES} ${IMGUI_CPP_FILES} ${IMGUI_BACKEND_FILES})

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
    file(GLOB IMGUI_HEADERS ${PROJECT_SOURCE_DIR}/ext/imgui/*.h)
    file(GLOB IMGUI_BACKEND_HEADERS ${PROJECT_SOURCE_DIR}/ext/imgui/backends/*.h)

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
    source_group("imgui" FILES ${IMGUI_FILES})
    source_group("io" FILES ${IO_FILES} {IO_HEADERS})
    source_group("io/gamefiles" FILES ${IO_GAMEFILES_FILES})
    source_group("content" FILES ${CONTENT_FILES})
    source_group("config" FILES ${CONFIG_FILES})
    source_group("resource" FILES ${RESOURCE_FILES} ${SCRIPTS_FILES})
    source_group("graphics" FILES ${GRAPHICS_FILES})
    source_group("js" FILES ${JS_FILES})
endif()

set(MACOSX_FILES "")
if(APPLE)
    set(MACOSX_FILES ${PROJECT_SOURCE_DIR}/res/akhenaten.icns)
elseif(MSVC)
    #set(RC_FILES ${PROJECT_SOURCE_DIR}/res/akhenaten.rc)
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
elseif (WIN_EMSCRIPTEN)
    set(SDL2_LIBRARY "SDL2")
    set(SDL2_INCLUDE_DIR "${EMSDK}/emscripten/system/include/SDL")
    # set(SDL2_MIXER_LIBRARIES "${SDL2_EXTRACT_PATH}/lib/x64/SDL2_mixer.lib")
    set(SDL2_MIXER_LIBRARY "SDL2_mixer")
    # set(SDL2_MIXER_INCLUDE_DIRS "${SDL2_EXTRACT_PATH}/include")
    set(SDL2_MIXER_INCLUDE_DIR "${EMSDK}/emscripten/system/include/SDL")
else()
    find_package(SDL2 REQUIRED)
    find_package(SDL2_mixer REQUIRED)
endif()

if (PLATFORM_ANDROID)
    add_library(${GAME} SHARED ${SDL2_ANDROID_HOOK} ${SOURCE_FILES})
else()
    add_executable(${GAME} WIN32 ${SOURCE_FILES})
endif()

if (MSVC)
    add_compile_definitions(_CRT_SECURE_NO_WARNINGS)
endif()

if(APPLE)
    # generating a macOS icns file (see https://stackoverflow.com/a/20703594)
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

    # setting variables that will populate Info.plist
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

    # if SDL2 library is a framework, we need to indicate to CMake
    # the path to its dependencies. SDL2_LIBRARY contains two parts.
    # Example: /Library/Frameworks/SDL2.framework;-framework Cocoa
    # So strip out everything after the ';'
    string(REGEX REPLACE ";.*$" "" SDL2_LIB_DIR "${SDL2_LIBRARY}")
    if(EXISTS "${SDL2_LIB_DIR}/Versions/A/Frameworks")
        list(APPEND DIRS "${SDL2_LIB_DIR}/Versions/A/Frameworks")
    endif()

    # if SDL2_mixer library is a framework, we need to indicate to CMake
    # the path to its dependencies (Ogg.framework etc):
    if(EXISTS "${SDL2_MIXER_LIBRARY}/Versions/A/Frameworks")
        list(APPEND DIRS "${SDL2_MIXER_LIBRARY}/Versions/A/Frameworks")
    endif()

    # Install the bundle first
    install(TARGETS ${GAME}
        BUNDLE DESTINATION .
        RUNTIME DESTINATION bin)
    
    # when installing, "fixup" automatically copies librairies inside the
    # bundle and links the binary against them
    install(CODE "
        include(BundleUtilities)
        fixup_bundle(\"\${CMAKE_INSTALL_PREFIX}/${PROJECT_NAME}.app\" \"${LIBS}\" \"${DIRS}\")
    ")

    # perform ad-hoc codesigning
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
include_directories(${EXTEXPAT_INCLUDE_DIR})
include_directories(${EXTMUJS_INCLUDE_DIR})
include_directories(${CMRC_INCLUDE_DIR})
include_directories(${EXTLAME_INCLUDE_DIR})

if (PLATFORM_ANDROID OR WIN_EMSCRIPTEN OR APPLE)
    # no filters on android
    set(GPUPIXEL_LIBRARY "")
else()
    include_directories(${GPUPIXEL_INCLUDE_DIR})
endif()

include_directories(ext)
include_directories(src)
include_directories(ext/imgui)
include_directories(ext/imgui/backends)
include_directories(ext/openssl/include)

if(MSVC)
    include_directories(ext/imgui/dirent)
    include_directories(ext/bugtrap)
    include_directories(ext/ffmpeg/include)
    set_target_properties(${GAME} PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY "${GAME_WORKING_DIRECTORY}")
endif()

if (UNIX AND NOT APPLE AND (CMAKE_COMPILER_IS_GNUCC OR CMAKE_C_COMPILER_ID STREQUAL "Clang"))
    target_link_libraries(${GAME} m)
endif()

if (OPTION_SYSTEM_LIBPNG)
    if (OPTION_BUILD_LIBPNG)
        include(FetchContent)
        FetchContent_Declare(
                zlib
                GIT_REPOSITORY https://github.com/madler/zlib
                GIT_TAG v1.3.1
        )
        FetchContent_MakeAvailable(zlib)
        include_directories(${ZLIB_INCLUDE_DIR})
        target_link_libraries(${GAME} ${ZLIB_LIBRARY})

        FetchContent_Declare(
                libpng
                GIT_REPOSITORY https://github.com/pnggroup/libpng.git
                GIT_TAG v1.6.50
        )
        FetchContent_MakeAvailable(libpng)
        set(PNG_LIBRARIES png_static)
    else()
        find_package(PNG)
    endif()

    include_directories(${PNG_INCLUDE_DIRS})
    target_link_libraries(${GAME} ${PNG_LIBRARIES})
else()
    add_subdirectory(ext/png)
    include_directories(${EXTPNG_INCLUDE_DIR})
    target_link_libraries(${GAME} ${EXTPNG_LIBRARY})
endif()

target_link_libraries (${GAME}
                        ${SDL2_LIBRARY} ${SDL2_MIXER_LIBRARY} ${EXTMUJS_LIBRARY}
                        ${EXTEXPAT_LIBRARY} ${CPPTRACE_LIBRARY}
                        ${EXTLAME_LIBRARY} ${LZMA_LIBRARY} ${BZIP_LIBRARY} ${AES_LIBRARY} ${GPUPIXEL_LIBRARY} akhenaten::rc)

if(MSVC)
   target_link_libraries(${GAME} "winmm" "imagehlp" "shlwapi")
   set(FFMPEG_LIB ${CMAKE_SOURCE_DIR}/ext/ffmpeg/lib)
   target_link_libraries(${GAME} ${FFMPEG_LIB}/avcodec.lib)
   target_link_libraries(${GAME} ${FFMPEG_LIB}/swscale.lib)
   target_link_libraries(${GAME} ${FFMPEG_LIB}/avutil.lib)
   target_link_libraries(${GAME} ${FFMPEG_LIB}/avformat.lib)
   target_link_libraries(${GAME} ${CMAKE_SOURCE_DIR}/ext/bugtrap/BugTrap-x64.lib)
   target_link_libraries(${GAME} ${CMAKE_SOURCE_DIR}/ext/openssl/lib/libssl.lib)
   target_link_libraries(${GAME} ${CMAKE_SOURCE_DIR}/ext/openssl/lib/libcrypto.lib)
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
