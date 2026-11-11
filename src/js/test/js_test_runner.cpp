#include "js/test/js_test_common.h"

#include "building/building.h"
#include "building/building_delivery_path.h"
#include "building/monument_pyramid.h"
#include "building/monuments.h"
#include "city/object_info.h"
#include "core/app.h"
#include "core/bstring.h"
#include "core/crc32.h"
#include "core/log.h"
#include "core/xstring.h"
#include "editor/editor.h"
#include "empire/empire.h"
#include "empire/trader_handler.h"
#include "figure/figure.h"
#include "figure/figure_impl.h"
#include "figuretype/figure_plagued_citizen.h"
#include "game/autosave_module.h"
#include "game/game.h"
#include "game/game_events.h"
#include "graphics/image.h"
#include "graphics/image_groups.h"
#include "graphics/view/view.h"
#include "graphics/view/zoom.h"
#include "grid/grid.h"
#include "grid/road_access.h"
#include "grid/routing/routing.h"
#include "input/hotkey.h"
#include "io/chunk_serializer.h"
#include "io/gamestate/boilerplate.h"
#include "io/gamestate/boilerplate_detail.h"
#include "io/gamestate/file_schemas.h"
#include "platform/integral_tests.h"
#include "scenario/scenario.h"
#include "sound/sound.h"
#include "widget/debug_console.h"
#include "window/window_info.h"

#include <SDL.h>
#include <algorithm>
#include <cstring>
#include <filesystem>
#include <fstream>
#include <string>

// SDL_main.h does `#define main SDL_main`; undo it here so building::main() etc.
// are not macro-mangled (this TU is not the program entry point).
#ifdef main
#undef main
#endif

static std::streamoff g_test_log_start = 0;

static std::streamoff log_file_size(pcstr path) {
    std::ifstream in(path, std::ios::binary | std::ios::ate);
    return in ? (std::streamoff)in.tellg() : 0;
}

void test_log_mark_test_start() {
    logs::flush();
    g_test_log_start = log_file_size(logs::output_path());
}

static bool file_contains_marker(pcstr path, pcstr marker, const size_t marker_len, std::streamoff start) {
    std::ifstream in(path, std::ios::binary);
    if (!in) {
        return false;
    }

    // A log shorter than the mark was restarted during this test: all of it is ours.
    if (start > log_file_size(path)) {
        start = 0;
    }
    in.seekg(start);

    std::string chunk;
    chunk.reserve(8192 + marker_len);
    std::string tail;
    char buf[8192];
    bool strip_bom = (start == 0);

    while (in) {
        in.read(buf, sizeof(buf));
        const std::streamsize got = in.gcount();
        if (got <= 0) {
            break;
        }

        chunk = tail;
        chunk.append(buf, static_cast<size_t>(got));

        if (strip_bom && chunk.size() >= 3 && (unsigned char)chunk[0] == 0xEF && (unsigned char)chunk[1] == 0xBB
            && (unsigned char)chunk[2] == 0xBF) {
            chunk.erase(0, 3);
        }
        strip_bom = false;

        if (chunk.find(marker) != std::string::npos) {
            return true;
        }

        if (marker_len <= 1) {
            tail.clear();
        } else if (chunk.size() >= marker_len - 1) {
            tail = chunk.substr(chunk.size() - (marker_len - 1));
        } else {
            tail = chunk;
        }
    }

    return tail.find(marker) != std::string::npos;
}

bool test_log_contains(pcstr marker) {
    if (!marker || !*marker) {
        return false;
    }

    logs::flush();

    const size_t marker_len = std::strlen(marker);
    return file_contains_marker(logs::output_path(), marker, marker_len, g_test_log_start);
}

static bool __test_find_inlog(pcstr marker) {
    return test_log_contains(marker);
}
ANK_FUNCTION_1(__test_find_inlog);

