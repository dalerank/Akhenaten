#ifndef FIGURE_FIGURE_H
#define FIGURE_FIGURE_H

#include "core/buffer.h"
#include "core/direction.h"
#include "figure/action.h"
#include "figure/type.h"
#include "figure/formation.h"
#include "map/point.h"
#include "window/building/common.h"
#include "widget/city.h"

// partial (forward) declaration for recursive class
class building;
#include "building/building.h"

static int MAX_FIGURES[] = {5000, 2000};

class figure {
private:
    unsigned char resource_id;
    unsigned char resource_amount_loads;
    unsigned short resource_amount_full; // full load counter

    short home_building_id;
    short immigrant_home_building_id;
    short destination_building_id;
public:
    int id;
    int sprite_image_id;
    int cart_image_id;
    int anim_base;
    int anim_offset;
    unsigned char anim_frame_duration;
    unsigned char anim_max_frames;
    unsigned char anim_frame;
    unsigned char is_enemy_image;

    unsigned char alternative_location_index;
    unsigned char flotsam_visible;
    short next_figure;
    unsigned char type;
//    unsigned char resource_id;
    bool use_cross_country;
    bool is_friendly;
    unsigned char state;
    unsigned char faction_id; // 1 = city, 0 = enemy
    unsigned char action_state_before_attack;
    signed char direction;
    signed char previous_tile_direction;
    signed char attack_direction;
    unsigned char tile_x;
    unsigned char tile_y;
    unsigned char previous_tile_x;
    unsigned char previous_tile_y;
    unsigned char missile_damage;
    unsigned char damage;
    int grid_offset_figure;
    unsigned char destination_x;
    unsigned char destination_y;
    int destination_grid_offset; // only used for soldiers
    unsigned char source_x;
    unsigned char source_y;
    union {
        unsigned char soldier;
        signed char enemy;
    } formation_position_x;
    union {
        unsigned char soldier;
        signed char enemy;
    } formation_position_y;
    short __unused_24;
    short wait_ticks;
    unsigned short action_state;
    unsigned char progress_on_tile;
    short routing_path_id;
    short routing_path_current_tile;
    short routing_path_length;
    unsigned char in_building_wait_ticks;
    unsigned char outside_road_ticks;
    short max_roam_length;
    short roam_length;
    unsigned char roam_wander_freely;
    unsigned char roam_random_counter;
    signed char roam_turn_direction;
    signed char roam_ticks_until_next_turn;
    short cross_country_x; // position = 15 * x + offset on tile
    short cross_country_y; // position = 15 * y + offset on tile
    short cc_destination_x;
    short cc_destination_y;
    short cc_delta_x;
    short cc_delta_y;
    short cc_delta_xy;
//    unsigned char loads_counter;
//    unsigned short loads_full; // full load counter
    unsigned char cc_direction; // 1 = x, 2 = y
    unsigned char speed_multiplier;
//    short building_id;
//    short immigrant_building_id;
//    short destination_building_id;

    short formation_id;
    unsigned char index_in_formation;
    unsigned char formation_at_rest;
    unsigned char migrant_num_people;
    bool is_ghost;
    unsigned char min_max_seen;
    unsigned char __unused_57;
    short leading_figure_id;
    unsigned char attack_image_offset;
    unsigned char wait_ticks_missile;
    signed char x_offset_cart;
    signed char y_offset_cart;
    unsigned char empire_city_id;
    unsigned char trader_amount_bought;
    short name;
    char terrain_usage;
    unsigned char is_boat; // 1 for boat, 2 for flotsam
    unsigned char height_adjusted_ticks;
    unsigned char current_height;
    unsigned char target_height;
    unsigned char collecting_item_id; // NOT a resource ID for cartpushers! IS a resource ID for warehousemen
    unsigned char trade_ship_failed_dock_attempts;
    unsigned char phrase_sequence_exact;
    signed char phrase_id;
    unsigned char phrase_sequence_city;
    unsigned char trader_id;
    unsigned char wait_ticks_next_target;
    unsigned char __unused_6f;
    short target_figure_id;
    short targeted_by_figure_id;
    unsigned short created_sequence;
    unsigned short target_figure_created_sequence;
    unsigned char num_attackers;
    short attacker_id1;
    short attacker_id2;
    short opponent_id;

