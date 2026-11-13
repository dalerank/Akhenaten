#include "js/test/js_test_common.h"

#include "city/city.h"
#include "city/city_food_supply.h"
#include "core/xstring.h"

int __test_food_supply_percentage_of(int floodplain, int meadow, int ranch, int hunting, int fishing, int imports,
  int consumption) {
    food_supply_sources s;
    s.floodplain_produce = floodplain;
    s.meadow_produce = meadow;
    s.ranch_food = ranch;
    s.hunting_food = hunting;
    s.fishing_food = fishing;
    s.import_food = imports;
    s.consumption_percentage = consumption;
    return food_supply_percentage(s, city_food_supply_rules);
}
ANK_FUNCTION_7(__test_food_supply_percentage_of)

int __test_food_supply_farm_produce(int fertility, int laborers, bool blessed) {
    return food_supply_farm_expected_produce(fertility, laborers, blessed, city_food_supply_rules);
}
ANK_FUNCTION_3(__test_food_supply_farm_produce)

bvariant_map __test_food_supply_sources() {
    const food_supply_sources s = g_city.food_supply.gather();
    bvariant_map m;
    m["floodplain_produce"] = bvariant(s.floodplain_produce);
    m["meadow_produce"] = bvariant(s.meadow_produce);
    m["ranch_food"] = bvariant(s.ranch_food);
    m["hunting_food"] = bvariant(s.hunting_food);
    m["fishing_food"] = bvariant(s.fishing_food);
    m["import_food"] = bvariant(s.import_food);
    m["consumption_percentage"] = bvariant(s.consumption_percentage);
    return m;
}
ANK_FUNCTION(__test_food_supply_sources)