static void test_pump(int n) {
    for (int i = 0; i < n && !g_app.quit; ++i) {
        game.tick_timer_ms = 0;
        g_app.pump_one_frame();
    }
}

void __test_pump_frames(int n) {
    n = std::clamp(n, 0, 240); // safety bound: ~4s at 60fps
    test_pump(n);
}
ANK_FUNCTION_1(__test_pump_frames);

// Wall-clock pause while still drawing (for visual layer-step tests).
static void __test_sleep_ms(int ms) {
    ms = std::clamp(ms, 0, 60000);
    const Uint32 deadline = SDL_GetTicks() + (Uint32)ms;
    while (!g_app.quit && !SDL_TICKS_PASSED(SDL_GetTicks(), deadline)) {
        g_app.pump_one_frame();
        SDL_Delay(16);
    }
}
ANK_FUNCTION_1(__test_sleep_ms);

static void push_mouse_motion(int x, int y) {
    SDL_Event e{};
    e.type = SDL_MOUSEMOTION;
    e.motion.which = 0; // not SDL_TOUCH_MOUSEID
    e.motion.x = x;
    e.motion.y = y;
    e.motion.xrel = 0;
    e.motion.yrel = 0;
    SDL_PushEvent(&e);
}

static void push_mouse_button(Uint32 type, Uint8 button, int x, int y) {
    SDL_Event e{};
    e.type = type;
    e.button.which = 0;
    e.button.button = button;
    e.button.state = (type == SDL_MOUSEBUTTONDOWN) ? SDL_PRESSED : SDL_RELEASED;
    e.button.clicks = 1;
    e.button.x = x;
    e.button.y = y;
    SDL_PushEvent(&e);
}

static void do_synthetic_click(Uint8 sdl_button, int logical_x, int logical_y) {
    // No window id, so SDL does not remap these. Real events arrive already logical.
    push_mouse_motion(logical_x, logical_y);
    push_mouse_button(SDL_MOUSEBUTTONDOWN, sdl_button, logical_x, logical_y);
    test_pump(2);
    push_mouse_button(SDL_MOUSEBUTTONUP, sdl_button, logical_x, logical_y);
    test_pump(8);
}

void __test_mouse_click(int x, int y) {
    do_synthetic_click(SDL_BUTTON_LEFT, x, y);
}
ANK_FUNCTION_2(__test_mouse_click);

void __test_mouse_right_click(int x, int y) {
    do_synthetic_click(SDL_BUTTON_RIGHT, x, y);
}
ANK_FUNCTION_2(__test_mouse_right_click);

void __test_signal_ready() {
    g_test_signal_ready = true;
}
ANK_FUNCTION(__test_signal_ready);

void __test_run_console_command(pcstr command) {
    run_debug_command(command);
}
ANK_FUNCTION_1(__test_run_console_command);

bool __test_start_city_session(pcstr map_path) {
    if (game.session.active) {
        return true;
    }

    // load_map only clears scenario events when a *.meta.js sidecar exists.
    g_scenario.events.clear_for_editor();

    if (!GamestateIO::load_map(map_path, false, true)) {
        logs::error("test_start_city_session: load_map(%s) failed", map_path);
        return false;
    }

    GamestateIO::start_loaded_file();
    auto cities = g_empire.get_cities();
    cities[0].type = EMPIRE_CITY_OURS;
    cities[0].in_use = true;

    return game.session.active;
}
ANK_FUNCTION_1(__test_start_city_session);

void test_reset_session_between_tests() {
    if (editor_is_active()) {
        editor_set_active(0);
    }
    game.session.active = false;
    g_scenario.events.clear_for_editor();
    events::emit(event_show_main_menu{false});
    events::process();
}

void __test_end_city_session() {
    test_reset_session_between_tests();
}
ANK_FUNCTION(__test_end_city_session);

pcstr __test_music_current_track() {
    return g_sound.music_current_track().c_str();
}
ANK_FUNCTION(__test_music_current_track);

