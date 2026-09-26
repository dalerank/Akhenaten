#include "stacktrace.h"

#include "core/log.h"
#include "platform/arguments.h"
#include "platform/platform.h"
#include "platform/screen.h"

#include "SDL.h"

#include <cstdlib>
#include <cstring>

#if defined(GAME_PLATFORM_UNIX) && !defined(GAME_PLATFORM_WIN64) && !defined(GAME_PLATFORM_ANDROID) && !defined(ANDROID_BUILD)

#include <csignal>
#include <execinfo.h>

static bool should_show_crash_dialog() {
    if (!g_args.use_crashdlg() || g_args.is_integral_tests()) {
        return false;
    }
    const char *vid = SDL_getenv("SDL_VIDEODRIVER");
    if (vid && (!std::strcmp(vid, "dummy") || !std::strcmp(vid, "offscreen"))) {
        return false;
    }
    return true;
}

static void display_crash_message() {
    g_platform_screen.show_error_message_box(
      "Ozzy has crashed :(",
      "There was an unrecoverable error, which will now close.\n"
      "The piece of code that caused the crash has been saved to akhenaten-log.txt.\n"
      "If you can, please create an issue by going to:\n"
      "https://github.com/dalerank/akhenaten/issues/new \n"
      "Please attach log.txt and your city save to the issue report.\n"
      "Also, please describe what you were doing when the game crashed.\n"
      "With your help, we can avoid this crash in the future.\n"
      "Copy this message press Ctrl + C.\n"
      "Thanks!\n");
}

static void backtrace_print() {
    void* array[100];
    int size = backtrace(array, 100);

    char** stack = backtrace_symbols(array, size);

    for (int i = 0; i < size; i++) {
        logs::info("%s", stack[i]);
    }
    free(stack);
}

static void crash_handler(int sig) {
    logs::error("Oops, crashed with signal %d :(", sig);
    backtrace_print();
    logs::flush();
    if (should_show_crash_dialog()) {
        display_crash_message();
    }
    _Exit(128 + (sig > 0 ? sig : 1));
}

void crashhandler_install() {
    signal(SIGSEGV, crash_handler);
}

#endif
