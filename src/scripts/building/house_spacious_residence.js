log_info("akhenaten: loading building_house_spacious_residence")

[es=(building_house_spacious_residence, consume_food_weekly)]
function building_house_spacious_residence_consume_food_weekly(ev) { house_es_consume_food_weekly(ev) }

[es=(building_house_spacious_residence, consume_goods_weekly)]
function building_house_spacious_residence_consume_goods_weekly(ev) { house_es_consume_goods_weekly(ev) }
