cmake_minimum_required(VERSION 3.0.2)
include(CMakeDependentOption)

#
# Ozymandias
#
option(SYSTEM_LIBS "Use system libraries when available." ON)
set(CMAKE_BUILD_PLATFORM "default" CACHE STRING "Platform to cross-compile for. Options: android default")

set(GAME ozymandias)
project(${GAME} CXX)
message("C++ compiler is ${CMAKE_CXX_COMPILER_ID}" )

if(CMAKE_SIZEOF_VOID_P EQUAL 8)
  set(GAME_ARCH_64 TRUE)
  set(GAME_PROCESSOR_ARCH "x64")
else()
  set(GAME_ARCH_64 FALSE)
  set(GAME_PROCESSOR_ARCH "x86")
endif(CMAKE_SIZEOF_VOID_P EQUAL 8)

set(CMAKE_MODULE_PATH "${CMAKE_MODULE_PATH}" "${CMAKE_SOURCE_DIR}/cmake/")

# Find revision ID and hash of the sourcetree
include("${CMAKE_SOURCE_DIR}/cmake/GenerateVersionHPP.cmake")

#set(CMAKE_RC_LINK_EXECUTABLE "${CMAKE_CXX_LINK_EXECUTABLE}")
if (MSVC)
    add_compile_options(/wd4244)
    add_compile_options(/MP)
    add_compile_options(/EHsc)
elseif (APPLE)
    set(CMAKE_CXX_FLAGS "-Wno-c++11-narrowing -Wno-deprecated-declarations -Wno-switch --std=c++17 -fno-exceptions -stdlib=libc++ ${CMAKE_CXX_FLAGS}")
else()
    set(CMAKE_CXX_FLAGS "-Wno-c++11-narrowing -fno-exceptions -static-libgcc -static-libstdc++ ${CMAKE_CXX_FLAGS}")
endif()

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(GAME_WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}/bin_x64")

set(SDL2_VERSION "2.28.0")
set(SDL2_DEP_FILENAME "SDL2-devel-${SDL2_VERSION}-VC.zip")
set(SDL2_UNPACK_DIR "SDL2-${SDL2_VERSION}")
set(SDL2_DOWNLOAD_URL "http://libsdl.org/release/${SDL2_DEP_FILENAME}")
set(SDL2_TMP_ZIP_PATH "${CMAKE_BINARY_DIR}/tmp/${SDL2_DEP_FILENAME}")
set(SDL2_EXTRACT_PATH "${CMAKE_CURRENT_SOURCE_DIR}/ext/SDL2")
set(SDL2_CHECK_PATH "${SDL2_EXTRACT_PATH}/include/SDL.h")

if (MSVC)
    set(SDL_EXT_DIR ${CMAKE_CURRENT_SOURCE_DIR}/ext/SDL2)
endif()

if(CMAKE_BUILD_TYPE STREQUAL "RelWithDebInfo")
    SET(GAME_BUILD_TYPE "RelWithDebInfo")
elseif(CMAKE_BUILD_TYPE STREQUAL "Release")
    SET(GAME_BUILD_TYPE "Release")
else()
    SET(GAME_BUILD_TYPE "Debug")
endif()

if (MSVC AND NOT EXISTS "${SDL2_CHECK_PATH}")
    message("Download SDL2 to ${SDL2_TMP_ZIP_PATH}")
    file(DOWNLOAD "${SDL2_DOWNLOAD_URL}" "${SDL2_TMP_ZIP_PATH}")
    message("Unpack SDL2 to ${SDL2_EXTRACT_PATH}")
    execute_process(COMMAND ${CMAKE_COMMAND} -E tar xzf ${SDL2_TMP_ZIP_PATH} WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/tmp)
    file(COPY ${CMAKE_BINARY_DIR}/tmp/${SDL2_UNPACK_DIR}/include DESTINATION ${SDL2_EXTRACT_PATH})
    file(COPY ${CMAKE_BINARY_DIR}/tmp/${SDL2_UNPACK_DIR}/lib DESTINATION ${SDL2_EXTRACT_PATH})
