#include "js/js_game.h"
#include "js/js.h"
#include "widget/debug_console.h"
#include "core/log.h"
#include "core/cstring.h"
#include "core/hvector.h"

#include <sstream>
#include <string>

#if !defined(GAME_PLATFORM_ANDROID)
static void console_command_wrapper_global(const std::string &funcRefStr, std::istream &is, std::ostream &os) {
    auto J = js_vm_state();
    if (js_vm_have_error() || J == nullptr) {
        os << "Error: JavaScript VM is not available" << std::endl;
        return;
    }

    js_getglobal(J, funcRefStr.c_str());
    if (!J->iscallable(-1)) {
        os << "Error: Console command function not found" << std::endl;
        js_pop(J, 1);
        return;
    }

    js_pushnull(J);

    hvector<cstring, 4> args;
    cstring arg(frameAlloc());
    while (is >> arg) {
        args.emplace_back(std::move(arg));
    }
    js_newarray(J);
    for (size_t i = 0; i < args.size(); ++i) {
        js_pushstring(J, args[i].c_str());
        js_setindex(J, -2, (int)i);
    }

    bool ok = js_vm_trypcall(J, 1);
    if (!ok) {
        const char *error = js_tostring(J, -1);
        os << "Error executing console command: " << error << std::endl;
        logs::error("JS console command error: %s", error);
        js_pop(J, 1);
    }

    js_pop(J, 2);
}

static void console_command_wrapper_registry(const std::string &funcRefStr, std::istream &is, std::ostream &os) {
    auto J = js_vm_state();
    if (js_vm_have_error() || J == nullptr) {
        os << "Error: JavaScript VM is not available" << std::endl;
        return;
    }

    js_getregistry(J, funcRefStr.c_str());
    if (!J->iscallable(-1)) {
        os << "Error: Console command function not found" << std::endl;
        js_pop(J, 1);
        return;
    }

    js_pushnull(J);

    hvector<cstring, 4> args;
    cstring arg(frameAlloc());
    while (is >> arg) {
        args.emplace_back(std::move(arg));
    }
    js_newarray(J);
    for (size_t i = 0; i < args.size(); ++i) {
        js_pushstring(J, args[i].c_str());
        js_setindex(J, -2, (int)i);
    }

    bool ok = js_vm_trypcall(J, 1);
    if (!ok) {
        const char *error = js_tostring(J, -1);
        os << "Error executing console command: " << error << std::endl;
        logs::error("JS console command error: %s", error);
        js_pop(J, 1);
    }

    js_pop(J, 2);
}
#endif

void js_register_console_command_from_function(pcstr functionName, pcstr commandName) {
#if !defined(GAME_PLATFORM_ANDROID)
    auto J = js_vm_state();
    if (js_vm_have_error() || J == nullptr) {
        logs::error("JS: Cannot register console command '%s': VM not available", commandName);
        return;
    }

    js_getglobal(J, functionName);
    if (!J->iscallable(-1)) {
        logs::error("JS: Function '%s' is not callable for console command '%s'", functionName, commandName);
        js_pop(J, 1);
        return;
    }

    std::string funcRefStr(functionName);
    auto wrapper = [funcRefStr](std::istream &is, std::ostream &os) {
        console_command_wrapper_global(funcRefStr, is, os);
    };

    bind_debug_command(commandName, wrapper);
#endif
}

void js_register_console_command(js_State *J) {
#if !defined(GAME_PLATFORM_ANDROID)
    if (js_gettop(J) < 2) {
        logs::error("__register_console_command: expected at least 2 arguments (commandName, callback)");
        J->pushundefined();
        return;
    }

    if (!js_isstring(J, 1)) {
        logs::error("__register_console_command: first argument must be a string (command name)");
        J->pushundefined();
        return;
    }

    if (!J->iscallable(2)) {
        logs::error("__register_console_command: second argument must be a function");
        J->pushundefined();
        return;
    }

    pcstr commandName = js_tostring(J, 1);

    js_copy(J, 2);
    pcstr funcRef = js_ref(J);
    js_setregistry(J, funcRef);
    js_pop(J, 1);

    std::string funcRefStr(funcRef);
    auto wrapper = [funcRefStr](std::istream &is, std::ostream &os) {
        console_command_wrapper_registry(funcRefStr, is, os);
    };

    bind_debug_command(commandName, wrapper);
#endif

    J->pushundefined();
}

static void on_modifier_console_command(js_State *J, pcstr name, pcstr value) {
    js_register_console_command_from_function(name, value);
}
ANK_REGISTER_MODIFIER_ITERATOR(console_command, on_modifier_console_command);
