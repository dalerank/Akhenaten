log_info("akhenaten: loading building_house_rough_cottage")

[es=(building_house_rough_cottage, consume_food_weekly)]
function building_house_rough_cottage_consume_food_weekly(ev) { house_es_consume_food_weekly(ev) }

[es=(building_house_rough_cottage, consume_goods_weekly)]
function building_house_rough_cottage_consume_goods_weekly(ev) { house_es_consume_goods_weekly(ev) }
