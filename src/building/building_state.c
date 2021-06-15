#include "building_state.h"

#include "game/resource.h"
#include "core/game_environment.h"

static int is_industry_type(const building *b) {
    return b->output_resource_id || b->type == BUILDING_NATIVE_CROPS
           || b->type == BUILDING_SHIPYARD || b->type == BUILDING_WHARF;
}

static void write_type_data(buffer *buf, const building *b) {
    if (building_is_house(b->type)) {
        for (int i = 0; i < INVENTORY_MAX; i++) {
            buf->write_i16(b->data.house.inventory[i]);
        }
        buf->write_u8(b->data.house.theater);
        buf->write_u8(b->data.house.amphitheater_actor);
        buf->write_u8(b->data.house.amphitheater_gladiator);
        buf->write_u8(b->data.house.colosseum_gladiator);
        buf->write_u8(b->data.house.magistrate);
        buf->write_u8(b->data.house.hippodrome);
        buf->write_u8(b->data.house.school);
        buf->write_u8(b->data.house.library);
        buf->write_u8(b->data.house.academy);
        buf->write_u8(b->data.house.barber);
        buf->write_u8(b->data.house.clinic);
        buf->write_u8(b->data.house.bathhouse);
        buf->write_u8(b->data.house.hospital);
        buf->write_u8(b->data.house.temple_ceres);
        buf->write_u8(b->data.house.temple_neptune);
        buf->write_u8(b->data.house.temple_mercury);
        buf->write_u8(b->data.house.temple_mars);
        buf->write_u8(b->data.house.temple_venus);
        buf->write_u8(b->data.house.no_space_to_expand);
        buf->write_u8(b->data.house.num_foods);
        buf->write_u8(b->data.house.entertainment);
        buf->write_u8(b->data.house.education);
        buf->write_u8(b->data.house.health);
        buf->write_u8(b->data.house.num_gods);
        buf->write_u8(b->data.house.devolve_delay);
        buf->write_u8(b->data.house.evolve_text_id);
    } else if (b->type == BUILDING_MARKET) {
        buf->write_i16(0);
        for (int i = 0; i < INVENTORY_MAX; i++) {
            buf->write_i16(b->data.market.inventory[i]);
        }
        buf->write_i16(b->data.market.pottery_demand);
        buf->write_i16(b->data.market.furniture_demand);
        buf->write_i16(b->data.market.oil_demand);
        buf->write_i16(b->data.market.wine_demand);
        for (int i = 0; i < 3; i++) {
            buf->write_i16(0);
        }
        buf->write_u8(b->data.market.fetch_inventory_id);
        for (int i = 0; i < 9; i++) {
            buf->write_u8(0);
        }
    } else if (b->type == BUILDING_GRANARY) {
        buf->write_i16(0);
        for (int i = 0; i < RESOURCE_MAX[GAME_ENV]; i++) {
            buf->write_i16(b->data.granary.resource_stored[i]);
        }
        buf->write_i32(0);
        buf->write_i32(0);
    } else if (b->type == BUILDING_DOCK) {
        buf->write_i16(b->data.dock.queued_docker_id);
        for (int i = 0; i < 25; i++) {
            buf->write_u8(0);
        }
        buf->write_u8(b->data.dock.num_ships);
        buf->write_u8(0);
        buf->write_u8(0);
        buf->write_i8(b->data.dock.orientation);
        buf->write_u8(0);
        buf->write_u8(0);
        buf->write_u8(0);
        for (int i = 0; i < 3; i++) {
            buf->write_i16(b->data.dock.docker_ids[i]);
        }
        buf->write_i16(b->data.dock.trade_ship_id);
    } else if (is_industry_type(b)) {
        buf->write_i16(b->data.industry.progress);
        for (int i = 0; i < 12; i++) {
            buf->write_u8(0);
        }
        buf->write_u8(b->data.industry.has_fish);
        for (int i = 0; i < 14; i++) {
            buf->write_u8(0);
        }
        buf->write_u8(b->data.industry.blessing_days_left);
        buf->write_u8(b->data.industry.orientation);
        buf->write_u8(b->data.industry.has_raw_materials);
        buf->write_u8(0);
        buf->write_u8(b->data.industry.curse_days_left);
        for (int i = 0; i < 6; i++) {
            buf->write_u8(0);
        }
        buf->write_i16(b->data.industry.fishing_boat_id);
    } else {
        for (int i = 0; i < 26; i++) {
            buf->write_u8(0);
        }
        buf->write_u8(b->data.entertainment.num_shows);
        buf->write_u8(b->data.entertainment.days1);
        buf->write_u8(b->data.entertainment.days2);
        buf->write_u8(b->data.entertainment.days3_or_play);
        for (int i = 0; i < 12; i++) {
            buf->write_u8(0);
        }
    }
}

