#include "monuments.h"

#include "building/building.h"
#include "building/model.h"
#include "graphics/image.h"
#include "graphics/image_groups.h"
#include "graphics/view/view.h"
#include "empire/empire.h"
#include "figure/figure.h"
#include "core/svector.h"
#include "city/city_resource.h"
#include "city/city_message.h"
#include "game/resource.h"
#include "grid/grid.h"
#include "grid/figure.h"
#include "grid/building_tiles.h"
#include "grid/terrain.h"
#include "core/calc.h"
#include "core/log.h"
#include "city/city.h"
#include "io/io_buffer.h"

#include "js/js_game.h"

#include <algorithm>

#define DELIVERY_ARRAY_SIZE_STEP 200
#define ORIGINAL_DELIVERY_BUFFER_SIZE 16
#define MODULES_PER_TEMPLE 2
#define ARCHITECTS RESOURCE_NONE

#define MAX_PHASES 10

#define BUILDING_MONUMENT_FIRST_ID BUILDING_SMALL_MASTABA

#define NOTHING 0
#define INFINITE 10000

grid_xx g_monuments_progress_grid = {0, FS_UINT32};

io_buffer* iob_monuments_progress_grid = new io_buffer([](io_buffer* iob, size_t version) {
    iob->bind(BIND_SIGNATURE_GRID, &g_monuments_progress_grid);
});

struct monument_phase_resource {
    e_resource resource;
    uint16_t count;
};

struct monument_phase {
    std::array<monument_phase_resource, 6> resources;
};

struct monument {
    e_building_type btype;
    svector<monument_phase, MAX_PHASES> phases;
};

struct monument_small_mastaba : public monument {
    monument_small_mastaba() : monument{BUILDING_SMALL_MASTABA} {
        phases.push_back({monument_phase_resource{ARCHITECTS, 1}, {RESOURCE_NONE, 0} });
        phases.push_back({monument_phase_resource{ARCHITECTS, 1}, {RESOURCE_NONE, 0} });
        phases.push_back({monument_phase_resource{ARCHITECTS, 1}, {RESOURCE_BRICKS, 4800} });
        phases.push_back({monument_phase_resource{ARCHITECTS, 1}, {RESOURCE_CLAY, 2000}, {RESOURCE_BRICKS, 4000}});
        phases.push_back({monument_phase_resource{ARCHITECTS, 1}, {RESOURCE_CLAY, 1600}, {RESOURCE_BRICKS, 3200}});
        phases.push_back({monument_phase_resource{ARCHITECTS, 1}, {RESOURCE_CLAY, 1200}, {RESOURCE_BRICKS, 2400}});
        phases.push_back({monument_phase_resource{ARCHITECTS, 1}, {RESOURCE_CLAY, 800}, {RESOURCE_BRICKS, 1600}});
        phases.push_back({monument_phase_resource{ARCHITECTS, 1}, {RESOURCE_CLAY, 400}, {RESOURCE_BRICKS, 800}});
        phases.push_back({monument_phase_resource{RESOURCE_NONE, 0}});
    }
} g_monument_small_mastaba;

struct monument_medium_mastaba : public monument {
    monument_medium_mastaba() : monument{ BUILDING_MEDIUM_MASTABA } {
        phases.push_back({ monument_phase_resource{ARCHITECTS, 1}, {RESOURCE_NONE, 0} });
        phases.push_back({ monument_phase_resource{ARCHITECTS, 1}, {RESOURCE_NONE, 0} });
        phases.push_back({ monument_phase_resource{ARCHITECTS, 1}, {RESOURCE_BRICKS, 8000} });
        phases.push_back({ monument_phase_resource{ARCHITECTS, 1}, {RESOURCE_CLAY, 4000}, {RESOURCE_BRICKS, 8000} });
        phases.push_back({ monument_phase_resource{ARCHITECTS, 1}, {RESOURCE_CLAY, 3200}, {RESOURCE_BRICKS, 6400} });
        phases.push_back({ monument_phase_resource{ARCHITECTS, 1}, {RESOURCE_CLAY, 2400}, {RESOURCE_BRICKS, 4800} });
        phases.push_back({ monument_phase_resource{ARCHITECTS, 1}, {RESOURCE_CLAY, 1600}, {RESOURCE_BRICKS, 3200} });
        phases.push_back({ monument_phase_resource{ARCHITECTS, 1}, {RESOURCE_CLAY, 800}, {RESOURCE_BRICKS, 1600} });
        phases.push_back({ monument_phase_resource{RESOURCE_NONE, 0} });
    }
} g_monument_medium_mastaba;

