#include "figure/figure.h"

#include "building/building.h"
#include "city/emperor.h"
#include "core/random.h"
#include "empire/city.h"
#include "figure/name.h"
#include "figure/route.h"
#include "figure/trader.h"
#include "map/figure.h"
#include "map/grid.h"

#include <string.h>

static struct {
    int created_sequence;
    figure figures[5000];
} data = {0};

figure *figure_get(int id) {
    return &data.figures[id];
}

figure *figure_create(int type, int x, int y, int dir) {
    int id = 0;
    for (int i = 1; i < MAX_FIGURES[GAME_ENV]; i++) {
        if (!data.figures[i].state) {
            id = i;
            break;
        }
    }
    if (!id)
        return &data.figures[0];

    figure *f = &data.figures[id];
    f->state = FIGURE_STATE_ALIVE;
    f->faction_id = 1;
    f->type = type;
    f->use_cross_country = 0;
    f->is_friendly = 1;
    f->created_sequence = data.created_sequence++;
    f->direction = dir;
    f->source_x = f->destination_x = f->previous_tile_x = f->x = x;
    f->source_y = f->destination_y = f->previous_tile_y = f->y = y;
    f->grid_offset = map_grid_offset(x, y);
    f->cross_country_x = 15 * x;
    f->cross_country_y = 15 * y;
    f->progress_on_tile = 15;
    f->phrase_sequence_city = f->phrase_sequence_exact = random_byte() & 3;
    f->name = figure_name_get(type, 0);
    map_figure_add(f);
    if (type == FIGURE_TRADE_CARAVAN || type == FIGURE_TRADE_SHIP)
        f->trader_id = trader_create();

    return f;
}

void figure_delete(figure *f) {
    building *b = building_get(f->building_id);
    switch (f->type) {
        case FIGURE_LABOR_SEEKER:
        case FIGURE_MARKET_BUYER:
            if (f->building_id)
                b->figure_id2 = 0;

            break;
        case FIGURE_BALLISTA:
            b->figure_id4 = 0;
            break;
        case FIGURE_DOCKER:
            for (int i = 0; i < 3; i++) {
                if (b->data.dock.docker_ids[i] == f->id)
                    b->data.dock.docker_ids[i] = 0;

            }
            break;
        case FIGURE_ENEMY_CAESAR_LEGIONARY:
            city_emperor_mark_soldier_killed();
            break;
        case FIGURE_EXPLOSION:
        case FIGURE_FORT_STANDARD:
        case FIGURE_ARROW:
        case FIGURE_JAVELIN:
        case FIGURE_BOLT:
        case FIGURE_SPEAR:
        case FIGURE_FISH_GULLS:
        case FIGURE_SHEEP:
        case FIGURE_WOLF:
        case FIGURE_ZEBRA:
        case FIGURE_DELIVERY_BOY:
        case FIGURE_PATRICIAN:
            // nothing to do here
            break;
        default:
            if (f->building_id)
                b->figure_id = 0;

            break;
    }
    if (f->empire_city_id)
        empire_city_remove_trader(f->empire_city_id, f->id);

    if (f->immigrant_building_id)
        b->immigrant_figure_id = 0;

    figure_route_remove(f);
    map_figure_delete(f);

    int figure_id = f->id;
    memset(f, 0, sizeof(figure));
    f->id = figure_id;
}

int figure_is_dead(const figure *f) {
    return f->state != FIGURE_STATE_ALIVE || f->action_state == FIGURE_ACTION_149_CORPSE;
}

int figure_is_enemy(const figure *f) {
    return f->type >= FIGURE_ENEMY43_SPEAR && f->type <= FIGURE_ENEMY_CAESAR_LEGIONARY;
}

int figure_is_legion(const figure *f) {
    return f->type >= FIGURE_FORT_JAVELIN && f->type <= FIGURE_FORT_LEGIONARY;
}

int figure_is_herd(const figure *f) {
    return f->type >= FIGURE_SHEEP && f->type <= FIGURE_ZEBRA;
}

void figure_init_scenario(void) {
    for (int i = 0; i < MAX_FIGURES[GAME_ENV]; i++) {
        memset(&data.figures[i], 0, sizeof(figure));
        data.figures[i].id = i;
    }
    data.created_sequence = 0;
}

void figure_kill_all() {
    for (int i = 1; i < MAX_FIGURES[GAME_ENV]; i++) {
        data.figures[i].state = FIGURE_STATE_DEAD;
    }
}

