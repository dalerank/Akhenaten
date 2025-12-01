cmake_minimum_required(VERSION 3.18.1)

# Устанавливаем ANDROID_STL ДО project() для правильной инициализации toolchain
# Это обеспечивает символы __cxa_guard_acquire и др. для инициализации C++
# Используем c++_static чтобы соответствовать статически собранным зависимостям (SDL2, SDL2_mixer и др.)
if(ANDROID)
    set(ANDROID_STL "c++_static" CACHE STRING "" FORCE)
endif()

project(akhenaten)

# Подключаем CMakeRC для создания заголовков cmrc/cmrc.hpp
set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/../../../../../cmake")
include("${CMAKE_MODULE_PATH}/CMakeRC.cmake")

# Используем готовые prebuilt библиотеки
set(PREBUILT_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../../../../prebuilt")
set(PREBUILT_LIB_DIR "${PREBUILT_DIR}/${ANDROID_ABI}/lib")
set(PREBUILT_INCLUDE_DIR "${PREBUILT_DIR}/${ANDROID_ABI}/include")

# Корневая директория исходников
set(SRC_ROOT "${CMAKE_CURRENT_SOURCE_DIR}/../../../../../src")

# ImGui исходники (скачаны через Gradle)
set(DEPS_ROOT "${CMAKE_CURRENT_SOURCE_DIR}/_deps")

# Автоматический поиск исходных файлов (как в основном CMakeLists.txt)
file(GLOB PLATFORM_FILES ${SRC_ROOT}/platform/*.cpp)
file(GLOB ANDROID_FILES ${SRC_ROOT}/platform/android/*.cpp)
file(GLOB CONFIG_FILES ${SRC_ROOT}/config/*.cpp)
file(GLOB CONTENT_FILES ${SRC_ROOT}/content/*.cpp)
file(GLOB CORE_FILES ${SRC_ROOT}/core/*.cpp)
file(GLOB CORE_ENCODING_FILES ${SRC_ROOT}/core/encoding/*.cpp)
file(GLOB BUILDING_FILES ${SRC_ROOT}/building/*.cpp)
file(GLOB BUILDING_CONSTRUCTION_FILES ${SRC_ROOT}/building/construction/*.cpp)
file(GLOB CITY_FILES ${SRC_ROOT}/city/*.cpp)
file(GLOB EMPIRE_FILES ${SRC_ROOT}/empire/*.cpp)
file(GLOB FIGURE_FILES ${SRC_ROOT}/figure/*.cpp)
file(GLOB FIGURETYPE_FILES ${SRC_ROOT}/figuretype/*.cpp)
file(GLOB GAME_FILES ${SRC_ROOT}/game/*.cpp)
file(GLOB TUTORIAL_FILES ${SRC_ROOT}/tutorial/*.cpp)
file(GLOB INPUT_FILES ${SRC_ROOT}/input/*.cpp)
file(GLOB GRID_FILES ${SRC_ROOT}/grid/*.cpp)
file(GLOB GRID_ROUTING_FILES ${SRC_ROOT}/grid/routing/*.cpp)
file(GLOB SCENARIO_FILES ${SRC_ROOT}/scenario/*.cpp)
file(GLOB GRAPHICS_ELEMENTS_FILES ${SRC_ROOT}/graphics/elements/*.cpp)
file(GLOB GRAPHICS_VIEW_FILES ${SRC_ROOT}/graphics/view/*.cpp)
file(GLOB GRAPHICS_FONTGEN_FILES ${SRC_ROOT}/graphics/fontgen/*.cpp)
file(GLOB SOUND_FILES ${SRC_ROOT}/sound/*.cpp)
file(GLOB WIDGET_FILES ${SRC_ROOT}/widget/*.cpp)
file(GLOB WIDGET_CITY_FILES ${SRC_ROOT}/widget/city/*.cpp)
file(GLOB OVERLAYS_FILES ${SRC_ROOT}/overlays/*.cpp)
file(GLOB WIDGET_SIDEBAR_FILES ${SRC_ROOT}/widget/sidebar/*.cpp)
file(GLOB WINDOW_ADVISOR_FILES ${SRC_ROOT}/window/advisor/*.cpp)
file(GLOB WINDOW_FILES ${SRC_ROOT}/window/*.cpp)
file(GLOB WINDOW_EDITOR_FILES ${SRC_ROOT}/window/editor/*.cpp)
file(GLOB WINDOW_BUILDING_FILES ${SRC_ROOT}/window/building/*.cpp)
file(GLOB DEV_FILES ${SRC_ROOT}/dev/*.cpp)
file(GLOB EDITOR_FILES ${SRC_ROOT}/editor/*.cpp)
file(GLOB TRANSLATION_FILES ${SRC_ROOT}/translation/*.cpp)
file(GLOB GRAPHICS_FILES ${SRC_ROOT}/graphics/*.cpp)
file(GLOB IO_FILES ${SRC_ROOT}/io/*.cpp)
file(GLOB IO_CONFIG_FILES ${SRC_ROOT}/io/config/*.cpp)
file(GLOB IO_GAMEFILES_FILES ${SRC_ROOT}/io/gamefiles/*.cpp)
file(GLOB IO_GAMESTATE_FILES ${SRC_ROOT}/io/gamestate/*.cpp)
file(GLOB IO_IMAGEPAKS_FILES ${SRC_ROOT}/io/imagepaks/*.cpp)
file(GLOB IO_PLAYERDATA_FILES ${SRC_ROOT}/io/playerdata/*.cpp)
file(GLOB RESOURCE_FILES ${SRC_ROOT}/resource/*.cpp)
file(GLOB JS_FILES ${SRC_ROOT}/js/*.cpp)
file(GLOB SCRIPTS_FILES ${SRC_ROOT}/scripts/*.cpp)
file(GLOB LZMA_FILES ${SRC_ROOT}/lzma/*.c)
file(GLOB BZIP_FILES ${SRC_ROOT}/bzip/*.c)
file(GLOB LAME_FILES ${SRC_ROOT}/lame/libmp3lame/*.c)
file(GLOB MUJS_FILES ${SRC_ROOT}/mujs/*.c)

# ImGui файлы (скачаны через Gradle)
set(IMGUI_FILES "")
if(EXISTS "${DEPS_ROOT}/imgui-src/imgui.cpp")
    list(APPEND IMGUI_FILES
        ${DEPS_ROOT}/imgui-src/imgui.cpp
        ${DEPS_ROOT}/imgui-src/imgui_draw.cpp
        ${DEPS_ROOT}/imgui-src/imgui_tables.cpp
        ${DEPS_ROOT}/imgui-src/imgui_widgets.cpp
        ${DEPS_ROOT}/imgui-src/backends/imgui_impl_sdl2.cpp
        ${DEPS_ROOT}/imgui-src/backends/imgui_impl_sdlrenderer2.cpp
        ${DEPS_ROOT}/imgui-src/misc/cpp/imgui_stdlib.cpp
    )
endif()

# Используем готовые prebuilt библиотеки из prebuilt/ директории
# Библиотеки должны быть собраны заранее и размещены в android/prebuilt/${ANDROID_ABI}/

# Объединяем все исходные файлы
set(SOURCE_FILES
    ${PLATFORM_FILES}
    ${ANDROID_FILES}
    ${CONFIG_FILES}
    ${CONTENT_FILES}
    ${CORE_FILES}
    ${CORE_ENCODING_FILES}
    ${BUILDING_FILES}
    ${BUILDING_CONSTRUCTION_FILES}
    ${CITY_FILES}
    ${EMPIRE_FILES}
    ${FIGURE_FILES}
    ${FIGURETYPE_FILES}
    ${GAME_FILES}
    ${TUTORIAL_FILES}
    ${INPUT_FILES}
    ${GRID_FILES}
    ${GRID_ROUTING_FILES}
    ${SCENARIO_FILES}
    ${GRAPHICS_FILES}
    ${GRAPHICS_ELEMENTS_FILES}
    ${GRAPHICS_VIEW_FILES}
    ${GRAPHICS_FONTGEN_FILES}
    ${SOUND_FILES}
    ${WIDGET_FILES}
    ${WIDGET_CITY_FILES}
    ${OVERLAYS_FILES}
    ${WIDGET_SIDEBAR_FILES}
    ${WINDOW_FILES}
    ${WINDOW_ADVISOR_FILES}
    ${WINDOW_EDITOR_FILES}
    ${WINDOW_BUILDING_FILES}
    ${DEV_FILES}
    ${EDITOR_FILES}
    ${TRANSLATION_FILES}
    ${IO_FILES}
    ${IO_CONFIG_FILES}
    ${IO_GAMEFILES_FILES}
    ${IO_GAMESTATE_FILES}
    ${IO_IMAGEPAKS_FILES}
    ${IO_PLAYERDATA_FILES}
    ${RESOURCE_FILES}
    ${JS_FILES}
    ${SCRIPTS_FILES}
    ${LZMA_FILES}
    ${BZIP_FILES}
    ${LAME_FILES}
    ${MUJS_FILES}
    ${IMGUI_FILES}
)

# Создаем библиотеку ресурсов (CMRC)
set(PROJECT_ROOT "${CMAKE_CURRENT_SOURCE_DIR}/../../../../../")
set(SCRIPTS_FOLDER "${PROJECT_ROOT}/src/scripts")
file(GLOB SCRIPT_FILES ${SCRIPTS_FOLDER}/*.js)
set(RES_FOLDER "${PROJECT_ROOT}/res")

cmrc_add_resource_library(
    resources
    ALIAS akhenaten::rc
    NAMESPACE akhenaten
)

# Добавляем ресурсы с указанием базовой директории (WHENCE)
cmrc_add_resources(
    resources
    WHENCE ${PROJECT_ROOT}
    ${SCRIPT_FILES}
    ${RES_FOLDER}/akhenaten_72.png
    ${RES_FOLDER}/patreon_48.png
)

# Создаем библиотеку
add_library(akhenaten SHARED ${SOURCE_FILES})

# Включаемые директории
target_include_directories(akhenaten PRIVATE
    ${SRC_ROOT}
    ${SRC_ROOT}/mujs
    ${SRC_ROOT}/lame/include
    ${PREBUILT_INCLUDE_DIR}
    ${PREBUILT_INCLUDE_DIR}/SDL2
    ${PREBUILT_INCLUDE_DIR}/SDL2_mixer
    ${PREBUILT_INCLUDE_DIR}/freetype2
    ${PREBUILT_INCLUDE_DIR}/harfbuzz
    ${PREBUILT_INCLUDE_DIR}/png
    ${DEPS_ROOT}/imgui-src
    ${DEPS_ROOT}/imgui-src/backends
    ${DEPS_ROOT}/imgui-src/misc/cpp
    ${DEPS_ROOT}/stb-src
    ${CMAKE_CURRENT_SOURCE_DIR}/../../../../../ext
    ${CMRC_INCLUDE_DIR}
)

# Флаги компиляции
target_compile_definitions(akhenaten PRIVATE
    ANDROID_BUILD=ON
    GAME_BUILD_NUMBER=0
    HAVE_MEMCPY=1
    STDC_HEADERS=1
    HAVE_MPGLIB=1       
)

# Флаги только для C++ файлов
target_compile_options(akhenaten PRIVATE
    $<$<COMPILE_LANGUAGE:CXX>:-std=c++17>
    $<$<COMPILE_LANGUAGE:CXX>:-Wno-format-security>
    $<$<COMPILE_LANGUAGE:CXX>:-Wno-switch>
    $<$<COMPILE_LANGUAGE:CXX>:-Wno-absolute-value>
)

# Связываем готовые prebuilt библиотеки
target_link_libraries(akhenaten
    akhenaten::rc
    ${PREBUILT_LIB_DIR}/libSDL2-static.a
    ${PREBUILT_LIB_DIR}/libSDL2_mixer.a
    ${PREBUILT_LIB_DIR}/libzlibstatic.a
    ${PREBUILT_LIB_DIR}/libfreetype.a
    ${PREBUILT_LIB_DIR}/libharfbuzz.a
    ${PREBUILT_LIB_DIR}/libpng.a
    log
    android
    EGL
    GLESv2
    GLESv1_CM
    OpenSLES
    c++
)