void __test_music_next_track() {
    g_sound.music_next_track();
}
ANK_FUNCTION(__test_music_next_track);

int __test_music_load_playlist(pcstr text) {
    return g_sound.music_load_playlist_text(text ? text : "");
}
ANK_FUNCTION_1(__test_music_load_playlist);

void __test_set_campaign_scenario_id(int id) {
    g_scenario.campaign_scenario_id = id;
    g_scenario.scmode = e_scenario_normal;
}
ANK_FUNCTION_1(__test_set_campaign_scenario_id);

void __test_process_events() {
    events::process();
}
ANK_FUNCTION(__test_process_events);

void __test_process_scenario_events() {
    g_scenario.events.process_events();
}
ANK_FUNCTION(__test_process_scenario_events);

color __test_color_roundtrip(color c) {
    return c;
}
ANK_FUNCTION_1(__test_color_roundtrip);

void __test_show_tile_info(int bid) {
    building* b = building_get(bid);
    if (!b || !b->is_valid()) {
        return;
    }

    events::emit(event_show_tile_info{b->tile, true, "test"});
}
ANK_FUNCTION_1(__test_show_tile_info);

pcstr __test_info_ui_text(pcstr element_id) {
    static bstring512 buf;
    buf = "";
    if (!element_id || !*element_id) {
        return buf.c_str();
    }
    object_info& context = common_info_window::get_object_info();
    if (!context.ui || !context.ui->contains(element_id)) {
        return buf.c_str();
    }
    buf = (*context.ui)[element_id].text().c_str();
    return buf.c_str();
}
ANK_FUNCTION_1(__test_info_ui_text);

int __test_info_ui_image(pcstr element_id) {
    auto& context = common_info_window::get_object_info();
    if (!context.ui) {
        return -1;
    }
    return (*context.ui)[element_id].image().tid();
}
ANK_FUNCTION_1(__test_info_ui_image);

int __test_info_ui_enabled(pcstr element_id) {
    if (!element_id || !*element_id) {
        return -1;
    }
    object_info& context = common_info_window::get_object_info();
    if (!context.ui || !context.ui->contains(element_id)) {
        return -1;
    }
    return (*context.ui)[element_id].enabled ? 1 : 0;
}
ANK_FUNCTION_1(__test_info_ui_enabled);

static void __test_camera_center_building(int bid) {
    building* b = building_get(bid);
    if (!b || !b->is_valid()) {
        return;
    }
    building* head = b->main();
    tile2i c = head->tile.shifted(head->size / 2, head->size / 2);
    int height_layers = 0;
    if (auto* pyr = head->dcast_pyramid()) {
        const vec2i foot = pyr->pyramid_params().init_tiles;
        c = head->tile.shifted(foot.x / 2, foot.y / 2);
        // Aim by *built* height, not max monument size — otherwise a 2-tier shot
        // is framed as a 5-tier stack and looks like a tight close-up.
        const int max_layers = std::max(1, foot.x / 4);
        const int phase = pyr->phase();
        int built = 1;
        if (phase >= 6) {
            built = 1 + (phase - 6) / 6;
        }
        height_layers = std::clamp(built, 1, max_layers);
    } else if (auto* m = head->dcast_monument()) {
        c = m->center_point();
    }
    if (!c.valid()) {
        return;
    }

    // Instant collapse — animated widget_sidebar_expanded_collapse() leaves the
    // expanded chrome on screen until the slide finishes (and screenshots skip that).
    g_camera.toggle_sidebar(1);

    // Zoom OUT = higher percentage (zoom_min=25 is close-up, zoom_max=250 is far).
    // 180 fits a 20×20 two-tier stepped pyramid in a ~1200×770 collapsed viewport.
    g_zoom.set_scale(180.f);
    g_camera.set_extra_scroll_margin(120);

    // Tall brick courses draw upward from the footprint. Aim slightly NW of the
    // geometric centre so the on-screen mass (not the SE tip) lands mid-viewport.
    // Do not use lookup_tile_to_pixel: that cache is only filled during a city draw.
    if (height_layers > 1) {
        const int aim = height_layers - 1;
        c = c.shifted(-aim, -aim);
    }
    g_camera.go_to_mappoint(c);

    logs::info("[test-camera] tile=%d,%d cam=%d,%d zoom=%.0f layers=%d collapsed=%d vp=%d,%d", c.x(), c.y(),
      g_camera.camera_position.x, g_camera.camera_position.y, g_zoom.get_percentage(), height_layers,
      (int)g_camera.sidebar_collapsed, g_camera.size_pixels.x, g_camera.size_pixels.y);
}
ANK_FUNCTION_1(__test_camera_center_building);