void building_state_save_to_buffer(buffer *buf, const building *b) {
    buf->write_u8(b->state);
    buf->write_u8(b->faction_id);
    buf->write_u8(b->unknown_value);
    buf->write_u8(b->size);
    buf->write_u8(b->house_is_merged);
    buf->write_u8(b->house_size);
    buf->write_u8(b->x);
    buf->write_u8(b->y);
    buf->write_i16(b->grid_offset);
    buf->write_i16(b->type);
    buf->write_i16(b->subtype.house_level); // which union field we use does not matter
    buf->write_u8(b->road_network_id);
    buf->write_u8(0);
    buf->write_u16(b->creation_sequence_index);
    buf->write_i16(b->houses_covered);
    buf->write_i16(b->percentage_houses_covered);
    buf->write_i16(b->house_population);
    buf->write_i16(b->house_population_room);
    buf->write_i16(b->distance_from_entry);
    buf->write_i16(b->house_highest_population);
    buf->write_i16(b->house_unreachable_ticks);
    buf->write_u8(b->road_access_x);
    buf->write_u8(b->road_access_y);
    buf->write_i16(b->figure_id);
    buf->write_i16(b->figure_id2);
    buf->write_i16(b->immigrant_figure_id);
    buf->write_i16(b->figure_id4);
    buf->write_u8(b->figure_spawn_delay);
    buf->write_u8(0);
    buf->write_u8(b->figure_roam_direction);
    buf->write_u8(b->has_water_access);
    buf->write_u8(0);
    buf->write_u8(0);
    buf->write_i16(b->prev_part_building_id);
    buf->write_i16(b->next_part_building_id);
    buf->write_i16(b->loads_stored);
    buf->write_u8(0);
    buf->write_u8(b->has_well_access);
    buf->write_i16(b->num_workers);
    buf->write_u8(b->labor_category);
    buf->write_u8(b->output_resource_id);
    buf->write_u8(b->has_road_access);
    buf->write_u8(b->house_criminal_active);
    buf->write_i16(b->damage_risk);
    buf->write_i16(b->fire_risk);
    buf->write_i16(b->fire_duration);
    buf->write_u8(b->fire_proof);
    buf->write_u8(b->house_figure_generation_delay);
    buf->write_u8(b->house_tax_coverage);
    buf->write_u8(0);
    buf->write_i16(b->formation_id);
    write_type_data(buf, b);
    buf->write_i32(b->tax_income_or_storage);
    buf->write_u8(b->house_days_without_food);
    buf->write_u8(b->ruin_has_plague);
    buf->write_i8(b->desirability);
    buf->write_u8(b->is_deleted);
    buf->write_u8(b->is_adjacent_to_water);
    buf->write_u8(b->storage_id);
    buf->write_i8(b->sentiment.house_happiness); // which union field we use does not matter
    buf->write_u8(b->show_on_problem_overlay);
}