monument g_monument_invalid;
const monument *g_monument_types[] = {
    &g_monument_invalid,
    &g_monument_small_mastaba,
    &g_monument_medium_mastaba
};

struct monument_delivery {
    int walker_id;
    int destination_id;
    int resource;
    int cartloads;
};

svector<monument_delivery, 32> g_monument_deliveries;

uint32_t map_monuments_get_progress(tile2i tile) {
    return map_grid_get(g_monuments_progress_grid, tile.grid_offset());
}

void map_monuments_set_progress(tile2i tile, uint32_t progress) {
    map_grid_set(g_monuments_progress_grid, tile.grid_offset(), progress);
}

void map_monuments_clear() {
    map_grid_fill(g_monuments_progress_grid, 0);
}

bool building_monument_deliver_resource(building *b, e_resource resource, int amount) {
    if (b->id <= 0 || !building_monument_is_monument(b)) {
        return false;
    }

    auto monument = b->dcast_monument();
    auto &monumentd = monument->runtime_data();
    if (monumentd.resources_pct[resource] >= 100) {
        return false;
    }

    while (b->prev_part_building_id) {
        b = building_get(b->prev_part_building_id);
    }

    int full_resources = building_monument_needs_resources(b->type, resource, monumentd.phase);
    int amount_pct = calc_percentage(amount, full_resources);
    monumentd.resources_pct[resource] += amount_pct;

    return true;
}

const monument &building_monument_config(e_building_type type) {
    auto it = std::find_if(std::begin(g_monument_types), std::end(g_monument_types), [type] (const monument *it) { return it->btype == type; });
    return (it != std::end(g_monument_types) ? *(*it) : g_monument_invalid);
}

grid_area building_monument_get_area(building *b) {
    if (b->id <= 0 || !building_monument_is_monument(b)) {
        return {{-1, -1}, {-1, -1}};
    }

    tile2i main = b->tile;
    tile2i end = main;

    switch (b->type) {
    case BUILDING_SMALL_MASTABA: end = main.shifted(3, 9); break;
    case BUILDING_MEDIUM_MASTABA: end = main.shifted(5, 13); break;

    default:
        assert(false);
    }

    return {main, end};
}

int building_monument_workers_onsite(building *b, e_figure_type figure_type) {
    auto tiles = map_grid_get_tiles(b, 0);

    int num_workers = 0;
    for (auto &tile : tiles) {
        figure *f = map_figure_get(tile);
        num_workers += (f->destination() == b) ? 1 : 0;
    }

    return num_workers;
}

tile2i building_monument_center_point(building *b) {
    if (b->id <= 0 || !building_monument_is_monument(b)) {
        return {-1, -1};
    }

    tile2i main = b->tile;
    tile2i end = main;

    switch (b->type) {
    case BUILDING_SMALL_MASTABA:
        end = main.shifted(3, 9);
        break;

    case BUILDING_MEDIUM_MASTABA:
        end = main.shifted(5, 13);
        break;

    default:
        assert(false);
    }

    return main.add(end).div(2);
}

tile2i building_monument_access_point(building *b) {
    switch (b->type) {
    case BUILDING_SMALL_MASTABA: return b->tile.shifted(0, 10);
    case BUILDING_MEDIUM_MASTABA: return b->tile.shifted(0, 14);
    default:
        assert(false);
    }

    if (b->size < 3) {
        return b->tile;
    }

    int half_size = b->size / 2;
    return b->tile.shifted(half_size, b->size - 1);
}

