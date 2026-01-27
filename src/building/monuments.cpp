#include "monuments.h"

#include "building/building.h"
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

#define BUILDING_MONUMENT_FIRST_ID BUILDING_SMALL_MASTABA

#define NOTHING 0
#define INFINITE 10000

grid_xx g_monuments_progress_grid = {0, FS_UINT32};

io_buffer* iob_monuments_progress_grid = new io_buffer([](io_buffer* iob, size_t version) {
    iob->bind(BIND_SIGNATURE_GRID, &g_monuments_progress_grid);
});

struct monument_delivery {
    int walker_id;
    int destination_id;
    int resource;
    int cartloads;
};

svector<monument_delivery, 32> g_monument_deliveries;

bool building_monument::deliver_resource(e_resource resource, int amount) {
    auto &d = runtime_data();
    if (d.resources_pct[resource] >= 100) {
        return false;
    }

    auto bmain = main()->dcast_monument();
    verify_no_crash(bmain);

    int full_resources = bmain->needs_resource(resource);
    int amount_pct = calc_percentage(amount, full_resources);
    d.resources_pct[resource] += amount_pct;

    return true;
}

uint32_t map_monuments_get_progress(tile2i tile) {
    return map_grid_get(g_monuments_progress_grid, tile.grid_offset());
}

void map_monuments_set_progress(tile2i tile, uint32_t progress) {
    map_grid_set(g_monuments_progress_grid, tile.grid_offset(), progress);
}

void map_monuments_clear() {
    map_grid_fill(g_monuments_progress_grid, 0);
}

grid_area building_monument::get_area() {
    tile2i main = tile();
    tile2i end = main;

    switch (type()) {
    case BUILDING_SMALL_MASTABA: end = main.shifted(3, 9); break;
    case BUILDING_SMALL_STEPPED_PYRAMID: end = main.shifted(3, 9); break;
    case BUILDING_MEDIUM_MASTABA: end = main.shifted(5, 13); break;

    default:
        verify_no_crash(false);
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
    buildings_valid_first([&] (building &b) {
        auto monument = b.dcast_monument();
        if (!monument) {
            return false;
        }

        return (monument->runtime_data().phase != MONUMENT_FINISHED);
    });
    return found;
}

int building_monument::phases() const {
    return config().phases.size();
}

int building_monument::needs_bricklayers(int ph_id) const {
    const monument &config = this->config();
    if (ph_id >= config.phases.size()) {
        return 0;
    }

    const monument_phase &ph = config.phases[ph_id];
    return ph.resources.size() > 0 ? ph.resources[0].count : 0;
}

int building_monument::needs_resource(e_resource resource) const {
    auto &d = runtime_data();
    return needs_resource(resource, d.phase);
}

int building_monument::needs_resource(e_resource resource, int phase) const {
    const monument &config = this->config();

    auto &d = runtime_data();
    if (d.phase && phase >= config.phases.size()) {
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
                return building_static_params::get(BUILDING_SMALL_MASTABA).base_img();
            default:
                return building_static_params::get(BUILDING_SMALL_MASTABA).base_img() + 1;
            }
        }

    case BUILDING_SMALL_STEPPED_PYRAMID:
        {
            auto monument = b->dcast_monument();
            switch (monument->runtime_data().phase) {
            case MONUMENT_START:
                return building_static_params::get(BUILDING_SMALL_STEPPED_PYRAMID).base_img();
            default:
                return building_static_params::get(BUILDING_SMALL_STEPPED_PYRAMID).base_img() + 1;
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
                return building_static_params::get(BUILDING_MEDIUM_MASTABA).base_img();
            default:
                return building_static_params::get(BUILDING_MEDIUM_MASTABA).base_img() + 1;
            }
        }

    default:
        verify_no_crash(false);
    }

    return 0;
}

void building_monument::set_phase(int phase) {
    if (phase == phases()) {
        phase = MONUMENT_FINISHED;
    }

    auto &d = runtime_data();
    if (phase == d.phase) {
        return;
    }

    d.phase = phase;
    if (phase >= 2) {
        map_building_tiles_add(id(), tile(), size(), building_image_get(&base), TERRAIN_BUILDING);
    }

    if (d.phase != MONUMENT_FINISHED) {
        for (e_resource resource = RESOURCE_NONE; resource < RESOURCES_MAX; ++resource) {
            d.resources_pct[resource] = 0;
        }
    }
}

void building_monument_finish_monuments() {
    buildings_valid_do([&] (building &b) {
        auto monument = b.dcast_monument();
        auto &monumentd = monument->runtime_data();
        if (monumentd.phase != MONUMENT_FINISHED) {
            return;
        }

        monument->set_phase(MONUMENT_FINISHED);
        for (auto &r: monumentd.resources_pct) {
            r = 0;
        }
    });
}