    short unk_fest_269;
    short unk_fest_ffff;
    char festival_remaining_dances;

    //

    figure(int _id) {
        id = _id;
    };

    // map search tests
    bool is_dead(); // figure.c
    bool is_enemy();
    bool is_herd();
    bool is_legion();
    bool is_formation(); // formation_legion.c
    bool is_attacking_native(); // combat.c
    bool is_citizen(); // missile.c
    bool is_non_citizen();
    bool is_fighting_friendly(); // routing.c
    bool is_fighting_enemy();
    bool has_figure_color(); // minimap.c

    void kill() {
        if (state != FIGURE_STATE_ALIVE)
            return;
        set_state(FIGURE_STATE_DYING);
        action_state = FIGURE_ACTION_149_CORPSE;
    };
    void poof() {
        set_state(FIGURE_STATE_DEAD);
    };
    bool available() {
        return state == FIGURE_STATE_NONE;
    };
    bool is(figure_type value);
    bool is(figure_state value);
    void set_state(figure_state s) {
        state = s;
    };
    void load(buffer *buf);
    void save(buffer *buf);

    // figure/figure.c
    void figure_delete_UNSAFE();
    building *home();
    building *immigrant_home();
    building *destination();
    const int homeID() const {
        return home_building_id;
    }
    const int immigrant_homeID() const {
        return immigrant_home_building_id;
    }
    const int destinationID() const {
        return destination_building_id;
    }

    void set_home(int _id);
    void set_immigrant_home(int _id);
    void set_destination(int _id);
    void set_home(building *b);
    void set_immigrant_home(building *b);
    void set_destination(building *b);
    bool has_home(int _id = -1);
    bool has_home(building *b);
    bool has_immigrant_home(int _id = -1);
    bool has_immigrant_home(building *b);
    bool has_destination(int _id = -1);
    bool has_destination(building *b);

//    bool is_roamer();

    // map/figure.c
    void map_figure_add();
    void map_figure_update();
    void map_figure_remove();
    void figure_route_add();
    void route_remove();

    // image.c
    void image_set_animation(int group, int offset = 0, int max_frames = 12, int duration = 1);
    void figure_image_update();
    void figure_image_set_cart_offset(int direction);
    int figure_image_corpse_offset();
    int figure_image_missile_launcher_offset();
    int figure_image_direction();

    // city_figure.c
    void draw_debug();
    void adjust_pixel_offset(int *x, int *y);
//    void draw_figure(int x, int y, int highlight);
    void draw_figure_main(int x, int y);
    void draw_figure_cart(int x, int y);
    void city_draw_figure(int x, int y, int highlight, pixel_coordinate *coord = nullptr);
//    void city_draw_selected_figure(int x, int y, pixel_coordinate *coord);
    void draw_figure_with_cart(int x, int y);
//    void draw_hippodrome_horse(int x, int y);
    void draw_fort_standard(int x, int y);
    void draw_map_flag(int x, int y);

    // movement.c
    void advance_tick();
    void set_target_height_bridge();
    int get_permission_for_int();
    void move_to_next_tile();
    void set_next_tile_and_direction();
    void advance_route_tile(int roaming_enabled);
    void init_roaming_from_building(int roam_dir);
    void roam_set_direction();
    void move_ticks(int num_ticks, int roaming_enabled = false);
    void move_ticks_tower_sentry(int num_ticks);
    void roam_ticks(int num_ticks);
    void follow_ticks(int num_ticks);
    void advance_attack();
    void set_cross_country_direction(int x_src, int y_src, int x_dst, int y_dst, int is_missile);
    void set_cross_country_destination(int x_dst, int y_dst);
    int move_ticks_cross_country(int num_ticks);