static void __camera_scroll(int dx, int dy) {
    // Unclamped nudge for screenshot framing.
    g_camera.camera_position.x += dx;
    g_camera.camera_position.y += dy;
    g_camera.tile_internal.x = g_camera.camera_position.x / TILE_WIDTH_PIXELS;
    g_camera.tile_internal.y = g_camera.camera_position.y / HALF_TILE_HEIGHT_PIXELS;
    g_camera.tile_internal.y &= ~1;
    g_camera.update_derived_camera_state();
}
ANK_FUNCTION_2(__camera_scroll);

static void __camera_sidebar_collapsed(int collapsed) {
    g_camera.toggle_sidebar(collapsed ? 1 : 0);
}
ANK_FUNCTION_1(__camera_sidebar_collapsed);

// Hot-reload stack regression: each js_vm_sync used to leave ~1 stack slot per
// [console_command=…] handler (~30). JS_STACKSIZE is 256, so ~10 reloads then
// crashed in config::refresh / UI archive load (stackoverflow ? fatal exit).
static bool __test_js_hotreload_handlers_stack_ok(int iterations) {
    js_State* J = js_vm_state();
    if (!J || iterations < 1) {
        return false;
    }

    const int baseline = J->gettop();
    for (int i = 0; i < iterations; ++i) {
        js_register_game_handlers({});
    }
    const int after = J->gettop();
    logs::info("[test-marker] hotreload_handlers_stack baseline=%d after=%d iterations=%d", baseline, after,
      iterations);
    if (after != baseline) {
        logs::info("[hotreload] handlers stack leak delta=%d", after - baseline);
        return false;
    }
    return true;
}
ANK_FUNCTION_1(__test_js_hotreload_handlers_stack_ok);

static bool __test_js_hotreload_file_stack_ok(pcstr path, int iterations) {
    js_State* J = js_vm_state();
    if (!J || !path || !*path || iterations < 1) {
        return false;
    }

    const int baseline = J->gettop();
    for (int i = 0; i < iterations; ++i) {
        js_vm_reload_file(path);
        js_vm_sync({});
    }
    const int after = J->gettop();
    logs::info("[test-marker] hotreload_file_stack path=%s baseline=%d after=%d iterations=%d", path, baseline, after,
      iterations);
    if (after != baseline) {
        logs::info("[hotreload] file reload stack leak delta=%d", after - baseline);
        return false;
    }
    return true;
}
ANK_FUNCTION_2(__test_js_hotreload_file_stack_ok);

static pcstr __test_autosave_format(int slots, int slot) {
    static bstring256 buf;
    buf = autosave_module_t::format_monthly_filename(slots, slot, "svx");
    return buf.c_str();
}
ANK_FUNCTION_2(__test_autosave_format);

