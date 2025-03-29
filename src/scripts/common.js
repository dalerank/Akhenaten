var _format = function() {
    var formatted = arguments[0]
    for (var arg in arguments) {
                if(arg==0)
                    continue
        formatted = formatted.replace("{" + (arg-1) + "}", arguments[arg])
    }
    return formatted
};

var building_sounds = []
var walker_sounds = []
var city_sounds = []
var overlays = []
var images = []
var cart_images = []
var cart_offsets = []
var sled_offsets = []
var localization = []
// buildings
var building_academy = {}
var building_firehouse = {}
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

// ui
var uioptions = {}
var advisor_chief_window = {}
var advisor_ratings_window = {}
var advisor_labors_window = {}
var advisor_trade_window = {}
var advisor_imperial_window = {}
var info_window_figure_enemy = {}
var info_window_figure_animal = {}
var roadblock_info_window = {}
var hold_festival_window = {}
var empty_info_window = {}
var advisors_window = {}
var advisor_military_window = {}
var advisor_population_window = {}
var advisor_health_window = {}
var advisor_education_window = {}
var advisor_entertainment_window = {}
var advisor_financial_window = {}
var display_options_window = {}
var sidebar_window_expanded = {}
var sidebar_window_collapsed = {}
var sidebar_window_extra = {}
var dock_info_window = {}
var dock_orders_window = {}

//figures
var figure_fireman = {}
var figure_hippo = {}
var figure_crocodile = {}
var figure_immigrant = {}
var figure_architector = {}
var figure_market_buyer = {}
var figure_delivery_boy = {}
var figure_cartpusher = {}
var figure_storageyard_cart = {}
var figure_trade_ship = {}
var figure_sled = {}
var figure_sled_puller = {}
var figure_tax_collector = {}
var figure_physician = {}
var figure_herbalist = {}
var figure_emigrant = {}
var figure_juggler = {}
var figure_dancer = {}
var figure_musician = {}
var figure_labor_seeker = {}
var figure_explosion = {}
var figure_caravan_donkey = {}
var figure_trade_caravan = {}
var figure_homeless = {}
var figure_teacher = {}
var figure_docker = {}
var figure_ostrich_hunter = {}
var figure_lumberjack = {}
var figure_soldier_infantry = {}
var figure_soldier_archer = {}
var figure_soldier_charioteer = {}
var figure_flotsam = {}
var figure_scriber = {}
var figure_dentist = {}
var figure_native_trader = {}
var figure_librarian = {}
var figure_constable = {}
var figure_governor = {}
var figure_arrow = {}
var figure_hunter_arrow = {}
var figure_spear = {}
var figure_javelin = {}
var figure_bolt = {}
var figure_senet_player = {}
