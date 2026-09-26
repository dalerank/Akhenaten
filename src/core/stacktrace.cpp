#include "stacktrace.h"

#include "core/log.h"
#include "platform/platform.h"

#include <cstdarg>

namespace debug {
    void va_backend(pcstr msg, pcstr FILE, int line, pcstr F, va_list arg) {
        bstring<4096> reason;
        bstring<4096> buffer;
        vsnprintf(buffer, sizeof(buffer) - 1, F, arg);
        buffer[sizeof(buffer) - 1] = 0;

        buffer[4000] = 0; // if longer than can fit in reason
        reason.printf("%s:%d|%s\n%s", FILE, line, msg, buffer.c_str());

        debug_break_if_debugger_present();
        logs::critical("%s", reason.c_str());
    }

    void critical(const char *FILE, int line, const char* F, ...) {
        va_list		args;
        va_start(args, F);
        va_backend("", FILE, line, F, args);
        va_end(args);
    }
}

#if !defined(GAME_PLATFORM_WIN)

void debug_break_if_debugger_present() {
}

#endif

#if !defined(GAME_PLATFORM_WIN64) && (!defined(GAME_PLATFORM_UNIX) || defined(GAME_PLATFORM_ANDROID) || defined(ANDROID_BUILD))

void crashhandler_install() {
    logs::error("Oops, crashed with signal :(");
}

#endif
