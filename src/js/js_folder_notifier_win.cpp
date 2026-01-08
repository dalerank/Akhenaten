#include "platform/platform.h"

#if defined(GAME_PLATFORM_WIN)

#include "js_folder_notifier.h"

#include "core/log.h"

#include <Windows.h>

int js_vm_notifier_watch_directory(const char *lpDir) {
    DWORD dwWaitStatus;
    HANDLE dwChangeHandles[2];

    // Watch the directory for file creation and deletion.
    dwChangeHandles[0] = FindFirstChangeNotification(
                             lpDir,                         // directory to watch
                             FALSE,                         // do not watch subtree
                             FILE_NOTIFY_CHANGE_SIZE); // watch file modify

    if (dwChangeHandles[0] == INVALID_HANDLE_VALUE) {
        logs::info("FindFirstChangeNotification function failed er=%x", GetLastError());
        return 0;
    }

    // Watch the subtree for directory creation and deletion.
    dwChangeHandles[1] = FindFirstChangeNotification(
                             lpDir,                         // directory to watch
                             FALSE,                          // watch the subtree
                             FILE_NOTIFY_CHANGE_LAST_WRITE);  // watch file size change

    if (dwChangeHandles[1] == INVALID_HANDLE_VALUE) {
        logs::info("FindFirstChangeNotification function failed er=%x", GetLastError());
        return 0;
    }


    // Make a final validation check on our handles.
    if ((dwChangeHandles[0] == NULL) || (dwChangeHandles[1] == NULL)) {
        logs::info("Unexpected NULL from FindFirstChangeNotification er=%x", GetLastError());
        return 0;
    }

    // Change notification is set. Now wait on both notification
    // handles and refresh accordingly.
    while (1) {
        // Wait for notification.

        logs::info("Waiting for notification...", 0, 0);

        dwWaitStatus = WaitForMultipleObjects(2, dwChangeHandles, FALSE, INFINITE);

        switch (dwWaitStatus) {
            case WAIT_OBJECT_0:

                // A file was created, renamed, or deleted in the directory.
                // Refresh this directory and restart the notification.

                if ( FindNextChangeNotification(dwChangeHandles[0]) == FALSE ) {
                    logs::info("FindNextChangeNotification function failed er=%x", GetLastError());
                    return 0;
                }
                return 2;
                break;

            case WAIT_OBJECT_0 + 1:

                // A directory was created, renamed, or deleted.
                // Refresh the tree and restart the notification.

                if (FindNextChangeNotification(dwChangeHandles[1]) == FALSE ) {
                    logs::info("FindNextChangeNotification function failed er=%x", GetLastError());
                    return 0;
                }
                return 3;
                break;

            case WAIT_TIMEOUT:

                // A timeout occurred, this would happen if some value other
                // than INFINITE is used in the Wait call and no changes occur.
                // In a single-threaded environment you might not want an
                // INFINITE wait.

                logs::info("No changes in the timeout period.");
                break;

            default:
                logs::info("Unhandled dwWaitStatus.");
                return 0;
        }
    }

    return 1;
}

#endif // defined(GAME_PLATFORM_WIN)