static int __test_autosave_pick(int slots, int exists_mask, int m0, int m1, int m2) {
    bool exists[10] = {};
    uint64_t mtime[10] = {};
    if (slots < 1) {
        slots = 1;
    }
    if (slots > 10) {
        slots = 10;
    }
    const int mtimes_in[] = {m0, m1, m2};
    for (int i = 0; i < slots; ++i) {
        exists[i] = (exists_mask & (1 << i)) != 0;
        mtime[i] = exists[i] ? (uint64_t)(i < 3 ? mtimes_in[i] : (100 + i)) : UINT64_MAX;
    }
    return autosave_module_t::pick_slot(slots, exists, mtime);
}
ANK_FUNCTION_5(__test_autosave_pick);

static bool __test_ironwill_exempt(pcstr filename_short) {
    return autosave_module_t::is_ironwill_exempt_save(filename_short);
}
ANK_FUNCTION_1(__test_ironwill_exempt);

// Headless: no frame pump, no rendering, no per-frame anti_scum roll — only what game_t::update does per tick.
static int __test_run_ticks(int n) {
    if (!game.session.active || editor_is_active()) {
        logs::error("[test] __test_run_ticks: no active city session");
        return 0;
    }
    n = std::clamp(n, 0, 100000);
    for (int i = 0; i < n; ++i) {
        game.update_tick(game.simtime.tick);
        events::process();
    }
    return n;
}
ANK_FUNCTION_1(__test_run_ticks);

// Water animation advances from the renderer (widget_city), so the frame a tile shows depends on
// what was drawn, not on the simulation. Collapse each animation cycle onto its first frame.
static void state_hash_normalise_water(std::vector<uint8_t>& raw) {
    const int water_first = image_id_from_group(GROUP_TERRAIN_WATER);
    const int deepwater_first = image_id_from_group(GROUP_TERRAIN_DEEPWATER);
    // Without art the groups resolve to 0, which would collide with the map-edge markers 1..5.
    const bool has_water = water_first > 0;
    const bool has_deepwater = deepwater_first > 0;
    if (!has_water && !has_deepwater) {
        return;
    }

    const uint32_t water_last = water_first + 5;
    const uint32_t deepwater_last = deepwater_first + 89;
    for (size_t off = 0; off + sizeof(uint32_t) <= raw.size(); off += sizeof(uint32_t)) {
        uint32_t id;
        memcpy(&id, &raw[off], sizeof(id));
        if (has_water && id >= (uint32_t)water_first && id <= water_last) {
            id = water_first;
        } else if (has_deepwater && id >= (uint32_t)deepwater_first && id <= deepwater_last) {
            // deepwater steps +15 per frame over 90 ids: a cycle is a residue class mod 15
            id = deepwater_first + (id - deepwater_first) % 15;
        }
        memcpy(&raw[off], &id, sizeof(id));
    }
}

// Record 0 is the null building/figure that OG and we both use as scratch.
static void state_hash_zero_record0(std::vector<uint8_t>& raw, size_t record_size) {
    std::fill(raw.begin(), raw.begin() + std::min(record_size, raw.size()), 0);
}

static pcstr __test_state_hash() {
    static std::string result;
    result.clear();

    chunk_snapshots chunks;
    if (!g_chunk_io.write_to_memory(FILE_FORMAT_SAVE_FILE_EXT, save_data_version(), file_schema, chunks)) {
        logs::error("[state-hash] write_to_memory failed");
        return result.c_str();
    }

    std::vector<uint32_t> crcs;
    std::string entries;
    crcs.reserve(chunks.size());
    for (chunk_snapshot& chunk : chunks) {
        if (chunk.name == "image_grid") {
            state_hash_normalise_water(chunk.raw);
        } else if (chunk.name == "buildings") {
            state_hash_zero_record0(chunk.raw, 264);
        } else if (chunk.name == "figures") {
            state_hash_zero_record0(chunk.raw, 388);
        }

        const uint32_t crc = crc32(chunk.raw.data(), (uint32_t)chunk.raw.size());
        crcs.push_back(crc);
        logs::info("[state-hash] %s %08x", chunk.name.c_str(), crc);

        char hex[16];
        snprintf(hex, sizeof(hex), "%08x", crc);
        entries += ";" + chunk.name + "=" + hex;
    }

    const uint32_t total = crc32(crcs.data(), (uint32_t)(crcs.size() * sizeof(uint32_t)));
    logs::info("[state-hash] total %08x chunks=%d", total, (int)chunks.size());

    char hex[16];
    snprintf(hex, sizeof(hex), "%08x", total);
    result = std::string("total=") + hex + entries;
    return result.c_str();
}
ANK_FUNCTION(__test_state_hash);

