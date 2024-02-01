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
var building_info = []
var mission_sounds = []
var walker_sounds = []
var city_sounds = []
var overlays = []
var images = []
var cart_offsets = []
var sled_offsets = []
var small_statue_images = []
var medium_statue_images = []
var big_statue_images = []
var top_menu_bar = {}
var main_menu_window = {}
var building_booth = {}
var building_bandstand = {}
var building_scribal_school = {}
var building_scribal_school_info = {}
var empire_window = {}
var images_remap = []
var imagepaks = []
var advisor_rating_window = {}
var mission_briefing_window = {}
var mission0 = {}
var mission1 = {}
var mission5 = {}
var mission6 = {}
