log_info("akhenaten: loading building_house_elegant_manor")

[es=(building_house_elegant_manor, consume_food_weekly)]
function building_house_elegant_manor_consume_food_weekly(ev) { house_es_consume_food_weekly(ev) }

[es=(building_house_elegant_manor, consume_goods_weekly)]
function building_house_elegant_manor_consume_goods_weekly(ev) { house_es_consume_goods_weekly(ev) }