int get_temple_complex_part_image(e_building_type type, int part, int orientation, int level) {
    int packid = -1;
    
    switch (type) {
    case BUILDING_TEMPLE_COMPLEX_OSIRIS: packid = PACK_TEMPLE_NILE; break;
    case BUILDING_TEMPLE_COMPLEX_RA: packid = PACK_TEMPLE_RA; break;
    case BUILDING_TEMPLE_COMPLEX_PTAH: packid = PACK_TEMPLE_PTAH; break;
    case BUILDING_TEMPLE_COMPLEX_SETH: packid = PACK_TEMPLE_SETH; break;
    case BUILDING_TEMPLE_COMPLEX_BAST: packid = PACK_TEMPLE_BAST; break;
        break;
    }

    if (packid == -1) {
        return 0;
    }

    if (level == 0) {
        switch (part) {
        case 0: return image_id_from_group(packid, 1) + 3 * orientation;
        case 1: return image_id_from_group(packid, 2) + 3 * orientation;
        case 2: return image_id_from_group(packid, 3) + 3 * orientation;
        }
    } else if (level == 1) {
        switch (part) {
        case 0: return image_id_from_group(packid, 1) + orientation;
        case 1: return image_id_from_group(packid, 7) + orientation;
        case 2: return image_id_from_group(packid, 7) + 2 + orientation;
        }
    }

    return 0;
}

int get_monument_part_image(int part, int orientation, int level) {
    level = std::clamp(level, 0, 11);

    assert(false && "not implemented yet");
    int base_image_id = 0;// image_id_from_group(GROUP_MONUMENT_BLOCKS);
    return base_image_id;

    //switch (part) {
    //case MONUMENT_PART_CORNERS:
    //    return base_image_id + orientation + level * 8;
    //case MONUMENT_PART_SIDES:
    //    return base_image_id + orientation + level * 8 + 4;
    //case MONUMENT_PART_CENTER:
    //    if (level > 5)
    //        level = 5;
    //    return base_image_id + 96 + level + orientation * 6;
    //case MONUMENT_PART_EXTRA: // ramps, mastaba entrance, etc.
    //    return base_image_id + 108 + orientation;
    //case MONUMENT_PART_EXTERIORS: // TODO
    //    return image_id_from_group(GROUP_MONUMENT_EXTERIORS_END_DRY);
    //    break;
    //case MONUMENT_PART_CORNERS_2: // for bent pyramids
    //    if (level > 5)
    //        level = 5;
    //    return image_id_from_group(GROUP_MONUMENT_EXTRA_BLOCKS) + orientation + level * 8;
    //case MONUMENT_PART_SIDES_2: // for bent pyramids
    //    if (level > 5)
    //        level = 5;
    //    return image_id_from_group(GROUP_MONUMENT_EXTRA_BLOCKS) + orientation + level * 8 + 4;
    //}
}

int building_monument_add_module(building *b, int module) {
    //if (!building_monument_is_monument(b) ||
    //    b->data.monuments.phase != MONUMENT_FINISHED ||
    //    (b->data.monuments.upgrades && b->type != BUILDING_A && b->type != BUILDING_B)) {
    //    return 0;
    //}
    //b->data.monuments.upgrades = module;
    //map_building_tiles_add(b->id, b->tile, b->size, building_image_get(b), TERRAIN_BUILDING);
    return 1;
}

int building_monument_get_monument(tile2i tile, e_resource resource, int road_network_id, tile2i &dst) {
    if (g_city.resource.is_stockpiled(resource)) {
        return 0;
    }

    //int min_dist = INFINITE;
    //building *min_building = 0;
    //for (e_building_type type = BUILDING_MONUMENT_FIRST_ID; type < BUILDING_TYPE_MAX; type++) {
    //    if (!g_monument_types[type]) {
    //        continue;
    //    }
    //
    //    for (building *b = building_first_of_type(type); b; b = b->next_of_type) {
    //        if (b->data.monuments.phase == MONUMENT_FINISHED ||
    //            b->data.monuments.phase < MONUMENT_START ||
    //            building_monument_is_construction_halted(b) ||
    //            (!resource && building_monument_needs_resources(b))) {
    //            continue;
    //        }
    //        short needed = b->resources[resource];
    //        if ((needed - building_monument_resource_in_delivery(b, resource)) <= 0) {
    //            continue;
    //        }
    //        if (!map_has_road_access(b->tile, b->size) ||
    //            b->distance_from_entry <= 0 || b->road_network_id != road_network_id) {
    //            continue;
    //        }
    //        int dist = calc_maximum_distance(b->tile, tile);
    //        if (dist < min_dist) {
    //            min_dist = dist;
    //            min_building = b;
    //        }
    //    }
    //}
    //
    //if (min_building && min_dist < INFINITE) {
    //    map_point_store_result(min_building->road_access, dst);
    //    return min_building->id;
    //}
    return 0;
}

