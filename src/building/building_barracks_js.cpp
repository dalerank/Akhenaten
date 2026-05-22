#include "building_barracks.h"

#include "figure/formation_batalion.h"
#include "grid/building.h"
#include "js/js_game.h"

int __building_recruiter_get_priority(int bid) {
    building *b = building_get(bid);
    building_recruiter *r = b ? b->dcast_recruiter() : nullptr;
    return r ? r->get_priority() : 0;
}
ANK_FUNCTION_1(__building_recruiter_get_priority)

void __building_recruiter_set_priority(int bid, int v) {
    building *b = building_get(bid);
    building_recruiter *r = b ? b->dcast_recruiter() : nullptr;
    if (r) {
        r->set_priority(v);
    }
}
ANK_FUNCTION_2(__building_recruiter_set_priority)

bool __formation_batalion_recruits_needed() {
    return formation_batalion_recruits_needed();
}
ANK_FUNCTION(__formation_batalion_recruits_needed)

int __building_barracks_has_tower_sentry_request() {
    return building_barracks_has_tower_sentry_request();
}
ANK_FUNCTION(__building_barracks_has_tower_sentry_request)
