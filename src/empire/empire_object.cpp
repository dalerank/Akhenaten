#include "empire_object.h"

#include "core/calc.h"
#include "core/log.h"
#include "empire/empire.h"
#include "empire/trade_route.h"
#include "empire/type.h"
#include "graphics/image.h"
#include "graphics/image_groups.h"
#include "io/gamestate/boilerplate.h"
#include "io/io_buffer.h"
#include "io/manager.h"
#include "scenario/empire.h"
#include "game/game.h"
#include "dev/debug.h"

#define MAX_OBJECTS 200
#define MAX_ROUTES 20

full_empire_object g_empire_objects[MAX_OBJECTS];

void empire_t::foreach_object(std::function<void(const empire_object&)> callback) {
    auto& objects = g_empire_objects;
    for (int i = 0; i < MAX_OBJECTS; i++) {
        if (objects[i].in_use)
            callback(objects[i].obj);
    }
}

static bool is_trade_city(int index) {
    auto& objects = g_empire_objects;
    if (objects[index].obj.type != EMPIRE_OBJECT_CITY)
        return 0;

    return (objects[index].city_type == EMPIRE_CITY_OURS || objects[index].city_type == EMPIRE_CITY_PHARAOH_TRADING
            || objects[index].city_type == EMPIRE_CITY_EGYPTIAN_TRADING
            || objects[index].city_type == EMPIRE_CITY_FOREIGN_TRADING);
}

static int get_trade_amount_code(int index, int resource) {
    auto& objects = g_empire_objects;
    if (!is_trade_city(index))
        return 0;

    if (FILEIO.get_file_version() < 160) {
        int result = 0;
        if (resource < 32) { // only holds data up to 31 (sandstone)
            int resource_flag = 1 << resource;
            if (objects[index].trade40 & resource_flag)
                result = 3;
            else if (objects[index].trade25 & resource_flag)
                result = 2;
            else if (objects[index].trade15 & resource_flag)
                result = 1;
        }
        objects[index].trade_demand[resource] = result; // also record into post-160 format automatically
        return result;
    } else
        return objects[index].trade_demand[resource];
}

bool empire_t::is_sea_trade_route(int route_id) const {
    const auto& route = get_route_object(route_id);
    return route.route_type == 2;
}

void empire_t::set_trade_route_type(int route_id, bool is_sea_route) {
    auto &route = ref_route_object(route_id);
    route.route_type = is_sea_route ? 2 : 1;
}

void empire_t::init_cities() {
    auto& objects = g_empire_objects;
    g_empire.clear_cities_data();
    //    int route_index = 1;
    for (int i = 0; i < MAX_OBJECTS; i++) {
        if (!objects[i].in_use || objects[i].obj.type != EMPIRE_OBJECT_CITY)
            continue;

        full_empire_object* obj = &objects[i];
        obj->obj.trade_route_id = std::clamp<uint8_t>(obj->obj.trade_route_id, 0, MAX_ROUTES - 1);
        empire_city* city = g_empire.city(obj->city_name_id);
        city->in_use = 1;
        city->type = obj->city_type;
        city->name_id = obj->city_name_id;

        city->route_id = obj->obj.trade_route_id;
        city->is_open = obj->trade_route_open;
        city->cost_to_open = obj->trade_route_cost;
        city->is_sea_trade = is_sea_trade_route(obj->obj.trade_route_id);

        for (e_resource resource = RESOURCES_MIN; resource < RESOURCES_MAX; ++resource) {
            city->sells_resource[resource] = false;
            city->buys_resource[resource] = false;
            if (!is_trade_city(i))
                continue;
            //            if (city->type == EMPIRE_CITY_PHARAOH
            //                || city->type == EMPIRE_CITY_EGYPTIAN
            //                || city->type == EMPIRE_CITY_FOREIGN) {
            //                continue;
            //            }

            city->sells_resource[resource] = g_empire.city_sells_resource(i, resource, true);
            city->buys_resource[resource] = g_empire.city_buys_resource(i, resource, true);

            int amount;
            switch (get_trade_amount_code(i, resource)) {
            case 1:
                amount = 1500;
                break;
            case 2:
                amount = 2500;
                break;
            case 3:
                amount = 4000;
                break;
            default:
                amount = 0;
                break;
            }

            city->get_route().init(resource, amount);
        }
        city->trader_entry_delay = 4;
        city->trader_figure_ids[0] = 0;
        city->trader_figure_ids[1] = 0;
        city->trader_figure_ids[2] = 0;
        city->empire_object_id = i;
    }
}