int building_monument_has_unfinished_monuments() {
    bool found = false;
    for (const auto &m: g_monument_types) {
        buildings_valid_do([&] (building &b) {
            auto monument = b.dcast_monument();
            if (!monument) {
                return;
            }

            if (monument->runtime_data().phase != MONUMENT_FINISHED) {
                found |= true;
            }
        }, m->btype);
    }
    return found;
}

int building_monument_phases(e_building_type type) {
    const monument &config = building_monument_config(type);
    return (int)config.phases.size();
}

int building_monument_needs_bricklayers(e_building_type type, int phase) {
    const monument &config = building_monument_config(type);

    if (phase >= config.phases.size()) {
        return 0;
    }

    const monument_phase &ph = config.phases[phase];
    return ph.resources.size() > 0 ? ph.resources[0].count : 0;
}

int building_monument_needs_resources(e_building_type type, e_resource resource, int phase) {
    const monument &config = building_monument_config(type);

    if (phase >= config.phases.size()) {
        return 0;
    }

    const monument_phase &ph = config.phases[phase];
    auto r_it = std::find_if(ph.resources.begin(), ph.resources.end(), [&] (auto &p) { return p.resource == resource; });
    return (r_it != ph.resources.end() ? r_it->count : 0);
}

int building_image_get(building *b) {
    switch (b->type) {
    case BUILDING_SMALL_MASTABA:
    case BUILDING_SMALL_MASTABA_SIDE:
    case BUILDING_SMALL_MASTABA_WALL:
    case BUILDING_SMALL_MASTABA_ENTRANCE:
        {
            auto monument = b->dcast_monument();
            switch (monument->runtime_data().phase) {
            case MONUMENT_START:
                return building_impl::params(BUILDING_SMALL_MASTABA).anim[animkeys().base].first_img();
            default:
                return building_impl::params(BUILDING_SMALL_MASTABA).anim[animkeys().base].first_img() + 1;
            }
        }

    case BUILDING_MEDIUM_MASTABA:
    case BUILDING_MEDIUM_MASTABA_SIDE:
    case BUILDING_MEDIUM_MASTABA_WALL:
    case BUILDING_MEDIUM_MASTABA_ENTRANCE:
        {
            auto monument = b->dcast_monument();
            switch (monument->runtime_data().phase) {
            case MONUMENT_START:
                return building_impl::params(BUILDING_MEDIUM_MASTABA).anim[animkeys().base].first_img();
            default:
                return building_impl::params(BUILDING_MEDIUM_MASTABA).anim[animkeys().base].first_img() + 1;
            }
        }

    default:
        assert(false);
    }

    return 0;
}

void building_monument_set_phase(building *b, int phase) {
    if (phase == building_monument_phases(b->type)) {
        phase = MONUMENT_FINISHED;
    }

    auto monument = b->dcast_monument();
    auto &monumentd = monument->runtime_data();
    if (phase == monumentd.phase) {
        return;
    }

    monumentd.phase = phase;
    if (phase >= 2) {
        map_building_tiles_add(b->id, b->tile, b->size, building_image_get(b), TERRAIN_BUILDING);
    }

    if (monumentd.phase != MONUMENT_FINISHED) {
        for (e_resource resource = RESOURCE_NONE; resource < RESOURCES_MAX; ++resource) {
            monumentd.resources_pct[resource] = 0;
        }
    }
}

bool building_monument_is_monument(const building *b) {
    return building_monument_type_is_monument(b->type);
}