static void figure_save(buffer *buf, const figure *f) {
    buf->write_u8(f->alternative_location_index);
    buf->write_u8(f->image_offset);
    buf->write_u8(f->is_enemy_image);
    buf->write_u8(f->flotsam_visible);
    buf->write_i16(f->image_id);
    buf->write_i16(f->cart_image_id);
    buf->write_i16(f->next_figure_id_on_same_tile);
    buf->write_u8(f->type);
    buf->write_u8(f->resource_id);
    buf->write_u8(f->use_cross_country);
    buf->write_u8(f->is_friendly);
    buf->write_u8(f->state);
    buf->write_u8(f->faction_id);
    buf->write_u8(f->action_state_before_attack);
    buf->write_i8(f->direction);
    buf->write_i8(f->previous_tile_direction);
    buf->write_i8(f->attack_direction);
    buf->write_u8(f->x);
    buf->write_u8(f->y);
    buf->write_u8(f->previous_tile_x);
    buf->write_u8(f->previous_tile_y);
    buf->write_u8(f->missile_damage);
    buf->write_u8(f->damage);
    buf->write_i16(f->grid_offset);
    buf->write_u8(f->destination_x);
    buf->write_u8(f->destination_y);
    buf->write_i16(f->destination_grid_offset);
    buf->write_u8(f->source_x);
    buf->write_u8(f->source_y);
    buf->write_u8(f->formation_position_x.soldier);
    buf->write_u8(f->formation_position_y.soldier);
    buf->write_i16(f->__unused_24);
    buf->write_i16(f->wait_ticks);
    buf->write_u8(f->action_state);
    buf->write_u8(f->progress_on_tile);
    buf->write_i16(f->routing_path_id);
    buf->write_i16(f->routing_path_current_tile);
    buf->write_i16(f->routing_path_length);
    buf->write_u8(f->in_building_wait_ticks);
    buf->write_u8(f->is_on_road);
    buf->write_i16(f->max_roam_length);
    buf->write_i16(f->roam_length);
    buf->write_u8(f->roam_choose_destination);
    buf->write_u8(f->roam_random_counter);
    buf->write_i8(f->roam_turn_direction);
    buf->write_i8(f->roam_ticks_until_next_turn);
    buf->write_i16(f->cross_country_x);
    buf->write_i16(f->cross_country_y);
    buf->write_i16(f->cc_destination_x);
    buf->write_i16(f->cc_destination_y);
    buf->write_i16(f->cc_delta_x);
    buf->write_i16(f->cc_delta_y);
    buf->write_i16(f->cc_delta_xy);
    buf->write_u8(f->cc_direction);
    buf->write_u8(f->speed_multiplier);
    buf->write_i16(f->building_id);
    buf->write_i16(f->immigrant_building_id);
    buf->write_i16(f->destination_building_id);
    buf->write_i16(f->formation_id);
    buf->write_u8(f->index_in_formation);
    buf->write_u8(f->formation_at_rest);
    buf->write_u8(f->migrant_num_people);
    buf->write_u8(f->is_ghost);
    buf->write_u8(f->min_max_seen);
    buf->write_u8(f->__unused_57);
    buf->write_i16(f->leading_figure_id);
    buf->write_u8(f->attack_image_offset);
    buf->write_u8(f->wait_ticks_missile);
    buf->write_i8(f->x_offset_cart);
    buf->write_i8(f->y_offset_cart);
    buf->write_u8(f->empire_city_id);
    buf->write_u8(f->trader_amount_bought);
    buf->write_i16(f->name);
    buf->write_u8(f->terrain_usage);
    buf->write_u8(f->loads_sold_or_carrying);
    buf->write_u8(f->is_boat);
    buf->write_u8(f->height_adjusted_ticks);
    buf->write_u8(f->current_height);
    buf->write_u8(f->target_height);
    buf->write_u8(f->collecting_item_id);
    buf->write_u8(f->trade_ship_failed_dock_attempts);
    buf->write_u8(f->phrase_sequence_exact);
    buf->write_i8(f->phrase_id);
    buf->write_u8(f->phrase_sequence_city);
    buf->write_u8(f->trader_id);
    buf->write_u8(f->wait_ticks_next_target);
    buf->write_u8(f->__unused_6f);
    buf->write_i16(f->target_figure_id);
    buf->write_i16(f->targeted_by_figure_id);
    buf->write_u16(f->created_sequence);
    buf->write_u16(f->target_figure_created_sequence);
    buf->write_u8(f->figures_on_same_tile_index);
    buf->write_u8(f->num_attackers);
    buf->write_i16(f->attacker_id1);
    buf->write_i16(f->attacker_id2);
    buf->write_i16(f->opponent_id);
}