int empire_t::init_distant_battle_travel_months(int object_type) {
    auto& objects = g_empire_objects;
    int month = 0;
    for (int i = 0; i < MAX_OBJECTS; i++) {
        if (objects[i].in_use && objects[i].obj.type == object_type) {
            month++;
            objects[i].obj.distant_battle_travel_months = month;
        }
    }
    return month;
}

const full_empire_object* empire_t::get_full_object(int object_id) const {
    auto& objects = g_empire_objects;
    return &objects[object_id];
}

const empire_object* empire_t::get_object(int object_id) const {
    auto& objects = g_empire_objects;
    return &objects[object_id].obj;
}

const empire_object* empire_t::get_our_city() const {
    auto& objects = g_empire_objects;
    for (int i = 0; i < MAX_OBJECTS; i++) {
        if (objects[i].in_use) {
            const empire_object* obj = &objects[i].obj;
            if (obj->type == EMPIRE_OBJECT_CITY && objects[i].city_type == EMPIRE_CITY_PHARAOH_TRADING)
                return obj;
        }
    }
    assert(false && "our city should exist");
    return nullptr;
}

const empire_object* empire_t::get_battle_icon(int path_id, int year) {
    auto& objects = g_empire_objects;
    for (int i = 0; i < MAX_OBJECTS; i++) {
        if (objects[i].in_use) {
            empire_object* obj = &objects[i].obj;
            if (obj->type == EMPIRE_OBJECT_BATTLE_ICON && obj->invasion_path_id == path_id
                && obj->invasion_years == year) {
                return obj;
            }
        }
    }
    return 0;
}

int empire_t::get_max_invasion_path() {
    auto& objects = g_empire_objects;
    int max_path = 0;
    for (int i = 0; i < MAX_OBJECTS; i++) {
        if (objects[i].in_use && objects[i].obj.type == EMPIRE_OBJECT_BATTLE_ICON) {
            if (objects[i].obj.invasion_path_id > max_path)
                max_path = objects[i].obj.invasion_path_id;
        }
    }
    return max_path;
}

int empire_t::get_closest_object(vec2i pos) const {
    auto& objects = g_empire_objects;
    int min_dist = 10000;
    int min_obj_id = 0;
    for (int i = 0; i < MAX_OBJECTS && objects[i].in_use; i++) {
        const empire_object* obj = &objects[i].obj;
        vec2i obj_pos;
        if (scenario_empire_is_expanded()) {
            obj_pos = obj->expanded.pos;
        } else {
            obj_pos = obj->pos;
        }

        if (obj_pos.x - 8 > pos.x || obj_pos.x + obj->width + 8 <= pos.x) {
            continue;
        }

        if (obj_pos.y - 8 > pos.y || obj_pos.y + obj->height + 8 <= pos.y) {
            continue;
        }

        int dist = calc_maximum_distance(pos, vec2i(obj_pos.x + obj->width / 2, obj_pos.y + obj->height / 2));
        if (dist < min_dist) {
            min_dist = dist;
            min_obj_id = i + 1;
        }
    }
    return min_obj_id;
}

void empire_t::object_set_expanded(int object_id, e_empire_city new_city_type) {
    auto& objects = g_empire_objects;
    objects[object_id].city_type = new_city_type;
    if (new_city_type == EMPIRE_CITY_PHARAOH)
        objects[object_id].obj.expanded.image_id = image_id_from_group(GROUP_EMPIRE_CITY_PH_PHARAOH);
    else if (new_city_type == EMPIRE_CITY_OURS)
        objects[object_id].obj.expanded.image_id = image_id_from_group(GROUP_EMPIRE_CITY_PH_OURS);
}

bool empire_t::city_buys_resource(int object_id, e_resource resource, bool from_raw_object) {
    auto& objects = g_empire_objects;
    if (object_id == -1)
        return false;

    if (from_raw_object) {
        const full_empire_object* object = &objects[object_id];
        for (int i = 0; i < EMPIRE_OBJ_MAX_BOUGHT_RESOURCES; i++) {
            if (object->city_buys_resource[i] == resource)
                return true;
        }
        return false;
    } 

    int city_id = g_empire.get_city_for_object(object_id);
    const empire_city* city = g_empire.city(city_id);
    return city->buys_resource[resource];
}

