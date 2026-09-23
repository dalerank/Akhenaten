#include "js/js_game.h"
#include "js/js.h"
#include "widget/debug_console.h"
#include "core/log.h"

#if !defined(GAME_PLATFORM_ANDROID)
enum e_console_callback_source {
    CONSOLE_CALLBACK_GLOBAL,
    CONSOLE_CALLBACK_REGISTRY,
};

static void console_command_wrapper(e_console_callback_source source, const xstring &func_ref, console_args &args, console_output &out) {
    auto J = js_vm_state();
    if (js_vm_have_error() || J == nullptr) {
        out.println("Error: JavaScript VM is not available");
        return;
    }

    const int baseline = js_gettop(J);
    if (source == CONSOLE_CALLBACK_REGISTRY) {
        js_getregistry(J, js_intern(func_ref.c_str()));
    } else {
        js_getglobal(J, func_ref.c_str());
    }

    if (!J->iscallable(-1)) {
        out.println("Error: Console command function not found");
        js_pop(J, 1);
        return;
    }

    js_pushnull(J);

    J->newarray();
    bstring256 arg;
    for (int i = 0; args.next(arg); ++i) {
        J->pushstring(arg.c_str());
        js_setindex(J, -2, i);
    }

    if (!js_vm_trypcall(J, 1)) {
        out.println("Error executing console command");
        logs::error("JS console command error");
    }
    while (js_gettop(J) > baseline) {
        js_pop(J, 1);
    }
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
    js_pop(J, 1); // only needed the callable check; keep MuJS stack balanced across hot-reload

    const xstring func_ref(functionName);
    bind_debug_command(commandName, [func_ref] (console_args &args, console_output &out) {
        console_command_wrapper(CONSOLE_CALLBACK_GLOBAL, func_ref, args, out);
    });
#endif
}

void js_register_console_command(js_State *J) {
#if !defined(GAME_PLATFORM_ANDROID)
    if (js_gettop(J) < 2) {
        logs::error("__register_console_command: expected at least 2 arguments (commandName, callback)");
        J->pushundefined();
        return;
    }

    if (!J->isstring(1)) {
        logs::error("__register_console_command: first argument must be a string (command name)");
        J->pushundefined();
        return;
    }

    if (!J->iscallable(2)) {
        logs::error("__register_console_command: second argument must be a function");
        J->pushundefined();
        return;
    }

    auto commandName = js_tostring(J, 1);

    // js_ref() stores the value in the registry and pops it
    js_copy(J, 2);
    auto funcRef = js_ref(J);

    const xstring func_ref(funcRef->value.c_str());
    bind_debug_command(commandName->value.c_str(), [func_ref] (console_args &args, console_output &out) {
        console_command_wrapper(CONSOLE_CALLBACK_REGISTRY, func_ref, args, out);
    });
#endif

    J->pushundefined();
}

static void on_modifier_console_command(js_State *J, pcstr name, pcstr value) {
    js_register_console_command_from_function(name, value);
}
ANK_REGISTER_MODIFIER_ITERATOR(console_command, on_modifier_console_command);
