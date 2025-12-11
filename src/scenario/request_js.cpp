#include "request.h"

#include "js/js_game.h"
#include "scenario/scenario.h"
#include "core/variant.h"

void ANK_FUNCTION_UNIFIED(__city_create_good_request)(const bvariant_map &args) {
    g_scenario.events.create_good_request(
        args.n("tag_id"), (e_resource)args.n("resource"), args.n("amount"), args.n("months_initial")
    );
}

void __city_request_set_reasons(int tag, int r1, int r2, int r3, int r4) {
    g_scenario.events.set_request_reasons(tag, r1, r2, r3, r4);
}
ANK_FUNCTION_5(__city_request_set_reasons)

void __city_event_create_trade_city_under_siege(int tag, int months_initial) {
    g_scenario.events.create_trade_city_under_siege(tag, months_initial);
}
ANK_FUNCTION_2(__city_event_create_trade_city_under_siege)

void __city_request_execute(int tag) {
    g_scenario.events.execute_event(tag);
}
ANK_FUNCTION_1(__city_request_execute)