bool empire_t::city_sells_resource(int object_id, e_resource resource, bool from_raw_object) {
    auto& objects = g_empire_objects;
    if (object_id == -1) {
        return false;
    }

    if (from_raw_object) {
        const full_empire_object* object = &objects[object_id];
        for (int i = 0; i < EMPIRE_OBJ_MAX_SOLD_RESOURCES; i++) {
            if (object->city_sells_resource[i] == resource)
                return true;
        }
        return false;
    } 
    
    int city_id = g_empire.get_city_for_object(object_id);
    const empire_city* city = g_empire.city(city_id);
    return city->sells_resource[resource];
}

static int get_animation_offset(int image_id, int current_index) {
    if (current_index <= 0)
        current_index = 1;

    const image_t* img = image_get(image_id);
    int animation_speed = img->animation.speed_id;
    if (!game.animation_should_advance(animation_speed))
        return current_index;

    if (img->animation.can_reverse) {
        int is_reverse = 0;
        if (current_index & 0x80)
            is_reverse = 1;

        int current_sprite = current_index & 0x7f;
        if (is_reverse) {
            current_index = current_sprite - 1;
            if (current_index < 1) {
                current_index = 1;
                is_reverse = 0;
            }
        } else {
            current_index = current_sprite + 1;
            if (current_index > img->animation.num_sprites) {
                current_index = img->animation.num_sprites;
                is_reverse = 1;
            }
        }
        if (is_reverse)
            current_index = current_index | 0x80;

    } else {
        // Absolutely normal case
        current_index++;
        if (current_index > img->animation.num_sprites)
            current_index = 1;
    }
    return current_index;
}

int empire_t::update_animation(const empire_object &obj, int image_id) {
    auto& objects = g_empire_objects;
    objects[obj.id].obj.animation_index = get_animation_offset(image_id, obj.animation_index);
    return objects[obj.id].obj.animation_index;
}

std::array<map_route_object, 50> g_empire_route_objects;

const map_route_object& empire_t::get_route_object(int id) const {
    return g_empire_route_objects[id];
}

map_route_object &empire_t::ref_route_object(int id) {
    return g_empire_route_objects[id];
}

io_buffer* iob_empire_map_objects = new io_buffer([](io_buffer* iob, size_t version) {
    logs::info("iob_empire_map_objects");
    auto& objects = g_empire_objects;
    int last_object_was_used = 1;
    for (int i = 0; i < MAX_OBJECTS; i++) {
        full_empire_object* full = &objects[i];
        empire_object* obj = &full->obj;
        obj->id = i;
        //
        iob->bind(BIND_SIGNATURE_UINT8, &obj->type);
        iob->bind(BIND_SIGNATURE_UINT8, &full->in_use);
        iob->bind(BIND_SIGNATURE_UINT8, &obj->animation_index);
        iob->bind____skip(1);
        iob->bind(BIND_SIGNATURE_INT16, &obj->pos.x);
        iob->bind(BIND_SIGNATURE_INT16, &obj->pos.y);
        iob->bind(BIND_SIGNATURE_INT16, &obj->width);
        iob->bind(BIND_SIGNATURE_INT16, &obj->height);
        iob->bind(BIND_SIGNATURE_INT16, &obj->image_id);
        iob->bind(BIND_SIGNATURE_INT16, &obj->expanded.image_id);
        iob->bind____skip(1);
        iob->bind(BIND_SIGNATURE_UINT8, &obj->distant_battle_travel_months);
        iob->bind____skip(1);
        iob->bind(BIND_SIGNATURE_UINT8, &obj->text_align);
        iob->bind(BIND_SIGNATURE_INT16, &obj->expanded.pos.x);
        iob->bind(BIND_SIGNATURE_INT16, &obj->expanded.pos.y);
        iob->bind(BIND_SIGNATURE_UINT8, &full->city_type);
        iob->bind(BIND_SIGNATURE_UINT8, &full->city_name_id);
        iob->bind_u8(obj->trade_route_id);
        iob->bind(BIND_SIGNATURE_UINT8, &full->trade_route_open);
        iob->bind(BIND_SIGNATURE_INT16, &full->trade_route_cost);

        for (int r = 0; r < EMPIRE_OBJ_MAX_SOLD_RESOURCES; r++) {
            iob->bind(BIND_SIGNATURE_UINT8, &full->city_sells_resource[r]);
        }
        iob->bind____skip(8);
        for (int r = 0; r < EMPIRE_OBJ_MAX_BOUGHT_RESOURCES; r++) {
            iob->bind(BIND_SIGNATURE_UINT8, &full->city_buys_resource[r]);
        }

        iob->bind(BIND_SIGNATURE_UINT8, &obj->invasion_path_id);
        iob->bind(BIND_SIGNATURE_UINT8, &obj->invasion_years);

        // TODO: WRITE
        if (FILEIO.get_file_version() < 160) {
            iob->bind____skip(2);
            iob->bind(BIND_SIGNATURE_UINT32, &full->trade40);
            iob->bind(BIND_SIGNATURE_UINT32, &full->trade25);
            iob->bind(BIND_SIGNATURE_UINT32, &full->trade15);
        } else {
            for (int r = 0; r < RESOURCES_MAX; r++) {
                iob->bind(BIND_SIGNATURE_UINT8, &full->trade_demand[r]);
            }
        }

        if (last_object_was_used)
            last_object_was_used = full->in_use;
        else
            full->in_use = last_object_was_used;
    }
});

