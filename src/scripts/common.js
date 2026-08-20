function extend(target, props) {
    if (props == null) {
        return target
    }
    var keys = Object.keys(props)
    for (var i = 0; i < keys.length; i++) {
        var k = keys[i]
        var desc = Object.getOwnPropertyDescriptor(props, k)
        if (desc && (desc.get || desc.set)) {
            Object.defineProperty(target, k, desc)
        } else {
            target[k] = desc ? desc.value : props[k]
        }
    }
    return target
}

function _format() {
    var formatted = arguments[0]
    for (var arg in arguments) {
        if(arg==0)
           continue

        formatted = formatted.replace("{" + (arg-1) + "}", arguments[arg])
    }
    return formatted
};

function _eformat_eval_expr(expr, locals) {
    // short notation ${group.id} → __loc(group, id)
    var locShorthand = /^(\d+)\.(\d+)$/.exec(expr);
    if (locShorthand) {
        return __loc(parseInt(locShorthand[1], 10), parseInt(locShorthand[2], 10));
    }

    // ${loc.keyname} → __loc("#keyname")
    var locKey = /^loc\.([A-Za-z_][A-Za-z0-9_]*)$/.exec(expr);
    if (locKey) {
        return __loc("#" + locKey[1]);
    }

    var result;
    if (locals && typeof locals === 'object') {
        with (locals) {
            result = eval(expr);
        }
    } else {
        result = eval(expr);
    }

    if (result === undefined) return 'undefined';
    if (result === null) return 'null';
    if (typeof result === 'object') {
        if (result.toString) return result.toString();
        return '[object]';
    }
    return String(result);
}

function _eformat(message, locals) {
    if (typeof message !== 'string') {
        return message;
    }

    if (message.indexOf('${') !== -1) {
        try {
            message = message.replace(/\$\{([^}]+)\}/g, function(match, expr) {
                try {
                    return _eformat_eval_expr(expr, locals);
                } catch (e) {
                    __log_warning_native('[format error: ' + e + ' in ${' + expr + '}]');
                    return '[error: ' + e + ' in ${' + expr + '}]';
                }
            });
        } catch (e) {
            __log_warning_native('[format error: ' + e + ']');
            message = '[format error: ' + e + ']';
        }
    }

    if (message.indexOf('#') !== -1) {
        message = message.replace(/#([A-Za-z_][A-Za-z0-9_]*)/g, function(match, key) {
            return __loc("#" + key);
        });
    }

    return message;
}

fmt = _eformat

var MONTH_LOC_KEYS = [
    "#month_jan", "#month_feb", "#month_mar", "#month_apr",
    "#month_may", "#month_jun", "#month_jul", "#month_aug",
    "#month_sep", "#month_oct", "#month_nov", "#month_dec"
]

function month_name(month) {
    return __loc(MONTH_LOC_KEYS[month] || MONTH_LOC_KEYS[0])
}

function log_info(message, locals) {
    __log_info_native(_eformat(message, locals));
}

function log_warning(message, locals) {
    __log_warning_native(_eformat(message, locals));
}

// Native Vec2i (frame-zone safe): methods live on C prototype, no per-instance closures.
function vec2i(x, y) {
    if (y === undefined) {
        if (typeof x === 'object' && x !== null) {
            return new Vec2i(x.x || 0, x.y || 0)
        }
        return new Vec2i(x || 0, x || 0)
    }
    return new Vec2i(x, y)
}

function vec2i_add(a, b) { return vec2i(a).add(b) }
function vec2i_sub(a, b) { return vec2i(a).sub(b) }
function vec2i_mul(a, scalar) { return vec2i(a).mul(scalar) }
function vec2i_div(a, scalar) { return vec2i(a).div(scalar) }

var trade_city_sell = {}
var trade_city_want_sell = {}
var trade_city_buy = {}
var trade_city_want_buy = {}

// misc

Math.approximate_value = function(v, arr) {
    var index = Math.max(0, Math.min(Math.floor(v * arr.length), arr.length - 1));
    return arr[index];
}

Math.calc_percentage = function(value, total) {
    if (total) {
        return (100 * value / total) | 0;
    }
    return 0;
}

Math.color_from_green_to_red = function(value) {
    if (value < 0) {
        value = 0;
    } else if (value > 100) {
        value = 100;
    }
    var red = (value * 255 / 100) | 0;
    var green = 255 - red;
    return 0xff000000 | (red << 16) | (green << 8);
}

function normalize_savegame_path_for_load(path) {
    if (!path || path.length === 0)
        return path

    var s = path
    if (s.length > 0 && s.charAt(s.length - 1) === ".")
        s = s.substring(0, s.length - 1)

    var n = s.length
    var lower = s.toLowerCase()
    if (n >= 4 && lower.substring(n - 4) === ".svx")
        return s

    if (n >= 4 && lower.substring(n - 4) === ".sav")
        return s

    return s + ".svx"
}