endif()

set(SDL2_MIXER_VERSION "2.0.4")
set(SDL2_MIXER_DEP_FILENAME "SDL2_mixer-devel-${SDL2_MIXER_VERSION}-VC.zip")
set(SDL2_MIXER_DOWNLOAD_URL "https://libsdl.org/projects/SDL_mixer/release/${SDL2_MIXER_DEP_FILENAME}")
set(SDL2_MIXER_UNPACK_DIR "SDL2_mixer-${SDL2_MIXER_VERSION}")
set(SDL2_MIXER_CHECK_PATH "${SDL2_EXTRACT_PATH}/include/SDL_mixer.h")
set(SDL2_MIXER_TMP_ZIP_PATH "${CMAKE_BINARY_DIR}/tmp/${SDL2_MIXER_DEP_FILENAME}")

if (MSVC AND NOT EXISTS "${SDL2_MIXER_CHECK_PATH}")
    message("Download SDL2_mixer to ${SDL2_MIXER_TMP_ZIP_PATH}")
    file(DOWNLOAD "${SDL2_MIXER_DOWNLOAD_URL}" "${SDL2_MIXER_TMP_ZIP_PATH}")
    message("Unpack SDL2_mixer to ${SDL2_EXTRACT_PATH}")
    execute_process(COMMAND ${CMAKE_COMMAND} -E tar xzf ${SDL2_MIXER_TMP_ZIP_PATH} WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/tmp)
    file(COPY ${CMAKE_BINARY_DIR}/tmp/${SDL2_MIXER_UNPACK_DIR}/include DESTINATION ${SDL2_EXTRACT_PATH})
    file(COPY ${CMAKE_BINARY_DIR}/tmp/${SDL2_MIXER_UNPACK_DIR}/lib DESTINATION ${SDL2_EXTRACT_PATH})
endif()

set(SDL2_IMAGE_VERSION "2.6.3")
set(SDL2_IMAGE_DEP_FILENAME "SDL2_image-devel-${SDL2_IMAGE_VERSION}-VC.zip")
set(SDL2_IMAGE_DOWNLOAD_URL "https://libsdl.org/projects/SDL_image/release/${SDL2_IMAGE_DEP_FILENAME}")
set(SDL2_IMAGE_UNPACK_DIR "SDL2_image-${SDL2_IMAGE_VERSION}")
set(SDL2_IMAGE_CHECK_PATH "${SDL2_EXTRACT_PATH}/include/SDL_image.h")
set(SDL2_IMAGE_TMP_ZIP_PATH "${CMAKE_BINARY_DIR}/tmp/${SDL2_IMAGE_DEP_FILENAME}")

if (MSVC AND NOT EXISTS "${SDL2_IMAGE_CHECK_PATH}")
    message("Download SDL2_image to ${SDL2_IMAGE_TMP_ZIP_PATH}")
    file(DOWNLOAD "${SDL2_IMAGE_DOWNLOAD_URL}" "${SDL2_IMAGE_TMP_ZIP_PATH}")
    message("Unpack SDL2_image to ${SDL2_EXTRACT_PATH}")
    execute_process(COMMAND ${CMAKE_COMMAND} -E tar xzf ${SDL2_IMAGE_TMP_ZIP_PATH} WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/tmp)
    file(COPY ${CMAKE_BINARY_DIR}/tmp/${SDL2_IMAGE_UNPACK_DIR}/include DESTINATION ${SDL2_EXTRACT_PATH})
    file(COPY ${CMAKE_BINARY_DIR}/tmp/${SDL2_IMAGE_UNPACK_DIR}/lib DESTINATION ${SDL2_EXTRACT_PATH})
endif()

set(CPPTRACE_EXT_PATH "${CMAKE_CURRENT_SOURCE_DIR}/ext/cpptrace")
set(CPPTRACE_CHECK_PATH "${CPPTRACE_EXT_PATH}/include/cpptrace/cpptrace.hpp")