bool building_monument_type_is_monument(e_building_type type) {
    return building_type_any_of(type, { BUILDING_SMALL_MASTABA, BUILDING_SMALL_MASTABA_SIDE, BUILDING_SMALL_MASTABA_WALL, BUILDING_SMALL_MASTABA_ENTRANCE,
                                      BUILDING_MEDIUM_MASTABA, BUILDING_MEDIUM_MASTABA_SIDE, BUILDING_MEDIUM_MASTABA_WALL, BUILDING_MEDIUM_MASTABA_ENTRANCE });
}

bool building_monument_type_is_mini_monument(e_building_type type) {
    return building_monument_type_is_monument(type) && building_impl::params(type).building_size < 5;
}

bool building_monument_is_temple_complex(e_building_type type) {
    switch (type) {
    case BUILDING_TEMPLE_COMPLEX_OSIRIS:
    case BUILDING_TEMPLE_COMPLEX_RA:
    case BUILDING_TEMPLE_COMPLEX_PTAH:
    case BUILDING_TEMPLE_COMPLEX_SETH:
    case BUILDING_TEMPLE_COMPLEX_BAST:
        return 1;
    default:
        return 0;
    }
}

int building_monument_needs_resource(building *b, e_resource resource) {
    auto monument = b->dcast_monument();
    auto &monumentd = monument->runtime_data();
    if (monumentd.phase == MONUMENT_FINISHED) {
        return 0;
    }

    int full_resources = building_monument_needs_resources(b->type, resource, monumentd.phase);
    int resources_pct = monumentd.resources_pct[resource];
    return full_resources - (full_resources * resources_pct / 100);
}

void building_monument_finish_monuments() {
    bool found = false;
    for (const auto &m: g_monument_types) {
        buildings_valid_do([&] (building &b) {
            auto monument = b.dcast_monument();
            auto &monumentd = monument->runtime_data();
            if (monumentd.phase != MONUMENT_FINISHED) {
                return;
            }

            building_monument_set_phase(&b, MONUMENT_FINISHED);
            for (auto &r: monumentd.resources_pct) {
                r = 0;
            }
        }, m->btype);
    }
}

bool building_monument_needs_resources(building *b) {
    if (!building_is_monument(b->type)) {
        return false;
    }
    
    auto &monumentd = b->dcast_monument()->runtime_data();
    if (monumentd.phase == MONUMENT_FINISHED) {
        return false;
    }

    for (auto &r: monumentd.resources_pct) {
        if (r < 100) {
            return true;
        }
    }
    return false;
}

constexpr int MESSAGE_MONUMENT_COMPLETE = 171;
int building_monument_progress(building *b) {
    if (building_monument_needs_resources(b)) {
        return 0;
    }

    auto &monumentd = b->dcast_monument()->runtime_data();
    if (monumentd.phase == MONUMENT_FINISHED) {
        return 0;
    }

    while (b->prev_part_building_id) {
        b = building_get(b->prev_part_building_id);
    }

    building_monument_set_phase(b, monumentd.phase + 1);

    building *next = b;
    while (next->next_part_building_id) {
        next = building_get(b->next_part_building_id);
        auto &nextd = b->dcast_monument()->runtime_data();
        building_monument_set_phase(b, nextd.phase + 1);
    }

    if (monumentd.phase == MONUMENT_FINISHED) {
        if (building_monument_is_temple_complex(b->type)) {
            messages::popup(MESSAGE_MONUMENT_COMPLETE, 0, b->tile.grid_offset());
        } else if (b->type == BUILDING_SMALL_MASTABA) {
            messages::popup(MESSAGE_MONUMENT_COMPLETE, 0, b->tile.grid_offset());
        }
    }
    return 1;
}

static int delivery_in_use(const monument_delivery *delivery) {
    return delivery->destination_id != 0;
}

void building_monument_initialize_deliveries(void) {
    //if (!array_init(monument_deliveries, DELIVERY_ARRAY_SIZE_STEP, 0, delivery_in_use)) {
    //    logs::error("Failed to create monument array. The game will likely crash.");
    //}
}

