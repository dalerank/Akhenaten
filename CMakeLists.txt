cmake_minimum_required(VERSION 3.0.2)
include(CMakeDependentOption)

if(VITA_BUILD AND SWITCH_BUILD)
    message(FATAL_ERROR "Cannot build with -DVITA_BUILD=ON and -DSWITCH_BUILD=ON at the same time")
endif()

option(DRAW_FPS "Draw FPS on the top left corner of the window." OFF)
option(SYSTEM_LIBS "Use system libraries when available." ON)
cmake_dependent_option(VITA_BUILD "Build for the PlayStation Vita handheld game console." OFF "NOT MSVC" OFF)
cmake_dependent_option(SWITCH_BUILD "Build for the Nintendo Switch handheld game console." OFF "NOT MSVC; NOT VITA_BUILD" OFF)

if(VITA_BUILD AND NOT DEFINED CMAKE_TOOLCHAIN_FILE)
    if(DEFINED ENV{VITASDK})
        set(CMAKE_TOOLCHAIN_FILE "$ENV{VITASDK}/share/vita.toolchain.cppmake" CACHE PATH "toolchain file")
    else()
        message(FATAL_ERROR "Please define VITASDK to point to your SDK path!")
    endif()
endif()

if(SWITCH_BUILD AND NOT DEFINED CMAKE_TOOLCHAIN_FILE)
    if(DEFINED ENV{DEVKITPRO})
        set(DEVKITPRO $ENV{DEVKITPRO})
        set(CMAKE_TOOLCHAIN_FILE "./cmake/switch.cppmake" CACHE PATH "toolchain file")
    else()
        message(FATAL_ERROR "Please define DEVKITPRO to point to your SDK path!")
    endif()
endif()

set(SHORT_NAME ozymandias)
project(${SHORT_NAME} CXX)

if (VITA_BUILD)
    include("${VITASDK}/share/vita.cppmake" REQUIRED)
    set(VITA_TITLEID  "AUGUSTUS001")
endif()

set(CMAKE_MODULE_PATH "${CMAKE_MODULE_PATH}" "${CMAKE_SOURCE_DIR}/cmake/")

#set(CMAKE_RC_LINK_EXECUTABLE "${CMAKE_CXX_LINK_EXECUTABLE}")
set(CMAKE_CXX_FLAGS "-std=c++0x -Wno-c++11-narrowing -static-libgcc -static-libstdc++" ${CMAKE_CXX_FLAGS})
set(CMAKE_CXX_STANDARD 14)

#SET_SOURCE_FILES_PROPERTIES(${SOURCE_FILES} PROPERTIES LANGUAGE CXX)
#list(APPEND CMAKE_CXX_SOURCE_FILE_EXTENSIONS c)
#set(CMAKE_USER_MAKE_RULES_OVERRIDE "CryptoppMakeRulesOverwrite.cppmake")

#if (CMAKE_VERSION VERSION_LESS 3.1)
#    if (CMAKE_COMPILER_IS_GNUCC)
#        set(CMAKE_C_FLAGS "-std=gnu99 ${CMAKE_C_FLAGS}")
#    endif()
#else()
#    set(CMAKE_C_STANDARD 99)
#endif()
#
#if (CMAKE_COMPILER_IS_GNUCC)
#    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Werror=implicit-function-declaration")
#
#    if (CMAKE_C_COMPILER_VERSION VERSION_GREATER 5.0)
#        set(CMAKE_C_FLAGS "-Werror=incompatible-pointer-types -Werror=int-conversion -Wstrict-prototypes ${CMAKE_C_FLAGS}")
#    endif()
#endif()

set(PROJECT_VERSION_MAJOR 0)
set(PROJECT_VERSION_MINOR 0)
set(PROJECT_VERSION_PATCH 2)
set(IS_RELEASE_VERSION FALSE)

if(IS_RELEASE_VERSION)
    set(PROJECT_VERSION_TWEAK 0)
    set(VERSION_REVISION "")
elseif (EXISTS "${CMAKE_SOURCE_DIR}/.git")
    find_package(Git)
    if(Git_FOUND)
        execute_process(
            COMMAND git rev-list --count HEAD ^tags/v${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}.${PROJECT_VERSION_PATCH}
            WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
            RESULT_VARIABLE TWEAK_RESULT
            OUTPUT_VARIABLE PROJECT_VERSION_TWEAK
            OUTPUT_STRIP_TRAILING_WHITESPACE
        )
        execute_process(
            COMMAND git rev-parse --short --verify HEAD
            WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
            OUTPUT_VARIABLE VERSION_COMMIT_HASH
            OUTPUT_STRIP_TRAILING_WHITESPACE
        )
        execute_process(
            COMMAND git diff-index --quiet HEAD --
            WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
            RESULT_VARIABLE VERSION_COMMIT_DIRTY
        )
        if(VERSION_COMMIT_DIRTY)
            set(DIRTY_POSTFIX "-dirty")
        else()
            set(DIRTY_POSTFIX "")
        endif()
        if(NOT TWEAK_RESULT EQUAL 0)
            # Happens on a shallow git clone, like Travis does. Append date to version ref.
            set(PROJECT_VERSION_TWEAK 0)
            string(TIMESTAMP TODAY "%Y%m%d")
            set(VERSION_REVISION "-${TODAY}-${VERSION_COMMIT_HASH}${DIRTY_POSTFIX}")
        else()
            set(VERSION_REVISION ".${PROJECT_VERSION_TWEAK}-${VERSION_COMMIT_HASH}${DIRTY_POSTFIX}")
        endif()
    else()
        set(PROJECT_VERSION_TWEAK 0)
        set(VERSION_REVISION " unknown development version")
    endif()
else()
    set(PROJECT_VERSION_TWEAK 0)
    set(VERSION_REVISION " unknown development version")
endif()