if(CMAKE_BUILD_TYPE STREQUAL "RelWithDebInfo" OR CMAKE_BUILD_TYPE STREQUAL "Debug")
    if (MSVC AND EXISTS "${CPPTRACE_CHECK_PATH}")
        add_definitions(-DCPPTRACE_ENABLED=ON)
        include_directories(${PROJECT_SOURCE_DIR}/ext/cpptrace/include)
        set(CPPTRACE_LIBRARY cpptrace)
        add_subdirectory(ext/cpptrace)
    endif()
endif()

if (MSVC)
    file(GLOB SDL2_DLL_PUBLIC_DLL "${SDL2_EXTRACT_PATH}/lib/${GAME_PROCESSOR_ARCH}/*.dll")
endif()

set(PROJECT_VERSION_MAJOR 0)
set(PROJECT_VERSION_MINOR 0)
set(PROJECT_VERSION_PATCH 2)
set(IS_RELEASE_VERSION FALSE)
set(VERSION_REVISION "")

file(COPY ${SDL2_DLL_PUBLIC_DLL} DESTINATION ${GAME_WORKING_DIRECTORY})

#configure_file(${PROJECT_SOURCE_DIR}/gen/version.rc.in ${PROJECT_SOURCE_DIR}/res/version.rc)
#configure_file(${PROJECT_SOURCE_DIR}/gen/version.txt.in ${PROJECT_SOURCE_DIR}/res/version.txt)

set(EXPAT_FILES
    ext/expat/xmlparse.c
    ext/expat/xmlrole.c
    ext/expat/xmltok.c
)

#add_subdirectory(ext/png)

add_subdirectory(ext/zlib)

#set(SDL_IMAGE_FILES
##    ext/SDL_image/IMG_savejpg.c
#    ext/SDL_image/IMG_savepng.c
#)

set(IO_FILES
    ${PROJECT_SOURCE_DIR}/src/io/log.cpp
    ${PROJECT_SOURCE_DIR}/src/io/dir.cpp
    ${PROJECT_SOURCE_DIR}/src/io/file.cpp
    ${PROJECT_SOURCE_DIR}/src/io/file_formats.cpp
    ${PROJECT_SOURCE_DIR}/src/io/io.cpp
    ${PROJECT_SOURCE_DIR}/src/io/io_buffer.cpp
    ${PROJECT_SOURCE_DIR}/src/io/config/config.cpp
    ${PROJECT_SOURCE_DIR}/src/io/config/hotkeys.cpp
    ${PROJECT_SOURCE_DIR}/src/io/gamestate/chunks.cpp
    ${PROJECT_SOURCE_DIR}/src/io/manager.cpp
    ${PROJECT_SOURCE_DIR}/src/io/gamestate/boilerplate.cpp
    ${PROJECT_SOURCE_DIR}/src/io/imagepaks/imagepak.cpp
    ${PROJECT_SOURCE_DIR}/src/io/imagepaks/atlas_packer.cpp
    ${PROJECT_SOURCE_DIR}/src/io/playerdata/player_data.cpp
    ${PROJECT_SOURCE_DIR}/src/io/gamefiles/lang.cpp
    ${PROJECT_SOURCE_DIR}/src/io/gamefiles/smacker.cpp
#    ${PROJECT_SOURCE_DIR}/src/io/gamefiles/mods.cpp
#    ${PROJECT_SOURCE_DIR}/src/io/gamefiles/png_read.cpp
)

set(GRAPHICS_FILES
    ${PROJECT_SOURCE_DIR}/src/graphics/image.cpp
    ${PROJECT_SOURCE_DIR}/src/graphics/boilerplate.cpp
    ${PROJECT_SOURCE_DIR}/src/graphics/screen.cpp
    #    ${PROJECT_SOURCE_DIR}/src/graphics/screenshot.cpp
    ${PROJECT_SOURCE_DIR}/src/graphics/window.cpp
    ${PROJECT_SOURCE_DIR}/src/graphics/video.cpp
    ${PROJECT_SOURCE_DIR}/src/graphics/animation_timers.cpp
    ${PROJECT_SOURCE_DIR}/src/graphics/font.cpp
    ${PROJECT_SOURCE_DIR}/src/graphics/text.cpp
)