static void read_type_data(buffer *buf, building *b) {
    if (building_is_house(b->type)) {
        if (GAME_ENV == ENGINE_ENV_C3) {
            for (int i = 0; i < INVENTORY_MAX; i++)
                b->data.house.inventory[i] = buf->read_i16();
        } else if (GAME_ENV == ENGINE_ENV_PHARAOH) {
            for (int i = 0; i < 9; i++)
                b->data.house.foods_ph[i] = buf->read_i16();
            for (int i = 0; i < 4; i++) {
                int food_n = ALLOWED_FOODS(i);
                b->data.house.inventory[i] = b->data.house.foods_ph[food_n];
                b->data.house.inventory[i + 4] = buf->read_i16();
            }
        }
        b->data.house.theater = buf->read_u8();
        b->data.house.amphitheater_actor = buf->read_u8();
        b->data.house.amphitheater_gladiator = buf->read_u8();
        b->data.house.colosseum_gladiator = buf->read_u8();
        b->data.house.magistrate = buf->read_u8();
        b->data.house.hippodrome = buf->read_u8();
        b->data.house.school = buf->read_u8();
        b->data.house.library = buf->read_u8();
        b->data.house.academy = buf->read_u8();
        b->data.house.barber = buf->read_u8();
        b->data.house.clinic = buf->read_u8();
        b->data.house.bathhouse = buf->read_u8();
        b->data.house.hospital = buf->read_u8();
        b->data.house.temple_ceres = buf->read_u8();
        b->data.house.temple_neptune = buf->read_u8();
        b->data.house.temple_mercury = buf->read_u8();
        b->data.house.temple_mars = buf->read_u8();
        b->data.house.temple_venus = buf->read_u8();
        b->data.house.no_space_to_expand = buf->read_u8();
        b->data.house.num_foods = buf->read_u8();
        b->data.house.entertainment = buf->read_u8();
        b->data.house.education = buf->read_u8();
        b->data.house.health = buf->read_u8();
        b->data.house.num_gods = buf->read_u8();
        b->data.house.devolve_delay = buf->read_u8();
        b->data.house.evolve_text_id = buf->read_u8();
    } else if (b->type == BUILDING_MARKET) {
        buf->skip(2);
        for (int i = 0; i < INVENTORY_MAX; i++) {
            b->data.market.inventory[i] = buf->read_i16();
        }
        b->data.market.pottery_demand = buf->read_i16();
        b->data.market.furniture_demand = buf->read_i16();
        b->data.market.oil_demand = buf->read_i16();
        b->data.market.wine_demand = buf->read_i16();
        buf->skip(6);
        b->data.market.fetch_inventory_id = buf->read_u8();
        buf->skip(9);
    } else if (b->type == BUILDING_GRANARY) {
        buf->skip(2);
        if (GAME_ENV == ENGINE_ENV_PHARAOH)
            buf->skip(2);
        for (int i = 0; i < RESOURCE_MAX[GAME_ENV]; i++) {
            b->data.granary.resource_stored[i] = buf->read_i16();
            b->data.granary.resource_stored[i] = (b->data.granary.resource_stored[i] / 100) * 100; // todo
        }
        if (GAME_ENV == ENGINE_ENV_PHARAOH)
            buf->skip(6);
        else
            buf->skip(8);
    } else if (b->type == BUILDING_DOCK) {
        b->data.dock.queued_docker_id = buf->read_i16();
        buf->skip(25);
        b->data.dock.num_ships = buf->read_u8();
        buf->skip(2);
        b->data.dock.orientation = buf->read_i8();
        buf->skip(3);
        for (int i = 0; i < 3; i++)
            b->data.dock.docker_ids[i] = buf->read_i16();
        b->data.dock.trade_ship_id = buf->read_i16();
    } else if (is_industry_type(b)) {
        if (GAME_ENV == ENGINE_ENV_PHARAOH)
            for (int i = 0; i < 2; i++)
                b->data.industry.unk_2[i] = buf->read_u8();
//            buf->skip(2);
        b->data.industry.progress = buf->read_i16();
        for (int i = 0; i < 12; i++)
            b->data.industry.unk_b[i] = buf->read_u8();
//        buf->skip(12);
        b->data.industry.has_fish = buf->read_u8();
        for (int i = 0; i < 14; i++)
            b->data.industry.unk_c[i] = buf->read_u8();
//        buf->skip(14);
        b->data.industry.blessing_days_left = buf->read_u8();
        b->data.industry.orientation = buf->read_u8();
        b->data.industry.has_raw_materials = buf->read_u8();
        b->data.industry.unk_1 = buf->read_u8();
//        buf->skip(1);
        b->data.industry.curse_days_left = buf->read_u8();
        for (int i = 0; i < 6; i++)
            b->data.industry.unk_6[i] = buf->read_u8();
//        buf->skip(6);
        b->data.industry.fishing_boat_id = buf->read_i16();
        if (GAME_ENV == ENGINE_ENV_PHARAOH) {
            for (int i = 0; i < 40; i++)
                b->data.industry.unk_40[i] = buf->read_u8();
            b->data.industry.labor_state = buf->read_u8();
            b->data.industry.labor_days_left = buf->read_u8();
            for (int i = 0; i < 12; i++)
                b->data.industry.unk_12[i] = buf->read_u8();
            b->data.industry.worker_id = buf->read_u8();
        }
    } else {
        buf->skip(26);
        if (GAME_ENV == ENGINE_ENV_C3) {
            b->data.entertainment.num_shows = buf->read_u8();
            b->data.entertainment.days1 = buf->read_u8();
            b->data.entertainment.days2 = buf->read_u8();
            b->data.entertainment.days3_or_play = buf->read_u8();
        } else if (GAME_ENV == ENGINE_ENV_PHARAOH) {
            buf->skip(58);
            b->data.entertainment.num_shows = buf->read_u8();
            b->data.entertainment.days1 = buf->read_u8();
            b->data.entertainment.days2 = buf->read_u8();
            b->data.entertainment.days3_or_play = buf->read_u8();
            buf->skip(20);
            b->data.entertainment.ph_unk00_u32 = buf->read_u32(); //  5 for latched booth??
            b->data.entertainment.ph_unk01_u8 = buf->read_u8();   // 50 ???
            b->data.entertainment.ph_unk02_u8 = buf->read_u8();   //  2 for latched booth??
            buf->skip(12);
            b->data.entertainment.booth_corner_grid_offset = buf->read_i32();
        }
    }
}

