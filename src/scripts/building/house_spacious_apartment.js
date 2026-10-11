log_info("akhenaten: loading building_house_spacious_apartment")

[es=(building_house_spacious_apartment, consume_food_weekly)]
function building_house_spacious_apartment_consume_food_weekly(ev) { house_es_consume_food_weekly(ev) }

[es=(building_house_spacious_apartment, consume_goods_weekly)]
function building_house_spacious_apartment_consume_goods_weekly(ev) { house_es_consume_goods_weekly(ev) }