// Compares two chunk lists written through the same schema; logs every differing chunk and
// returns their names joined by ',' (empty when identical).
static std::string chunk_snapshots_diff(const chunk_snapshots& expected, const chunk_snapshots& actual, pcstr tag) {
    std::string diffs;
    auto add = [&diffs](const std::string& name) { diffs += diffs.empty() ? name : "," + name; };

    if (expected.size() != actual.size()) {
        logs::info("[roundtrip] %s chunk count %d != %d", tag, (int)expected.size(), (int)actual.size());
        add("chunk_count");
    }

    const size_t n = std::min(expected.size(), actual.size());
    for (size_t i = 0; i < n; ++i) {
        const chunk_snapshot& a = expected[i];
        const chunk_snapshot& b = actual[i];
        if (a.name != b.name) {
            logs::info("[roundtrip] %s chunk %d name %s != %s", tag, (int)i, a.name.c_str(), b.name.c_str());
            add(a.name);
            continue;
        }

        if (a.raw.size() != b.raw.size()) {
            logs::info("[roundtrip] %s diff %s size %d != %d", tag, a.name.c_str(), (int)a.raw.size(),
              (int)b.raw.size());
            add(a.name);
            continue;
        }

        // Record-array chunks: report "record.offset" instead of a flat offset.
        int record_size = 0;
        if (a.name == "buildings") {
            record_size = 264;
        } else if (a.name == "figures") {
            record_size = 388;
        }

        int count = 0;
        std::string samples;
        for (size_t off = 0; off < a.raw.size(); ++off) {
            if (a.raw[off] != b.raw[off]) {
                if (count < 12) {
                    char buf[48];
                    if (record_size > 0) {
                        const int rec = (int)(off / record_size);
                        const int type
                          = a.name == "buildings" ? (int)building_get(rec)->type : (int)figure_get(rec)->type;
                        snprintf(buf, sizeof(buf), " %d(t%d).%d:%02x->%02x", rec, type, (int)(off % record_size),
                          a.raw[off], b.raw[off]);
                    } else {
                        snprintf(buf, sizeof(buf), " %d:%02x->%02x", (int)off, a.raw[off], b.raw[off]);
                    }
                    samples += buf;
                }
                ++count;
            }
        }

        if (count > 0) {
            logs::info("[roundtrip] %s diff %s size=%d bytes=%d%s", tag, a.name.c_str(), (int)a.raw.size(), count,
              samples.c_str());
            add(a.name);
        }
    }

    return diffs;
}

// Our save -> load -> our save again; returns the chunks that changed, "" when none, "error:..." on failure.
static std::string save_roundtrip(pcstr filename) {
    chunk_snapshots before;
    if (!g_chunk_io.write_to_memory(FILE_FORMAT_SAVE_FILE_EXT, save_data_version(), file_schema, before)) {
        return "error:write_before";
    }

    if (!GamestateIO::write_savegame(filename)) {
        return "error:write_file";
    }

    const bool loaded = GamestateIO::load_savegame(filename);
    GamestateIO::delete_savegame(filename);
    if (!loaded) {
        return "error:load_file";
    }

    chunk_snapshots after;
    if (!g_chunk_io.write_to_memory(FILE_FORMAT_SAVE_FILE_EXT, save_data_version(), file_schema, after)) {
        return "error:write_after";
    }

    // Route counters (junk8 bytes 12..27): loading routes the kingdom-access check, and OG counts
    // that route too (game_file.c:755), so a load always bumps them.
    for (chunk_snapshots* snap : {&before, &after}) {
        for (chunk_snapshot& chunk : *snap) {
            if (chunk.name == "junk8" && chunk.raw.size() >= 28) {
                std::fill(chunk.raw.begin() + 12, chunk.raw.begin() + 28, 0);
            }
        }
    }

    return chunk_snapshots_diff(before, after, filename);
}

