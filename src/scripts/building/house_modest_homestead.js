log_info("akhenaten: loading building_house_modest_homestead")

[es=(building_house_modest_homestead, consume_food_weekly)]
function building_house_modest_homestead_consume_food_weekly(ev) { house_es_consume_food_weekly(ev) }

[es=(building_house_modest_homestead, consume_goods_weekly)]
function building_house_modest_homestead_consume_goods_weekly(ev) { house_es_consume_goods_weekly(ev) }
