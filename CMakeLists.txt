cmake_minimum_required(VERSION 3.0.2)
include(CMakeDependentOption)

option(DRAW_FPS "Draw FPS on the top left corner of the window." OFF)
option(SYSTEM_LIBS "Use system libraries when available." ON)

set(SHORT_NAME ozymandias)
project(${SHORT_NAME} CXX)
message("C++ compiler is ${CMAKE_CXX_COMPILER_ID}" )

if(CMAKE_SIZEOF_VOID_P EQUAL 8)
  set(GAME_ARCH_64 TRUE)
  set(GAME_PROCESSOR_ARCH "x64")
else()
  set(GAME_ARCH_64 FALSE)
  set(GAME_PROCESSOR_ARCH "x86")
endif(CMAKE_SIZEOF_VOID_P EQUAL 8)

set(CMAKE_MODULE_PATH "${CMAKE_MODULE_PATH}" "${CMAKE_SOURCE_DIR}/cmake/")

#set(CMAKE_RC_LINK_EXECUTABLE "${CMAKE_CXX_LINK_EXECUTABLE}")
if (NOT MSVC)
    set(CMAKE_CXX_FLAGS "-Wno-c++11-narrowing -static-libgcc -static-libstdc++" ${CMAKE_CXX_FLAGS})
endif()
set(CMAKE_CXX_STANDARD 14)
set(GAME_WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}/bin_x64")

set(SDL2_VERSION "2.28.0")
set(SDL2_DEP_FILENAME "SDL2-devel-${SDL2_VERSION}-VC.zip")
set(SDL2_UNPACK_DIR "SDL2-${SDL2_VERSION}")
set(SDL2_DOWNLOAD_URL "http://libsdl.org/release/${SDL2_DEP_FILENAME}")
set(SDL2_TMP_ZIP_PATH "${CMAKE_BINARY_DIR}/tmp/${SDL2_DEP_FILENAME}")
set(SDL2_EXTRACT_PATH "${CMAKE_CURRENT_SOURCE_DIR}/ext/SDL2")
set(SDL2_CHECK_PATH "${SDL2_EXTRACT_PATH}/include/SDL.h")

if (MSVC)
    set(SDL_EXT_DIR ${CMAKE_CURRENT_SOURCE_DIR}/ext)
endif()

if(CMAKE_BUILD_TYPE STREQUAL "Release")
    SET(GAME_BUILD_TYPE "Release")
else()
    SET(GAME_BUILD_TYPE "Debug")
endif()

if (MSVC AND NOT EXISTS "${SDL2_CHECK_PATH}")
    message("Download SDL2 to ${SDL2_TMP_ZIP_PATH}")
    file(DOWNLOAD "${SDL2_DOWNLOAD_URL}" "${SDL2_TMP_ZIP_PATH}")
    message("Unppack SDL2 to ${SDL2_EXTRACT_PATH}")
    execute_process(COMMAND ${CMAKE_COMMAND} -E tar xzf ${SDL2_TMP_ZIP_PATH} WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/tmp)
    file(COPY ${CMAKE_BINARY_DIR}/tmp/${SDL2_UNPACK_DIR}/include DESTINATION ${SDL2_EXTRACT_PATH})
    file(COPY ${CMAKE_BINARY_DIR}/tmp/${SDL2_UNPACK_DIR}/lib DESTINATION ${SDL2_EXTRACT_PATH})
endif()
message("Found SDL2 at ${SDL2_LIBRARY}")

set(SDL2_MIXER_VERSION "2.0.4")
set(SDL2_MIXER_DEP_FILENAME "SDL2_mixer-devel-${SDL2_MIXER_VERSION}-VC.zip")
set(SDL2_MIXER_DOWNLOAD_URL "https://libsdl.org/projects/SDL_mixer/release/${SDL2_MIXER_DEP_FILENAME}")
set(SDL2_MIXER_UNPACK_DIR "SDL2_mixer-${SDL2_MIXER_VERSION}")
set(SDL2_MIXER_CHECK_PATH "${SDL2_EXTRACT_PATH}/include/SDL_mixer.h")
set(SDL2_MIXER_TMP_ZIP_PATH "${CMAKE_BINARY_DIR}/tmp/${SDL2_MIXER_DEP_FILENAME}")