io_buffer* iob_empire_map_routes = new io_buffer([](io_buffer* iob, size_t version) {
    logs::info("iob_empire_map_routes");
    const int MAX_ROUTE_OBJECTS = 50;
    for (int id = 0; id < MAX_ROUTE_OBJECTS; id++) {
        map_route_object& obj = g_empire_route_objects[id];

        iob->bind(BIND_SIGNATURE_UINT32, &obj.unk_header[0]); // 05 00 00 00
        iob->bind(BIND_SIGNATURE_UINT32, &obj.unk_header[1]); // 00 00 00 00

        for (int i = 0; i < 50; i++) {
            iob->bind(BIND_SIGNATURE_UINT16, &obj.points[i].p.x);
            iob->bind(BIND_SIGNATURE_UINT16, &obj.points[i].p.y);
            iob->bind(BIND_SIGNATURE_UINT16, &obj.points[i].is_in_use);
        }
        iob->bind(BIND_SIGNATURE_UINT32, &obj.length);

        iob->bind(BIND_SIGNATURE_UINT32, &obj.unk_00); // 00 00 00 00
        iob->bind(BIND_SIGNATURE_UINT32, &obj.unk_01); // FF FF FF FF

        iob->bind(BIND_SIGNATURE_UINT8, &obj.route_type); // 1 = land; 2 = sea;
        iob->bind(BIND_SIGNATURE_UINT8, &obj.num_points);
        iob->bind(BIND_SIGNATURE_UINT8, &obj.in_use);

        iob->bind(BIND_SIGNATURE_UINT8, &obj.unk_03);

        obj.path_length = obj.calc_length();
        //        SDL_Log("TRADE DATA: %04i %04i -- %02i %02i %02i", obj->unk_header[0], obj->unk_header[1],
        //        obj->route_type, obj->in_use, obj->unk_03);
    }
});

void full_empire_object::add_sell_resource(e_resource r) {
    // check resource exist in set
    auto it = std::find(std::begin(city_sells_resource), std::end(city_sells_resource), r);
    if (it != std::end(city_sells_resource)) {
        return;
    }

    // find empty place
    it = std::find(std::begin(city_sells_resource), std::end(city_sells_resource), 0);
    assert(it != std::end(city_sells_resource));
    *it = r;
}

int map_route_object::calc_length() {
    if (num_points == 0) {
        return 0;
    }

    float pathlen = 0.f;
    for (int i = 0; i < num_points - 1; i++) {
        const auto route_point = points[0];
        const auto nextup_route_point = points[i + 1];
        vec2i d = nextup_route_point.p - route_point.p;
        pathlen += 0.2f * sqrtf(float(d.x * d.x) + float(d.y * d.y));
    }

    return (int)pathlen;
}
