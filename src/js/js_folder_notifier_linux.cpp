#include "platform/platform.h"

#if defined(__linux__) || defined(__android__)

#include "js_folder_notifier.h"

#include "core/log.h"

#include <sys/inotify.h>
#include <unistd.h>

#define EVENT_SIZE  ( sizeof (struct inotify_event) )
#define BUF_LEN     ( 1024 * ( EVENT_SIZE + 16 ) )

int js_vm_notifier_watch_directory(const char *lpDir)
{
    int length, i = 0;
    int fd;
    int wd;
    char buffer[BUF_LEN];

    fd = inotify_init();

    if ( fd < 0 ) {
        logs::info( "WARNING !!! Cant init inotify for %s", lpDir);
        return 0;
    }

    wd = inotify_add_watch( fd, lpDir, IN_MODIFY );
    length = read( fd, buffer, BUF_LEN );

    if ( length < 0 ) {
        logs::info( "WARNING !!! Cant read inotify event %s", lpDir);
        return 0;
    }

    int result = 1;
    while ( i < length ) {
        struct inotify_event *event = ( struct inotify_event * ) &buffer[ i ];
        if ( event->len ) {
            if ( event->mask & IN_MODIFY ) {
                if ( event->mask & IN_ISDIR ) {
                    logs::info( "WARNING !!! The directory was modified %s", event->name);
                } else {
                    logs::info( "WARNING !!! The file was modified %s", event->name);
                    result = 2;
                    break;
                }
            }
        }
        i += EVENT_SIZE + event->len;
    }

    inotify_rm_watch( fd, wd );
    close( fd );

    return result;
}

#endif // defined(__linux__) || defined(__android__)