void building_monument_add_delivery(int monument_id, int figure_id, int resource_id, int num_loads) {
    g_monument_deliveries.push_back({0});
    monument_delivery &delivery = g_monument_deliveries.back();

    delivery.destination_id = monument_id;
    delivery.walker_id = figure_id;
    delivery.resource = resource_id;
    delivery.cartloads = num_loads;
}

bool building_monument_has_delivery_for_worker(int figure_id) {
    for(auto &delivery: g_monument_deliveries) {
        if (delivery.walker_id == figure_id && delivery.destination_id > 0) {
            return 1;
        }
    }
    return 0;
}

void building_monument_remove_delivery(int figure_id) {
    for(auto &delivery: g_monument_deliveries) {
        if (delivery.walker_id == figure_id) {
            delivery.destination_id = 0;
        }
    }

    auto &delv = g_monument_deliveries;
    delv.erase(std::remove_if(delv.begin(), delv.end(), [] (auto &d) { return !d.destination_id; }), delv.end());
}

void building_monument_remove_all_deliveries(int monument_id) {
    for(auto &delivery: g_monument_deliveries) {
        if (delivery.destination_id == monument_id) {
            delivery.destination_id = 0;
        }
    }

    auto &delv = g_monument_deliveries;
    delv.erase(std::remove_if(delv.begin(), delv.end(), [] (auto &d) { return !d.destination_id; }), delv.end());
}

int building_monument_resource_in_delivery(int monument_id, int resource_id) {
    int resources = 0;
    for(auto &delivery: g_monument_deliveries) {
        if (delivery.destination_id == monument_id &&
            delivery.resource == resource_id) {
            resources += delivery.cartloads;
        }
    }

    return resources;
}

static int resource_in_delivery_multipart(building *b, int resource_id) {
    int resources = 0;

    while (b->prev_part_building_id) {
        b = building_get(b->prev_part_building_id);
    }

    while (b->id) {
        for(auto &delivery: g_monument_deliveries) {
            if (delivery.destination_id == b->id &&
                delivery.resource == resource_id) {
                resources += delivery.cartloads;
            }
        }
        b = building_get(b->next_part_building_id);
    }

    return resources;
}

int building_monument_resource_in_delivery(building *b, int resource_id)
{
    if (b->next_part_building_id || b->prev_part_building_id) {
        return resource_in_delivery_multipart(b, resource_id);
    } else {
        return building_monument_resource_in_delivery(b->id, resource_id);
    }
}

int building_monument_get_id(e_building_type type) {
    building *b = building_first_of_type(type);
    if (!building_monument_type_is_monument(type) || !b) {
        return 0;
    }
    return b->id;
}

int building_monument_count_temple_complex(void) {
    auto temple_complex = {
        BUILDING_TEMPLE_COMPLEX_OSIRIS,
        BUILDING_TEMPLE_COMPLEX_RA,
        BUILDING_TEMPLE_COMPLEX_PTAH,
        BUILDING_TEMPLE_COMPLEX_SETH,
        BUILDING_TEMPLE_COMPLEX_BAST,
    };

    const int count = g_city.buildings.count_active(temple_complex);
    return count;
}

bool building_monument_has_labour_problems(building *b) {
    const model_building *model = model_get_building(b->type);
    return (b->num_workers < model->laborers);
}

int building_monument_working(e_building_type type) {
    int monument_id = building_monument_get_id(type);
    building *b = building_get(monument_id);
    if (!monument_id) {
        return 0;
    }

    auto &monumentd = b->dcast_monument()->runtime_data();
    if (monumentd.phase != MONUMENT_FINISHED || b->state != BUILDING_STATE_VALID) {
        return 0;
    }

    if (building_monument_has_labour_problems(b)) {
        return 0;
    }

    return monument_id;
}

bool building_monument_requires_resource(e_building_type type, e_resource resource) {
    int phases = building_monument_phases(type);
    for (int phase = 1; phase < phases; phase++) {
        if (building_monument_needs_resources(type, resource, phase) > 0) {
            return true;
        }
    }
    return false;
}

