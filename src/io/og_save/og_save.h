#pragma once

#include "io/og_save/og_types.h"

#include <array>
#include <cstring>
#include <string>
#include <vector>

// Stage 1 of the original-save converter: the positional, partly compressed Pharaoh .sav stream read into
// raw chunks and plain OG records. No game logic and no engine types, so the result can feed any model.
namespace og {

    // Chunk order of a v160 (Cleopatra) save, as savegame_chunk_table + savegame_chunks_ext in the reference.
    enum e_chunk : int {
        CHUNK_MISSION_ID = 0,
        CHUNK_CAMPAIGN = 1,
        CHUNK_PREVIOUS_CAMPAIGN_LINK = 2,
        CHUNK_CAMPAIGN_LINK = 3,
        CHUNK_FILE_VERSION = 4,
        CHUNK_SCHEMA_COUNT = 5,
        CHUNK_SCHEMA = 6,
        CHUNK_GRID_IMAGES = 7,
        CHUNK_GRID_EDGE = 8,
        CHUNK_GRID_BUILDING_IDS = 9,
        CHUNK_GRID_TERRAIN = 10,
        CHUNK_GRID_CANALS = 11,
        CHUNK_GRID_FIGURE_IDS = 12,
        CHUNK_GRID_BITFIELDS = 13,
        CHUNK_GRID_SPRITE = 14,
        CHUNK_GRID_RANDOM = 15,
        CHUNK_GRID_DESIRABILITY = 16,
        CHUNK_GRID_ELEVATION = 17,
        CHUNK_GRID_BUILDING_DAMAGE = 18,
        CHUNK_GRID_CANALS_BACKUP = 19,
        CHUNK_GRID_SPRITE_BACKUP = 20,
        CHUNK_FIGURES = 21,
        CHUNK_ROUTE_FIGURE_IDS = 22,
        CHUNK_ROUTE_PATHS = 23,
        CHUNK_FORMATIONS = 24,
        CHUNK_FORMATION_ID_LAST_IN_USE = 25,
        CHUNK_FORMATION_ID_LAST_LEGION = 26,
        CHUNK_FORMATION_NUM_LEGIONS = 27,
        CHUNK_CITY_PLAYERS = 28,
        CHUNK_CITY_PLAYER_FACTION = 29,
        CHUNK_CITY_PLAYER_NAMES = 30,
        CHUNK_CITY_CURRENT_PLAYER = 31,
        CHUNK_BUILDINGS = 32,
        CHUNK_CITY_VIEW_ORIENTATION = 33,
        CHUNK_GAME_TIME_TICK = 34,
        CHUNK_GAME_TIME_DAY = 35,
        CHUNK_GAME_TIME_MONTH = 36,
        CHUNK_GAME_TIME_YEAR = 37,
        CHUNK_GAME_TIME_TOTAL_DAYS = 38,
        CHUNK_BUILDING_HIGHEST_ID_EVER = 39,
        CHUNK_CITY_LOCUSTS_COUNTDOWN = 40,
        CHUNK_RANDOM_IV1 = 41,
        CHUNK_RANDOM_IV2 = 42,
        CHUNK_CAMERA_X = 43,
        CHUNK_CAMERA_Y = 44,
        CHUNK_CITY_POPULATION_GRAPH_ORDER = 45,
        CHUNK_CITY_HAILSTORM_COUNTDOWN = 46,
        CHUNK_EMPIRE_SCROLL_X = 47,
        CHUNK_EMPIRE_SCROLL_Y = 48,
        CHUNK_EMPIRE_SELECTED_OBJECT = 49,
        CHUNK_EMPIRE_CITIES = 50,
        CHUNK_BUILDING_COUNT_INDUSTRY_TOTAL = 51,
        CHUNK_BUILDING_COUNT_INDUSTRY_ACTIVE = 52,
        CHUNK_TRADE_PRICES = 53,
        CHUNK_NAME_COUNTER_SLOT_40 = 54,
        CHUNK_NAME_COUNTER_SLOT_39 = 55,
        CHUNK_NAME_COUNTER_SLOT_38 = 56,
        CHUNK_NAME_COUNTER_SLOT_37 = 57,
        CHUNK_NAME_COUNTER_SLOT_36 = 58,
        CHUNK_NAME_COUNTER_SLOT_35 = 59,
        CHUNK_NAME_COUNTER_SLOT_34 = 60,
        CHUNK_NAME_COUNTER_SLOT_33 = 61,
        CHUNK_NAME_COUNTER_SLOT_32 = 62,
        CHUNK_NAME_COUNTER_SLOT_31 = 63,
        CHUNK_NAME_COUNTER_SLOT_30 = 64,
        CHUNK_NAME_COUNTER_SLOT_29 = 65,
        CHUNK_NAME_COUNTER_SLOT_28 = 66,
        CHUNK_NAME_COUNTER_SLOT_27 = 67,
        CHUNK_NAME_COUNTER_SLOT_26 = 68,
        CHUNK_NAME_COUNTER_SLOT_25 = 69,
        CHUNK_NAME_COUNTER_SLOT_24 = 70,
        CHUNK_NAME_COUNTER_SLOT_23 = 71,
        CHUNK_NAME_COUNTER_SLOT_22 = 72,
        CHUNK_NAME_COUNTER_SLOT_21 = 73,
        CHUNK_NAME_COUNTER_SLOT_20 = 74,
        CHUNK_SCENARIO = 75,
        CHUNK_SCENARIO_MAX_YEAR = 76,
        CHUNK_MESSAGES = 77,
        CHUNK_CITY_MESSAGE_NEXT_SEQUENCE = 78,
        CHUNK_CITY_MESSAGE_TOTAL = 79,
        CHUNK_CITY_MESSAGE_CURRENT_ID = 80,
        CHUNK_CITY_MESSAGE_POPULATION_SHOWN = 81,
        CHUNK_CITY_MESSAGE_COUNT = 82,
        CHUNK_CITY_MESSAGE_DELAY = 83,
        CHUNK_BUILDING_BURNING_TOTAL = 84,
        CHUNK_BUILDING_BURNING_SIZE = 85,
        CHUNK_FIGURE_CREATED_SEQUENCE = 86,
        CHUNK_STARTING_FAVOR = 87,
        CHUNK_PERSONAL_SAVINGS_LAST_MISSION = 88,
        CHUNK_CURRENT_MISSION_ID = 89,
        CHUNK_INVASION_WARNINGS = 90,
        CHUNK_IS_CUSTOM_SCENARIO = 91,
        CHUNK_CITY_SOUNDS = 92,
        CHUNK_BUILDING_HIGHEST_ID = 93,
        CHUNK_EMPIRE_TRADERS = 94,
        CHUNK_TRADER_NEXT_INDEX = 95,
        CHUNK_BUILDING_LIST_BURNING = 96,
        CHUNK_BUILDING_LIST_SMALL = 97,
        CHUNK_BUILDING_LIST_LARGE = 98,
        CHUNK_SAVED_RESERVED_1 = 99,
        CHUNK_SCENARIO_START_FLAGS_EMPIRE_LOCKED = 100,
        CHUNK_NAME_COUNTER_SLOT_3 = 101,
        CHUNK_NAME_COUNTER_SLOT_2 = 102,
        CHUNK_NAME_COUNTER_SLOT_1 = 103,
        CHUNK_NAME_COUNTER_SLOT_0 = 104,
        CHUNK_CITY_FROGS_COUNTDOWN = 105,
        CHUNK_PYRAMID_SPEEDUP_COUNTDOWN = 106,
        CHUNK_MAP_SWEEP_TOTAL = 107,
        CHUNK_ENEMY_ARMY_ENEMY_FORMATIONS = 108,
        CHUNK_ENEMY_ARMY_ENEMY_STRENGTH = 109,
        CHUNK_ENEMY_ARMY_LEGION_FORMATIONS = 110,
        CHUNK_ENEMY_ARMY_LEGION_STRENGTH = 111,
        CHUNK_ENEMY_ARMY_UPDATE_COUNTER = 112,
        CHUNK_BUILDING_STORAGES = 113,
        CHUNK_TRADE_ROUTE_LIMITS = 114,
        CHUNK_TRADE_ROUTE_TRADED = 115,
        CHUNK_BUILDING_BARRACKS_TOWER_SENTRY_REQUEST = 116,
        CHUNK_BUILDING_EXTRA_SEQUENCE = 117,
        CHUNK_ROUTING_STATS_UNUSED_B = 118,
        CHUNK_ROUTING_STATS_ENEMY_ROUTES_CALCULATED = 119,
        CHUNK_ROUTING_STATS_TOTAL_ROUTES_CALCULATED = 120,
        CHUNK_ROUTING_STATS_UNUSED_A = 121,
        CHUNK_CITY_ENTRY_FLAG_X = 122,
        CHUNK_CITY_ENTRY_FLAG_Y = 123,
        CHUNK_CITY_EXIT_FLAG_X = 124,
        CHUNK_CITY_EXIT_FLAG_Y = 125,
        CHUNK_INVASION_LAST_ID = 126,
        CHUNK_BUILDING_CORRUPT_HOUSES_A = 127,
        CHUNK_BUILDING_CORRUPT_HOUSES_B = 128,
        CHUNK_SCENARIO_MAP_NAME = 129,
        CHUNK_MAP_BOOKMARKS = 130,
        CHUNK_MAP_SWEEP_COUNTDOWN = 131,
        CHUNK_CITY_ENTRY_FLAG_OFFSET = 132,
        CHUNK_CITY_EXIT_FLAG_OFFSET = 133,
        CHUNK_SAVED_WITH_GAME = 134,
        CHUNK_GRID_SOIL_FERTILITY = 135,
        CHUNK_SCENARIO_EVENTS = 136,
        CHUNK_FERRY_QUEUES = 137,
        CHUNK_FERRY_PATHS = 138,
        CHUNK_FIGURE_NAME_COUNTERS_UNUSED = 139,
        CHUNK_DOCK_QUEUES = 140,
        CHUNK_EMPIRE_MAP_HEADERS = 141,
        CHUNK_EMPIRE_OBJECTS = 142,
        CHUNK_EMPIRE_ROUTES = 143,
        CHUNK_GRID_VEGETATION_GROWTH = 144,
        CHUNK_VEGETATION_GROWTH_STATE = 145,
        CHUNK_SPHINX_SPOTS = 146,
        CHUNK_FLOODPLAIN_SETTINGS = 147,
        CHUNK_GRID_SERVICE_VISIT = 148,
        CHUNK_SUN_TEMPLE_SPOTS = 149,
        CHUNK_NAME_COUNTER_EXT_0 = 150,
        CHUNK_NAME_COUNTER_EXT_1 = 151,
        CHUNK_NAME_COUNTER_EXT_2 = 152,
        CHUNK_NAME_COUNTER_EXT_3 = 153,
        CHUNK_NAME_COUNTER_EXT_4 = 154,
        CHUNK_NAME_COUNTER_EXT_5 = 155,
        CHUNK_NAME_COUNTER_EXT_6 = 156,
        CHUNK_NAME_COUNTER_EXT_7 = 157,
        CHUNK_NAME_COUNTER_EXT_8 = 158,
        CHUNK_NAME_COUNTER_EXT_9 = 159,
        CHUNK_NAME_COUNTER_EXT_10 = 160,
        CHUNK_NAME_COUNTER_EXT_11 = 161,
        CHUNK_NAME_COUNTER_EXT_12 = 162,
        CHUNK_NAME_COUNTER_EXT_13 = 163,
        CHUNK_NAME_COUNTER_EXT_14 = 164,
        CHUNK_NAME_COUNTER_EXT_15 = 165,
        CHUNK_TUTORIAL_FLAGS_A = 166,
        CHUNK_TUTORIAL_FLAGS_B = 167,
        CHUNK_GRID_RUBBLE_BUILDING_TYPE = 168,
        CHUNK_GAME_IS_REPLAY = 169,
        CHUNK_GRID_MOISTURE = 170,
        CHUNK_OBELISK_SMALL_SPOTS = 171,
        CHUNK_OBELISK_LARGE_SPOTS = 172,
        CHUNK_MUMMIES_MAX = 173,
        CHUNK_DIFFICULTY = 174,
        CHUNK_RECORD_SAVINGS = 175,
        CHUNK_LIBRARY_SPOTS = 176,
        CHUNK_CAESAREUM_SPOTS = 177,
        CHUNK_LIGHTHOUSE_SPOTS = 178,
        CHUNK_ABU_SIMBEL_SPOTS = 179,
        CHUNK_ROYAL_TOMB_CHAMBER_SPOTS = 180,
        CHUNK_COUNT = 181,
    };