    void cross_country_update_delta();
    void cross_country_advance_x();
    void cross_country_advance_y();
    void cross_country_advance();

    // actions.c
    void action_perform();
    void advance_action(short NEXT_ACTION);
    bool do_roam(int terrainchoice = TERRAIN_USAGE_ROADS, short NEXT_ACTION = ACTION_2_ROAMERS_RETURNING);
    bool do_goto(int x, int y, int terrainchoice = TERRAIN_USAGE_ROADS, short NEXT_ACTION = 0, short FAIL_ACTION = 0);
    bool do_gotobuilding(building *dest, bool stop_at_road = true, int terrainchoice = TERRAIN_USAGE_ROADS, short NEXT_ACTION = 0, short FAIL_ACTION = 0);
    bool do_returnhome(int terrainchoice = TERRAIN_USAGE_ROADS, short NEXT_ACTION = 0);
    bool do_exitbuilding(bool invisible, short NEXT_ACTION = 0, short FAIL_ACTION = 0);
    bool do_enterbuilding(bool invisible, building *b, short NEXT_ACTION = 0, short FAIL_ACTION = 0);

    void immigrant_action();
    void emigrant_action();
    void homeless_action();
    void cartpusher_action();
//    void labor_seeker_action();
    void explosion_cloud_action();
    void tax_collector_action();
    void engineer_action();
    void warehouseman_action();
    void prefect_action(); //10
    void soldier_action();
    void military_standard_action();
    void entertainer_action();
    void trade_caravan_action();
    void trade_ship_action(); //20
    void trade_caravan_donkey_action();
    void protestor_action();
    void criminal_action();
    void rioter_action();
    void fishing_boat_action();
    void market_trader_action();
    void priest_action();
    void school_child_action();
//    void teacher_action();
//    void librarian_action(); //30
//    void barber_action();
//    void bathhouse_worker_action();
//    void doctor_action();
    void worker_action();
    void editor_flag_action();
    void flotsam_action();
    void docker_action();
    void market_buyer_action();
//    void patrician_action(); //40
    void indigenous_native_action();
    void tower_sentry_action();
    void enemy43_spear_action();
    void enemy44_sword_action();
    void enemy45_sword_action();
    void enemy_camel_action();
    void enemy_elephant_action();
    void enemy_chariot_action();
    void enemy49_fast_sword_action();
    void enemy50_sword_action(); //50
    void enemy51_spear_action();
    void enemy52_mounted_archer_action();
    void enemy53_axe_action();
    void enemy_gladiator_action();
    void enemy_caesar_legionary_action();
    void native_trader_action();
    void arrow_action();
    void javelin_action();
    void bolt_action();
    void ballista_action();
//    void missionary_action();
    void seagulls_action();
    void delivery_boy_action();
    void shipwreck_action();
    void sheep_action();
    void wolf_action(); // C3 only? hyena???
    void ostrich_action();
    void hippo_action();
    void zebra_action();
    void spear_action();
    void hippodrome_horse_action();
    // pharaoh
    void hunter_action();
    void policeman_action();
    void magistrate_action();
    void water_carrier_action();
    void festival_guy_action();

    // migrant.c
    void update_direction_and_image();

    // animal.c
    int is_nearby(int category, int *distance, int max_distance = 10000, bool gang_on = true);
    bool herd_roost(int step, int bias, int max_dist);

    // docker.c
    void get_trade_center_location(int *_x, int *_y);
    int deliver_import_resource(building *dock);
    int fetch_export_resource(building *dock);

