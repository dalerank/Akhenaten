log_info("akhenaten: figure_prototype.js loaded")

/* type, action_state, state, wait_ticks, direction, target_figure_id,
   destination_building_id, home_building_id, movement_ticks_watchdog,
   resource_id, resource_amount_full, draw_mode, phrase_key, phrase_sound:
   native CPTROFF (js_register_figure). */

Figure.property.valid = { get: function() { return this.__valid() } }
Figure.property.name = { }
Figure.property.class_name = { }
Figure.property.city_name = { }
Figure.property.cls = { }
Figure.property.action_tip = { }
Figure.property.resource = { get: function() { return this.resource_id } }
Figure.property.resource_amount = { get: function() { return this.resource_amount_full } }
Figure.property.movement_watchdog = { get: function() { return this.movement_ticks_watchdog } }
Figure.property.is_on_previous_tile = { get: function() { return this.__is_on_previous_tile() } }
Figure.property.destination_id = { get: function() { return this.destination_building_id } }
Figure.property.destination = { get: function() { return city.get_building(this.destination_building_id) } }
Figure.property.home = { get: function() { return city.get_building(this.home_building_id) } }
Figure.property.anim_key = { get: function() { return this.__anim_key() } }
Figure.property.overlay = { get: function() { return this.__overlay() } }
Figure.property.params = { get: function() { return city.get_figure_params_by_type(this.type) } }
Figure.property.trade = { get: function() { return city.get_figure_trade(this.id) } }
Figure.property.transport_ship = { get: function() { return city.get_transport_ship(this.id) } }
Figure.property.warship = { get: function() { return city.get_warship(this.id) } }

FigureTrade.property.valid = { get: function() { return this.__valid() } }
FigureTrade.property.capacity = { get: function() { return this.__capacity() } }
FigureTrade.property.per_good = { get: function() { return this.__per_good() } }
FigureTrade.property.empire_city_id = { get: function() { return this.__empire_city_id() } }
FigureTrade.property.has_traded = { get: function() { return this.__has_traded() } }
FigureTrade.property.can_buy_at_destination = { get: function() { return this.__can_buy_at_destination() } }
FigureTrade.property.can_sell_at_destination = { get: function() { return this.__can_sell_at_destination() } }
FigureTrade.property.city = { get: function() { return empire.get_city(this.empire_city_id) } }

FigureTransportShip.property.valid = { get: function() { return this.__valid() } }
FigureTransportShip.property.has_troops = { get: function() { return this.__has_troops() } }
FigureTransportShip.property.can_embark = { get: function() { return this.__can_embark() } }
FigureTransportShip.property.transported_formation = { get: function() { return this.__transported_formation() } }
FigureTransportShip.property.phase = { get: function() { return this.__phase() } }

FigureWarship.property.valid = { get: function() { return this.__valid() } }
FigureWarship.property.active_order = { get: function() { return this.__active_order() } }
FigureWarship.property.crew_fatigue = { get: function() { return this.__crew_fatigue() } }
FigureWarship.property.damage = { get: function() { return this.__damage() } }
FigureWarship.property.max_damage = { get: function() { return this.__max_damage() } }
