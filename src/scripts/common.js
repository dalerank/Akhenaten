var _format = function() {
    var formatted = arguments[0]
    for (var arg in arguments) {
                if(arg==0)
                    continue
        formatted = formatted.replace("{" + (arg-1) + "}", arguments[arg])
    }
    return formatted
};

// buildings
var building_police_station = {}
var building_courthouse = {}
var building_temple_osiris = {}
var building_temple_ra = {}
var building_temple_ptah = {}
var building_temple_seth = {}
var building_temple_bast = {}
var building_temple = {}
var building_bandstand = {}
var building_pavilion = {}
var building_ferry = {}
var building_dentist = {}
var building_mortuary = {}
var building_dancer_school = {}
var building_conservatory = {}
var building_hunting_lodge = {}
var building_brick_gatehouse = {}
var building_library = {}
var building_military_academy = {}
var building_juggler_school = {}
var building_bazaar = {}
var building_architect_post = {}
var building_apothecary = {}
var building_storage_yard = {}
var building_storage_room = {}
var building_work_camp = {}
var building_wood_cutter = {}
var building_water_supply = {}
var building_guild_stonemasons = {}
var building_carpenters_guild = {}
var building_tax_collector = {}
var building_tax_collector_up = {}
var building_shrine_osiris = {}
var building_shrine_ra = {}
var building_shrine_ptah = {}
var building_shrine_seth = {}
var building_shrine_bast = {}
var building_vacant_lot = {}
var building_senet_house = {}
var building_bullfight_school = {}
var building_plaza = {}
var building_brick_tower = {}
var building_mud_tower = {}
var building_marble_quarry = {}
var trade_city_sell = {}
var trade_city_want_sell = {}
var trade_city_buy = {}
var trade_city_want_buy = {}

// houses
var building_house_crude_hut = {}
var building_house_sturdy_hut = {}
var building_house_meager_shanty = {}
var building_house_common_shanty = {}
var building_house_rough_cottage = {}
var building_house_ordinary_cottage = {}
var building_house_modest_homestead = {}
var building_house_spacious_homestead = {}
var building_house_modest_apartment = {}
var building_house_spacious_apartment = {}
var building_house_common_residence = {}
var building_house_spacious_residence = {}
var building_house_elegant_residence = {}
var building_house_fancy_residence = {}
var building_house_common_manor = {}
var building_house_spacious_manor = {}
var building_house_elegant_manor = {}
var building_house_stately_manor = {}
var building_house_modest_estate = {}
var building_house_palatial_estate = {}

// misc
var empire_window = {}
var empire_images_remap = []