static void figure_load(buffer *buf, figure *f) {
    f->alternative_location_index = buf->read_u8();
    f->image_offset = buf->read_u8();
    f->is_enemy_image = buf->read_u8();
    f->flotsam_visible = buf->read_u8();
    f->image_id = buf->read_i16();
    f->cart_image_id = buf->read_i16();
    f->next_figure_id_on_same_tile = buf->read_i16();
    f->type = buf->read_u8();
    f->resource_id = buf->read_u8();
    f->use_cross_country = buf->read_u8();
    f->is_friendly = buf->read_u8();
    f->state = buf->read_u8();
    f->faction_id = buf->read_u8();
    f->action_state_before_attack = buf->read_u8();
    f->direction = buf->read_i8();
    f->previous_tile_direction = buf->read_i8();
    f->attack_direction = buf->read_i8();
    f->x = buf->read_u8();
    f->y = buf->read_u8();
    f->previous_tile_x = buf->read_u8();
    f->previous_tile_y = buf->read_u8();
    f->missile_damage = buf->read_u8();
    f->damage = buf->read_u8();
    f->grid_offset = buf->read_i16();
    f->destination_x = buf->read_u8();
    f->destination_y = buf->read_u8();
    f->destination_grid_offset = buf->read_i16();
    f->source_x = buf->read_u8();
    f->source_y = buf->read_u8();
    f->formation_position_x.soldier = buf->read_u8();
    f->formation_position_y.soldier = buf->read_u8();
    f->__unused_24 = buf->read_i16();
    f->wait_ticks = buf->read_i16();
    f->action_state = buf->read_u8();
    f->progress_on_tile = buf->read_u8();
    f->routing_path_id = buf->read_i16();
    f->routing_path_current_tile = buf->read_i16();
    f->routing_path_length = buf->read_i16();
    f->in_building_wait_ticks = buf->read_u8();
    f->is_on_road = buf->read_u8();
    f->max_roam_length = buf->read_i16();
    f->roam_length = buf->read_i16();
    f->roam_choose_destination = buf->read_u8();
    f->roam_random_counter = buf->read_u8();
    f->roam_turn_direction = buf->read_i8();
    f->roam_ticks_until_next_turn = buf->read_i8();
    f->cross_country_x = buf->read_i16();
    f->cross_country_y = buf->read_i16();
    f->cc_destination_x = buf->read_i16();
    f->cc_destination_y = buf->read_i16();
    f->cc_delta_x = buf->read_i16();
    f->cc_delta_y = buf->read_i16();
    f->cc_delta_xy = buf->read_i16();
    f->cc_direction = buf->read_u8();
    f->speed_multiplier = buf->read_u8();
    f->building_id = buf->read_i16();
    f->immigrant_building_id = buf->read_i16();
    f->destination_building_id = buf->read_i16();
    f->formation_id = buf->read_i16();
    f->index_in_formation = buf->read_u8();
    f->formation_at_rest = buf->read_u8();
    f->migrant_num_people = buf->read_u8();
    f->is_ghost = buf->read_u8();
    f->min_max_seen = buf->read_u8();
    f->__unused_57 = buf->read_u8();
    f->leading_figure_id = buf->read_i16();
    f->attack_image_offset = buf->read_u8();
    f->wait_ticks_missile = buf->read_u8();
    f->x_offset_cart = buf->read_i8();
    f->y_offset_cart = buf->read_i8();
    f->empire_city_id = buf->read_u8();
    f->trader_amount_bought = buf->read_u8();
    f->name = buf->read_i16();
    f->terrain_usage = buf->read_u8();
    f->loads_sold_or_carrying = buf->read_u8();
    f->is_boat = buf->read_u8();
    f->height_adjusted_ticks = buf->read_u8();
    f->current_height = buf->read_u8();
    f->target_height = buf->read_u8();
    f->collecting_item_id = buf->read_u8();
    f->trade_ship_failed_dock_attempts = buf->read_u8();
    f->phrase_sequence_exact = buf->read_u8();
    f->phrase_id = buf->read_i8();
    f->phrase_sequence_city = buf->read_u8();
    f->trader_id = buf->read_u8();
    f->wait_ticks_next_target = buf->read_u8();
    f->__unused_6f = buf->read_u8();
    f->target_figure_id = buf->read_i16();
    f->targeted_by_figure_id = buf->read_i16();
    f->created_sequence = buf->read_u16();
    f->target_figure_created_sequence = buf->read_u16();
    f->figures_on_same_tile_index = buf->read_u8();
    f->num_attackers = buf->read_u8();
    f->attacker_id1 = buf->read_i16();
    f->attacker_id2 = buf->read_i16();
    f->opponent_id = buf->read_i16();
    if (GAME_ENV == ENGINE_ENV_PHARAOH)
        buf->skip(260);
}

void figure_save_state(buffer *list, buffer *seq) {
    seq->write_i32(data.created_sequence);

    for (int i = 0; i < MAX_FIGURES[GAME_ENV]; i++) {
        figure_save(list, &data.figures[i]);
    }
}

void figure_load_state(buffer *list, buffer *seq) {
    data.created_sequence = seq->read_i32();

    for (int i = 0; i < MAX_FIGURES[GAME_ENV]; i++) {
        figure_load(list, &data.figures[i]);
        data.figures[i].id = i;
    }
}
