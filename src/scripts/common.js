function _format() {
    var formatted = arguments[0]
    for (var arg in arguments) {
        if(arg==0)
           continue

        formatted = formatted.replace("{" + (arg-1) + "}", arguments[arg])
    }
    return formatted
};

function _eformat(message, locals) {
    if (typeof message === 'string' && message.indexOf('${') !== -1) {
        try {
            message = message.replace(/\$\{([^}]+)\}/g, function(match, expr) {
                try {
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
                } catch (e) {
                    return '[error: ' + e + ' in ${' + expr + '}]';
                }
            });
        } catch (e) {
            message = '[format error: ' + e + ']';
        }
    }
    return message;
}

function log_info(message, locals) {
    __log_info_native(_eformat(message, locals));
}

function log_warning(message, locals) {
    __log_warning_native(_eformat(message, locals));
}

// vec2i helper functions with chainable methods
function vec2i(x, y) {
    var obj;
    if (y === undefined) {
        // If only one argument, assume it's an object with x and y
        if (typeof x === 'object' && x !== null) {
            obj = {x: x.x || 0, y: x.y || 0};
        } else {
            // If it's a number, return vec2i with both components equal
            obj = {x: x, y: x};
        }
    } else {
        obj = {x: x, y: y};
    }

    // Add chainable methods
    obj.add = function(other) {
        var o = vec2i(other);
        return vec2i(this.x + o.x, this.y + o.y);
    };

    obj.sub = function(other) {
        var o = vec2i(other);
        return vec2i(this.x - o.x, this.y - o.y);
    };

    obj.mul = function(scalar) {
        return vec2i(this.x * scalar, this.y * scalar);
    };

    obj.div = function(scalar) {
        return vec2i(this.x / scalar, this.y / scalar);
    };

    return obj;
}

var trade_city_sell = {}
var trade_city_want_sell = {}
var trade_city_buy = {}
var trade_city_want_buy = {}

// misc
var empire_window = {}
var empire_images_remap = []

function approximate_value(v, arr) {
    var index = Math.max(0, Math.min(Math.floor(v * arr.length), arr.length - 1));
    return arr[index];
}

function calc_percentage(value, total) {
    if (total) {
        var value_times_100 = 100 * value;
        return Math.floor(value_times_100 / total);
    }

    return 0;
}