#include <assert.h>

void building_state_load_from_buffer(buffer *buf, building *b) {
    int sind = buf->get_offset();
    if (sind ==  640)
        int a = 2134;
    b->state = buf->read_u8();
    b->faction_id = buf->read_u8();
    b->unknown_value = buf->read_u8();
    b->size = buf->read_u8();
    b->house_is_merged = buf->read_u8();
    b->house_size = buf->read_u8();
    if (GAME_ENV == ENGINE_ENV_C3) {
        b->x = buf->read_u8();
        b->y = buf->read_u8();
        b->grid_offset = buf->read_i16();
    } else if (GAME_ENV == ENGINE_ENV_PHARAOH) {
        b->x = buf->read_u16();
        b->y = buf->read_u16();
        buf->skip(2);
        b->grid_offset = buf->read_i32();
    }
    b->type = buf->read_i16();
    b->subtype.house_level = buf->read_i16(); // which union field we use does not matter
    b->road_network_id = buf->read_u8();
    buf->skip(1);
    b->creation_sequence_index = buf->read_u16();
    b->houses_covered = buf->read_i16();
    b->percentage_houses_covered = buf->read_i16();
    b->house_population = buf->read_i16();
    b->house_population_room = buf->read_i16();
    b->distance_from_entry = buf->read_i16();
    b->house_highest_population = buf->read_i16();

    b->house_unreachable_ticks = buf->read_i16();
    if (GAME_ENV == ENGINE_ENV_C3) {
        b->road_access_x = buf->read_u8();
        b->road_access_y = buf->read_u8();
    } else if (GAME_ENV == ENGINE_ENV_PHARAOH) {
        b->road_access_x = buf->read_u16();
        b->road_access_y = buf->read_u16();
    }
    b->figure_id = buf->read_i16();
    b->figure_id2 = buf->read_i16(); // laborseeker
    b->immigrant_figure_id = buf->read_i16();
    b->figure_id4 = buf->read_i16();
    b->figure_spawn_delay = buf->read_u8(); // 1 (workcamp 1)
    buf->skip(1);
    b->figure_roam_direction = buf->read_u8();
    b->has_water_access = buf->read_u8(); // 16 bytes

    buf->skip(2);
    b->prev_part_building_id = buf->read_i16();
    b->next_part_building_id = buf->read_i16();
    if (GAME_ENV == ENGINE_ENV_PHARAOH) {
        int resource_quantity = buf->read_u16(); // 4772 >>>> 112 (resource amount! 2-bytes)

        // ignore partial loads (for now....)
        if (resource_quantity > 350)
            resource_quantity = 400;
        else if (resource_quantity > 250)
            resource_quantity = 300;
        else if (resource_quantity > 150)
            resource_quantity = 200;
        else if (resource_quantity > 50)
            resource_quantity = 100;
        else
            resource_quantity = 0;

        b->loads_stored = resource_quantity / 100;
    } else
        b->loads_stored = buf->read_i16();
    buf->skip(1);
    b->has_well_access = buf->read_u8();

    b->num_workers = buf->read_i16();
    b->labor_category = buf->read_u8(); // FF
    b->output_resource_id = buf->read_u8();
    b->has_road_access = buf->read_u8();
    b->house_criminal_active = buf->read_u8();

    b->damage_risk = buf->read_i16();
    b->fire_risk = buf->read_i16();
    b->fire_duration = buf->read_i16();
    b->fire_proof = buf->read_u8();

    b->house_figure_generation_delay = buf->read_u8(); // 20 (workcamp 1)
    b->house_tax_coverage = buf->read_u8();
    buf->skip(1);
    b->formation_id = buf->read_i16();

    read_type_data(buf, b); // 42 bytes for C3, 102 for PH

    int currind = buf->get_offset() - sind;
    if (GAME_ENV == ENGINE_ENV_PHARAOH)
        buf->skip(184 - currind);

    b->tax_income_or_storage = buf->read_i32();
    b->house_days_without_food = buf->read_u8();
    b->ruin_has_plague = buf->read_u8(); // 6

    b->desirability = buf->read_i8();
    b->is_deleted = buf->read_u8();
    b->is_adjacent_to_water = buf->read_u8();

    b->storage_id = buf->read_u8();
    b->sentiment.house_happiness = buf->read_i8(); // which union field we use does not matter // 90 for house, 50 for wells
    b->show_on_problem_overlay = buf->read_u8(); // 4

    // 68 additional bytes

    if (GAME_ENV == ENGINE_ENV_PHARAOH) {
        buf->skip(68); // temp for debugging
        assert(buf->get_offset() - sind == 264);
    }
}