if (MSVC AND NOT EXISTS "${SDL2_MIXER_CHECK_PATH}")
    message("Download SDL2_mixer to ${SDL2_MIXER_TMP_ZIP_PATH}")
    file(DOWNLOAD "${SDL2_MIXER_DOWNLOAD_URL}" "${SDL2_MIXER_TMP_ZIP_PATH}")
    message("Unppack SDL2_mixer to ${SDL2_EXTRACT_PATH}")
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
    message("Unppack SDL2_image to ${SDL2_EXTRACT_PATH}")
    execute_process(COMMAND ${CMAKE_COMMAND} -E tar xzf ${SDL2_IMAGE_TMP_ZIP_PATH} WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/tmp)
    file(COPY ${CMAKE_BINARY_DIR}/tmp/${SDL2_IMAGE_UNPACK_DIR}/include DESTINATION ${SDL2_EXTRACT_PATH})
    file(COPY ${CMAKE_BINARY_DIR}/tmp/${SDL2_IMAGE_UNPACK_DIR}/lib DESTINATION ${SDL2_EXTRACT_PATH})
endif()

if (MSVC)
    file(GLOB SDL2_DLL_PUBLIC_DLL "${SDL2_EXTRACT_PATH}/lib/${GAME_PROCESSOR_ARCH}/*.dll")
    file(COPY ${SDL2_DLL_PUBLIC_DLL} DESTINATION ${GAME_WORKING_DIRECTORY})
endif()

set(PROJECT_VERSION_MAJOR 0)
set(PROJECT_VERSION_MINOR 0)
set(PROJECT_VERSION_PATCH 2)
set(IS_RELEASE_VERSION FALSE)
set(VERSION_REVISION "")

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
    src/io/log.cpp
    ${PROJECT_SOURCE_DIR}/src/platform/mouse.cpp
    ${PROJECT_SOURCE_DIR}/src/platform/platform.cpp
    ${PROJECT_SOURCE_DIR}/src/platform/prefs.cpp
    ${PROJECT_SOURCE_DIR}/src/platform/sound_device.cpp
    ${PROJECT_SOURCE_DIR}/src/platform/touch.cpp
    ${PROJECT_SOURCE_DIR}/src/platform/version.cpp
    ${PROJECT_SOURCE_DIR}/src/platform/virtual_keyboard.cpp
    ${PROJECT_SOURCE_DIR}/src/platform/renderer.cpp
)

set(PLATFORM_FILES
    ${PLATFORM_FILES}
    ${PROJECT_SOURCE_DIR}/src/platform/cursor.cpp
    ${PROJECT_SOURCE_DIR}/src/platform/screen.cpp
)

