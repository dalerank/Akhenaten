#include "platform/platform.h"

#if defined(GAME_PLATFORM_MACOSX) || defined(__APPLE__)

#include "js_folder_notifier.h"

#include "core/log.h"

#include <sys/event.h>
#include <sys/time.h>
#include <unistd.h>
#include <fcntl.h>

int js_vm_notifier_watch_directory(const char *lpDir)
{
    int kq;
    int fd;
    struct kevent ke;
    struct kevent events[10]; // Buffer for multiple events

    // Create kqueue
    kq = kqueue();
    if (kq < 0) {
        logs::info("WARNING !!! Cant init kqueue for %s", lpDir);
        return 0;
    }

    // Open directory for monitoring
    fd = open(lpDir, O_RDONLY);
    if (fd < 0) {
        logs::info("WARNING !!! Cant open directory %s", lpDir);
        close(kq);
        return 0;
    }

    // Set up event to monitor directory
    // NOTE_WRITE on directory detects changes to files within (on macOS/APFS)
    // NOTE_EXTEND detects file size changes
    // NOTE_DELETE detects file deletions
    // NOTE_RENAME detects file renames
    EV_SET(&ke, fd, EVFILT_VNODE, EV_ADD | EV_ENABLE | EV_ONESHOT, 
           NOTE_WRITE | NOTE_EXTEND | NOTE_DELETE | NOTE_RENAME, 0, NULL);

    // Register the event
    if (kevent(kq, &ke, 1, NULL, 0, NULL) == -1) {
        logs::info("WARNING !!! Cant add kqueue event for %s", lpDir);
        close(fd);
        close(kq);
        return 0;
    }

    logs::info("Waiting for notification...", 0, 0);
    
    // Wait for event (blocking call)
    // NULL timeout means wait indefinitely
    int nev = kevent(kq, NULL, 0, events, 10, NULL);
    
    if (nev < 0) {
        logs::info("WARNING !!! Error waiting for kqueue event in %s", lpDir);
        close(fd);
        close(kq);
        return 0;
    }

    if (nev == 0) {
        // Timeout (shouldn't happen with NULL timeout, but handle it)
        logs::info("No changes in the timeout period.");
        close(fd);
        close(kq);
        return 1;
    }

    // Process events
    int result = 1;
    for (int i = 0; i < nev; i++) {
        if (events[i].flags & EV_ERROR) {
            logs::info("WARNING !!! kqueue event error in %s", lpDir);
            result = 0;
            break;
        }
        
        if (events[i].fflags & (NOTE_WRITE | NOTE_EXTEND)) {
            logs::info("WARNING !!! The file was modified in %s", lpDir);
            result = 2;
            break;
        } else if (events[i].fflags & (NOTE_DELETE | NOTE_RENAME)) {
            logs::info("WARNING !!! The file was deleted/renamed in %s", lpDir);
            result = 3;
            break;
        }
    }

    close(fd);
    close(kq);
    return result;
}

#endif // defined(GAME_PLATFORM_MACOSX) || defined(__APPLE__)