file(GLOB PLATFORM_FILES ${PROJECT_SOURCE_DIR}/src/platform/*.cpp)
file(GLOB CORE_FILES ${PROJECT_SOURCE_DIR}/src/core/*.cpp)
file(GLOB CORE_ENCODING_FILES ${PROJECT_SOURCE_DIR}/src/core/encoding/*.cpp)
file(GLOB BUILDING_FILES ${PROJECT_SOURCE_DIR}/src/building/*.cpp)
file(GLOB BUILDING_CONSTRUCTION_FILES ${PROJECT_SOURCE_DIR}/src/building/construction/*.cpp)
file(GLOB CITY_FILES ${PROJECT_SOURCE_DIR}/src/city/*.cpp)
file(GLOB EMPIRE_FILES ${PROJECT_SOURCE_DIR}/src/empire/*.cpp)
file(GLOB FIGURE_FILES ${PROJECT_SOURCE_DIR}/src/figure/*.cpp)
file(GLOB FIGURETYPE_FILES ${PROJECT_SOURCE_DIR}/src/figuretype/*.cpp)
file(GLOB GAME_FILES ${PROJECT_SOURCE_DIR}/src/game/*.cpp)
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

if (CMAKE_BUILD_PLATFORM STREQUAL "Android")
    file(GLOB ANDROID_BACKEND_FILES ${PROJECT_SOURCE_DIR}/src/platform/android/*.cpp)
    set(PLATFORM_FILES ${PLATFORM_FILES} ${ANDROID_BACKEND_FILES})
    set(SDL2_ANDROID_HOOK ${SDL_EXT_DIR}/src/main/android/SDL_android_main.c)
    # set(SDL2_LIBRARY SDL2::SDL2)
    # set(SDL2_MIXER_LIBRARY SDL2::SDL2_mixer)
endif()

set(TRACY_EXT_PATH "${CMAKE_CURRENT_SOURCE_DIR}/ext/tracy")
set(TRACY_CHECK_PATH "${TRACY_EXT_PATH}/public/TracyClient.cpp")

if (MSVC AND EXISTS "${TRACY_CHECK_PATH}")
    add_definitions(-DTRACY_ENABLE=ON)
    set(TRACY_FILES ${PROJECT_SOURCE_DIR}/ext/tracy/public/TracyClient.cpp)
    include_directories(${PROJECT_SOURCE_DIR}/ext/tracy/public/)
endif ()

set(WIDGET_CITY_FILES ${WIDGET_CITY_FILES}
    ${PROJECT_SOURCE_DIR}/src/widget/city.cpp)

set(WINDOW_ADVISOR_FILES ${WINDOW_ADVISOR_FILES}
    ${PROJECT_SOURCE_DIR}/src/window/advisors.cpp)

set(IMGUI_FILES ${IMGUI_FILES} ${IMGUI_CPP_FILES} ${IMGUI_BACKEND_FILES})

if(MSVC)
    file(GLOB CORE_HEADERS ${PROJECT_SOURCE_DIR}/src/core/*.h)
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

    set(CORE_FILES ${CORE_FILES} ${CORE_HEADERS})
    set(PLATFORM_FILES ${PLATFORM_FILES} ${PLATFORM_HEADERS})
    set(BUILDING_FIELS ${BUILDING_FIELS} ${BUILDING_HEADERS})
    set(BUILDING_CONSTRUCTION_FILES ${BUILDING_CONSTRUCTION_FILES} ${BUILDING_CONSTRUCTION_HEADERS})
    set(CITY_FILES ${CITY_FILES} ${CITY_HEADERS})
    set(EMPIRE_FILES ${EMPIRE_FILES} ${EMPIRE_HEADERS})
    set(FIGURE_FILES ${FIGURE_FILES} ${FIGURE_HEADERS})
    set(FIGURETYPE_FILES ${FIGURETYPE_FILES} ${FIGURETYPE_HEADERS})
    set(GAME_FILES ${GAME_FILES} ${GAME_HEADERS})
    set(INPUT_FILES ${INPUT_FILES} ${INPUT_HEADERS})
    set(GRID_FILES ${GRID_FILES} ${GRID_HEADERS})
    set(GRID_ROUTING_FILES ${GRID_ROUTING_FILES} ${GRID_ROUTING_HEADERS})
    set(SCENARIO_FILES ${SCENARIO_FILES} ${SCENARIO_HEADERS})
    set(GRAPHICS_ELEMENTS_FILES ${GRAPHICS_ELEMENTS_FILES} ${GRAPHICS_ELEMENTS_HEADERS})
    set(GRAPHICS_VIEW_FILES ${GRAPHICS_VIEW_FILES} ${GRAPHICS_VIEW_HEADERS})
    set(SOUND_FILES ${SOUND_FILES} ${SOUND_HEADERS})
    set(WIDGET_FILES ${WIDGET_FILES} ${WIDGET_HEADERS})
    set(WIDGET_CITY_FILES ${WIDGET_CITY_FILES} ${WIDGET_CITY_HEADERS})
    set(OVERLAYS_FILES ${OVERLAYS_FILES} ${OVERLAYS_HEADERS})
    set(WIDGET_SIDEBAR_FILES ${WIDGET_SIDEBAR_FILES} ${WIDGET_SIDEBAR_HEADERS})
    set(WINDOW_ADVISOR_FILES ${WINDOW_ADVISOR_FILES} ${WINDOW_ADVISOR_HEADERS})
    set(WINDOW_FILES ${WINDOW_FILES} ${WINDOW_HEADERS})
    set(WINDOW_BUILDING_FILES ${WINDOW_BUILDING_FILES} ${WINDOW_BUILDING_HEADERS})
    set(DEV_FILES ${DEV_FILES} ${DEV_HEADERS})

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
endif()

set(MACOSX_FILES "")
if(APPLE)
    #set(RC_FILES ${PROJECT_SOURCE_DIR}/res/ozymandias.icns)
elseif(MSVC)
    #set(RC_FILES ${PROJECT_SOURCE_DIR}/res/ozymandias.rc)
endif()

set(SOURCE_FILES
    ${PLATFORM_FILES}
    ${CORE_FILES}
    ${IO_FILES}
    ${BUILDING_FILES}
    ${CITY_FILES}
    ${EMPIRE_FILES}
    ${FIGURE_FILES}
    ${FIGURETYPE_FILES}
    ${GAME_FILES}
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
    ${MACOSX_FILES}
    ${RC_FILES}
    ${TRACY_FILES}
#    ${PNG_FILES}
#    ${SDL_IMAGE_FILES}
#    ${ZLIB_FILES}
)

set_source_files_properties(${SOURCE_FILES} PROPERTIES LANGUAGE CXX)

find_package(SDL2 REQUIRED)
find_package(SDL2_mixer REQUIRED)
find_package(SDL2_image REQUIRED)

if (CMAKE_BUILD_PLATFORM STREQUAL "Android")
    add_library(${GAME} SHARED ${SDL2_ANDROID_HOOK} ${SOURCE_FILES})
else()
    add_executable(${GAME} WIN32 ${SOURCE_FILES})
endif()

if (MSVC)
    add_compile_definitions(_CRT_SECURE_NO_WARNINGS)
endif()

if(APPLE)
    # generating a macOS icns file (see https://stackoverflow.cppom/a/20703594)
    add_custom_command(OUTPUT ${PROJECT_SOURCE_DIR}/res/ozymandias.icns
        COMMAND mkdir -p ozymandias.iconset
        COMMAND sips -z 16 16    ozymandias_256.png --out ozymandias.iconset/icon_16x16.png
        COMMAND sips -z 32 32    ozymandias_256.png --out ozymandias.iconset/icon_16x16@2x.png
        COMMAND sips -z 32 32    ozymandias_256.png --out ozymandias.iconset/icon_32x32.png
        COMMAND sips -z 64 64    ozymandias_256.png --out ozymandias.iconset/icon_32x32@2x.png
        COMMAND sips -z 128 128  ozymandias_256.png --out ozymandias.iconset/icon_128x128.png
        COMMAND sips -z 256 256  ozymandias_256.png --out ozymandias.iconset/icon_128x128@2x.png
        COMMAND sips -z 256 256  ozymandias_256.png --out ozymandias.iconset/icon_256x256.png
        COMMAND iconutil -c icns ozymandias.iconset
        COMMAND rm -R ozymandias.iconset
        WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/res)

    set_source_files_properties(${PROJECT_SOURCE_DIR}/res/ozymandias.icns PROPERTIES
        MACOSX_PACKAGE_LOCATION "Resources")

    # setting variables that will populate Info.plist
    set(MACOSX_BUNDLE_GUI_IDENTIFIER "mt.dalerank.ozymandias")
    set(MACOSX_BUNDLE_BUNDLE_NAME ${PROJECT_NAME})
    set(CMAKE_OSX_DEPLOYMENT_TARGET "10.10" CACHE STRING "Minimum OS X deployment version" FORCE)
    set(MACOSX_BUNDLE_ICON_FILE "ozymandias.icns")
    set(MACOSX_BUNDLE_BUNDLE_VERSION "${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}.${PROJECT_VERSION_PATCH}${VERSION_REVISION}")
    set(MACOSX_BUNDLE_LONG_VERSION_STRING ${MACOSX_BUNDLE_BUNDLE_VERSION})
    set(MACOSX_BUNDLE_SHORT_VERSION_STRING ${MACOSX_BUNDLE_BUNDLE_VERSION})

    set_target_properties(${GAME} PROPERTIES
        MACOSX_BUNDLE TRUE
        MACOSX_BUNDLE_INFO_PLIST "${PROJECT_SOURCE_DIR}/res/Info.plist.in")

    set(DIRS "")

    # if SDL2 library is a framework, we need to indicate to CMake
    # the path to its dependencies. SDL2_LIBRARY contains two parts.
    # Example: /Library/Frameworks/SDL2.framework;-framework Cocoa
    # So strip out everything after the ';'
    string(REGEX REPLACE ";.*$" "" SDL2_LIB_DIR "${SDL2_LIBRARY}")
    if(EXISTS "${SDL2_LIB_DIR}/Versions/A/Frameworks")
        set(DIRS "${DIRS};${SDL2_LIB_DIR}/Versions/A/Frameworks")
    endif()

    # if SDL2_mixer library is a framework, we need to indicate to CMake
    # the path to its dependencies (Ogg.framework etc):
    if(EXISTS "${SDL2_MIXER_LIBRARY}/Versions/A/Frameworks")
        set(DIRS "${DIRS};${SDL2_MIXER_LIBRARY}/Versions/A/Frameworks")
    endif()

    # if SDL2_image library is a framework, we need to indicate to CMake
    # the path to its dependencies (Ogg.framework etc):
    if(EXISTS "${SDL2_IMAGE_LIBRARY}/Versions/A/Frameworks")
        set(DIRS "${DIRS};${SDL2_IMAGE_LIBRARY}/Versions/A/Frameworks")
    endif()

    # when installing, "fixup" automatically copies librairies inside the
    # bundle and links the binary against them
    install(CODE "
        include(BundleUtilities)
        fixup_bundle(${CMAKE_BINARY_DIR}/${PROJECT_NAME}.app \"\" \"${DIRS}\")
    " BUNDLE DESTINATION ${CMAKE_BINARY_DIR})
endif()

include_directories(${SDL2_INCLUDE_DIR})
include_directories(${SDL2_MIXER_INCLUDE_DIR})
include_directories(${SDL2_IMAGE_INCLUDE_DIR})
include_directories(${EXTZLIB_INCLUDE_DIR})

if(SYSTEM_LIBS)
    find_package(ZLIB)
    find_package(PNG)
    find_package(EXPAT)
endif()

if(PNG_FOUND)
    include_directories(${PNG_INCLUDE_DIRS})
    target_link_libraries(${GAME} ${PNG_LIBRARIES})
#else()
#    include_directories("ext/png")
#    target_sources(${GAME} PRIVATE "${PNG_FILES}")
endif()

if(EXPAT_FOUND)
    include_directories(${EXPAT_INCLUDE_DIRS})
    target_link_libraries(${GAME} ${EXPAT_LIBRARIES})
else()
    include_directories("ext/expat")
    target_sources(${GAME} PRIVATE "${EXPAT_FILES}")
    if(NOT WIN32)
        add_compile_definitions(XML_DEV_URANDOM)
    endif()
endif()

include_directories(ext)
include_directories(src)
include_directories(ext/imgui)
include_directories(ext/imgui/backends)
if(MSVC)
    include_directories(ext/dirent)
    set_target_properties(${GAME} PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY "${GAME_WORKING_DIRECTORY}")
endif()

if (UNIX AND NOT APPLE AND (CMAKE_COMPILER_IS_GNUCC OR CMAKE_C_COMPILER_ID STREQUAL "Clang"))
    target_link_libraries(${GAME} m)
endif()

target_link_libraries (${GAME} ${SDL2_LIBRARY} ${SDL2_MIXER_LIBRARY} ${SDL2_IMAGE_LIBRARY} ${CPPTRACE_LIBRARY} ${EXTZLIB_LIBRARY})

if(MSVC)
   target_link_libraries(${GAME} "winmm" "imagehlp" "shlwapi")
endif()

if (CMAKE_BUILD_PLATFORM STREQUAL "Android")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -DPNG_ARM_NEON_OPT=0 -D_BSD_SOURCE")
    find_library(log-lib log)
    find_library(android-lib android)
    target_link_libraries(${GAME} ${log-lib} ${android-lib})
endif()

if(NOT APPLE)
    install(TARGETS ${GAME} RUNTIME DESTINATION bin)
endif()

if(UNIX AND NOT APPLE)
    install(FILES "res/ozymandias.desktop" DESTINATION "share/applications" RENAME "com.github.dalerank.ozymandias.desktop")
    install(FILES "res/ozymandias.metainfo.xml" DESTINATION "share/metainfo" RENAME "com.github.dalerank.ozymandias.metainfo.xml")
    install(FILES "res/ozymandias_48.png" DESTINATION "share/icons/hicolor/48x48/apps" RENAME "com.github.dalerank.ozymandias.png")
    install(FILES "res/ozymandias_256.png" DESTINATION "share/icons/hicolor/256x256/apps" RENAME "com.github.dalerank.ozymandias.png")
    install(FILES "res/ozymandias_512.png" DESTINATION "share/icons/hicolor/512x512/apps" RENAME "com.github.dalerank.ozymandias.png")
endif()

if (MSVC)
    set(BINARY_FILES "${CMAKE_BINARY_DIR}/${GAME_BUILD_TYPE}/${GAME}.exe")

    if(CMAKE_BUILD_TYPE STREQUAL "RelWithDebInfo" OR CMAKE_BUILD_TYPE STREQUAL "Debug")
        set(BINARY_FILES ${BINARY_FILES} "${CMAKE_BINARY_DIR}/ext/cpptrace/${GAME_BUILD_TYPE}/cpptrace.dll")
    endif()

    foreach( file_i ${BINARY_FILES})
        add_custom_command(
            TARGET ${GAME}
            POST_BUILD
            COMMAND ${CMAKE_COMMAND}
            ARGS -E copy ${file_i} "${GAME_WORKING_DIRECTORY}"
        )
    endforeach( file_i )
endif()

