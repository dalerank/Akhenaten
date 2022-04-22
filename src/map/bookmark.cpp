#include <game/io/io_buffer.h>
#include "bookmark.h"

#include "city/view.h"
#include "map/grid.h"
#include "map/point.h"

#define MAX_BOOKMARKS 4

static map_point bookmarks[MAX_BOOKMARKS];

void map_bookmarks_clear(void) {
    for (int i = 0; i < MAX_BOOKMARKS; i++) {
        bookmarks[i].x = -1;
        bookmarks[i].y = -1;
    }
}

void map_bookmark_save(int number) {
    if (number >= 0 && number < MAX_BOOKMARKS)
        city_view_get_camera_tile(&bookmarks[number].x, &bookmarks[number].y);

}

bool map_bookmark_go_to(int number) {
    if (number >= 0 && number < MAX_BOOKMARKS) {
        int x = bookmarks[number].x;
        int y = bookmarks[number].y;
        if (x > -1 && map_grid_offset(x, y) > -1) {
            city_view_go_to_tile_corner(x, y, true);
            return true;
        }
    }
    return false;
}

io_buffer *iob_bookmarks = new io_buffer([](io_buffer *iob) {
    for (int i = 0; i < MAX_BOOKMARKS; i++) {
        iob->bind(BIND_SIGNATURE_INT32, &bookmarks[i].x);
        iob->bind(BIND_SIGNATURE_INT32, &bookmarks[i].y);
    }
});