bool building_monument_has_required_resources_to_build(e_building_type type) {
    int phases = building_monument_phases(type);
    for (int phase = 1; phase < phases; phase++) {
        for (e_resource r = RESOURCES_MIN; r < RESOURCES_MAX; ++r) {
            if (building_monument_needs_resources(type, r, phase) > 0 &&
                !g_city.can_produce_resource(r)) {
                return false;
            }
        }
    }
    return true;
}

int building_monument_upgraded(e_building_type type) {
    int monument_id = building_monument_working(type);
    building *b = building_get(monument_id);
    if (!monument_id) {
        return 0;
    }
    auto &monumentd = b->dcast_monument()->runtime_data();
    if (!monumentd.upgrades) {
        return 0;
    }
    return monument_id;
}

int building_monument_module_type(e_building_type type) {
    int monument_id = building_monument_working(type);

    if (!monument_id) {
        return 0;
    }

    building *b = building_get(monument_id);
    auto &monumentd = b->dcast_monument()->runtime_data();
    return monumentd.upgrades;
}

io_buffer *iob_city_building_monuments = new io_buffer([] (io_buffer *iob, size_t version) {
    int delivers_size = (int)g_monument_deliveries.size();
    iob->bind(BIND_SIGNATURE_INT32, &delivers_size);
    for (int i = 0; i < g_monument_deliveries.capacity(); ++i) {
        monument_delivery &delivery = g_monument_deliveries[i];
        iob->bind(BIND_SIGNATURE_INT32, &delivery.walker_id);
        iob->bind(BIND_SIGNATURE_INT32, &delivery.destination_id);
        iob->bind(BIND_SIGNATURE_INT32, &delivery.resource);
        iob->bind(BIND_SIGNATURE_INT32, &delivery.cartloads);
    }
});

bool building_monument_need_workers(building *b) {
    if (!b->is_main()) {
        return false;
    }

    if (building_type_none_of(*b, { BUILDING_SMALL_MASTABA, BUILDING_MEDIUM_MASTABA })) {
        return false;
    }

    auto &monumentd = b->dcast_monument()->runtime_data();
    for (auto w_id : monumentd.workers) {
        if (!w_id) {
            return true;
        }
    }

    return false;
}

int building_monument_is_construction_halted(building *b) {
    return b->main()->state == BUILDING_STATE_MOTHBALLED;
}

int building_monument_toggle_construction_halted(building *b) {
    if (b->state == BUILDING_STATE_MOTHBALLED) {
        b->state = BUILDING_STATE_VALID;
        return 0;
    } else {
        b->state = BUILDING_STATE_MOTHBALLED;
        return 1;
    }
}

bool building_monument_need_stonemason(const building *b) {
    return false;
}

bool building_monument_need_bricklayers(const building *b) {
    if (!building_is_monument(b->type)) {
        return false;
    }

    auto &monumentd = ((building*)b)->dcast_monument()->runtime_data();
    if (monumentd.phase == MONUMENT_FINISHED) {
        return false;
    }

    int phase = monumentd.phase;
    int works_bricklayers = 0;
    for (auto &id : monumentd.workers) {
        figure *f = id > 0 ? figure_get(id) : nullptr;
        works_bricklayers += (f && f->type == FIGURE_BRICKLAYER) ? 1 : 0;
    }

    switch (b->type) {
    case BUILDING_SMALL_MASTABA:
    case BUILDING_MEDIUM_MASTABA:
        return (phase >= 2 && phase <= 5 && works_bricklayers < building_monument_needs_bricklayers(b->type, monumentd.phase));

    default:
        assert(false);
    }

    return false;
}

bool building_monument_is_unfinished(const building *b) {
    auto monument = ((building*)b)->dcast_monument();
    if (!monument) {
        return false;
    }

    return monument->runtime_data().phase != MONUMENT_FINISHED;
}

bool building_monument_is_finished(const building *b) {
    auto monument = ((building *)b)->dcast_monument();
    if (!monument) {
        return false;
    }

    return monument->runtime_data().phase == MONUMENT_FINISHED;
}

building *city_has_unfinished_monuments() {
    return buildings_valid_first([] (building &b) { 
        auto monument = b.dcast_monument();
        if (!monument) {
            return false;
        }

        return (monument->runtime_data().phase == MONUMENT_FINISHED); 
    });
}
