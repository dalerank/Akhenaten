var _format = function() {
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

var trade_city_sell = {}
var trade_city_want_sell = {}
var trade_city_buy = {}
var trade_city_want_buy = {}

// misc
var empire_window = {}
var empire_images_remap = []