static pcstr __test_save_roundtrip(pcstr filename) {
    static std::string result;
    result = save_roundtrip(filename);
    return result.c_str();
}
ANK_FUNCTION_1(__test_save_roundtrip);

// Loads an original .sav and writes it back through the same schema and version: what we write
// differs from the file bytes only where a bind loses or reinterprets a field. Compared right after
// the binds read, before post_load recalculates anything.
static std::string og_save_fidelity(const std::string& path) {
    GamestateLoadDetail::pre_load();
    auto reader = vfs::file_open(vfs::path(path.c_str()));
    if (
      !g_chunk_io.unserialize(reader, 0, FILE_FORMAT_SAVE_FILE, GamestateLoadDetail::read_file_version, file_schema)) {
        return "error:load";
    }

    const int version = g_chunk_io.get_file_version();
    chunk_snapshots file;
    g_chunk_io.snapshot_chunks(file);

    chunk_snapshots ours;
    if (!g_chunk_io.write_to_memory(FILE_FORMAT_SAVE_FILE, version, file_schema, ours)) {
        return "error:write";
    }

    const std::string tag = "og v" + std::to_string(version);
    const std::string diffs = chunk_snapshots_diff(file, ours, tag.c_str());

    game.session.last_loaded = e_session_save;
    game.session.last_loaded_mission = path.c_str();
    GamestateLoadDetail::post_load();
    GamestateIO::start_loaded_file();
    return diffs;
}

// Every Save/<player>/*.sav of the Pharaoh install except the family.sav dynasty stubs: OG bytes
// against our .sav writer, then the loaded city through an .svx round trip.
// Returns "skip" without a Save folder, else "<checked>;|<path>=<chunks>|svx <path>=<chunks>..." for differences.
static pcstr __test_og_save_corpus() {
    static std::string result;
    namespace fs = std::filesystem;

    const fs::path root(vfs::content_path(vfs::SAVE_FOLDER).c_str());
    std::error_code ec;
    if (!fs::is_directory(root, ec)) {
        result = "skip";
        return result.c_str();
    }

    std::vector<std::string> files;
    for (const auto& player : fs::directory_iterator(root, ec)) {
        if (!player.is_directory()) {
            continue;
        }
        for (const auto& e : fs::directory_iterator(player.path(), ec)) {
            const std::string name = e.path().filename().string();
            if (!e.is_regular_file() || e.path().extension() != ".sav" || name == "family.sav") {
                continue;
            }
            files.push_back(e.path().generic_string());
        }
    }
    std::sort(files.begin(), files.end());

    std::string diffs;
    for (const std::string& f : files) {
        const std::string d = og_save_fidelity(f);
        logs::info("[roundtrip] og %s: %s", f.c_str(), d.empty() ? "identical" : d.c_str());
        if (!d.empty()) {
            diffs += "|" + f + "=" + d;
        }
        if (d.rfind("error:", 0) == 0) {
            continue;
        }

        // The same city through our own format: OG saves carry far more state than a test city.
        const std::string svx = save_roundtrip("test_og_roundtrip.svx");
        logs::info("[roundtrip] og->svx %s: %s", f.c_str(), svx.empty() ? "identical" : svx.c_str());
        if (!svx.empty()) {
            diffs += "|svx " + f + "=" + svx;
        }
    }

    result = std::to_string(files.size()) + ";" + diffs;
    return result.c_str();
}
ANK_FUNCTION(__test_og_save_corpus);