    enum e_og_save_limits {
        SAVE_VERSION = 160,
        // First chunk of savegame_chunks_ext (the Cleopatra additions).
        CHUNK_FIRST_EXTENDED = 147,
        SCHEMA_RECORDS = 300,
        GRID_CELLS = 228 * 228,
    };

    struct chunk_spec {
        const char* name;
        int element_size;
        int count;
        bool compressed;
    };

    struct chunk_schema_record {
        int32_t compressed;
        uint32_t reserved_1;
        int32_t element_size;
        int32_t count;
        uint32_t reserved_2;
    };
    static_assert(sizeof(chunk_schema_record) == 20, "chunk_schema_record is a savegame record of 20 bytes");

    const chunk_spec& chunk_info(int index);

    struct savegame {
        int32_t version = 0;
        int32_t schema_count = 0;
        // Extended chunks the file's schema left empty; they read as zeros.
        int missing_chunks = 0;
        std::array<std::vector<uint8_t>, CHUNK_COUNT> chunks;

        std::vector<building> buildings;
        std::vector<figure> figures;
        std::vector<formation> formations;
        std::vector<city_player> players;
        std::vector<city_player_name> player_names;
        scenario_record scenario = {};
        std::vector<empire_city> empire_cities;
        std::vector<empire_object> empire_objects;
        std::vector<empire_route> empire_routes;
        std::vector<empire_trader> empire_traders;
        std::vector<empire_map_header> empire_map_headers;
        std::vector<city_message> messages;
        std::vector<city_sound_channel> city_sounds;
        std::vector<building_storage> storages;
        std::vector<ferry_queue> ferry_queues;
        std::vector<ferry_path> ferry_paths;
        std::vector<dyn_queue_save> dock_queues;
        floodplain_settings floodplain = {};
        vegetation_growth_record vegetation_growth = {};

        template <typename T>
        T value(e_chunk c) const {
            T v = {};
            const auto& bytes = chunks[c];
            std::memcpy(&v, bytes.data(), bytes.size() < sizeof(T) ? bytes.size() : sizeof(T));
            return v;
        }

        template <typename T>
        const T* array(e_chunk c) const {
            return reinterpret_cast<const T*>(chunks[c].data());
        }

        int city_player_index() const;
        const city_player& player() const;
    };

    // Reads a whole .sav image. On failure returns false with a reason; out is then unusable.
    bool read_savegame(const uint8_t* data, size_t size, savegame& out, std::string& error);

    // The chunk layout of the file must match the v160 table exactly; the file carries its own schema, which is checked
    // against chunk_info() before any chunk is read.
    bool read_savegame_file(const char* path, savegame& out, std::string& error);

} // namespace og
