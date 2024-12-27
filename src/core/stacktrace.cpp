#include "stacktrace.h"

#include "core/log.h"
#include "platform/platform.h"
#include "platform/screen.h"

#include "SDL.h"

static void display_crash_message() {
    platform_screen_show_error_message_box(
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

#if defined(GAME_PLATFORM_UNIX) && !defined(GAME_PLATFORM_WIN64) && !defined(ANDROID_BUILD)

#include <signal.h>

#include <execinfo.h>

static void backtrace_print() {
    void* array[100];
    int size = backtrace(array, 100);

    char** stack = backtrace_symbols(array, size);

    for (int i = 0; i < size; i++) {
        logs::info(stack[i]);
    }
}

static void crash_handler(int sig) {
    logs::error("Oops, crashed with signal %d :(", sig);
    backtrace_print();
    display_crash_message();
    exit(1);
}

void crashhandler_install() {
    signal(SIGSEGV, crash_handler);
}

#elif defined(GAME_PLATFORM_WIN64)

#include "platform/arguments.h"
#include "Windows.h"
#include <Psapi.h>
#include <dbghelp.h>
#include <signal.h>
#include <eh.h>
#include <new.h>
#include "BugTrap.h"

void crashhandler_install() {
    static bool is_bugtrap_inited = false;

    if (is_bugtrap_inited) {
        return;
    }
    is_bugtrap_inited = true;

    BT_SetAppName("Akhenaten");
    BT_SetSupportEMail("dalerankn8@gmail.com");
    BT_SetSupportURL("www.akhenaten.game");
    BT_SetFlags(BTF_DETAILEDMODE | BTF_ATTACHREPORT | BTF_EDITMAIL | BTF_SHOWADVANCEDUI | BTF_SCREENCAPTURE | BTF_INTERCEPTSUEF);
    BT_SetReportFormat(BTRF_TEXT);
    BT_SetSupportServer("localhost", 9999);

    // required for VS 2005 & 2008
    BT_InstallSehFilter();
    BT_SetTerminate(); // set_terminate() must be called from every thread
}

LONG CALLBACK debug_sehgilter(PEXCEPTION_POINTERS pExceptionPointers) {
    if (IsDebuggerPresent()) {
        return 0;
    }

    return BT_SehFilter((PEXCEPTION_POINTERS)pExceptionPointers);
}

#else
void crashhandler_install() {
    logs::error("Oops, crashed with signal :(");
}
#endif