set(CORE_FILES
    ${PROJECT_SOURCE_DIR}/src/core/backtrace.cpp
    ${PROJECT_SOURCE_DIR}/src/core/buffer.cpp
    ${PROJECT_SOURCE_DIR}/src/core/calc.cpp
    ${PROJECT_SOURCE_DIR}/src/core/encoding.cpp
    ${PROJECT_SOURCE_DIR}/src/core/encoding/korean.cpp
    ${PROJECT_SOURCE_DIR}/src/core/encoding/simp_chinese.cpp
    ${PROJECT_SOURCE_DIR}/src/core/encoding/trad_chinese.cpp
    ${PROJECT_SOURCE_DIR}/src/core/locale.cpp
    ${PROJECT_SOURCE_DIR}/src/core/random.cpp
    ${PROJECT_SOURCE_DIR}/src/core/speed.cpp
    ${PROJECT_SOURCE_DIR}/src/core/string.cpp
    ${PROJECT_SOURCE_DIR}/src/core/time.cpp
    ${PROJECT_SOURCE_DIR}/src/core/zip.cpp
    ${PROJECT_SOURCE_DIR}/src/core/game_environment.cpp
    ${PROJECT_SOURCE_DIR}/src/core/stopwatch.cpp
)
set(IO_FILES
    ${PROJECT_SOURCE_DIR}/src/io/dir.cpp
    ${PROJECT_SOURCE_DIR}/src/io/file.cpp
    ${PROJECT_SOURCE_DIR}/src/io/file_formats.cpp
    ${PROJECT_SOURCE_DIR}/src/io/io.cpp
    ${PROJECT_SOURCE_DIR}/src/io/io_buffer.cpp
    ${PROJECT_SOURCE_DIR}/src/io/config/config.cpp
    ${PROJECT_SOURCE_DIR}/src/io/config/hotkeys.cpp
    ${PROJECT_SOURCE_DIR}/src/io/gamestate/chunks.cpp
    src/io/manager.cpp
    ${PROJECT_SOURCE_DIR}/src/io/gamestate/boilerplate.cpp
    ${PROJECT_SOURCE_DIR}/src/io/imagepaks/imagepak.cpp
    ${PROJECT_SOURCE_DIR}/src/io/imagepaks/atlas_packer.cpp
    ${PROJECT_SOURCE_DIR}/src/io/playerdata/player_data.cpp
    ${PROJECT_SOURCE_DIR}/src/io/gamefiles/lang.cpp
    ${PROJECT_SOURCE_DIR}/src/io/gamefiles/smacker.cpp
#    ${PROJECT_SOURCE_DIR}/src/io/gamefiles/mods.cpp
#    ${PROJECT_SOURCE_DIR}/src/io/gamefiles/png_read.cpp
)
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
)
set(GRID_FILES
    ${PROJECT_SOURCE_DIR}/src/grid/aqueduct.cpp
    ${PROJECT_SOURCE_DIR}/src/grid/bookmark.cpp
    ${PROJECT_SOURCE_DIR}/src/grid/bridge.cpp
    ${PROJECT_SOURCE_DIR}/src/grid/building.cpp
    ${PROJECT_SOURCE_DIR}/src/grid/building_tiles.cpp
    ${PROJECT_SOURCE_DIR}/src/grid/desirability.cpp
    ${PROJECT_SOURCE_DIR}/src/grid/elevation.cpp
    ${PROJECT_SOURCE_DIR}/src/grid/figure.cpp
    ${PROJECT_SOURCE_DIR}/src/grid/grid.cpp
    ${PROJECT_SOURCE_DIR}/src/grid/image.cpp
    ${PROJECT_SOURCE_DIR}/src/grid/image_context.cpp
    ${PROJECT_SOURCE_DIR}/src/grid/natives.cpp
    ${PROJECT_SOURCE_DIR}/src/grid/orientation.cpp
    ${PROJECT_SOURCE_DIR}/src/grid/point.cpp
    ${PROJECT_SOURCE_DIR}/src/grid/property.cpp
    ${PROJECT_SOURCE_DIR}/src/grid/random.cpp
    ${PROJECT_SOURCE_DIR}/src/grid/ring.cpp
    ${PROJECT_SOURCE_DIR}/src/grid/road_access.cpp
    ${PROJECT_SOURCE_DIR}/src/grid/road_aqueduct.cpp
    ${PROJECT_SOURCE_DIR}/src/grid/road_network.cpp
    ${PROJECT_SOURCE_DIR}/src/grid/routing/routing.cpp
    ${PROJECT_SOURCE_DIR}/src/grid/routing/routing_grids.cpp
    ${PROJECT_SOURCE_DIR}/src/grid/routing/queue.cpp
    ${PROJECT_SOURCE_DIR}/src/grid/routing/routing_terrain.cpp
    ${PROJECT_SOURCE_DIR}/src/grid/soldier_strength.cpp
    ${PROJECT_SOURCE_DIR}/src/grid/sprite.cpp
    ${PROJECT_SOURCE_DIR}/src/grid/terrain.cpp
    ${PROJECT_SOURCE_DIR}/src/grid/tiles.cpp
    ${PROJECT_SOURCE_DIR}/src/grid/water.cpp
    ${PROJECT_SOURCE_DIR}/src/grid/water_supply.cpp
    ${PROJECT_SOURCE_DIR}/src/grid/tile_cache.cpp
    ${PROJECT_SOURCE_DIR}/src/grid/floodplain.cpp
    ${PROJECT_SOURCE_DIR}/src/grid/vegetation.cpp
    ${PROJECT_SOURCE_DIR}/src/grid/moisture.cpp
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
    ${PROJECT_SOURCE_DIR}/src/graphics/image.cpp
    ${PROJECT_SOURCE_DIR}/src/graphics/boilerplate.cpp
    ${PROJECT_SOURCE_DIR}/src/graphics/screen.cpp
    #    ${PROJECT_SOURCE_DIR}/src/graphics/screenshot.cpp
    ${PROJECT_SOURCE_DIR}/src/graphics/window.cpp
    ${PROJECT_SOURCE_DIR}/src/graphics/video.cpp
    ${PROJECT_SOURCE_DIR}/src/graphics/animation_timers.cpp
    ${PROJECT_SOURCE_DIR}/src/graphics/font.cpp
    ${PROJECT_SOURCE_DIR}/src/graphics/text.cpp
    ${PROJECT_SOURCE_DIR}/src/graphics/elements/lang_text.cpp
    ${PROJECT_SOURCE_DIR}/src/graphics/elements/rich_text.cpp
    ${PROJECT_SOURCE_DIR}/src/graphics/elements/tooltip.cpp
    ${PROJECT_SOURCE_DIR}/src/graphics/elements/warning.cpp
    ${PROJECT_SOURCE_DIR}/src/graphics/elements/button.cpp
    ${PROJECT_SOURCE_DIR}/src/graphics/elements/arrow_button.cpp
    ${PROJECT_SOURCE_DIR}/src/graphics/elements/generic_button.cpp
    ${PROJECT_SOURCE_DIR}/src/graphics/elements/image_button.cpp
    ${PROJECT_SOURCE_DIR}/src/graphics/elements/panel.cpp
    ${PROJECT_SOURCE_DIR}/src/graphics/elements/scrollbar.cpp
    ${PROJECT_SOURCE_DIR}/src/graphics/elements/scroll_list_panel.cpp
    ${PROJECT_SOURCE_DIR}/src/graphics/view/view.cpp
    ${PROJECT_SOURCE_DIR}/src/graphics/view/lookup.cpp
    ${PROJECT_SOURCE_DIR}/src/graphics/view/zoom.cpp
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
    ${PROJECT_SOURCE_DIR}/src/widget/city/figures_cached_draw.cpp
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
    ${TINYFD_FILES}
#    ${PROJECT_SOURCE_DIR}/res/augustus.rc
    ${MACOSX_FILES}
#    ${PNG_FILES}
#    ${SDL_IMAGE_FILES}
#    ${ZLIB_FILES}
)

SET_SOURCE_FILES_PROPERTIES(${SOURCE_FILES} PROPERTIES LANGUAGE CXX)

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


include_directories(ext)
include_directories(src)
if(MSVC)
    include_directories(ext/dirent)
    set_target_properties(${SHORT_NAME} PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY "${GAME_WORKING_DIRECTORY}")
endif()

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

if (MSVC)
    ADD_CUSTOM_COMMAND(
          TARGET ${SHORT_NAME}
          POST_BUILD
          COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_BINARY_DIR}/${GAME_BUILD_TYPE}/${SHORT_NAME}.exe" "${GAME_WORKING_DIRECTORY}/${SHORT_NAME}.exe"
     )
endif()