if(VITA_BUILD)
    string(LENGTH "${PROJECT_VERSION_MAJOR}" NUM_DIGITS)
    if(NUM_DIGITS EQUAL 1)
        set(VITA_VERSION_MAJOR "0${PROJECT_VERSION_MAJOR}")
    elseif(NUM_DIGITS EQUAL 2)
        set(VITA_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
    else()
        message(FATAL_ERROR "On Vita, major version number can only have one or two digits, found ${NUM_DIGITS} digits instead")
    endif()

    string(LENGTH "${PROJECT_VERSION_MINOR}" NUM_DIGITS)
    if(NUM_DIGITS EQUAL 1)
        set(VITA_VERSION_MINOR "0${PROJECT_VERSION_MINOR}")
    elseif(NUM_DIGITS EQUAL 2)
        set(VITA_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
    else()
        message(FATAL_ERROR "On Vita, minor version number can only have one or two digits, found ${NUM_DIGITS} digits instead")
    endif()

    set(VITA_VERSION "${VITA_VERSION_MAJOR}.${VITA_VERSION_MINOR}")
endif()

if (SWITCH_BUILD)
    string(SUBSTRING "${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}.${PROJECT_VERSION_PATCH}${VERSION_REVISION}" 0 15 SWITCH_VERSION)
endif()

configure_file(${PROJECT_SOURCE_DIR}/gen/version.cpp.in ${PROJECT_SOURCE_DIR}/src/platform/version.cpp)
configure_file(${PROJECT_SOURCE_DIR}/gen/version.rc.in ${PROJECT_SOURCE_DIR}/res/version.rc)
configure_file(${PROJECT_SOURCE_DIR}/gen/version.txt.in ${PROJECT_SOURCE_DIR}/res/version.txt)

if(DRAW_FPS)
  add_definitions(-DDRAW_FPS)
endif()

set(EXPAT_FILES
    ext/expat/xmlparse.c
    ext/expat/xmlrole.c
    ext/expat/xmltok.c
)

set(TINYFD_FILES
    ext/tinyfiledialogs/tinyfiledialogs.c
)

#set(PNG_FILES
#    ext/png/png.c
#    ext/png/pngerror.c
#    ext/png/pngget.c
#    ext/png/pngmem.c
#    ext/png/pngpread.c
#    ext/png/pngread.c
#    ext/png/pngrio.c
#    ext/png/pngrtran.c
#    ext/png/pngrutil.c
#    ext/png/pngset.c
#    ext/png/pngtrans.c
#    ext/png/pngwio.c
#    ext/png/pngwrite.c
#    ext/png/pngwtran.c
#    ext/png/pngwutil.c
#)

#set(ZLIB_FILES
#    ext/zlib/adler32.c
#    ext/zlib/crc32.c
#    ext/zlib/deflate.c
#    ext/zlib/inffast.c
#    ext/zlib/inflate.c
#    ext/zlib/inftrees.c
#    ext/zlib/trees.c
#    ext/zlib/zutil.c
#)

#set(SDL_IMAGE_FILES
##    ext/SDL_image/IMG_savejpg.c
#    ext/SDL_image/IMG_savepng.c
#)

set(PLATFORM_FILES
    ${PROJECT_SOURCE_DIR}/src/platform/arguments.cpp
    ${PROJECT_SOURCE_DIR}/src/platform/file_manager.cpp
    ${PROJECT_SOURCE_DIR}/src/platform/julius.cpp
    ${PROJECT_SOURCE_DIR}/src/platform/keyboard_input.cpp
    ${PROJECT_SOURCE_DIR}/src/platform/log.cpp
    ${PROJECT_SOURCE_DIR}/src/platform/mouse.cpp
    ${PROJECT_SOURCE_DIR}/src/platform/platform.cpp
    ${PROJECT_SOURCE_DIR}/src/platform/prefs.cpp
    ${PROJECT_SOURCE_DIR}/src/platform/sound_device.cpp
    ${PROJECT_SOURCE_DIR}/src/platform/touch.cpp
    ${PROJECT_SOURCE_DIR}/src/platform/version.cpp
    ${PROJECT_SOURCE_DIR}/src/platform/virtual_keyboard.cpp
    ${PROJECT_SOURCE_DIR}/src/platform/renderer.cpp
)

if (VITA_BUILD)
    set(PLATFORM_FILES
        ${PLATFORM_FILES}
        ${PROJECT_SOURCE_DIR}/src/platform/vita/cursor.cpp
        ${PROJECT_SOURCE_DIR}/src/platform/vita/screen.cpp
        ${PROJECT_SOURCE_DIR}/src/platform/vita/vita.cpp
        ${PROJECT_SOURCE_DIR}/src/platform/vita/vita_input.cpp
        ${PROJECT_SOURCE_DIR}/src/platform/vita/vita_keyboard.cpp
    )
elseif (SWITCH_BUILD)
    set(PLATFORM_FILES
        ${PLATFORM_FILES}
        ${PROJECT_SOURCE_DIR}/src/platform/switch/cursor.cpp
        ${PROJECT_SOURCE_DIR}/src/platform/switch/screen.cpp
        ${PROJECT_SOURCE_DIR}/src/platform/switch/switch_input.cpp
    )
else()
    set(PLATFORM_FILES
        ${PLATFORM_FILES}
        ${PROJECT_SOURCE_DIR}/src/platform/cursor.cpp
        ${PROJECT_SOURCE_DIR}/src/platform/screen.cpp
    )
endif()

set(CORE_FILES
    ${PROJECT_SOURCE_DIR}/src/core/backtrace.cpp
    ${PROJECT_SOURCE_DIR}/src/core/buffer.cpp
    ${PROJECT_SOURCE_DIR}/src/core/calc.cpp
    ${PROJECT_SOURCE_DIR}/src/core/config.cpp
    ${PROJECT_SOURCE_DIR}/src/core/dir.cpp
    ${PROJECT_SOURCE_DIR}/src/core/encoding.cpp
    ${PROJECT_SOURCE_DIR}/src/core/encoding_korean.cpp
    ${PROJECT_SOURCE_DIR}/src/core/encoding_simp_chinese.cpp
    ${PROJECT_SOURCE_DIR}/src/core/encoding_trad_chinese.cpp
    ${PROJECT_SOURCE_DIR}/src/core/file.cpp
    ${PROJECT_SOURCE_DIR}/src/core/hotkey_config.cpp
    ${PROJECT_SOURCE_DIR}/src/core/image.cpp
    ${PROJECT_SOURCE_DIR}/src/core/image_packer.cpp
    ${PROJECT_SOURCE_DIR}/src/core/io.cpp
    ${PROJECT_SOURCE_DIR}/src/core/lang.cpp
    ${PROJECT_SOURCE_DIR}/src/core/locale.cpp
#    ${PROJECT_SOURCE_DIR}/src/core/mods.cpp
#    ${PROJECT_SOURCE_DIR}/src/core/png_read.cpp
    ${PROJECT_SOURCE_DIR}/src/core/random.cpp
    ${PROJECT_SOURCE_DIR}/src/core/smacker.cpp
    ${PROJECT_SOURCE_DIR}/src/core/speed.cpp
    ${PROJECT_SOURCE_DIR}/src/core/string.cpp
    ${PROJECT_SOURCE_DIR}/src/core/time.cpp
    ${PROJECT_SOURCE_DIR}/src/core/zip.cpp
    ${PROJECT_SOURCE_DIR}/src/core/game_environment.cpp
    ${PROJECT_SOURCE_DIR}/src/core/stopwatch.cpp)

set(BUILDING_FILES
    ${PROJECT_SOURCE_DIR}/src/building/animation.cpp
    ${PROJECT_SOURCE_DIR}/src/building/barracks.cpp
    ${PROJECT_SOURCE_DIR}/src/building/building.cpp
    ${PROJECT_SOURCE_DIR}/src/building/count.cpp
    ${PROJECT_SOURCE_DIR}/src/building/destruction.cpp
    ${PROJECT_SOURCE_DIR}/src/building/dock.cpp
    ${PROJECT_SOURCE_DIR}/src/building/figure.cpp
    ${PROJECT_SOURCE_DIR}/src/building/government.cpp
    ${PROJECT_SOURCE_DIR}/src/building/granary.cpp
    ${PROJECT_SOURCE_DIR}/src/building/house.cpp
    ${PROJECT_SOURCE_DIR}/src/building/house_evolution.cpp
    ${PROJECT_SOURCE_DIR}/src/building/house_population.cpp
    ${PROJECT_SOURCE_DIR}/src/building/house_service.cpp
    ${PROJECT_SOURCE_DIR}/src/building/industry.cpp
    ${PROJECT_SOURCE_DIR}/src/building/list.cpp
    ${PROJECT_SOURCE_DIR}/src/building/maintenance.cpp
    ${PROJECT_SOURCE_DIR}/src/building/market.cpp
    ${PROJECT_SOURCE_DIR}/src/building/menu.cpp
    ${PROJECT_SOURCE_DIR}/src/building/model.cpp
    ${PROJECT_SOURCE_DIR}/src/building/properties.cpp
    ${PROJECT_SOURCE_DIR}/src/building/roadblock.cpp
    ${PROJECT_SOURCE_DIR}/src/building/rotation.cpp
    ${PROJECT_SOURCE_DIR}/src/building/storage.cpp
    ${PROJECT_SOURCE_DIR}/src/building/warehouse.cpp
    ${PROJECT_SOURCE_DIR}/src/building/monuments.cpp
    ${PROJECT_SOURCE_DIR}/src/building/construction/build_planner.cpp
    ${PROJECT_SOURCE_DIR}/src/building/construction/clear.cpp
    ${PROJECT_SOURCE_DIR}/src/building/construction/routed.cpp
    ${PROJECT_SOURCE_DIR}/src/building/construction/warnings.cpp
)
set(CITY_FILES
    ${PROJECT_SOURCE_DIR}/src/city/buildings.cpp
    ${PROJECT_SOURCE_DIR}/src/city/culture.cpp
    ${PROJECT_SOURCE_DIR}/src/city/data.cpp
    ${PROJECT_SOURCE_DIR}/src/city/data_private.cpp
    ${PROJECT_SOURCE_DIR}/src/city/emperor.cpp
    ${PROJECT_SOURCE_DIR}/src/city/entertainment.cpp
    ${PROJECT_SOURCE_DIR}/src/city/festival.cpp
    ${PROJECT_SOURCE_DIR}/src/city/figures.cpp
    ${PROJECT_SOURCE_DIR}/src/city/finance.cpp
    ${PROJECT_SOURCE_DIR}/src/city/gods.cpp
    ${PROJECT_SOURCE_DIR}/src/city/health.cpp
    ${PROJECT_SOURCE_DIR}/src/city/houses.cpp
    ${PROJECT_SOURCE_DIR}/src/city/labor.cpp
    ${PROJECT_SOURCE_DIR}/src/city/map.cpp
    ${PROJECT_SOURCE_DIR}/src/city/message.cpp
    ${PROJECT_SOURCE_DIR}/src/city/migration.cpp
    ${PROJECT_SOURCE_DIR}/src/city/military.cpp
    ${PROJECT_SOURCE_DIR}/src/city/mission.cpp
    ${PROJECT_SOURCE_DIR}/src/city/population.cpp
    ${PROJECT_SOURCE_DIR}/src/city/ratings.cpp
    ${PROJECT_SOURCE_DIR}/src/city/resource.cpp
    ${PROJECT_SOURCE_DIR}/src/city/sentiment.cpp
    ${PROJECT_SOURCE_DIR}/src/city/sound.cpp
    ${PROJECT_SOURCE_DIR}/src/city/trade.cpp
    ${PROJECT_SOURCE_DIR}/src/city/victory.cpp
    ${PROJECT_SOURCE_DIR}/src/city/warning.cpp
    ${PROJECT_SOURCE_DIR}/src/city/floods.cpp
    ${PROJECT_SOURCE_DIR}/src/city/view/view.cpp
    ${PROJECT_SOURCE_DIR}/src/city/view/lookup.cpp
)
set(EMPIRE_FILES
    ${PROJECT_SOURCE_DIR}/src/empire/city.cpp
    ${PROJECT_SOURCE_DIR}/src/empire/empire.cpp
    ${PROJECT_SOURCE_DIR}/src/empire/object.cpp
    ${PROJECT_SOURCE_DIR}/src/empire/trade_prices.cpp
    ${PROJECT_SOURCE_DIR}/src/empire/trade_route.cpp
)
set(FIGURE_FILES
    ${PROJECT_SOURCE_DIR}/src/figure/action.cpp
    ${PROJECT_SOURCE_DIR}/src/figure/combat.cpp
    ${PROJECT_SOURCE_DIR}/src/figure/enemy_army.cpp
    ${PROJECT_SOURCE_DIR}/src/figure/figure.cpp
    ${PROJECT_SOURCE_DIR}/src/figure/formation.cpp
    ${PROJECT_SOURCE_DIR}/src/figure/formation_enemy.cpp
    ${PROJECT_SOURCE_DIR}/src/figure/formation_herd.cpp
    ${PROJECT_SOURCE_DIR}/src/figure/formation_layout.cpp
    ${PROJECT_SOURCE_DIR}/src/figure/formation_legion.cpp
    ${PROJECT_SOURCE_DIR}/src/figure/image.cpp
    ${PROJECT_SOURCE_DIR}/src/figure/movement.cpp
    ${PROJECT_SOURCE_DIR}/src/figure/name.cpp
    ${PROJECT_SOURCE_DIR}/src/figure/phrase.cpp
    ${PROJECT_SOURCE_DIR}/src/figure/properties.cpp
    ${PROJECT_SOURCE_DIR}/src/figure/route.cpp
    ${PROJECT_SOURCE_DIR}/src/figure/service.cpp
    ${PROJECT_SOURCE_DIR}/src/figure/trader.cpp
    ${PROJECT_SOURCE_DIR}/src/figure/sound.cpp
    ${PROJECT_SOURCE_DIR}/src/figure/figure_draw.cpp
)
set(FIGURETYPE_FILES
    ${PROJECT_SOURCE_DIR}/src/figuretype/animal.cpp
    ${PROJECT_SOURCE_DIR}/src/figuretype/cartpusher.cpp
    ${PROJECT_SOURCE_DIR}/src/figuretype/crime.cpp
    ${PROJECT_SOURCE_DIR}/src/figuretype/docker.cpp
    ${PROJECT_SOURCE_DIR}/src/figuretype/editor.cpp
    ${PROJECT_SOURCE_DIR}/src/figuretype/enemy.cpp
    ${PROJECT_SOURCE_DIR}/src/figuretype/entertainer.cpp
    ${PROJECT_SOURCE_DIR}/src/figuretype/maintenance.cpp
    ${PROJECT_SOURCE_DIR}/src/figuretype/market.cpp
    ${PROJECT_SOURCE_DIR}/src/figuretype/migrant.cpp
    ${PROJECT_SOURCE_DIR}/src/figuretype/missile.cpp
    ${PROJECT_SOURCE_DIR}/src/figuretype/native.cpp
    ${PROJECT_SOURCE_DIR}/src/figuretype/service.cpp
    ${PROJECT_SOURCE_DIR}/src/figuretype/soldier.cpp
    ${PROJECT_SOURCE_DIR}/src/figuretype/trader.cpp
    ${PROJECT_SOURCE_DIR}/src/figuretype/wall.cpp
    ${PROJECT_SOURCE_DIR}/src/figuretype/water.cpp
    ${PROJECT_SOURCE_DIR}/src/figuretype/gatherers.cpp
)
set(GAME_FILES
    ${PROJECT_SOURCE_DIR}/src/game/animation.cpp
    ${PROJECT_SOURCE_DIR}/src/game/cheats.cpp
    ${PROJECT_SOURCE_DIR}/src/game/difficulty.cpp
    ${PROJECT_SOURCE_DIR}/src/game/file_editor.cpp
    ${PROJECT_SOURCE_DIR}/src/game/game.cpp
    ${PROJECT_SOURCE_DIR}/src/game/mission.cpp
    ${PROJECT_SOURCE_DIR}/src/game/orientation.cpp
    ${PROJECT_SOURCE_DIR}/src/game/resource.cpp
    ${PROJECT_SOURCE_DIR}/src/game/settings.cpp
    ${PROJECT_SOURCE_DIR}/src/game/state.cpp
    ${PROJECT_SOURCE_DIR}/src/game/tick.cpp
    ${PROJECT_SOURCE_DIR}/src/game/time.cpp
    ${PROJECT_SOURCE_DIR}/src/game/tutorial.cpp
    ${PROJECT_SOURCE_DIR}/src/game/undo.cpp
    ${PROJECT_SOURCE_DIR}/src/game/player_data.cpp
    ${PROJECT_SOURCE_DIR}/src/game/io/io_buffer.cpp
    ${PROJECT_SOURCE_DIR}/src/game/io/chunks.cpp
    ${PROJECT_SOURCE_DIR}/src/game/io/manager.cpp
    ${PROJECT_SOURCE_DIR}/src/game/io/boilerplate.cpp
)
set(INPUT_FILES
    ${PROJECT_SOURCE_DIR}/src/input/cursor.cpp
    ${PROJECT_SOURCE_DIR}/src/input/hotkey.cpp
    ${PROJECT_SOURCE_DIR}/src/input/input.cpp
    ${PROJECT_SOURCE_DIR}/src/input/keyboard.cpp
    ${PROJECT_SOURCE_DIR}/src/input/keys.cpp
    ${PROJECT_SOURCE_DIR}/src/input/mouse.cpp
    ${PROJECT_SOURCE_DIR}/src/input/scroll.cpp
    ${PROJECT_SOURCE_DIR}/src/input/touch.cpp
    ${PROJECT_SOURCE_DIR}/src/input/zoom.cpp
)
set(MAP_FILES
    ${PROJECT_SOURCE_DIR}/src/map/aqueduct.cpp
    ${PROJECT_SOURCE_DIR}/src/map/bookmark.cpp
    ${PROJECT_SOURCE_DIR}/src/map/bridge.cpp
    ${PROJECT_SOURCE_DIR}/src/map/building.cpp
    ${PROJECT_SOURCE_DIR}/src/map/building_tiles.cpp
    ${PROJECT_SOURCE_DIR}/src/map/desirability.cpp
    ${PROJECT_SOURCE_DIR}/src/map/elevation.cpp
    ${PROJECT_SOURCE_DIR}/src/map/figure.cpp
    ${PROJECT_SOURCE_DIR}/src/map/grid.cpp
    ${PROJECT_SOURCE_DIR}/src/map/image.cpp
    ${PROJECT_SOURCE_DIR}/src/map/image_context.cpp
    ${PROJECT_SOURCE_DIR}/src/map/natives.cpp
    ${PROJECT_SOURCE_DIR}/src/map/orientation.cpp
    ${PROJECT_SOURCE_DIR}/src/map/point.cpp
    ${PROJECT_SOURCE_DIR}/src/map/property.cpp
    ${PROJECT_SOURCE_DIR}/src/map/random.cpp
    ${PROJECT_SOURCE_DIR}/src/map/ring.cpp
    ${PROJECT_SOURCE_DIR}/src/map/road_access.cpp
    ${PROJECT_SOURCE_DIR}/src/map/road_aqueduct.cpp
    ${PROJECT_SOURCE_DIR}/src/map/road_network.cpp
    ${PROJECT_SOURCE_DIR}/src/map/routing/routing.cpp
    ${PROJECT_SOURCE_DIR}/src/map/routing/routing_grids.cpp
    ${PROJECT_SOURCE_DIR}/src/map/routing/queue.cpp
    ${PROJECT_SOURCE_DIR}/src/map/routing/routing_terrain.cpp
    ${PROJECT_SOURCE_DIR}/src/map/soldier_strength.cpp
    ${PROJECT_SOURCE_DIR}/src/map/sprite.cpp
    ${PROJECT_SOURCE_DIR}/src/map/terrain.cpp
    ${PROJECT_SOURCE_DIR}/src/map/tiles.cpp
    ${PROJECT_SOURCE_DIR}/src/map/water.cpp
    ${PROJECT_SOURCE_DIR}/src/map/water_supply.cpp
    ${PROJECT_SOURCE_DIR}/src/map/tile_cache.cpp
    ${PROJECT_SOURCE_DIR}/src/map/floodplain.cpp
    ${PROJECT_SOURCE_DIR}/src/map/vegetation.cpp
    ${PROJECT_SOURCE_DIR}/src/map/moisture.cpp
)
set(SCENARIO_FILES
    ${PROJECT_SOURCE_DIR}/src/scenario/building.cpp
    ${PROJECT_SOURCE_DIR}/src/scenario/criteria.cpp
    ${PROJECT_SOURCE_DIR}/src/scenario/demand_change.cpp
    ${PROJECT_SOURCE_DIR}/src/scenario/distant_battle.cpp
    ${PROJECT_SOURCE_DIR}/src/scenario/earthquake.cpp
    ${PROJECT_SOURCE_DIR}/src/scenario/editor.cpp
    ${PROJECT_SOURCE_DIR}/src/scenario/editor_events.cpp
    ${PROJECT_SOURCE_DIR}/src/scenario/editor_map.cpp
    ${PROJECT_SOURCE_DIR}/src/scenario/emperor_change.cpp
    ${PROJECT_SOURCE_DIR}/src/scenario/empire.cpp
    ${PROJECT_SOURCE_DIR}/src/scenario/gladiator_revolt.cpp
    ${PROJECT_SOURCE_DIR}/src/scenario/invasion.cpp
    ${PROJECT_SOURCE_DIR}/src/scenario/map.cpp
    ${PROJECT_SOURCE_DIR}/src/scenario/price_change.cpp
    ${PROJECT_SOURCE_DIR}/src/scenario/property.cpp
    ${PROJECT_SOURCE_DIR}/src/scenario/random_event.cpp
    ${PROJECT_SOURCE_DIR}/src/scenario/request.cpp
    ${PROJECT_SOURCE_DIR}/src/scenario/events.cpp
    ${PROJECT_SOURCE_DIR}/src/scenario/scenario.cpp
)
set(GRAPHICS_FILES
    ${PROJECT_SOURCE_DIR}/src/graphics/arrow_button.cpp
    ${PROJECT_SOURCE_DIR}/src/graphics/button.cpp
    ${PROJECT_SOURCE_DIR}/src/graphics/font.cpp
    ${PROJECT_SOURCE_DIR}/src/graphics/generic_button.cpp
    ${PROJECT_SOURCE_DIR}/src/graphics/graphics.cpp
    ${PROJECT_SOURCE_DIR}/src/graphics/renderer.cpp
    ${PROJECT_SOURCE_DIR}/src/graphics/image.cpp
    ${PROJECT_SOURCE_DIR}/src/graphics/image_button.cpp
    ${PROJECT_SOURCE_DIR}/src/graphics/lang_text.cpp
    ${PROJECT_SOURCE_DIR}/src/graphics/menu.cpp
    ${PROJECT_SOURCE_DIR}/src/graphics/panel.cpp
    ${PROJECT_SOURCE_DIR}/src/graphics/rich_text.cpp
    ${PROJECT_SOURCE_DIR}/src/graphics/screen.cpp
#    ${PROJECT_SOURCE_DIR}/src/graphics/screenshot.cpp
    ${PROJECT_SOURCE_DIR}/src/graphics/scrollbar.cpp
    ${PROJECT_SOURCE_DIR}/src/graphics/scroll_list_panel.cpp
    ${PROJECT_SOURCE_DIR}/src/graphics/text.cpp
    ${PROJECT_SOURCE_DIR}/src/graphics/tooltip.cpp
    ${PROJECT_SOURCE_DIR}/src/graphics/video.cpp
    ${PROJECT_SOURCE_DIR}/src/graphics/warning.cpp
    ${PROJECT_SOURCE_DIR}/src/graphics/window.cpp
)
set(SOUND_FILES
    ${PROJECT_SOURCE_DIR}/src/sound/city.cpp
    ${PROJECT_SOURCE_DIR}/src/sound/effect.cpp
    ${PROJECT_SOURCE_DIR}/src/sound/music.cpp
    ${PROJECT_SOURCE_DIR}/src/sound/speech.cpp
    ${PROJECT_SOURCE_DIR}/src/sound/system.cpp
)
set(WIDGET_FILES
    ${PROJECT_SOURCE_DIR}/src/widget/city.cpp
    ${PROJECT_SOURCE_DIR}/src/widget/input_box.cpp
    ${PROJECT_SOURCE_DIR}/src/widget/map_editor.cpp
    ${PROJECT_SOURCE_DIR}/src/widget/map_editor_tool.cpp
    ${PROJECT_SOURCE_DIR}/src/widget/minimap.cpp
    ${PROJECT_SOURCE_DIR}/src/widget/top_menu.cpp
    ${PROJECT_SOURCE_DIR}/src/widget/top_menu_editor.cpp
    ${PROJECT_SOURCE_DIR}/src/widget/city/tile_draw.cpp
    ${PROJECT_SOURCE_DIR}/src/widget/city/bridges.cpp
    ${PROJECT_SOURCE_DIR}/src/widget/city/building_ghost.cpp
    ${PROJECT_SOURCE_DIR}/src/widget/city/ornaments.cpp
    ${PROJECT_SOURCE_DIR}/src/widget/overlays/city_overlay.cpp
    ${PROJECT_SOURCE_DIR}/src/widget/overlays/city_overlay_risks.cpp
    ${PROJECT_SOURCE_DIR}/src/widget/overlays/city_overlay_education.cpp
    ${PROJECT_SOURCE_DIR}/src/widget/overlays/city_overlay_entertainment.cpp
    ${PROJECT_SOURCE_DIR}/src/widget/overlays/city_overlay_health.cpp
    ${PROJECT_SOURCE_DIR}/src/widget/overlays/city_overlay_other.cpp
    ${PROJECT_SOURCE_DIR}/src/widget/sidebar/city.cpp
    ${PROJECT_SOURCE_DIR}/src/widget/sidebar/common.cpp
    ${PROJECT_SOURCE_DIR}/src/widget/sidebar/editor.cpp
    ${PROJECT_SOURCE_DIR}/src/widget/sidebar/extra.cpp
    ${PROJECT_SOURCE_DIR}/src/widget/sidebar/slide.cpp
)
set(WINDOW_FILES
    ${PROJECT_SOURCE_DIR}/src/window/advisors.cpp
    ${PROJECT_SOURCE_DIR}/src/window/advisor/chief.cpp
    ${PROJECT_SOURCE_DIR}/src/window/advisor/education.cpp
    ${PROJECT_SOURCE_DIR}/src/window/advisor/entertainment.cpp
    ${PROJECT_SOURCE_DIR}/src/window/advisor/financial.cpp
    ${PROJECT_SOURCE_DIR}/src/window/advisor/health.cpp
    ${PROJECT_SOURCE_DIR}/src/window/advisor/housing.cpp
    ${PROJECT_SOURCE_DIR}/src/window/advisor/imperial.cpp
    ${PROJECT_SOURCE_DIR}/src/window/advisor/labor.cpp
    ${PROJECT_SOURCE_DIR}/src/window/advisor/military.cpp
    ${PROJECT_SOURCE_DIR}/src/window/advisor/population.cpp
    ${PROJECT_SOURCE_DIR}/src/window/advisor/ratings.cpp
    ${PROJECT_SOURCE_DIR}/src/window/advisor/religion.cpp
    ${PROJECT_SOURCE_DIR}/src/window/advisor/trade.cpp
    ${PROJECT_SOURCE_DIR}/src/window/advisor/monuments.cpp
    ${PROJECT_SOURCE_DIR}/src/window/build_menu.cpp
    ${PROJECT_SOURCE_DIR}/src/window/building_info.cpp
    ${PROJECT_SOURCE_DIR}/src/window/building/common.cpp
    ${PROJECT_SOURCE_DIR}/src/window/building/culture.cpp
    ${PROJECT_SOURCE_DIR}/src/window/building/distribution.cpp
    ${PROJECT_SOURCE_DIR}/src/window/building/figures.cpp
    ${PROJECT_SOURCE_DIR}/src/window/building/government.cpp
    ${PROJECT_SOURCE_DIR}/src/window/building/house.cpp
    ${PROJECT_SOURCE_DIR}/src/window/building/industry.cpp
    ${PROJECT_SOURCE_DIR}/src/window/building/military.cpp
    ${PROJECT_SOURCE_DIR}/src/window/building/terrain.cpp
    ${PROJECT_SOURCE_DIR}/src/window/building/utility.cpp
    ${PROJECT_SOURCE_DIR}/src/window/editor/allowed_buildings.cpp
    ${PROJECT_SOURCE_DIR}/src/window/editor/attributes.cpp
    ${PROJECT_SOURCE_DIR}/src/window/editor/build_menu.cpp
    ${PROJECT_SOURCE_DIR}/src/window/editor/demand_changes.cpp
    ${PROJECT_SOURCE_DIR}/src/window/editor/edit_demand_change.cpp
    ${PROJECT_SOURCE_DIR}/src/window/editor/edit_invasion.cpp
    ${PROJECT_SOURCE_DIR}/src/window/editor/edit_price_change.cpp
    ${PROJECT_SOURCE_DIR}/src/window/editor/edit_request.cpp
    ${PROJECT_SOURCE_DIR}/src/window/editor/empire.cpp
    ${PROJECT_SOURCE_DIR}/src/window/editor/invasions.cpp
    ${PROJECT_SOURCE_DIR}/src/window/editor/map.cpp
    ${PROJECT_SOURCE_DIR}/src/window/editor/price_changes.cpp
    ${PROJECT_SOURCE_DIR}/src/window/editor/requests.cpp
    ${PROJECT_SOURCE_DIR}/src/window/editor/special_events.cpp
    ${PROJECT_SOURCE_DIR}/src/window/editor/start_year.cpp
    ${PROJECT_SOURCE_DIR}/src/window/editor/starting_conditions.cpp
    ${PROJECT_SOURCE_DIR}/src/window/editor/win_criteria.cpp
    ${PROJECT_SOURCE_DIR}/src/window/scenario_selection.cpp
    ${PROJECT_SOURCE_DIR}/src/window/city.cpp
    ${PROJECT_SOURCE_DIR}/src/window/config.cpp
    ${PROJECT_SOURCE_DIR}/src/window/console.cpp
    ${PROJECT_SOURCE_DIR}/src/window/difficulty_options.cpp
    ${PROJECT_SOURCE_DIR}/src/window/display_options.cpp
    ${PROJECT_SOURCE_DIR}/src/window/donate_to_city.cpp
    ${PROJECT_SOURCE_DIR}/src/window/empire.cpp
    ${PROJECT_SOURCE_DIR}/src/window/file_dialog.cpp
    ${PROJECT_SOURCE_DIR}/src/window/gift_to_emperor.cpp
    ${PROJECT_SOURCE_DIR}/src/window/hold_festival.cpp
    ${PROJECT_SOURCE_DIR}/src/window/hotkey_config.cpp
    ${PROJECT_SOURCE_DIR}/src/window/hotkey_editor.cpp
    ${PROJECT_SOURCE_DIR}/src/window/intermezzo.cpp
    ${PROJECT_SOURCE_DIR}/src/window/intro_video.cpp
    ${PROJECT_SOURCE_DIR}/src/window/labor_priority.cpp
    ${PROJECT_SOURCE_DIR}/src/window/logo.cpp
    ${PROJECT_SOURCE_DIR}/src/window/main_menu.cpp
    ${PROJECT_SOURCE_DIR}/src/window/message_dialog.cpp
    ${PROJECT_SOURCE_DIR}/src/window/message_list.cpp
    ${PROJECT_SOURCE_DIR}/src/window/mission_briefing.cpp
    ${PROJECT_SOURCE_DIR}/src/window/mission_end.cpp
    ${PROJECT_SOURCE_DIR}/src/window/mission_next.cpp
    ${PROJECT_SOURCE_DIR}/src/window/new_career.cpp
    ${PROJECT_SOURCE_DIR}/src/window/numeric_input.cpp
    ${PROJECT_SOURCE_DIR}/src/window/overlay_menu.cpp
    ${PROJECT_SOURCE_DIR}/src/window/plain_message_dialog.cpp
    ${PROJECT_SOURCE_DIR}/src/window/popup_dialog.cpp
    ${PROJECT_SOURCE_DIR}/src/window/resource_settings.cpp
    ${PROJECT_SOURCE_DIR}/src/window/select_list.cpp
    ${PROJECT_SOURCE_DIR}/src/window/set_salary.cpp
    ${PROJECT_SOURCE_DIR}/src/window/sound_options.cpp
    ${PROJECT_SOURCE_DIR}/src/window/speed_options.cpp
    ${PROJECT_SOURCE_DIR}/src/window/trade_opened.cpp
    ${PROJECT_SOURCE_DIR}/src/window/trade_prices.cpp
    ${PROJECT_SOURCE_DIR}/src/window/victory_dialog.cpp
    ${PROJECT_SOURCE_DIR}/src/window/victory_video.cpp
    ${PROJECT_SOURCE_DIR}/src/window/player_selection.cpp
    ${PROJECT_SOURCE_DIR}/src/window/game_menu.cpp
    ${PROJECT_SOURCE_DIR}/src/window/records.cpp
)
set(DEV_FILES
    ${PROJECT_SOURCE_DIR}/src/dev/debug.cpp
)
set(EDITOR_FILES
    ${PROJECT_SOURCE_DIR}/src/editor/editor.cpp
    ${PROJECT_SOURCE_DIR}/src/editor/tool.cpp
    ${PROJECT_SOURCE_DIR}/src/editor/tool_restriction.cpp
)
set(TRANSLATION_FILES
    ${PROJECT_SOURCE_DIR}/src/translation/english.cpp
    ${PROJECT_SOURCE_DIR}/src/translation/french.cpp
    ${PROJECT_SOURCE_DIR}/src/translation/german.cpp
    ${PROJECT_SOURCE_DIR}/src/translation/italian.cpp
    ${PROJECT_SOURCE_DIR}/src/translation/korean.cpp
    ${PROJECT_SOURCE_DIR}/src/translation/polish.cpp
    ${PROJECT_SOURCE_DIR}/src/translation/portuguese.cpp
    ${PROJECT_SOURCE_DIR}/src/translation/russian.cpp
    ${PROJECT_SOURCE_DIR}/src/translation/simplified_chinese.cpp
    ${PROJECT_SOURCE_DIR}/src/translation/spanish.cpp
    ${PROJECT_SOURCE_DIR}/src/translation/traditional_chinese.cpp
    ${PROJECT_SOURCE_DIR}/src/translation/translation.cpp
)

set(MACOSX_FILES "")
if(APPLE)
    #set(MACOSX_FILES ${PROJECT_SOURCE_DIR}/res/augustus.icns)
endif()

set(SOURCE_FILES
    ${PLATFORM_FILES}
    ${CORE_FILES}
    ${BUILDING_FILES}
    ${CITY_FILES}
    ${EMPIRE_FILES}
    ${FIGURE_FILES}
    ${FIGURETYPE_FILES}
    ${GAME_FILES}
    ${INPUT_FILES}
    ${MAP_FILES}
    ${SCENARIO_FILES}
    ${GRAPHICS_FILES}
    ${SOUND_FILES}
    ${WIDGET_FILES}
    ${WINDOW_FILES}
    ${DEV_FILES}
    ${EDITOR_FILES}
    ${TRANSLATION_FILES}
    ${TINYFD_FILES}
#    ${PROJECT_SOURCE_DIR}/res/augustus.rc
    ${MACOSX_FILES}
#    ${PNG_FILES}
#    ${SDL_IMAGE_FILES}
#    ${ZLIB_FILES}
)

SET_SOURCE_FILES_PROPERTIES(${SOURCE_FILES} PROPERTIES LANGUAGE CXX)

function(GET_SDL_EXT_DIR result module)
    if(NOT module STREQUAL "")
        set(module "_${module}")
    endif()
    set(SDL_LOCATION ${PROJECT_SOURCE_DIR}/ext/SDL2)
    file(GLOB children
        RELATIVE ${SDL_LOCATION}
        CONFIGURE_DEPENDS
        ${SDL_LOCATION}/SDL${module}
        ${SDL_LOCATION}/SDL2${module}
        ${SDL_LOCATION}/SDL${module}-*
        ${SDL_LOCATION}/SDL2${module}-*
    )
    foreach(child ${children})
        if(IS_DIRECTORY "${SDL_LOCATION}/${child}")
            set(${result} "${SDL_LOCATION}/${child}" PARENT_SCOPE)
            break()
        endif()
    endforeach()
endfunction()

find_package(SDL2 REQUIRED)
find_package(SDL2_mixer REQUIRED)
find_package(SDL2_image REQUIRED)

add_executable(${SHORT_NAME} WIN32 ${SOURCE_FILES})

if(MSVC)
    add_compile_definitions(_CRT_SECURE_NO_WARNINGS)
endif()

if(APPLE)
    # generating a macOS icns file (see https://stackoverflow.cppom/a/20703594)
    add_custom_command(OUTPUT ${PROJECT_SOURCE_DIR}/res/augustus.icns
        COMMAND mkdir -p augustus.iconset
        COMMAND sips -z 16 16    augustus_256.png --out augustus.iconset/icon_16x16.png
        COMMAND sips -z 32 32    augustus_256.png --out augustus.iconset/icon_16x16@2x.png
        COMMAND sips -z 32 32    augustus_256.png --out augustus.iconset/icon_32x32.png
        COMMAND sips -z 64 64    augustus_256.png --out augustus.iconset/icon_32x32@2x.png
        COMMAND sips -z 128 128  augustus_256.png --out augustus.iconset/icon_128x128.png
        COMMAND sips -z 256 256  augustus_256.png --out augustus.iconset/icon_128x128@2x.png
        COMMAND sips -z 256 256  augustus_256.png --out augustus.iconset/icon_256x256.png
        COMMAND sips -z 512 512  augustus_512.png --out augustus.iconset/icon_256x256@2x.png
        COMMAND iconutil -c icns augustus.iconset
        COMMAND rm -R augustus.iconset
        WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/res)
    set_source_files_properties(${PROJECT_SOURCE_DIR}/res/augustus.icns PROPERTIES
        MACOSX_PACKAGE_LOCATION "Resources")

    # setting variables that will populate Info.plist
    set(MACOSX_BUNDLE_GUI_IDENTIFIER "nl.biancavanschaik.julius")
    set(MACOSX_BUNDLE_BUNDLE_NAME ${PROJECT_NAME})
    set(CMAKE_OSX_DEPLOYMENT_TARGET "10.10" CACHE STRING "Minimum OS X deployment version" FORCE)
    set(MACOSX_BUNDLE_ICON_FILE "augustus.icns")
    set(MACOSX_BUNDLE_BUNDLE_VERSION
        "${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}.${PROJECT_VERSION_PATCH}${VERSION_REVISION}")
    set(MACOSX_BUNDLE_LONG_VERSION_STRING ${MACOSX_BUNDLE_BUNDLE_VERSION})
    set(MACOSX_BUNDLE_SHORT_VERSION_STRING ${MACOSX_BUNDLE_BUNDLE_VERSION})

    set_target_properties(${SHORT_NAME} PROPERTIES
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

    # when installing, "fixup" automatically copies librairies inside the
    # bundle and links the binary against them
    install(CODE "
        include(BundleUtilities)
        fixup_bundle(${CMAKE_BINARY_DIR}/${PROJECT_NAME}.app \"\" \"${DIRS}\")
    " BUNDLE DESTINATION ${CMAKE_BINARY_DIR})
endif()

include_directories(${SDL2_INCLUDE_DIR})
include_directories(${SDL2_MIXER_INCLUDE_DIR})
#include_directories("LIB/64/include")

if(SYSTEM_LIBS)
    find_package(ZLIB)
    find_package(PNG)
    find_package(EXPAT)
endif()

if(ZLIB_FOUND)
    include_directories(${ZLIB_INCLUDE_DIRS})
    target_link_libraries(${SHORT_NAME} ${ZLIB_LIBRARIES})
else()
    include_directories("ext/zlib")
    target_sources(${SHORT_NAME} PRIVATE "${ZLIB_FILES}")
endif()

if(PNG_FOUND)
    include_directories(${PNG_INCLUDE_DIRS})
    target_link_libraries(${SHORT_NAME} ${PNG_LIBRARIES})
#else()
#    include_directories("ext/png")
#    target_sources(${SHORT_NAME} PRIVATE "${PNG_FILES}")
endif()

if(EXPAT_FOUND)
    include_directories(${EXPAT_INCLUDE_DIRS})
    target_link_libraries(${SHORT_NAME} ${EXPAT_LIBRARIES})
else()
    include_directories("ext/expat")
    target_sources(${SHORT_NAME} PRIVATE "${EXPAT_FILES}")
    if(NOT WIN32)
        add_compile_definitions(XML_DEV_URANDOM)
    endif()
endif()

if(VITA_BUILD)
    include_directories(
        $ENV{VITASDK}/arm-vita-eabi/include
        ${CMAKE_CURRENT_SOURCE_DIR}
    )
elseif (SWITCH_BUILD)
    include_directories(
        ${DEVKITPRO}/portlibs/switch/include/SDL2
        ${DEVKITPRO}/libnx/include
        ${DEVKITPRO}/portlibs/switch/include
        ${CMAKE_CURRENT_SOURCE_DIR}
    )
endif()

include_directories(ext)
include_directories(src)
if(MSVC)
    include_directories(ext/dirent)
endif()

if (VITA_BUILD)
    target_link_libraries (${SHORT_NAME}
        ${SDL2_MIXER_LIBRARY}
        ${SDL2_LIBRARY}
        vorbisfile
        vorbis
        mikmod
        mpg123
        FLAC
        ogg
        vita2d
        m
        SceAppUtil_stub
        SceAudio_stub
        SceCommonDialog_stub
        SceCtrl_stub
        SceDisplay_stub
        SceGxm_stub
        SceHid_stub
        SceIofilemgr_stub
        SceSysmodule_stub
        SceTouch_stub
        ScePower_stub
        ScePgf_stub
        SceAppMgr_stub
    )
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -D__vita__")
    # this setting enables larger heap memory sizes on Vita, up to ~330 MB
    # useful for pre-loading videos into memory
    set(VITA_MKSFOEX_FLAGS "${VITA_MKSFOEX_FLAGS} -d ATTRIBUTE2=12")
    vita_create_self(${SHORT_NAME}.self ${SHORT_NAME} UNSAFE UNCOMPRESSED)
    vita_create_vpk(${SHORT_NAME}.vpk ${VITA_TITLEID} ${SHORT_NAME}.self
        VERSION ${VITA_VERSION}
        NAME ${SHORT_NAME}
        FILE res/sce_sys/icon0.png sce_sys/icon0.png
        FILE res/sce_sys/livearea/contents/bg.png sce_sys/livearea/contents/bg.png
        FILE res/sce_sys/livearea/contents/startup.png sce_sys/livearea/contents/startup.png
        FILE res/sce_sys/livearea/contents/template.xml sce_sys/livearea/contents/template.xml
    )
elseif(SWITCH_BUILD)
    target_link_libraries (${SHORT_NAME}
        SDL2_mixer
        SDL2
        EGL
        GLESv2
        glapi
        drm_nouveau
        vorbisidec
        modplug
        mpg123
        FLAC
        opusfile
        opus
        ogg
        m
        z
        nx
        stdc++
    )

    set(FLAGS
        -D__SWITCH__
        -Wno-write-strings
        -march=armv8-a
        -mtune=cortex-a57
        -mtp=soft
        -O2
        -fPIE
        -fno-asynchronous-unwind-tables
        -funroll-loops
        -fno-unwind-tables
        -fno-optimize-sibling-calls
        -mlittle-endian
        -ffunction-sections
    )

    foreach(flag ${FLAGS})
        set(FLAGS_GENERAL "${FLAGS_GENERAL} ${flag}")
    endforeach(flag ${FLAGS})

    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${FLAGS_GENERAL} --verbose")

    target_compile_options(${SHORT_NAME} PRIVATE ${FLAGS})
    add_custom_command(TARGET ${SHORT_NAME}
        POST_BUILD
        COMMAND ${DEVKITPRO}/tools/bin/nacptool --create "${SHORT_NAME}" "rsn8887" ${SWITCH_VERSION} ${SHORT_NAME}.nacp
        COMMAND ${DEVKITPRO}/tools/bin/elf2nro ${SHORT_NAME} ${SHORT_NAME}.nro --icon=${CMAKE_SOURCE_DIR}/res/switchdata/icon0.jpg --nacp=${SHORT_NAME}.nacp
    )
else()
    if (UNIX AND NOT APPLE AND (CMAKE_COMPILER_IS_GNUCC OR CMAKE_C_COMPILER_ID STREQUAL "Clang"))
        target_link_libraries(${SHORT_NAME} m)
    endif()
    target_link_libraries (${SHORT_NAME} ${SDL2_LIBRARY} ${SDL2_MIXER_LIBRARY} ${SDL2_IMAGE_LIBRARY})
    if(NOT APPLE)
        install(TARGETS ${SHORT_NAME} RUNTIME DESTINATION bin)
    endif()

    if(UNIX AND NOT APPLE)
        install(FILES "res/augustus.desktop" DESTINATION "share/applications" RENAME "com.github.keriew.augustus.desktop")
        install(FILES "res/augustus.metainfo.xml" DESTINATION "share/metainfo" RENAME "com.github.keriew.augustus.metainfo.xml")
        install(FILES "res/augustus_48.png" DESTINATION "share/icons/hicolor/48x48/apps" RENAME "com.github.keriew.augustus.png")
        install(FILES "res/augustus_256.png" DESTINATION "share/icons/hicolor/256x256/apps" RENAME "com.github.keriew.augustus.png")
        install(FILES "res/augustus_512.png" DESTINATION "share/icons/hicolor/512x512/apps" RENAME "com.github.keriew.augustus.png")
    endif()

endif()
