#include "js_events.h"

#include "game/game_events.h"
#include "city/city_maintenance.h"
#include "building/building_granary.h"
#include "city/city_migration.h"
#include "scenario/scenario.h"
#include "js/js_game.h"
#include "js/js.h"

ANK_SCRIPT_EVENT(event_population_changed, value)
ANK_SCRIPT_EVENT(event_fire_damage, bid) 
ANK_SCRIPT_EVENT(event_mission_start, id)
ANK_SCRIPT_EVENT(event_collase_damage, bid)
ANK_SCRIPT_EVENT(event_granary_resource_added, bid, r, amount)
ANK_SCRIPT_EVENT(event_migration_update, population)