bool building_monument::needs_resources() const {   
    auto &d = runtime_data();
    if (d.phase == MONUMENT_FINISHED) {
        return false;
    }

    for (auto &r: d.resources_pct) {
        if (r < 100) {
            return true;
        }
    }
    return false;
}

int building_monument::progress() {
    if (needs_resources()) {
        return 0;
    }

    auto &d = runtime_data();
    if (d.phase == MONUMENT_FINISHED) {
        return 0;
    }

    auto bmain = main()->dcast_monument();

    bmain->set_phase(d.phase + 1);

    auto next = bmain->next();
    while (next) {
        auto nextd = next->dcast_monument();
        nextd->set_phase(nextd->phase() + 1);
        next = next->next();
    }

    if (d.phase == MONUMENT_FINISHED) {
        if (bmain->dcast_temple_complex()) {
            messages::popup("message_monument_complete", 0, bmain->tile().grid_offset());
        } else if (bmain->dcast_mastaba()) {
            messages::popup("message_monument_complete", 0, bmain->tile().grid_offset());
        } else if (bmain->dcast_pyramid()) {
            messages::popup("message_monument_complete", 0, bmain->tile().grid_offset());
        }
    }
    return 1;
}

static int delivery_in_use(const monument_delivery *delivery) {
    return delivery->destination_id != 0;
}

void building_monument::add_delivery(int figure_id, int resource_id, int num_loads) {
    g_monument_deliveries.push_back({0});
    monument_delivery &delivery = g_monument_deliveries.back();

    delivery.destination_id = id();
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
    if (!b->is_monument()) {
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

bool building_monument::has_labour_problems() const {
    return (base.num_workers < base.max_workers);
}

int building_monument::working() {
    auto &d = runtime_data();
    if (d.phase != MONUMENT_FINISHED || base.state != BUILDING_STATE_VALID) {
        return 0;
    }

    if (has_labour_problems()) {
        return 0;
    }

    return id();
}

bool building_monument::requires_resource(e_resource resource) const {
    int phases = this->phases();
    for (int phase = 1; phase < phases; phase++) {
        if (needs_resource(resource, phase) > 0) {
            return true;
        }
    }
    return false;
}

bool building_monument::has_required_resources_to_build() const {
    int phases = this->phases();
    for (int phase = 1; phase < phases; phase++) {
        for (e_resource r = RESOURCES_MIN; r < RESOURCES_MAX; ++r) {
            if (needs_resource(r, phase) > 0 &&
                !g_city.can_produce_resource(r)) {
                return false;
            }
        }
    }
    return true;
}

int building_monument::upgraded() {
    int monument_id = working();
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

int building_monument::module_type() {
    auto &d = runtime_data();
    return d.upgrades;
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

bool building_monument::need_workers() {
    if (!is_main()) {
        return false;
    }

    auto &d = runtime_data();
    for (auto w_id : d.workers) {
        if (!w_id) {
            return true;
        }
    }

    return false;
}

int building_monument::is_construction_halted() {
    return main()->state() == BUILDING_STATE_MOTHBALLED;
}

int building_monument::toggle_construction_halted() {
    if (base.state == BUILDING_STATE_MOTHBALLED) {
        base.state = BUILDING_STATE_VALID;
        return 0;
    } else {
        base.state = BUILDING_STATE_MOTHBALLED;
        return 1;
    }
}

bool building_monument::need_stonemason() {
    return false;
}

bool building_monument::need_carpenter() {
    auto &d = runtime_data();
    if (d.phase == MONUMENT_FINISHED) {
        return false;
    }

    int phase = d.phase;
    
    // Check if monument needs TIMBER for current phase
    int needs_timber = needs_resource(RESOURCE_TIMBER, phase);
    if (needs_timber <= 0) {
        return false;
    }

    // Count existing carpenters
    int works_carpenters = 0;
    for (auto &id : d.workers) {
        figure *f = id > 0 ? figure_get(id) : nullptr;
        works_carpenters += (f && f->type == FIGURE_CARPENTER) ? 1 : 0;
    }

    // Carpenters are needed if monument needs TIMBER and we don't have enough carpenters
    // Typically need 1 carpenter for scaffolding construction
    return works_carpenters < 1;
}

bool building_monument::need_bricklayers() {
    auto &d = runtime_data();
    if (d.phase == MONUMENT_FINISHED) {
        return false;
    }

    int phase = d.phase;
    int works_bricklayers = 0;
    for (auto &id : d.workers) {
        figure *f = id > 0 ? figure_get(id) : nullptr;
        works_bricklayers += (f && f->type == FIGURE_BRICKLAYER) ? 1 : 0;
    }

    return (phase >= 2 && phase <= 5 && works_bricklayers < needs_bricklayers(d.phase));
}

bool building_monument::is_unfinished() const {
    return runtime_data().phase != MONUMENT_FINISHED;
}

bool building_monument::is_finished() const {
    return runtime_data().phase == MONUMENT_FINISHED;
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