    // cartpusher.c
    void set_resource(int resource);
    int get_resource() const;
    void load_resource(int amount, int resource);
    int unload_resource(int amount);
    int get_carrying_amount();
    void determine_deliveryman_destination();
    void determine_deliveryman_destination_food();
    void cart_update_image();
    void determine_granaryman_destination();
//    void remove_resource_from_warehouse();
    void determine_warehouseman_destination();
    ////
    void cartpusher_calculate_destination(bool warehouseman);
    void cartpusher_do_deliver(bool warehouseman, int ACTION_DONE);
    void cartpusher_do_retrieve(int ACTION_DONE);

    // market.c
    int create_delivery_boy(int leader_id);
    int take_food_from_granary(building *market, building *granary);
    int take_resource_from_warehouse(building *warehouse);
    void figure_delivery_boy_action();

    // trader.c
    void trader_buy(int loads);
    void trader_sell(int loads);
    int trader_total_bought();
    int trader_total_sold();
    int get_closest_warehouse(int x, int y, int city_id, int distance_from_entry, map_point *warehouse);
    void go_to_next_warehouse(int x_src, int y_src, int distance_to_entry);
    int trade_ship_lost_queue();
    int trade_ship_done_trading();

    // entertainer.c
    void entertainer_update_shows();
    void entertainer_update_image();

    // maintenance.c
    bool fight_enemy(int category, int max_distance);
    bool fight_fire();
    void extinguish_fire();
    int target_is_alive();

    // crime.c
    int figure_rioter_collapse_building();

    // enemy.c
    void enemy_initial(formation *m);
    void enemy_marching(const formation *m);
    void enemy_fighting(const formation *m);
    void enemy_action(formation *m);
    int get_direction();
    int get_missile_direction(const formation *m);

    // soldier.c
    void javelin_launch_missile();
    void legionary_attack_adjacent_enemy();
    int find_mop_up_target();
    void update_image_javelin(int dir);
    void update_image_mounted(int dir);
    void update_image_legionary(const formation *m, int dir);
    void soldier_update_image(const formation *m);

    // combat.c
    void figure_combat_handle_corpse();
    void resume_activity_after_attack();
    void hit_opponent();
    void figure_combat_handle_attack();
//    int figure_combat_get_target_for_soldier(int x, int y, int max_distance);
//    int figure_combat_get_target_for_wolf(int x, int y, int max_distance);
//    int figure_combat_get_target_for_enemy(int x, int y);
    void figure_combat_attack_figure_at(int grid_offset);

    // missile.c
    void missile_hit_target(int target_id, int legionary_type);
    void missile_fire_at(int target_id, int missile_type);

    // wall.c
    void tower_sentry_pick_target();

    // sound.c
    void play_die_sound();
    void play_hit_sound();

    // phrase.c
    void figure_phrase_determine();
    int figure_phrase_play();

    // service.c
    building *get_entertainment_building();
    int figure_service_provide_coverage();

    // window/building/figures.c
    figure *get_head_of_caravan();
    void draw_trader(building_info_context *c);
    void draw_enemy(building_info_context *c);
    void draw_animal(building_info_context *c);
    void draw_cartpusher(building_info_context *c);
    void draw_market_buyer(building_info_context *c);
    void draw_normal_figure(building_info_context *c);


};

figure *figure_get(int id);

/**
 * Creates a figure
 * @param type Figure type
 * @param x X position
 * @param y Y position
 * @param dir Direction the figure faces
 * @return Always a figure. If figure->id is zero, it is an invalid one.
 */
figure *figure_create(int type, int x, int y, int dir);

//void figure *f->map_figure_remove();
//int figure_is_dead(const figure *f);
//int const figure *f->is_enemy();
//int const figure *f->is_legion();
//int const figure *f->is_herd();

void figure_init_scenario(void);

void figure_kill_all();
void figure_save_state(buffer *list, buffer *seq);
void figure_load_state(buffer *list, buffer *seq);

//

int figure_movement_can_launch_cross_country_missile(int x_src, int y_src, int x_dst, int y_dst);

#endif // FIGURE_FIGURE_H
