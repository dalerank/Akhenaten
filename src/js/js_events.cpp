#include "js_events.h"

#include "game/game_events.h"
#include "city/city_maintenance.h"
#include "game/mission.h"
#include "building/building_granary.h"
#include "building/building_storage_yard.h"
#include "city/city_migration.h"
#include "city/city_health.h"
#include "scenario/scenario.h"
#include "city/victory.h"
#include "js/js_game.h"
#include "js/js.h"

ANK_SCRIPT_EVENT(event_population_changed, value)
ANK_SCRIPT_EVENT(event_fire_damage, bid) 
ANK_SCRIPT_EVENT(event_mission_start, id)
ANK_SCRIPT_EVENT(event_collase_damage, bid)
ANK_SCRIPT_EVENT(event_granary_resource_added, bid, r, amount)
ANK_SCRIPT_EVENT(event_migration_update, population)
ANK_SCRIPT_EVENT(event_update_victory_state, population)
ANK_SCRIPT_EVENT(event_advance_day, year, month, mday, abdday)
ANK_SCRIPT_EVENT(event_building_create, bid)
ANK_SCRIPT_EVENT(event_city_disease, absday)
ANK_SCRIPT_EVENT(event_warehouse_filled, bid)
ANK_SCRIPT_EVENT(event_update_mission_goal, mid)