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
var walker_images = []
var images = []
