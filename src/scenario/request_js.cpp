#include "request.h"

#include "js/js_game.h"
#include "scenario/scenario.h"
#include "scenario/scenario_invasion.h"
#include "core/variant.h"

void ANK_FUNCTION_UNIFIED(__city_create_good_request)(const bvariant_map &args) {
    g_scenario.events.create_good_request(
        args.n("tag_id"), (e_resource)args.n("resource"), args.n("amount"), args.n("months_initial")
    );
}

void ANK_FUNCTION_UNIFIED(__city_event_create_foreign_army_attack_warning)(const bvariant_map &args) {
    g_scenario.events.create_foreign_army_attack_warning(args.n("tag_id"), args.n("sender_faction"));
}

void __city_request_set_image(int tag, xstring image) {
    g_scenario.events.set_request_image(tag, image);
}
ANK_FUNCTION_2(__city_request_set_image)

void __city_request_set_reasons(int tag, int r1, int r2, int r3, int r4) {
    g_scenario.events.set_request_reasons(tag, r1, r2, r3, r4);
}
ANK_FUNCTION_5(__city_request_set_reasons)

void __city_event_create_trade_city_under_siege(int tag, int months_initial) {
    g_scenario.events.create_trade_city_under_siege(tag, months_initial);
}
ANK_FUNCTION_2(__city_event_create_trade_city_under_siege)

void __city_request_set_location_fields(int tag, int l1, int l2, int l3, int l4) {
    g_scenario.events.set_request_location_fields(tag, l1, l2, l3, l4);
}
ANK_FUNCTION_5(__city_request_set_location_fields)

void __city_request_set_sender_faction(int tag, int sender_faction) {
    g_scenario.events.set_request_sender_faction(tag, sender_faction);
}
ANK_FUNCTION_2(__city_request_set_sender_faction)

void __city_request_execute(int tag) {
    g_scenario.events.execute_event(tag);
}
ANK_FUNCTION_1(__city_request_execute)

void __city_request_set_param_1(int tag, pcstr name, int param1) {
    g_scenario.events.set_request_param(tag, name, param1);
}
ANK_FUNCTION_3(__city_request_set_param_1)

void ANK_FUNCTION_UNIFIED(__city_start_foreign_army_invasion)(const bvariant_map &args) {
    invasion_opts_t opts;
    opts.mode = ATTACK_TYPE_ENEMIES;
    opts.enemy_type = (e_enemy_type)args.n("enemy"); // 0 type, 1 kingdome, 2 seth natives
    opts.size = args.n("size");
    opts.invasion_point = { (int)args.n("tilex"), (int)args.n("tiley") };
    opts.invasion_id = args.n("invasion_id");
    opts.want_destroy = args.n("want_destroy_buildings");
    scenario_invasion_start(opts);
}
